#!/bin/sh

[ -n "$INCLUDE_ONLY" ] || {
    . /lib/functions.sh
    . ../netifd-proto.sh
    init_proto "$@"
}

proto_svpn_setup() {
    local cfg="$1"
    local device="svpn-$cfg"
    local confdir="/var/etc/$device"
    local conffile="${confdir}/shadowvpn.conf"
    local upscript="${confdir}/up.sh"
    local downscript="${confdir}/down.sh"
    local upd="/etc/shadowvpn/up.d"
    local downd="/etc/shadowvpn/down.d"
    local server port password ipaddr netmask gateway mtu concurrency defaultroute
    json_get_vars server port password ipaddr netmask gateway mtu concurrency defaultroute

    [ -n "$server" ] && {
            for ip in $(resolveip -t 5 "$server"); do
                    ( proto_add_host_dependency "$cfg" "$ip" )
                    serv_addr=1
            done
    }
    [ -n "$serv_addr" ] || {
            echo "Could not resolve server address"
            sleep 5
            proto_setup_failed "$cfg"
            exit 1
    }

    if [ ! -c "/dev/net/tun" ]; then
        mkdir -p /dev/net
        mknod /dev/net/tun c 10 200
        chmod 0666 /dev/net/tun
    fi

    rm -rf "$confdir"
    mkdir -p "$confdir"

    cat <<-EOF >$conffile
server=$serv_addr
port=$port
password=$password
mode=client
concurrency=${concurrency:=1}
mtu=${mtu:=1440}
intf=$device
up=$upscript
down=$downscript
pidfile=$confdir/shadowvpn.pid
EOF
    chmod 600 "$conffile"

    cat <<-EOF >$upscript
#!/bin/sh
. /lib/netifd/netifd-proto.sh
ifconfig $device $ipaddr netmask ${netmask:=255.255.255.0}
ifconfig $device mtu \$mtu
proto_init_update $device 1 1
proto_set_keep 1
proto_add_ipv4_address $ipaddr ${netmask:=255.255.255.0}
[ -n "$gateway" -a "$defaultroute" = 1 ] && \\
    proto_add_ipv4_route 0.0.0.0 0 $gateway
proto_send_update $cfg
[ -d "$upd" ] && {
    for script in $upd/*
    do
        [ -x "\$script" ] && "\$script" $device $ipaddr $netmask $gateway $cfg
    done
}
EOF

    cat <<-EOF >$downscript
#!/bin/sh
[ -d "$downd" ] && {
    for script in $downd/*
    do
        [ -x "\$script" ] && "\$script" $device $ipaddr $netmask $gateway $cfg
    done
}
EOF

    chmod 700 "$upscript" "$downscript"

    proto_run_command "$cfg" /usr/bin/shadowvpn \
                      -c "$conffile"
}

proto_svpn_teardown() {
    local cfg="$1"
    local device="svpn-$cfg"
    local confdir="/var/etc/$device"

    proto_init_update "$device" 0
    kill `cat $confdir/shadowvpn.pid` >/dev/null 2>&1
    proto_kill_command "$1"
    proto_send_update "$cfg"

    rm -rf "$confdir"
}

proto_svpn_init_config() {
    no_device=1
    available=1

    proto_config_add_string "server"
    proto_config_add_int "port"
    proto_config_add_string "password"
    proto_config_add_string "ipaddr"
    proto_config_add_string "netmask"
    proto_config_add_string "gateway"
    proto_config_add_int "mtu"
    proto_config_add_int "concurrency"
    proto_config_add_boolean "defaultroute"
}

[ -n "$INCLUDE_ONLY" ] || {
    add_protocol svpn
}

#!/bin/sh
. /lib/functions.sh
. ../netifd-proto.sh
init_proto "$@"

proto_openvpn_init_config() {
	proto_config_add_string "server"
	proto_config_add_int "port"
	proto_config_add_string "username"
	proto_config_add_string "password"
	proto_config_add_string "cipher"
	proto_config_add_string "dev_type"
	proto_config_add_int "verbosity"
	no_device=1
	available=1
}

proto_openvpn_setup() {
	local config="$1"
	local script="/lib/netifd/openvpn-script"
	logger -t "openvpn($config)" "initializing..."

	json_get_vars server port username password cipher dev_type verbosity
	grep -q tun /proc/modules || insmod tun

	serv_addr=
	for ip in $(resolveip -t 10 "$server"); do
		( proto_add_host_dependency "$config" "$ip" )
		serv_addr=1
	done
	[ -n "$serv_addr" ] || {
		logger -t openconnect "Could not resolve server address: '$server'"
		sleep 20
		proto_setup_failed "$config"
		exit 1
	}

	port=${port:-1194}
	dev_type=${dev_type:-tun}
	verbosity=${verbosity:-3}

	cmdline="--syslog openvpn($config) --dev vpn-$config --dev-type $dev_type --route-noexec"
	cmdline="$cmdline --verb $verbosity --client --nobind --remote $server $port"
	cmdline="$cmdline --script-security 2 --up-delay --up $script --down-pre --down $script"

	[ -f /etc/openvpn/$config.pem ] && append cmdline "--cert /etc/openvpn/$config.pem"
	[ -f /etc/openvpn/$config.key ] && append cmdline "--key /etc/openvpn/$config.key"
	[ -f /etc/openvpn/$config-ca.pem ] && append cmdline "--ca /etc/openvpn/$config-ca.pem"
	[ -f /etc/openvpn/$config-ta.key ] && append cmdline "--tls-auth /etc/openvpn/$config-ta.key 1"

	[ -n "$cipher" ] && append cmdline "--cipher $cipher"
	[ -n "$username" ] && [ -n "$password" ] && {
		umask 077
		pwfile="/var/run/openvpn-$config.passwd"
		echo "$username" > "$pwfile"
		echo "$password" >> "$pwfile"
		append cmdline "--auth-user-pass $pwfile"
	}

	append cmdline "--setenv INTERFACE $config"

	# Miscellaneous config options
	[ -f /etc/openvpn/$config.conf ] && append cmdline "--config /etc/openvpn/$config.conf"

	logger -t "openvpn($config)" "executing 'openvpn $cmdline'"

	proto_run_command "$config" /usr/sbin/openvpn $cmdline
}

proto_openvpn_teardown() {
	local config="$1"
	local pwfile="/var/run/openvpn-$config.passwd"

	rm -f $pwfile
	logger -t "openvpn($config)" "bringing down openvpn"
	proto_kill_command "$config"
}

add_protocol openvpn

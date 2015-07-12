local map, section, net = ...

server = section:taboption("general", Value, "server", translate("Server"))
server.datatype = "host"
server.rmempty = false

port = section:taboption("general", Value, "port", translate("Port"))
port.datatype = "port"
port.rmempty = false

password = section:taboption("general", Value, "password", translate("Password"))
password.password = true
password.rmempty = false

ipaddr = section:taboption("general", Value, "ipaddr", translate("IPv4 address"))
ipaddr.datatype = "ip4addr"
ipaddr.rmempty = false

netmask = section:taboption("general", Value, "netmask", translate("IPv4 netmask"))
netmask.datatype = "ip4addr"
netmask:value("255.255.255.0")
netmask:value("255.255.0.0")
netmask:value("255.0.0.0")

gateway = section:taboption("general", Value, "gateway", translate("IPv4 gateway"))
gateway.datatype = "ip4addr"

section:taboption("advanced", Flag, "defaultroute",
        translate("Use default gateway"),
        translate("If unchecked, no default route is configured"))

mtu = section:taboption("advanced", Value, "mtu", translate("Override MTU"))
mtu.placeholder = "1440"
mtu.datatype = "max(9200)"

concurrency = section:taboption("advanced", Value, "concurrency", translate("Concurrency"))
concurrency.placeholder = "1"
concurrency.datatype = "max(100)"

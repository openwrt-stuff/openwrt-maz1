
local wa = require "luci.tools.webadmin"
local fs = require "nixio.fs"

m = Map("qos_gargoyle", translate("Qos_Switch"),
	translate("Qos_Switch is designed for switching  on/off Qos_Gargoyle."))

s = m:section(NamedSection, "config", "qos_gargoyle", "")

e = s:option(Flag, "enabled", translate("Enable"))
e.rmempty = false
e.default = e.enabled

function e.write(self, section, value)
	if value == "0" then
		os.execute("/etc/init.d/qos_gargoyle stop")
		os.execute("/etc/init.d/qos_gargoyle disable")
	else
		os.execute("/etc/init.d/qos_gargoyle restart")
		os.execute("/etc/init.d/qos_gargoyle enable")
	end
	Flag.write(self, section, value)
end

return m

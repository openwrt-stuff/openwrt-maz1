local netmod = luci.model.network
local interface = luci.model.network.interface
local proto = netmod:register_protocol("svpn")

function proto.get_i18n(self)
	return luci.i18n.translate("ShadowVPN")
end

function proto.ifname(self)
	return "svpn-" .. self.sid
end

function proto.opkg_package(self)
	return "shadowvpn"
end

function proto.is_installed(self)
	return nixio.fs.access("/lib/netifd/proto/shadowvpn.sh")
end

function proto.is_floating(self)
	return true
end

function proto.is_virtual(self)
	return true
end

function proto.get_interfaces(self)
	return nil
end

function proto.contains_interface(self, ifc)
	 return (netmod:ifnameof(ifc) == self:ifname())
end

netmod:register_pattern_virtual("^svpn-%w")

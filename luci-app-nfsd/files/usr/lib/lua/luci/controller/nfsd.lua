
module("luci.controller.nfsd", package.seeall)

function index()
	
	if not nixio.fs.access("/etc/config/nfsd") then
		return
	end

	local page
	page = entry({"admin", "NAS", "nfsd"}, cbi("nfsd"), _("nfsd"), 49)
	page.i18n = "nfsd"
	page.dependent = true
end

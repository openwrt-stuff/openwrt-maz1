#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/delay.h>
#include "config.h"
#include "ufsdapi.h"

static void fool(const char * name)
{
	printk("fatal error: fool function %s called\n", name);
	mdelay(1000);
	BUG();
	*(int*)0=0;
}

#define MAKE_FOOL(x) void x(void){fool(#x);}

//MAKE_FOOL(__blockdev_direct_IO);
MAKE_FOOL(block_prepare_write);
MAKE_FOOL(block_sync_page);
MAKE_FOOL(create_proc_entry);
MAKE_FOOL(d_alloc_anon);
MAKE_FOOL(d_alloc_root);
MAKE_FOOL(file_fsync);
MAKE_FOOL(generic_commit_write);
MAKE_FOOL(generic_file_sendfile);
MAKE_FOOL(get_sb_bdev);
MAKE_FOOL(posix_acl_chmod_masq);
MAKE_FOOL(posix_acl_clone);
MAKE_FOOL(posix_acl_create_masq);
MAKE_FOOL(posix_acl_equiv_mode);
MAKE_FOOL(posix_acl_from_xattr);
MAKE_FOOL(posix_acl_permission);
MAKE_FOOL(posix_acl_to_xattr);
MAKE_FOOL(posix_acl_valid);
MAKE_FOOL(_spin_lock);
MAKE_FOOL(vmtruncate);
MAKE_FOOL(xtime);

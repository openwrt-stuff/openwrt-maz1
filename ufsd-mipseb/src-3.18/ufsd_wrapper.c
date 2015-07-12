#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>


#include <linux/fs.h>
#include <linux/buffer_head.h>
#include <linux/pagemap.h>
#include <linux/uio.h>

MODULE_LICENSE("GPL");


EXPORT_SYMBOL(__getblk);
EXPORT_SYMBOL(__bread);
EXPORT_SYMBOL(find_or_create_page);

EXPORT_SYMBOL(__blockdev_direct_IO);

ssize_t
generic_file_splice_write(struct pipe_inode_info *pipe, struct file *out,
                           loff_t *ppos, size_t len, unsigned int flags)
{
return iter_file_splice_write(pipe, out, ppos, len, flags);
}
EXPORT_SYMBOL(generic_file_splice_write);


ssize_t generic_file_aio_read(struct kiocb *iocb, const struct iovec *iov, unsigned long nr_segs, loff_t pos)
 {
	struct iov_iter iter;
        iov_iter_init(&iter, READ, iov, nr_segs, iov_length(iov, nr_segs));
	return generic_file_read_iter( iocb, &iter );
 }
EXPORT_SYMBOL(generic_file_aio_read);

ssize_t generic_file_aio_write(struct kiocb *iocb, const struct iovec *iov,
                 unsigned long nr_segs, loff_t pos)
{
	struct iov_iter iter;
        iov_iter_init(&iter, WRITE, iov, nr_segs, iov_length(iov, nr_segs));
	return generic_file_write_iter( iocb, &iter );
	
}
EXPORT_SYMBOL(generic_file_aio_write);

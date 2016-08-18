#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/utsname.h>
#include <linux/module.h>
#include <asm/uaccess.h>

#define SIZE 64

static int open_proc(struct inode *, struct file *);
static ssize_t read_proc(struct file *, char __user *, size_t, loff_t *);
static ssize_t write_proc(struct file *, const char __user *, size_t, loff_t *);
static int release_proc(struct inode *, struct  file *);

static struct proc_dir_entry *proc_file_entry;
static const struct file_operations proc_file_fops = { /* операции над нашим файлом */
	.open  		= open_proc,
	.read           = read_proc,
	.write		= write_proc,
	.release        = release_proc
};
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#include <linux/fs.h>
#include <linux/file.h>
#include <linux/err.h>
#include <linux/delay.h>

MODULE_LICENSE("Unlicense");
MODULE_AUTHOR("Jaime");
MODULE_DESCRIPTION("User can press a button to respond in kernel");
MODULE_VERSION("0.9");

static int __init userget_init(void) {
  struct file * filp = NULL;
  char buff[2];
  loff_t pos = 0;
  ssize_t bytes_read = 0;

  buff[0] = 0;
  buff[1] = 0;

  filp = filp_open("/tmp/listener", O_RDWR | O_NONBLOCK, 0);
  if (IS_ERR(filp)) return 1;

  printk(KERN_INFO "Listening\n");

  for (;bytes_read <= 0;) {
    bytes_read = kernel_read(filp, buff, 1, &pos);
    if (bytes_read == -EAGAIN) { msleep(100); continue; }
    if (bytes_read == -EWOULDBLOCK) { msleep(100); continue; }
    if (bytes_read <= 0) { msleep(100); continue; } 
    if (bytes_read > 0) {
      printk(KERN_INFO "Sound caught\n");
    }
  }
  printk(KERN_INFO "Being done\n");

  filp_close(filp, NULL);
  return 0;
}

static void __exit userget_exit(void) {
  printk(KERN_INFO "Done Listening\n");
}

module_init(userget_init);
module_exit(userget_exit);

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("Unlicense");
MODULE_AUTHOR("Jaime");
MODULE_DESCRIPTION("User can press a button to respond in kernel");
MODULE_VERSION("0.9");

static int __init userget_init(void) {
  printk(KERN_INFO "Listening\n");
  return 0;
}

static void __exit userget_exit(void) {
  printk(KERN_INFO "Done Listening\n");
}

module_init(userget_init);
module_exit(userget_exit);

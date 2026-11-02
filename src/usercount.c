#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kobject.h>
#include <linux/string.h>
#include <linux/sysfs.h>
#include <linux/device.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jaime");
MODULE_DESCRIPTION("Count button presses from user into kernel.");
MODULE_VERSION("1.0");

static char usercount_buffer[32] = "Hello from sysfs!\n";

static ssize_t usercount_show(struct kobject * kobj, struct kobj_attribute * attr, char * buf) {
  return sprintf(buf, "%s", usercount_buffer);
}

static ssize_t usercount_store(struct kobject * kobj, struct kobj_attribute * attr, const char * buf, size_t count) {
  if (count > sizeof(usercount_buffer) - 1)
    return -EINVAL;

  memset(usercount_buffer, 0, sizeof(usercount_buffer));
  memcpy(usercount_buffer, buf, count);
  usercount_buffer[count] = '\0';

  return count;
}

static struct kobj_attribute my_file_attribute = __ATTR(usercount, 0660, usercount_show, usercount_store);
static struct kobject * my_kobj = NULL;

static int __init usercount_init(void) {
  int error = 0;

  my_kobj = kobject_create_and_add("usercount", kernel_kobj);

  if (!my_kobj)
    return -ENOMEM;

  error = sysfs_create_file(my_kobj, &my_file_attribute.attr);
  if (error) {
    kobject_put(my_kobj);
    return error;
  }

  return 0;
}

static void __exit usercount_exit(void) {
  sysfs_remove_file(my_kobj, &my_file_attribute.attr);
  kobject_put(my_kobj);
}

module_init(usercount_init);
module_exit(usercount_exit);

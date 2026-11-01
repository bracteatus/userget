= Kernel Module

Wait for user input into kernel, using kernel_read, printk, and FIFO file.

= Development notes

```
make -f /lib/modules/`uname -r`/build/Makefile M=${PWD} modules
```
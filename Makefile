obj-m += getuser.o

.PHONEY: all clean

all:
	make -C /lib/modules/`uname -r`/build M=${PWD} modules

clean:
	echo "not done"

obj-m += src/userget.o

.PHONEY: all clean

all:
	@mkdir -p build/
	make -f /lib/modules/`uname -r`/build/Makefile M=${PWD} modules

clean:
	make -f /lib/modules/`uname -r`/build/Makefile M=${PWD} clean

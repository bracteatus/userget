obj-m += src/userget.o src/usercount.o

.PHONEY: all clean

/tmp/listener:
	@mkfifo /tmp/listener

all: /tmp/listener
	@mkdir -p build/
	make -f /lib/modules/`uname -r`/build/Makefile M=${PWD} modules

clean:
	make -f /lib/modules/`uname -r`/build/Makefile M=${PWD} clean
	@rm /tmp/listener

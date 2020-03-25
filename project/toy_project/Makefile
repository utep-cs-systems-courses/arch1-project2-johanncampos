# makefile configuration
COMMON_OBJECTS	=
CPU		= msp430g2533
CFLAGS		= -mmcu=${CPU} -I../../demos/h
LDFLAGS		= -L/opt/ti/msp430_gcc/include

# msp430 compilers
CC		= msp430-elf-gcc
AS		= msp430-elf-as

all: install toy.elf

#additional rules for files
toy.elf: ${COMMON_OBJECTS} toyMain.o led.o stateMachines.o switches.o buzzer.o wd_interrupt_handler.o p2_interrupt_handler.o ../../demos/lib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

install:
	(cd ../../demos/timerLib; make install)

load: toy.elf
	msp430loader.sh toy.elf

clean:
	(cd ../../demos/timerLib; make clean)
	(cd ../../demos; rm -rf lib h)
	rm -f *.o *.elf

led.o: led.c led.h

stateMachines.o: led.h stateMachines.h

switches.o: switches.h stateMachines.h

buzzer.o: buzzer.h

wd_interrupt_handler.o: stateMachines.h

p2_interrupt_handler.o: switches.h

# makfile configuration
CPU             	= msp430g2553
CFLAGS          	= -mmcu=${CPU} -Os -I../h
LDFLAGS		= -L../lib -L/opt/ti/msp430_gcc/include/ 

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-gcc -mmcu=${CPU} -c

all:game.elf

#additional rules for files
game.elf: ${COMMON_OBJECTS} main.o background.o bird.o led.o buttons.o smallBird.o buzzer.o button4If.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd 

load: game.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf

#include <msp430.h>				


/**
 * blink.c
 */
void delay(){
    volatile unsigned int j;
    for(j=10000; j>0; --j);
}

void toggleblink(int portNum){
    if (portNum == 1){
        P1DIR |= 0x01;
        P1OUT ^= 0x01;
    } else if (portNum == 4){
        P4DIR |= 0x80;
        P4OUT ^= 0x80;
    }
}

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;		// stop watchdog timer

	volatile unsigned int i;		// volatile to prevent optimization
	char message[] = "Hello World";

	while(1)
	{
	    for (i = 0; message[i] != 0; ++i) {
	        toggleblink(4);
	        delay();
	    }
	}
}

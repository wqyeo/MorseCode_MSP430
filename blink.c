#include <msp430.h>

// Signal Codes.
// We will fetch this by ASCII value with an offset.
char morse_ref[36][6] = {
                      // 0-9
                      "33333",
                      "13333",
                      "11333",
                      "11133",
                      "11113",
                      "11111",
                      "31111",
                      "33111",
                      "33311",
                      "33331",
                      // Alphabets
                      "13",
                      "3111",
                      "3131",
                      "311",
                      "1",
                      "1131",
                      "331",
                      "1111",
                      "11",
                      "1333",
                      "313",
                      "1311",
                      "33",
                      "31",
                      "333",
                      "1331",
                      "3313",
                      "131",
                      "111",
                      "3",
                      "113",
                      "1113",
                      "133",
                      "3113",
                      "3133",
                      "3311"
};

void delay() {
    volatile unsigned int j;
    for(j=10000; j>0; --j);
}

void toggle_blink(int portNum) {
    if (portNum == 1){
        P1OUT ^= 0x01;
    } else if (portNum == 4){
        P4OUT ^= 0x80;
    }
}

void blink_morse(char* blinkMessage) {
    volatile unsigned int x;
    for (x = 0; blinkMessage[x] != 0; ++x) {
        int blinkDuration = blinkMessage[x] - '0';

        // Turn on and blink for 3 loops if long
        // 1 loop if short.
        toggle_blink(1);
        while (blinkDuration > 0){
            delay();
            --blinkDuration;
        }
        // Turn off and delay before the next signal
        toggle_blink(1);
        delay();
    }
}

void main(void) {
	WDTCTL = WDTPW | WDTHOLD;

	// Clear signals and set output.
    P1DIR = 0x01;
    P4DIR = 0x80;

    P1OUT = 0x00;
    P4OUT = 0x00;

    char message[] = "HELLO WORLD";
    volatile unsigned int i;
    /* Un-comment this chunk if your message is in lower-case.
     * (Though this just converts it to upper-case, so it is better
     * if you just convert it yourself manually).
     *
    // Convert the message to all upper-case
    for (i = 0; message[i]!='\0'; ++i) {
       if(message[i] >= 'a' && message[i] <= 'z') {
           message[i] = message[i] -32;
       }
    }
    */

	while(1) {
	    for (i = 0; message[i] != 0; ++i) {
	        int ascii = message[i];
	        int offset = 0;
	        if (ascii <= '9'){
	            // current char is 0-9.
	            offset = -('0');
	        } else {
	            // assume char is A-Z
	            offset = -('A') + 10;
	        }

	        int index = ascii + offset;
	        // If index out of range
	        if (index < 0 || index >= 36){
	            // Assume its a whitespace and just delay
	            delay();
	        } else {
	            blink_morse(morse_ref[index]);
	        }

	        // 2 loop delay before the next
	        delay();
	        delay();
	    }

	    // To signal end-start of next loop.
	    toggle_blink(4);
        delay();
        delay();
        toggle_blink(4);
        delay();
	}
}

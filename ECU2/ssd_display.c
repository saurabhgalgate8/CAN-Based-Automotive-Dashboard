#include <xc.h>
#include "ssd_display.h"

void init_ssd_control(void)
{
	/* Setting PORTB as output for Data Lines */
	TRISD = 0x00;
	/* Setting SSD Enable lines as output */
	TRISA = TRISA & 0xF0;

	/* Switching OFF all the SSDs to start with */
	SSD_CNT_PORT = SSD_CNT_PORT & 0xF0;
}

/* Better if implemented in timer handler */
void display(unsigned char data[])
{
	unsigned int wait;
	unsigned char data_bit;
	unsigned char digit;
 for(int k = 0; k < 10; k++)   // refresh loop
    {
	for (digit = 0; digit < MAX_SSD_CNT; digit++)
	{
		SSD_DATA_PORT = data[digit];
		SSD_CNT_PORT = (SSD_CNT_PORT & 0xF0) | (0x01 << digit);

		for (wait = 1000; wait--; );
	}
 }
}


void ssd_display(int data[])
{
    for(int k = 0; k < 20; k++)   // refresh loop
    {
        for(unsigned char i = 0; i < 4; i++)
        {
            PORTD = data[i];   // send data
            
            PORTA = (PORTA & 0xF0) | ((1 << i)); // enable digit
            
              // small delay
//            
//            PORTA = (PORTA & 0xF0) | 0x0F;  // disable all digits
        }
        for(int delay = 200; delay--;);
    }
}

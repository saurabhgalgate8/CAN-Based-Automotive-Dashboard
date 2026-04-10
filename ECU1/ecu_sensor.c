#include<xc.h>
#include "ecu1_sensor.h"
#include "adc.h"
#include"digital_keypad.h"


int once = 0;
 static unsigned char gear_pos = 0;
unsigned char speed_array[3];
uint16_t get_speed()
{
    // Implement the speed function
   int speed =  read_adc(4);
   return speed ;
    
}

unsigned char get_gear_pos()
{
    // Implement the gear function
     
     unsigned char  sw = read_digital_keypad(EDGE);
     if(sw == SW1)
     {
         gear_pos--;
         if( gear_pos <=0)
         {
              gear_pos = 1;
         }
     }
     else if(sw==SW2)
     {
         gear_pos++;
         if(gear_pos >= 8)
             gear_pos = 7;
         
     }
     else if(sw==SW3)
     {
         gear_pos = 8 ;
     }
     
     return gear_pos ;
} 


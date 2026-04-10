#include "ecu2_sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
//#include "uart.h"
#include"digital_keypad.h"
static int del = 0 ,flag = 0;
uint16_t get_rpm()
{
    //Implement the rpm function
    int rpm = read_adc(CHANNEL4);
    if(rpm==1023)
        return 6000;
    else
    return  rpm *5.86510264; // min = 0 , max = 6000;
     
}

uint16_t get_engine_temp()
{
    //Implement the engine temperature function
    
}

IndicatorStatus process_indicator()
{
    //Implement the indicator function
    unsigned char  SW =  read_digital_keypad(EDGE);
    if(SW==SW1)
    {
        return e_ind_left;
      }
    else if(SW == SW2)
    {
        return e_ind_off ;
    }
    else if(SW== SW3)
    {
        return e_ind_right;
    }
    else if(SW==SW4)
        return e_ind_flash;
    
    return SW ;
}
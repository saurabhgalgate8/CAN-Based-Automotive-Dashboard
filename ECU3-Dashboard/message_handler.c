#include <xc.h>
#include <string.h>
#include "message_handler.h"
#include "msg_id.h"
#include "can.h"
#include "clcd.h"

unsigned char flag ;
int count = 0 ;

volatile unsigned char led_state = LED_OFF, status = e_ind_off;


void handle_speed_data(uint8_t *data, uint8_t len)
{
    //Implement the speed function
    clcd_print(data , LINE2(0));
}

void handle_gear_data(uint8_t *data, uint8_t len) 
{
    //Implement the gear function
     clcd_print(data , LINE2(4));
}

void handle_rpm_data(uint8_t *data, uint8_t len) 
{
    //Implement the rpm function
     clcd_print(data , LINE2(8));
}

void handle_engine_temp_data(uint8_t *data, uint8_t len) 
{
    //Implement the temperature function
}

void handle_indicator_data(uint8_t *data, uint8_t len) 
{
    //Implement the indicator function
    flag = data[0]- 48 ;
    if((data[0] - 48) == e_ind_off)
    {
        clcd_print("    " , LINE2(12));
        LEFT_IND_OFF();
        RIGHT_IND_OFF();
    }
    else if((data[0]-48) == e_ind_left)
    {
        clcd_print(" <-" , LINE2(12));
         RIGHT_IND_OFF(); 
    }
    else if((data[0]-48) == e_ind_right)
    {
        clcd_print(" ->" , LINE2(12));
         LEFT_IND_OFF();
    }
    else if((data[0] - 48 ) == e_ind_flash)
    {
        clcd_print("<->" , LINE2(12));
    }
}

void process_canbus_data() 
{   
    //process the CAN bus data
    int msg_id ;
    uint8_t  len ;
    char data[5];
    can_receive(&msg_id ,&data,&len );
//    data[len] = '\0';
    if(msg_id == SPEED_MSG_ID)
    {
        data[2] = '\0';
        handle_speed_data(&data,len) ;
        
    }
    if(msg_id == GEAR_MSG_ID)
    {
        data[2] = '\0';
        handle_gear_data(&data, len);
    }
    if(msg_id == RPM_MSG_ID)
    {
        data[4] = '\0';
        handle_rpm_data(&data,len);
    }
    if(msg_id == INDICATOR_MSG_ID)
    {
        data[1] = '\0';
        handle_indicator_data(&data,len);
    }
}

void __interrupt()isr()
{
    if(TMR0IF)
    {
        TMR0IF = 0 ;
        count++ ;
        if(count==10000)
        {
            
            if(flag == e_ind_left)
            {
                LEFT_IND_ON();   
            }
            else if(flag==e_ind_right)
            {
                RIGHT_IND_ON();
            }
            else if(flag == e_ind_flash)
            {
                FLASH_IND_ON();
            }
        }
        if(count == 20000)
        {
            count = 0 ;
            if(flag == e_ind_left)
            {
                LEFT_IND_OFF();        
            }
            else if(flag==e_ind_right)
            {
                RIGHT_IND_OFF();
            }
            else if(flag == e_ind_flash)
            {
                FLASH_IND_OFF();
            }
        }
    }
}
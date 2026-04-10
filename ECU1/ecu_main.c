/*
 * Date   : 2 /04/2026
 * Author : Saurabh Navnath Galgate
 * 
 * ECU1 - Speed & Gear Transmission Node
 *
 * Description:
 * This ECU acquires vehicle speed using an ADC input (potentiometer)
 * and reads gear position using a keypad interface.
 *
 * The ADC converts analog voltage from the potentiometer into a digital
 * value, which is scaled to represent vehicle speed in the range 0?99.
 * The keypad is used to change/select the current gear.
 *
 * The combined speed and gear data is transmitted directly to ECU3
 * over the CAN bus.
 *
 * Peripherals Used:
 * - ADC (Potentiometer for speed input)
 * - Keypad (gear selection)
 * - CAN Module (data transmission)
 *
 * Working:
 * 1. Initialize ADC, keypad, and CAN modules.
 * 2. Read analog value from potentiometer using ADC.
 * 3. Convert ADC value to speed (0?99). * Note: Speed is derived by scaling ADC value (0?1023) to range 0?99.
 * 4. Read keypad input to update gear position.
 * 5. Pack speed and gear data into CAN frame.
 * 6. Transmit data to ECU3.
 *
 * Role in System:
 * Acts as a transmitter node providing real-time speed and gear data
 * to the dashboard ECU (ECU3).
 */

#include "adc.h"
#include "can.h"
#include "ecu1_sensor.h"
#include "msg_id.h"
//#include "uart.h"
#include"digital_keypad.h"
#include "clcd.h"
#include"msg_id.h"
#define _XTAL_FREQ 8000000
char data[5] ="10";
int msg_id ;
int len ;
unsigned char gear_ar[3];
int main()

{
//    TRISB = 0xff;
//    RBPU = 0;
 
    unsigned char gears[9][3] ={"ON" ,"GN","G1","G2","G3","G4","G5","GR","C "};
    int key ;
    char speed_array[3] ;
    uint16_t speed ;
    unsigned char gear = 1;
     //Call the functions
    init_can();
    init_digital_keypad();
    init_clcd();
    init_adc();
    clcd_print("Speed",LINE1(1));
    clcd_print("Gear",LINE1(8));
//    clcd_print("ECU1",LINE2(5));
    while(1)
    {
        gear =  get_gear_pos();
        speed = get_speed();
         
         unsigned char i = 0 ;
    
         speed_array[i++] = 48 + speed/10 ;
         speed_array[i++] = 48 + speed%10 ;
         speed_array[i]='\0';
        
         
       
//        clcd_print(gears[gear] ,LINE2(8));
//        clcd_print(speed_array ,LINE2(2));
         
//       
          can_transmit(SPEED_MSG_ID, speed_array , 2);
         __delay_ms(80);
//         can_receive(&msg_id ,data,&len);
//         
//         clcd_print("Received data",LINE1(0));
//         clcd_print("SP:",LINE2(0));
//          data[2]='\0';
//          clcd_print(data ,LINE2(3));
//          
          can_transmit(GEAR_MSG_ID, gears[gear] , 2);
          __delay_ms(80);
//          can_receive(&msg_id ,data,&len);
////          
//          clcd_print("GR:",LINE2(6));
//          clcd_print(data ,LINE2(10));
//          __delay_ms(10000);
       
    }
   
}
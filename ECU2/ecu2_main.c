/*
 * Date   : 3/04/2026
 * Author : Saurabh Navnath Galgate
 * 
 * ECU2 - Engine RPM & Indicator Node
 *
 * Description:
 * This ECU reads engine RPM using an ADC input (potentiometer)
 * and controls indicator signals using a digital keypad.
 *
 * The ADC value is scaled to represent RPM in the range 0?6000.
 * Indicator states include LEFT, RIGHT, OFF, and HAZARD.
 *
 * The combined data is transmitted directly to ECU3 via CAN bus.
 *
 * Peripherals Used:
 * - ADC (Potentiometer for RPM input)
 * - Digital Keypad (indicator control)
 * - CAN Module (data transmission)
 *
 * Working:
 * 1. Initialize ADC, keypad, and CAN modules.
 * 2. Read analog value from potentiometer using ADC.
 * 3. Convert ADC value to RPM (0?6000).
 * 4. Detect keypad input for indicator status.
 * 5. Pack RPM and indicator data into CAN frame.
 * 6. Transmit data to ECU3.
 *
 * Role in System:
 * Acts as a monitoring and control node for engine RPM and indicators.
 */

#include "ecu2_sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
#include"ecu2_sensor.h"
#include"digital_keypad.h"
#include"ssd_display.h"
#include"clcd.h"
#define _XTAL_FREQ 8000000
void indicators(unsigned char indic);
//#include "uart.h"
int msg_id ;
unsigned char Data[5]="";
unsigned char indic ;
unsigned char indicator[4] ;

int len ;
//int Data ;
int RPM ;
int delay = 0 ;
int main()
{
   
    TRISB = 0X00 ;
    PORTB = 0X00 ;

    
//    PORTD = 0;
    static unsigned long int delay = 0 ;
    int rpm, prev = 0XFF ;
    
    unsigned char ssd[4];
    unsigned char digits[] = {ZERO ,ONE , TWO , THREE , FOUR ,FIVE,SIX,SEVEN,EIGHT,NINE};
    unsigned char rpm_arr[5],i = 0;
    init_digital_keypad();
    init_adc();
    init_ssd_control();
    init_can();
//    init_clcd();
    unsigned char indic ;
    while(1)
    {
        
    //call the functions
        rpm = get_rpm();
        rpm_arr[0] = 48 + (rpm /1000) ;
        rpm_arr[1] = 48 + ((rpm/100) %10);
        rpm_arr[2] = 48 + ((rpm/10)%10);
        rpm_arr[3] = 48 + (rpm%10);
        rpm_arr[4] = '\0' ;
//        
//        ssd[0] = digits[rpm_arr[0]-48];
//        ssd[1] = digits[rpm_arr[1]-48];
//        ssd[2] = digits[rpm_arr[2]-48];
//        ssd[3] = digits[rpm_arr[3]-48];
//        display(ssd);
//        ssd_display(ssd);
        
        
      
       
       can_transmit(RPM_MSG_ID , rpm_arr , 4);
       __delay_ms(80);
//       can_receive(&msg_id , Data , &len);
//       Data[4]='\0';
//        
//        ssd[0] = digits[Data[0]-48];
//        ssd[1] = digits[Data[1]-48];
//        ssd[2] = digits[Data[2]-48];
//        ssd[3] = digits[Data[3]-48];
//        display(ssd);
//        clcd_print(Data , LINE1(3));
//        clcd_putch(Data[0] , LINE1(0));
//        clcd_putch(Data[1] , LINE1(1));
//        clcd_putch(Data[2] , LINE1(2));
//        clcd_putch(Data[3] , LINE1(3));
        
        
        indic =  process_indicator();      // to get indicator
        indicator[0] = indic + 48 ;
        indicator[1] = '\0';
        can_transmit(INDICATOR_MSG_ID ,indicator ,1 ) ;
        __delay_ms(80);
//       can_receive(&msg_id ,Data   , &len);
       
//           indic = Data[0]  ;   
//        ssd[0] = digits[0];
//        ssd[1] = digits[1];
//        ssd[2] = digits[2];
//        ssd[3] = digits[3];
//        indic = Data[0] - 48 ;
//        __delay_ms(100);
//       if(indic == 0xff)
//       {
//           indic = prev ;
//       }
//       else
//           prev = indic ;
//      
////       indicators(indic);
//       
//         if(indic == e_ind_left  )
//       {
//           RIGHT_IND_OFF();
//           if(delay++ < 1000)
//                   LEFT_IND_ON();
//           else if(delay < 2000)
//               LEFT_IND_OFF() ;
//           else
//               delay = 0 ;
//
//       }
//       else  if(indic == e_ind_right )
//       {
//           LEFT_IND_OFF() ;
//           if(delay++ < 1000)
//                   RIGHT_IND_ON();
//           else if(delay < 2000)
//               RIGHT_IND_OFF() ;
//           else
//               delay = 0 ;
//                   
//       }
//       else if(indic == e_ind_off)
//       {
//          LEFT_IND_OFF() ;
//          RIGHT_IND_OFF();
//       }
//       else if(indic == e_ind_flash)
//       {
//           
//           if(delay++ < 100)
//           {
//             
//                FLASH_IND_ON();
//           }
//           
//           else if(delay < 200)
//           {             
//               FLASH_IND_OFF() ;
//
//           }
//           else
//               delay = 0 ;
//                   
//       }
}
}



//
//void indicators(unsigned char indic)
//{
//     
//       if(indic == e_ind_left  )
//       {
//           RIGHT_IND_OFF();
//           if(delay++ < 1000)
//                   LEFT_IND_ON();
//           else if(delay < 2000)
//               LEFT_IND_OFF() ;
//           else
//               delay = 0 ;
//
//       }
//       else  if(indic == e_ind_right )
//       {
//           LEFT_IND_OFF() ;
//           if(delay++ < 1000)
//                   RIGHT_IND_ON();
//           else if(delay < 2000)
//               RIGHT_IND_OFF() ;
//           else
//               delay = 0 ;
//                   
//       }
//       else if(indic == e_ind_off)
//       {
//          LEFT_IND_OFF() ;
//          RIGHT_IND_OFF();
//       }
//       else if(indic == e_ind_flash)
//       {
//           
//           if(delay++ < 100)
//           {
//             
//                FLASH_IND_ON();
//           }
//           
//           else if(delay < 200)
//           {             
//               FLASH_IND_OFF() ;
//
//           }
//           else
//               delay = 0 ;
//                   
//       }
//    }
//

/*
 * Date   : 04/04/2026
 * Author : Saurabh Navnath Galgate
 * /*
 * ECU3 - Automotive Dashboard Node
 *
 * Description:
 * This ECU functions as the dashboard display unit.
 * It receives CAN messages from ECU1 and ECU2 and displays
 * vehicle parameters in real time.
 *
 * Received Data:
 * - Speed (ADC-based) and Gear from ECU1
 * - RPM (ADC-based) and Indicator Status from ECU2
 *
 * Peripherals Used:
 * - CAN Module (data reception)
 * - CLCD Display (output display)
 *
 * Working:
 * 1. Initialize CAN and display modules.
 * 2. Continuously receive CAN messages.
 * 3. Identify message source using CAN ID.
 * 4. Extract speed, gear, RPM, and indicator status.
 * 5. Display all values on CLCD.
 *
 * Role in System:
 * Acts as the central dashboard integrating all vehicle data.
 */
 
#include <xc.h>
#include <stdint.h>
#include "can.h"
#include "clcd.h"
#include "msg_id.h"
#include "message_handler.h"
//#include "isr.h"
#include "timer0.h"

static int init_leds() {
    TRISB = 0x08; // Set RB2 as output, RB3 as input, remaining as output
    PORTB = 0x00;
}

static void init_config(void) {
    // Initialize CLCD and CANBUS
    init_clcd();
    init_can();
    init_leds();

    // Enable Interrupts
    PEIE = 1;
    GIE = 1;
    init_timer0();
}

void main(void) {
    // Initialize peripherals
    init_config();
    clcd_print("SP  GR  RPM  IND",LINE1(0));
    /* ECU1 main loop */
    while (1) {
        // Read CAN Bus data and handle it
        process_canbus_data();
    }

    return;
}

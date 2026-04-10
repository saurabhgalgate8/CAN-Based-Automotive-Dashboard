#include <xc.h>
#include "adc.h"

void init_adc(void)
{
	/* Selecting right justified ADRES Registers order */
	ADFM = 1;

	/* 
	 * Acqusition1 time selection bits 
	 * Set for 4 Tad
	 */
	ACQT2 = 0;
	ACQT1 = 1;
	ACQT0 = 0;

	/*
	 * Selecting the conversion clock of Fosc / 32 -> 1.6usecs -> 1Tad
	 * Our device frequency is 20 MHz
	 */
	ADCS0 = 0;
	ADCS1 = 1;
	ADCS2 = 0;

	/* Stop the conversion to start with */
	GODONE = 0;

	

	/* Voltage reference bit as VSS(AN2) */
	VCFG1 = 0;    
	/* Voltage reference bit as VDD(AN3) */
	VCFG0 = 0;

	/* Just clearing the ADRESH & ADRESL registers, for time pass */
    // result registers 
	ADRESH = 0;
	ADRESL = 0;

	/* Turn ON the ADC module */
	ADON = 1;
}

unsigned short read_adc(unsigned char channel)
{
	unsigned short reg_val;

	/*select the channel*/
	ADCON0 = (ADCON0 & 0xC3) | (channel << 2);

	/* Start the conversion */
	GO = 1;
	while (GO);  // To wait till conversion get complete
	reg_val = (ADRESH << 8) | ADRESL; 
 
	return (reg_val/10.33); // covert into percentage
}
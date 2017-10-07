// DAC.c
// Runs on LM4F120 or TM4C123, 
// edX lab 13 
// Implementation of the 4-bit digital to analog converter
// Daniel Valvano, Jonathan Valvano
// December 29, 2014
// Port B bits 3-0 have the 4-bit DAC

#include "Util.h"
#include "DAC.h"
#include "..//tm4c123gh6pm.h"

void InitPortB(void);
void InitPortB(void){
	volatile unsigned long delay;
	SYSCTL_RCGC2_R |= PIN(1);      // 1) A clock
	delay = SYSCTL_RCGC2_R;            // delay to allow clock to stabilize     
	GPIO_PORTB_AMSEL_R &= ~(PIN(0) | PIN(1) | PIN(2) | PIN(3));        // 2) disable analog function
	GPIO_PORTB_PCTL_R &= ~(PIN(0) | PIN(1) | PIN(2) | PIN(3));   // 3) GPIO clear bit PCTL  
	GPIO_PORTB_DIR_R |= (PIN(0) | PIN(1) | PIN(2) | PIN(3));          // PB0-3 output 
	GPIO_PORTB_DR8R_R |= (PIN(0) | PIN(1) | PIN(2) | PIN(3));     // can drive up to 8mA out	
	GPIO_PORTB_AFSEL_R &= ~(PIN(0) | PIN(1) | PIN(2) | PIN(3));        // 5) no alternate function      
	GPIO_PORTB_DEN_R |= (PIN(0) | PIN(1) | PIN(2) | PIN(3));          // 7) enable digital pins PB0-3
}

// **************DAC_Init*********************
// Initialize 4-bit DAC 
// Input: none
// Output: none
void DAC_Init(void){
  InitPortB();
}


// **************DAC_Out*********************
// output to DAC
// Input: 4-bit data, 0 to 15 
// Output: none
void DAC_Out(unsigned long data){
  GPIO_PORTB_DATA_R = (data & ((PIN(0) | PIN(1) | PIN(2) | PIN(3))));
}

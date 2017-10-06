// Piano.c
// Runs on LM4F120 or TM4C123, 
// edX lab 13 
// There are four keys in the piano
// Daniel Valvano
// December 29, 2014

// Port E bits 3-0 have 4 piano keys

#include "Util.h"
#include "Piano.h"
#include "..//tm4c123gh6pm.h"


void InitPortE(void);

void InitPortE(void){
	volatile unsigned long delay;
	SYSCTL_RCGC2_R |= PIN(4);      // 1) E clock
	delay = SYSCTL_RCGC2_R;            // delay to allow clock to stabilize     
	GPIO_PORTE_AMSEL_R &= ~(PIN(0) | PIN(1) | PIN(2) | PIN(3));        // 2) disable analog function
	GPIO_PORTE_PCTL_R &= ~(PIN(0) | PIN(1) | PIN(2) | PIN(3));   // 3) GPIO clear bit PCTL   
	GPIO_PORTE_DIR_R &= ~(PIN(0) | PIN(1) | PIN(2) | PIN(3));         // 4.1) PE0-3 input
	GPIO_PORTE_AFSEL_R &= ~(PIN(0) | PIN(1) | PIN(2) | PIN(3));        // 5) no alternate function      
	GPIO_PORTE_DEN_R |= (PIN(0) | PIN(1) | PIN(2) | PIN(3));          // 7) enable digital pins PE0-3
}


// **************Piano_Init*********************
// Initialize piano key inputs
// Input: none
// Output: none
void Piano_Init(void){ 
	InitPortE();
}
// **************Piano_In*********************
// Input from piano key inputs
// Input: none 
// Output: 0 to 15 depending on keys
// 0x01 is key 0 pressed, 0x02 is key 1 pressed,
// 0x04 is key 2 pressed, 0x08 is key 3 pressed
unsigned long Piano_In(void){
  return (GPIO_PORTE_DATA_R & (PIN(0) | PIN(1) | PIN(2) | PIN(3))); // remove this, replace with input
}

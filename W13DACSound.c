// Sound.c
// Runs on LM4F120 or TM4C123, 
// edX lab 13 
// Use the SysTick timer to request interrupts at a particular period.
// Daniel Valvano, Jonathan Valvano
// December 29, 2014
// This routine calls the 4-bit DAC

#include "Sound.h"
#include "DAC.h"
#include "..//tm4c123gh6pm.h"

void InitSysTickInterrupts(void);
void InitSysTickInterrupts(void){
	NVIC_ST_CTRL_R = 0;                   // disable SysTick during setup
	NVIC_ST_RELOAD_R = 0x0001631C;        // maximum reload value
	NVIC_ST_CURRENT_R = 0;                // any write to current clears it           
	NVIC_ST_CTRL_R = NVIC_ST_CTRL_INTEN | NVIC_ST_CTRL_ENABLE | NVIC_ST_CTRL_CLK_SRC;// enable SysTick with core clock
}

// **************Sound_Init*********************
// Initialize Systick periodic interrupts
// Also calls DAC_Init() to initialize DAC
// Input: none
// Output: none
void Sound_Init(void){
	DAC_Init();
	InitSysTickInterrupts();
}

// **************Sound_Tone*********************
// Change Systick periodic interrupts to start sound output
// Input: interrupt period
//           Units of period are 12.5ns
//           Maximum is 2^24-1
//           Minimum is determined by length of ISR
// Output: none
void Sound_Tone(unsigned long period){
// this routine sets the RELOAD and starts SysTick
}


// **************Sound_Off*********************
// stop outputing to DAC
// Output: none
void Sound_Off(void){
 // this routine stops the sound output
}


// Interrupt service routine
// Executed every 12.5ns*(period)
void SysTick_Handler(void){
   
}

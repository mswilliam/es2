// Sound.c
// Runs on LM4F120 or TM4C123, 
// edX lab 13 
// Use the SysTick timer to request interrupts at a particular period.
// Daniel Valvano, Jonathan Valvano
// December 29, 2014
// This routine calls the 4-bit DAC

#include "FSM.h"
#include "Sound.h"
#include "DAC.h"
#include "..//tm4c123gh6pm.h"

const unsigned char SineWave[16] = {8, 11, 13, 15, 15, 14, 12, 9, 7, 4, 2, 1, 1, 3, 5, 8};
unsigned char Index=0;           // Index varies from 0 to 15
void DoRing(void);
void DoQuiet(void);

Fsm finalStateMachine = {
	{
		{DoQuiet,		{Quiet, Ring}	},
		{DoRing,		{Quiet, Ring}	}
	}, 
	Quiet,
	InputOff
};

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

void transit(enum eInput input){
	finalStateMachine.currentState = finalStateMachine.transitionGraph[finalStateMachine.currentState].Next[input];
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
	NVIC_ST_RELOAD_R = period - 1;
	transit(InputOn);
}


// **************Sound_Off*********************
// stop outputing to DAC
// Output: none
void Sound_Off(void){
 // this routine stops the sound output
	transit(InputOff);
}

// **************Sound_Off*********************
// start outputing to DAC
// Output: none
void DoRing(void){
 // this routine stops the sound output
	Index = (Index+1)&0x0F;      // 8, 11, 13, 15, 15, 14, 12, 9, 7, 4, 2, 1, 1, 3, 5, 8, ... 
  DAC_Out(SineWave[Index]);
}
void DoQuiet(void){
}


// Interrupt service routine
// Executed every 12.5ns*(period)
void SysTick_Handler(void){
	(finalStateMachine.transitionGraph[finalStateMachine.currentState]).functionOut();
}

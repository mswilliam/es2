// Lab13.c
// Runs on LM4F120 or TM4C123
// Use SysTick interrupts to implement a 4-key digital piano
// edX Lab 13 
// Daniel Valvano, Jonathan Valvano
// December 29, 2014
// Port B bits 3-0 have the 4-bit DAC
// Port E bits 3-0 have 4 piano keys

#include "..//tm4c123gh6pm.h"
#include "Sound.h"
#include "Piano.h"
#include "Dac.h"
#include "TExaS.h"

const unsigned int reloadValue[4] = {9556, 8513, 7584, 6378};
 
// basic functions defined at end of startup.s
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void delay(unsigned long msec);

unsigned char toPin(unsigned long value){
	unsigned char result = 0x0F;
	if (value >= 0x08){
		result = 0x03;
	}else if(value >= 0x04){
		result = 0x02;
	}else if(value >= 0x02){
		result = 0x01;
	}else if(value == 0x01){
		result = 0x00;
	}else{
		result = 0x0F;
	}
	return result;
}

int main(void){ // Real Lab13 
	unsigned long touch = 0x00;
	unsigned char index = 0x00;
	// for the real board grader to work 
	// you must connect PD3 to your DAC output
  TExaS_Init(SW_PIN_PE3210, DAC_PIN_PB3210,ScopeOn); // activate grader and set system clock to 80 MHz
// PortE used for piano keys, PortB used for DAC        
  Sound_Init(); // initialize SysTick timer and DAC
  Piano_Init();
  EnableInterrupts();  // enable after all initialization are done
  while(1){
		touch = Piano_In();
		index = toPin(touch);
		if(index < 0x04)
		{
			Sound_Tone(reloadValue[index]);
		}else{
			Sound_Off();
		}
  }
            
}

// Inputs: Number of msec to delay
// Outputs: None
void delay(unsigned long msec){ 
  unsigned long count;
  while(msec > 0 ) {  // repeat while there are still delay
    count = 16000;    // about 1ms
    while (count > 0) { 
      count--;
    } // This while loop takes approximately 3 cycles
    msec--;
  }
}


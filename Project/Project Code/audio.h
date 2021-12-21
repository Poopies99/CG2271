#include "MKL25Z4.h"
#include "cmsis_os2.h"

#include "notes.h"

#define GET_MOD(x) (375000 / x)

volatile uint8_t shutup = 1;
volatile uint8_t takeOnMeIterator = 0;
//osMessageQueueId_t musicMsg;

uint8_t takeOnMeNoteCount = 32;

uint32_t takeOnMeMelody[] = { 
    NOTE_FS4, NOTE_FS4, NOTE_D4, NOTE_B3, 
		SILENCE, NOTE_B3, SILENCE, NOTE_E4, 
		SILENCE, NOTE_E4, SILENCE, NOTE_E4, 
		NOTE_GS4, NOTE_GS4, NOTE_A4, NOTE_B4, 
		NOTE_A4, NOTE_A4, NOTE_A4, NOTE_E4, 
		SILENCE, NOTE_D4, SILENCE, NOTE_FS4, 
		SILENCE, NOTE_FS4, SILENCE, NOTE_FS4,
		NOTE_E4, NOTE_E4, NOTE_FS4, NOTE_E4
};

uint8_t startNoteCount = 5;

uint32_t startMelody[] = {
    NOTE_C5, SILENCE, NOTE_A4, NOTE_F4, NOTE_E5
};

uint8_t endingNoteCount = 1;
uint32_t endingNote = NOTE_G5;


void setPWMFreq(TPM_Type *timer, uint8_t channel, uint32_t freq) 
{
   //set duty cycle, pass freq to PWM
  TPM_CnV_REG(timer, channel) = GET_MOD(freq) / 2; // 50% duty cycle
  timer->MOD = GET_MOD(freq);
}

void playNote(TPM_Type *timer, uint8_t channel, uint32_t note, uint32_t noteDuration){
  setPWMFreq(timer, channel, note);
  osDelay(noteDuration);
}

//Requirement D1
void playTakeOnMe(){
	if (takeOnMeIterator > takeOnMeNoteCount) {
		takeOnMeIterator = 0;
	}
	playNote(TPM0, 4, takeOnMeMelody[takeOnMeIterator], 120);
	playNote(TPM0, 4, 0, 25);
	takeOnMeIterator++;
}
    
//Requirement D2
void playEndUnique(){ 
   playNote(TPM0, 4, endingNote, 500);
}

//Requirement A3
void playStartUnique() { 
  for (int i=0; i<startNoteCount; i++) {
		playNote(TPM0, 4, startMelody[i], 120);
		playNote(TPM0, 4, 0, 30);
	}
	osDelay(1000);
}
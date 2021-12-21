#include "MKL25Z4.h"
#include "cmsis_os2.h"

#define RED_MOVE 500
#define RED_STOP 250

#define FRONT_1 2 		// Port E Pin 2
#define FRONT_2 3 		// Port E Pin 3
#define FRONT_3 4 		// Port E Pin 4
#define FRONT_4 5 		// Port E Pin 5
#define FRONT_5 20 		// Port E Pin 20
#define FRONT_6 21 		// Port E Pin 21
#define FRONT_7 22 		// Port E Pin 22
#define FRONT_8 29 		// Port E Pin 29

#define REAR 		12			// Port A Pin 12

#define MASK(x) (1 << (x))

typedef enum led_pos
{
	a = FRONT_1,
	b = FRONT_2,
	c = FRONT_3,
	d = FRONT_4,
	e = FRONT_5,
	f = FRONT_6,
	g = FRONT_7,
	h = FRONT_8,
	
	r = REAR
}led_pos_t;

char led_mapping_green[8][2] = {
	{0, a},
	{1, b},
	{2, c},
	{3, d},
	{4, e},
	{5, f},
	{6, g},
	{7, h}
};

char led_mapping_flash[2][2] = {
	{0,a},
	{1,h}
};

//osMessageQueueId_t greenLEDMsg;
//osMessageQueueId_t redLEDMsg;

void initLED(void) {
	// Enable Clock
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTE_MASK;
	
	// Configure MUX settings to make all pins GPIO
	PORTE->PCR[FRONT_1] &= ~PORT_PCR_MUX_MASK;
	PORTE->PCR[FRONT_1] |= PORT_PCR_MUX(1);
	PORTE->PCR[FRONT_2] &= ~PORT_PCR_MUX_MASK;
	PORTE->PCR[FRONT_2] |= PORT_PCR_MUX(1);
	PORTE->PCR[FRONT_3] &= ~PORT_PCR_MUX_MASK;
	PORTE->PCR[FRONT_3] |= PORT_PCR_MUX(1);
	PORTE->PCR[FRONT_4] &= ~PORT_PCR_MUX_MASK;
	PORTE->PCR[FRONT_4] |= PORT_PCR_MUX(1);
	PORTE->PCR[FRONT_5] &= ~PORT_PCR_MUX_MASK;
	PORTE->PCR[FRONT_5] |= PORT_PCR_MUX(1);
	PORTE->PCR[FRONT_6] &= ~PORT_PCR_MUX_MASK;
	PORTE->PCR[FRONT_6] |= PORT_PCR_MUX(1);
	PORTE->PCR[FRONT_7] &= ~PORT_PCR_MUX_MASK;
	PORTE->PCR[FRONT_7] |= PORT_PCR_MUX(1);
	PORTE->PCR[FRONT_8] &= ~PORT_PCR_MUX_MASK;
	PORTE->PCR[FRONT_8] |= PORT_PCR_MUX(1);
	
	PORTA->PCR[REAR] &= ~PORT_PCR_MUX_MASK;
	PORTA->PCR[REAR] |= PORT_PCR_MUX(1);
	
	// Set Data Direction Registers
	PTA->PDDR |= MASK(REAR);
	PTE->PDDR |= MASK(FRONT_1) | MASK(FRONT_2) | MASK(FRONT_3) | MASK(FRONT_4) | MASK(FRONT_5) | MASK(FRONT_6) | MASK(FRONT_7) | MASK(FRONT_8);
}

void offLED(void) {
	PTE->PCOR |= MASK(FRONT_1) | MASK(FRONT_2) | MASK(FRONT_3) | MASK(FRONT_4) | MASK(FRONT_5) | MASK(FRONT_6) | MASK(FRONT_7) | MASK(FRONT_8);
}

void ledControl(led_pos_t position) {
	offLED();
	switch(position)
	{
		case FRONT_1:
			PTE->PSOR = MASK(FRONT_1);
			break;
		case FRONT_2:
			PTE->PSOR = MASK(FRONT_2);
			break;
		case FRONT_3:
			PTE->PSOR = MASK(FRONT_3);
			break;
		case FRONT_4:
			PTE->PSOR = MASK(FRONT_4);
			break;
		case FRONT_5:
			PTE->PSOR = MASK(FRONT_5);
			break;
		case FRONT_6:
			PTE->PSOR = MASK(FRONT_6);
			break;
		case FRONT_7:
			PTE->PSOR = MASK(FRONT_7);
			break;
		case FRONT_8:
			PTE->PSOR = MASK(FRONT_8);
			break;
		case REAR:
			PTA->PSOR = MASK(REAR);
			break;
		default:
			offLED();
	}
}

void greenFlashTwice(void) {
	offLED();
	osDelay(250);
	PTE->PSOR = (MASK(FRONT_1) | MASK(FRONT_2) | MASK(FRONT_3) | MASK(FRONT_4) | MASK(FRONT_5) | MASK(FRONT_6) | MASK(FRONT_7) | MASK(FRONT_8));
	osDelay(250);
	offLED();
	osDelay(250);
	PTE->PSOR = (MASK(FRONT_1) | MASK(FRONT_2) | MASK(FRONT_3) | MASK(FRONT_4) | MASK(FRONT_5) | MASK(FRONT_6) | MASK(FRONT_7) | MASK(FRONT_8));
	osDelay(250);
	offLED();
}

void redStopState(void) {
	PTA->PSOR = MASK(REAR);
	osDelay(RED_STOP);
	PTA->PCOR = MASK(REAR);
	osDelay(RED_STOP);
}

void redMoveState(void) {
	PTA->PSOR = MASK(REAR);
	osDelay(RED_MOVE);
	PTA->PCOR = MASK(REAR);
	osDelay(RED_MOVE);
}

void greenStopState(void) {
	PTE->PSOR = (MASK(FRONT_1) | MASK(FRONT_2) | MASK(FRONT_3) 
	| MASK(FRONT_4) | MASK(FRONT_5) | MASK(FRONT_6) | MASK(FRONT_7) 
	| MASK(FRONT_8));
}
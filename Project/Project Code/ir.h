#include "MKL25Z4.h"
#include "cmsis_os2.h"
#include "self_driving.h"

#define MASK(x)						(1 << (x))

osMessageQueueId_t selfDriveMsg;

volatile uint8_t ir_control = 0;
uint8_t motor;
volatile uint8_t isUTurn = 1;

void PORTD_IRQHandler() {
	NVIC_ClearPendingIRQ(PORTD_IRQn);
	
	ir_control = 1;
		
	//executeUTurn();
	
	PORTD->ISFR |= MASK(7);
}

void ir_thread(void *argument) {
	uint8_t selfDriveData = 0;
		while(1) {
			osMessageQueueGet(selfDriveMsg, &selfDriveData, NULL, NULL);
			if (selfDriveData == 0x0b) {
				ir_control = 0;
				if (ir_control == 0) {
					moveForward();
				}
				while(1){
					if (ir_control == 1 && isUTurn == 1) {
						break;
					}
				}
				executeUTurn();
				isUTurn = 0;
				ir_control = 0;
				while(1) {
					if (ir_control == 1 && isUTurn == 0) {
						break;
					}
				}
				stop();
				break;
			}
		}
}
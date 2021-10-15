#include "MKL25Z4.h"                    // Device header

#define PTB0_Pin 0
#define PTB1_Pin 1
#define PTB2_Pin 2
#define PTB3_Pin 3
#define PTC1_Pin 1
#define PTC2_Pin 2
#define PTC3_Pin 3
#define PTC4_Pin 4

/* init PWM() */
void initPWM(void)
{
	// Enable Clock Gating for Port
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
	
	// Configure Mode for the PWM pin operation
	PORTB->PCR[PTB0_Pin] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[PTB0_Pin] |= PORT_PCR_MUX(3);
	
	PORTB->PCR[PTB1_Pin] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[PTB1_Pin] |= PORT_PCR_MUX(3);
	
	PORTB->PCR[PTB2_Pin] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[PTB2_Pin] |= PORT_PCR_MUX(3);
	
	PORTB->PCR[PTB3_Pin] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[PTB3_Pin] |= PORT_PCR_MUX(3);
	
	PORTC->PCR[PTC1_Pin] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[PTC1_Pin] |= PORT_PCR_MUX(4);
	
	PORTC->PCR[PTC2_Pin] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[PTC2_Pin] |= PORT_PCR_MUX(4);
	
	PORTC->PCR[PTC3_Pin] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[PTC3_Pin] |= PORT_PCR_MUX(4);
	
	PORTC->PCR[PTC4_Pin] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[PTC4_Pin] |= PORT_PCR_MUX(4);
	
	// Enable Clock Gating for Timer
	SIM_SCGC6 |= SIM_SCGC6_TPM0_MASK;
	SIM_SCGC6 |= SIM_SCGC6_TPM1_MASK;
	SIM_SCGC6 |= SIM_SCGC6_TPM2_MASK;
	
	// Select Clock for TPM module
	SIM->SOPT2 &= ~SIM_SOPT2_TPMSRC_MASK;
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1); // MCGFLLCLK clock or MCGPLLCLK/2
	
	// Set Modulo Value
	TPM0->MOD = 2500;
	TPM1->MOD = 2500;
	TPM2->MOD = 2500;
	
	// Edge-Aligned PWM
	// Update SnC register
	TPM0->SC &= ~((TPM_SC_CMOD_MASK) | (TPM_SC_PS_MASK));
	TPM0->SC |= (TPM_SC_CMOD(1) | TPM_SC_PS(7));
	TPM0->SC &= ~(TPM_SC_CPWMS_MASK);
	
	TPM1->SC &= ~((TPM_SC_CMOD_MASK) | (TPM_SC_PS_MASK));
	TPM1->SC |= (TPM_SC_CMOD(1) | TPM_SC_PS(7));
	TPM1->SC &= ~(TPM_SC_CPWMS_MASK);
	
	TPM2->SC &= ~((TPM_SC_CMOD_MASK) | (TPM_SC_PS_MASK));
	TPM2->SC |= (TPM_SC_CMOD(1) | TPM_SC_PS(7));
	TPM2->SC &= ~(TPM_SC_CPWMS_MASK);
	
	// Enable PWM on TPMx Channel n
	TPM0_C0SC &= ~((TPM_CnSC_ELSB_MASK) | (TPM_CnSC_ELSA_MASK) | (TPM_CnSC_MSB_MASK) | (TPM_CnSC_MSA_MASK));
	TPM0_C0SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1));
	
	TPM0_C1SC &= ~((TPM_CnSC_ELSB_MASK) | (TPM_CnSC_ELSA_MASK) | (TPM_CnSC_MSB_MASK) | (TPM_CnSC_MSA_MASK));
	TPM0_C1SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1));
	
	TPM0_C2SC &= ~((TPM_CnSC_ELSB_MASK) | (TPM_CnSC_ELSA_MASK) | (TPM_CnSC_MSB_MASK) | (TPM_CnSC_MSA_MASK));
	TPM0_C2SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1));
	
	TPM0_C3SC &= ~((TPM_CnSC_ELSB_MASK) | (TPM_CnSC_ELSA_MASK) | (TPM_CnSC_MSB_MASK) | (TPM_CnSC_MSA_MASK));
	TPM0_C3SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1));
	
	TPM1_C0SC &= ~((TPM_CnSC_ELSB_MASK) | (TPM_CnSC_ELSA_MASK) | (TPM_CnSC_MSB_MASK) | (TPM_CnSC_MSA_MASK));
	TPM1_C0SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1));
	
	TPM1_C1SC &= ~((TPM_CnSC_ELSB_MASK) | (TPM_CnSC_ELSA_MASK) | (TPM_CnSC_MSB_MASK) | (TPM_CnSC_MSA_MASK));
	TPM1_C1SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1));
	
	TPM2_C0SC &= ~((TPM_CnSC_ELSB_MASK) | (TPM_CnSC_ELSA_MASK) | (TPM_CnSC_MSB_MASK) | (TPM_CnSC_MSA_MASK));
	TPM2_C0SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1));
	
	TPM2_C1SC &= ~((TPM_CnSC_ELSB_MASK) | (TPM_CnSC_ELSA_MASK) | (TPM_CnSC_MSB_MASK) | (TPM_CnSC_MSA_MASK));
	TPM2_C1SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1));
}

void moveForwards(void) 
{
	TPM0_C0V = 2000; // PTC1
	TPM0_C1V = 0; // PTC2
	TPM0_C2V = 2000; // PTC3
	TPM0_C3V = 0; // PTC4
	TPM1_C0V = 2000; // PTB0
	TPM1_C1V = 0; // PTB1
	TPM2_C0V = 2000; // PTB2
	TPM2_C1V = 0; // PTB3
}

void moveBackwards(void) 
{
	TPM0_C0V = 0; // PTC1
	TPM0_C1V = 2000; // PTC2
	TPM0_C2V = 0; // PTC3
	TPM0_C3V = 2000; // PTC4
	TPM1_C0V = 0; // PTB0
	TPM1_C1V = 2000; // PTB1
	TPM2_C0V = 0; // PTB2
	TPM2_C1V = 2000; // PTB3
}

void moveLeft(void) 
{
	TPM0_C0V = 0; // PTC1
	TPM0_C1V = 2000; // PTC2
	TPM0_C2V = 2000; // PTC3
	TPM0_C3V = 0; // PTC4
	TPM1_C0V = 0; // PTB0
	TPM1_C1V = 2000; // PTB1
	TPM2_C0V = 2000; // PTB2
	TPM2_C1V = 0; // PTB3
}

void moveRight(void) 
{
	TPM0_C0V = 2000; // PTC1
	TPM0_C1V = 0; // PTC2
	TPM0_C2V = 0; // PTC3
	TPM0_C3V = 2000; // PTC4
	TPM1_C0V = 2000; // PTB0
	TPM1_C1V = 0; // PTB1
	TPM2_C0V = 0; // PTB2
	TPM2_C1V = 2000; // PTB3
}

void stop(void) 
{
	TPM0_C0V = 0; // PTC1
	TPM0_C1V = 0; // PTC2
	TPM0_C2V = 0; // PTC3
	TPM0_C3V = 0; // PTC4
	TPM1_C0V = 0; // PTB0
	TPM1_C1V = 0; // PTB1
	TPM2_C0V = 0; // PTB2
	TPM2_C1V = 0; // PTB3
}

/* Delay function */

static void delay(volatile uint32_t nof)
{
  while(nof!=0) {
    __asm("NOP");
    nof--;
  }
}

int main(void)
{
	SystemCoreClockUpdate();
	initPWM();
	
	while(1) {
		moveForwards();
	}
}

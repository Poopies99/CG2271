/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/
 
#include "RTE_Components.h"
#include  CMSIS_device_header
#include "cmsis_os2.h"

#define MASK(x)						(1 << (x))
#define PTB0_Pin					0
#define PTB1_Pin					1
#define PTB2_Pin					2
#define PTB3_Pin					3
#define PTC1_Pin 					1
#define PTC2_Pin 					2
#define PTC3_Pin 					3
#define PTC4_Pin 					4
#define BAUD_RATE					9600
#define UART_RX_PORTE23		23
#define UART2_INT_PRIO		128

volatile uint8_t rx_data = 0x0;
volatile uint8_t count = 0;


void initPWM(void)
{
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
	
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
	
	SIM_SCGC6 |= SIM_SCGC6_TPM0_MASK;
	SIM_SCGC6 |= SIM_SCGC6_TPM1_MASK;
	SIM_SCGC6 |= SIM_SCGC6_TPM2_MASK;
	
	SIM->SOPT2 &= ~SIM_SOPT2_TPMSRC_MASK;
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1);
	
	TPM0->MOD = 2500;
	TPM1->MOD = 2500;
	TPM2->MOD = 2500;
	
	TPM0->SC &= ~((TPM_SC_CMOD_MASK) | (TPM_SC_PS_MASK));
	TPM0->SC |= (TPM_SC_CMOD(1) | TPM_SC_PS(7));
	TPM0->SC &= ~(TPM_SC_CPWMS_MASK);
	
	TPM1->SC &= ~((TPM_SC_CMOD_MASK) | (TPM_SC_PS_MASK));
	TPM1->SC |= (TPM_SC_CMOD(1) | TPM_SC_PS(7));
	TPM1->SC &= ~(TPM_SC_CPWMS_MASK);
	
	TPM2->SC &= ~((TPM_SC_CMOD_MASK) | (TPM_SC_PS_MASK));
	TPM2->SC |= (TPM_SC_CMOD(1) | TPM_SC_PS(7));
	TPM2->SC &= ~(TPM_SC_CPWMS_MASK);
	
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

void initUART2(uint32_t baud_rate)
{
	uint32_t divisor, bus_clock;
	
	SIM->SCGC4 |= SIM_SCGC4_UART2_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	
	PORTE->PCR[UART_RX_PORTE23] &= ~PORT_PCR_MUX_MASK;
	PORTE->PCR[UART_RX_PORTE23] |= PORT_PCR_MUX(4);
	
	UART2->C2 &= ~((UART_C2_TE_MASK) | (UART_C2_RE_MASK));
	
	bus_clock = (DEFAULT_SYSTEM_CLOCK)/2;
	divisor = bus_clock / (baud_rate * 16);
	UART2->BDH = UART_BDH_SBR(divisor >> 8);
	UART2->BDL = UART_BDL_SBR(divisor);
	
	UART2->C1 = 0;
	UART2->S2 = 0;
	UART2->C3 = 0;
	
	UART2->C2 |= (UART_C2_RE_MASK);
	NVIC_SetPriority(UART2_IRQn, 1);
	NVIC_ClearPendingIRQ(UART2_IRQn);
	NVIC_EnableIRQ(UART2_IRQn);
	UART2->C2 |= UART_C2_RIE_MASK;
}

void UART2_IRQHandler(void) {
	NVIC_ClearPendingIRQ(UART2_IRQn);
	
	if (UART2->S1 & UART_S1_RDRF_MASK) {
		rx_data = UART2->D;
	}
	count++;
	//PORTD->ISFR = 0xffffffff;
	
}

void moveForward(void) {
	TPM0_C0V = 0; // PTC1
	TPM0_C1V = 2000; // PTC2
	TPM0_C2V = 0; // PTC3
	TPM0_C3V = 2000; // PTC4
	TPM1_C0V = 0; // PTB0
	TPM1_C1V = 2000; // PTB1
	TPM2_C0V = 0; // PTB2
	TPM2_C1V = 2000; // PTB3
}

void moveBackward(void) 
{
	TPM0_C0V = 2000; // Top-Right-A
	TPM0_C1V = 0; // Top-Right-B
	TPM0_C2V = 2000; // Rear-Right-A
	TPM0_C3V = 0; // Rear-Right-B
	TPM1_C0V = 2000; // Rear-Left-A
	TPM1_C1V = 0; // Rear-Left-B
	TPM2_C0V = 2000; // Top-Left-A
	TPM2_C1V = 0; // Top-Left-B
}

void moveLeft(void) 
{
	TPM0_C0V = 2000; // PTC1
	TPM0_C1V = 0; // PTC2
	TPM0_C2V = 2000; // PTC3
	TPM0_C3V = 0; // PTC4
	TPM1_C0V = 0; // PTB0
	TPM1_C1V = 2000; // PTB1
	TPM2_C0V = 0; // PTB2
	TPM2_C1V = 2000; // PTB3
}

void moveRight(void) 
{
	TPM0_C0V = 0; // PTC1
	TPM0_C1V = 2000; // PTC2
	TPM0_C2V = 0; // PTC3
	TPM0_C3V = 2000; // PTC4
	TPM1_C0V = 2000; // PTB0
	TPM1_C1V = 0; // PTB1
	TPM2_C0V = 2000; // PTB2
	TPM2_C1V = 0; // PTB3
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
 
/*----------------------------------------------------------------------------
 * Application main thread
 *---------------------------------------------------------------------------*/
void app_main (void *argument) {
 
  // ...
  for (;;) {
		//moveForward();
		switch (rx_data) {
		case 0x01: 
			moveForward();
			break;
		case 0x02:
			moveBackward();
			break;
		case 0x03:
			moveRight();
			break;
		case 0x04:
			moveLeft();
			break;
		default:
			stop();
		}
	}
}
 
int main (void) {
 
  // System Initialization
  SystemCoreClockUpdate();
	initPWM();
	initUART2(BAUD_RATE);
  // ...
 
  osKernelInitialize();                 // Initialize CMSIS-RTOS
  osThreadNew(app_main, NULL, NULL);    // Create application main thread
  osKernelStart();                      // Start thread execution
  for (;;) {}
}

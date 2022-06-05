/* p7_1.c: A to D conversion of channel 0
* This program converts the analog input from channel 0 (PTE20)
* using software trigger continuously.
* Bits 10-8 are used to control the tri-color LEDs. LED code is
* copied from p2_7. Connect a potentiometer between 3.3V and
* ground. The wiper of the potentiometer is connected to PTE20.
* When the potentiometer is turned, the LEDs should change color.
*/
#include <MKL25Z4.h>

void button_init(void);
void ADC0_init(void);
void LED_set(int s);
void LED_init(void);
void DAC0_init(void);
void delayMs(int n);
int type=0;





int main (void)
{

	short int result=0;
	int i;
	
	const static int sineWave[] =
	{1862, 2793, 3474, 3724, 3474, 2793,
	1862, 931, 249, 0, 249, 931};
	
	const static int sqrWave[] =
	{3724, 3724, 3724, 3724, 3724, 3724,
	0, 0, 0, 0, 0, 0};

	const static int trigWave[] =
	{1200, 1400, 1600, 1800, 2000, 2200,
	0, 200, 400, 600, 800, 1000};
	
	
	button_init();
	LED_init(); /* Configure LEDs */
	ADC0_init(); /* Configure ADC0 */
	DAC0_init(); /* Configure DAC0 */
	
	while (1) {
		ADC0->SC1[0] = 0; /* start conversion on channel 0 */
		while (!(ADC0->SC1[0] & 0x80)) {
			
		for (i = 0; i < 12; i++) {
				/* write value to DAC0 */
		if(type == 0) {
				DAC0->DAT[0].DATL = (sineWave[i]*result/5000 & 0xff);//*(result & 0xff); /* write low byte */
				DAC0->DAT[0].DATH = ((sineWave[i]*result/5000 >> 8) & 0x0f);//*((result >> 8) & 0x0f);/* write high byte */
				delayMs(631); /* delay for 510Hz with 12 values */}
		
		if(type == 1) {
				DAC0->DAT[0].DATL = (sqrWave[i]*result/5000 & 0xff);//*(result & 0xff); /* write low byte */
				DAC0->DAT[0].DATH = ((sqrWave[i]*result/5000 >> 8) & 0x0f);//*((result >> 8) & 0x0f);/* write high byte */
				delayMs(631); /* delay for 510Hz with 12 values */}
		
		//else{
		if(type == 2) {
				DAC0->DAT[0].DATL = (trigWave[i]*result/5000 & 0xff);//*(result & 0xff); /* write low byte */
				DAC0->DAT[0].DATH = ((trigWave[i]*result/5000 >> 8) & 0x0f);//*((result >> 8) & 0x0f);/* write high byte */
				delayMs(631); /* delay for 510Hz with 12 values */}
		
		}} 
		result = ADC0->R[0]; /* read conversion result and clear COCO flag */
		LED_set(result >> 7); /* display result on LED */
		} /* wait for conversion complete */
		
			
		
		

	}

	
void button_init(void) {
__disable_irq(); /* disable all IRQs */
SIM->SCGC5 |= 0x200; /* enable clock to Port A */
/* configure PTA1 for interrupt */
PORTA->PCR[1] |= 0x00100; /* make it GPIO */
PORTA->PCR[1] |= 0x00003; /* enable pull-up */
PTA->PDDR &= ~0x0002; /* make pin input */
PORTA->PCR[1] &= ~0xF0000; /* clear interrupt selection */
PORTA->PCR[1] |= 0xA0000; /* enable falling edge interrupt */

NVIC->ISER[0] |= 0x40000000; /* enable INT30 (bit 30 of ISER[0]) */
__enable_irq(); /* global enable IRQs */

}
	
	
void ADC0_init(void)
{
	SIM->SCGC5 |= 0x2000; /* clock to PORTE */
	PORTE->PCR[20] = 0; /* PTE20 analog input */
	SIM->SCGC6 |= 0x8000000; /* clock to ADC0 */
	ADC0->SC2 &= ~0x40; /* software trigger */
	/* clock div by 4, long sample time, single ended 12 bit, bus clock */
	ADC0->CFG1 = 0x40 | 0x10 | 0x04 | 0x00;
}

void LED_init(void) 
{
	SIM->SCGC5 |= 0x400; /* enable clock to Port B */
	SIM->SCGC5 |= 0x1000; /* enable clock to Port D */
	PORTB->PCR[18] = 0x100; /* make PTB18 pin as GPIO */
	PTB->PDDR |= 0x40000; /* make PTB18 as output pin */
	PORTB->PCR[19] = 0x100; /* make PTB19 pin as GPIO */
	PTB->PDDR |= 0x80000; /* make PTB19 as output pin */
	PORTD->PCR[1] = 0x100; /* make PTD1 pin as GPIO */
	PTD->PDDR |= 0x02; /* make PTD1 as output pin */
	
}

void LED_set(int s) 
{
	if (s & 1) /* use bit 0 of s to control red LED */
	PTB->PCOR = 0x40000; /* turn on red LED */
	else
	PTB->PSOR = 0x40000; /* turn off red LED */
	if (s & 2) /* use bit 1 of s to control green LED */
	PTB->PCOR = 0x80000; /* turn on green LED */
	else
	PTB->PSOR = 0x80000; /* turn off green LED */
	if (s & 4) /* use bit 2 of s to control blue LED */
	PTD->PCOR = 0x02; /* turn on blue LED */
	else
	PTD->PSOR = 0x02; /* turn off blue LED */
}


void DAC0_init(void) 
{
	SIM->SCGC6 |= 0x80000000; /* clock to DAC module */
	DAC0->C1 = 0; /* disable the use of buffer */
	DAC0->C0 = 0x80 | 0x20; /* enable DAC and use software trigger */
}

/* Delay n milliseconds
* The CPU core clock is set to MCGFLLCLK at 41.94 MHz in SystemInit().
*/
void delayMs(int n) 
{
	while (n--) 
		{
	}
}

void PORTA_IRQHandler(void) {	// clear pending interrupts
	//type = 1;
  type += 1; //Type 0 => Sine, 1 => Sqr, 2 => Trg
	if (type == 3){
		type = 0;}
	PORTA->ISFR = 0x00000006; /* clear interrupt flag */
	


}

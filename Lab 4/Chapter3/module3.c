
#include <MKL25Z4.H>
#include <stdio.h>
#include <math.h>
#include <string.h>  

#define RS 0x04     /* PTA2 mask */ 
#define RW 0x10     /* PTA4 mask */ 
#define EN 0x20     /* PTA5 mask */

void Delay(volatile unsigned int time_del);
void LCD_command(unsigned char command);
void LCD_data(unsigned char data);
void LCD_init(void);
void LCD_ready(void);
void keypad_init(void);
int reverse(int number);
void iToc(int c);
int cToi(char c);
int rev_number_1;
int rev_number_2;
int stored_1;
int stored_2;
int temp_1;
int temp_2;
int counter_z1=0;
int counter_z2=0;
int operations(int number_1, int number_2, char operation);
uint32_t keypad_getkey(void);

int main(void)
{
	int number_1 = 0;
	int number_2 = 0;
	char num_store;
	int num_count = 0;
	char op_store = ' ';
	int result;
	uint32_t key;

	char lookup[]= {'1','2','3','+','4','5','6','-','7','8','9','x',' ','0','=','/'};

	
	
	LCD_init();	
		keypad_init();
		while(keypad_getkey() == 0)
		{
		}
		LCD_command(0x01);
		while(1)
		{	
		Delay(300000);	
		key=keypad_getkey();
			if(key != 0)
			{
			num_store = lookup[key-1];
				if(num_store == ' '){
					if (op_store != ' '){
						op_store = ' ';
						num_count -= 1;

					}
					
					else {
					LCD_command(0x10);
					LCD_data(' ');
					LCD_command(0x10);
					temp_1 = reverse(number_1);
					temp_1 /= 10;
					num_count -= 1;
					number_1 = reverse(temp_1);
					}
				}
				else if (num_store != ' '){ 
				 if (num_store == '0'){
					 counter_z1 += 1;
				 }
				 else if (num_store != '+' || num_store != '-' || num_store != 'x' || num_store != '/' || num_store != '='){
				 }
				 
			
				num_count +=1;	
				if (num_store == '+' || num_store == '-' || num_store == 'x' || num_store == '/' ||  num_store == '='||num_count == 7){
					op_store = num_store;
					if( num_count == 7 ){
						while(keypad_getkey() == 0)
						{
						}
						while(1)
						{	
						Delay(300000);	
						key=keypad_getkey();
							if(key != 0)
							{
							if (lookup[key-1] == '+'||lookup[key-1] == '-'||lookup[key-1] == 'x'|| lookup[key-1] == '/'){
								op_store = lookup[key-1];
								break;
							}	
						}
					}		 
				 }
					LCD_data(op_store);
					num_count = 0;
					num_store = 0;
					while(1) {
						Delay(300000);
						key=keypad_getkey();
						if(key != 0){
						num_store = lookup[key-1];				
						if(num_store == ' '){
							
							if (op_store != ' '){
						op_store = ' ';
						num_count -= 1;

					}
					
					else {
						
							LCD_command(0x10);
							LCD_data(' ');
							LCD_command(0x10);
							temp_2 = reverse(number_2);
							temp_2 /= 10;
							num_count -= 1;
							number_2 = reverse(temp_2);
				}
			}
						else if (num_store != ' '){
						if (num_store == '0'){
							
					 counter_z2 += 1;
				 }
						else if (num_store != '+' || num_store != '-' || num_store != 'x' || num_store != '/' || num_store != '='){}
				 
						
						num_count +=1;
							if (num_store == '+' || num_store == '-' || num_store == 'x' || num_store == '/' ||  num_store == '='||num_count == 7){
					op_store = num_store;
							}
							if (num_count == 7 || num_store == '='){
								
								LCD_data('=');
								result = operations( rev_number_1*pow(10,counter_z1), rev_number_2*pow(10,counter_z2),  op_store);
								LCD_command(0xC0);
								iToc(result);
							}		
													
							else{
								
							 LCD_data(lookup[key-1]);		
							 stored_2 = cToi(num_store);
							 number_2 += stored_2*pow(10,num_count-1);
							 rev_number_2 = reverse(number_2);
							 
						}
					}
						Delay(300000);
						key =0;	
						 }
					}
				}	
			
			else{

				LCD_data(lookup[key-1]); 
				stored_1 = cToi(num_store);
				number_1 += stored_1*pow(10,num_count-1);	  
				rev_number_1 = reverse(number_1);
			}
		}
				Delay(300000);
			key =0;
	}
			
	}

	}		

void LCD_init(void)
{
		SIM->SCGC5 |= 0x1000;       /* enable clock to Port D */ 
		PORTD->PCR[0] = 0x100;      /* make PTD0 pin as GPIO */
		PORTD->PCR[1] = 0x100;      /* make PTD1 pin as GPIO */
		PORTD->PCR[2] = 0x100;      /* make PTD2 pin as GPIO */
		PORTD->PCR[3] = 0x100;      /* make PTD3 pin as GPIO */
		PORTD->PCR[4] = 0x100;      /* make PTD4 pin as GPIO */
		PORTD->PCR[5] = 0x100;      /* make PTD5 pin as GPIO */
		PORTD->PCR[6] = 0x100;      /* make PTD6 pin as GPIO */
		PORTD->PCR[7] = 0x100;      /* make PTD7 pin as GPIO */
		PTD->PDDR = 0xFF;           /* make PTD7-0 as output pins */
		
		SIM->SCGC5 |= 0x0200;       /* enable clock to Port A */ 
		PORTA->PCR[2] = 0x100;      /* make PTA2 pin as GPIO */
		PORTA->PCR[4] = 0x100;      /* make PTA4 pin as GPIO */
		PORTA->PCR[5] = 0x100;      /* make PTA5 pin as GPIO */
		PTA->PDDR |= 0x34;          /* make PTA5, 4, 2 as output pins */
		
		LCD_command(0x38);      /* set 8-bit data, 2-line, 5x7 font */
		LCD_command(0x01);      /* clear screen, move cursor to home */
		LCD_command(0x0F);      /* turn on display, cursor blinking */
}

/* This function waits until LCD controller is ready to
 * accept a new command/data before returns.
 */
void LCD_ready(void)
{
		uint32_t status;
		
		PTD->PDDR = 0x00;          /* PortD input */
		PTA->PCOR = RS;         /* RS = 0 for status */
		PTA->PSOR = RW;         /* R/W = 1, LCD output */
		
		do {    /* stay in the loop until it is not busy */
				PTA->PCOR = EN;
				Delay(500);
				PTA->PSOR = EN;     /* raise E */
				Delay(500);
				status = PTD->PDIR; /* read status register */
				PTA->PCOR = EN;
				Delay(500);			/* clear E */
		} while (status & 0x80UL);    /* check busy bit */
		
		PTA->PCOR = RW;         /* R/W = 0, LCD input */
		PTD->PDDR = 0xFF;       /* PortD output */
}

void LCD_command(unsigned char command)
{
		LCD_ready();			/* wait until LCD is ready */
		PTA->PCOR = RS | RW;    /* RS = 0, R/W = 0 */
		PTD->PDOR = command;
		PTA->PSOR = EN;         /* pulse E */
		Delay(500);
		PTA->PCOR = EN;
}

void LCD_data(unsigned char data)
{
		LCD_ready();			/* wait until LCD is ready */
		PTA->PSOR = RS;         /* RS = 1, R/W = 0 */
		PTA->PCOR = RW;
		PTD->PDOR = data;
		PTA->PSOR = EN;         /* pulse E */
		Delay(500);
		PTA->PCOR = EN;
}

/* Delay n milliseconds
 * The CPU core clock is set to MCGFLLCLK at 41.94 MHz in SystemInit().
 */

/* delay n microseconds
 * The CPU core clock is set to MCGFLLCLK at 41.94 MHz in SystemInit().
 */


void Delay(volatile unsigned int time_del) {
	while (time_del--) 
		{
	}
}


void keypad_init(void)
{
		SIM->SCGC5 |= 0x0800;       /* enable clock to Port C */ 
		PORTC->PCR[0] = 0x103;      /* make PTC0 pin as GPIO and enable pullup*/
		PORTC->PCR[1] = 0x103;      /* make PTC1 pin as GPIO and enable pullup*/
		PORTC->PCR[2] = 0x103;      /* make PTC2 pin as GPIO and enable pullup*/
		PORTC->PCR[3] = 0x103;      /* make PTC3 pin as GPIO and enable pullup*/
		PORTC->PCR[4] = 0x103;      /* make PTC4 pin as GPIO and enable pullup*/
		PORTC->PCR[5] = 0x103;      /* make PTC5 pin as GPIO and enable pullup*/
		PORTC->PCR[6] = 0x103;      /* make PTC6 pin as GPIO and enable pullup*/
		PORTC->PCR[7] = 0x103;      /* make PTC7 pin as GPIO and enable pullup*/
		PTC->PDDR = 0x00;         /* make PTC7-0 as input pins */
}




uint32_t keypad_getkey(void)
{
		uint32_t row, col;
		const char row_select[] = {0x01, 0x02, 0x04, 0x08}; /* one row is active */

		/* check to see any key pressed */
		PTC->PDDR |= 0x0F;          /* rows output */
		PTC->PCOR = 0x0F;               /* ground rows */
		Delay(500);                 /* wait for signal return */
		col =  PTC->PDIR & 0xF0UL;     /* read all columns */
		PTC->PDDR = 0;              /*  rows input */
		if (col == 0xF0UL)
				return 0;               /* no key pressed */

		/* If a key is pressed, it gets here to find out which key.
		 * It activates one row at a time and read the input to see
		 * which column is active. */
		for (row = 0; row < 4; row++)
		{
				PTC->PDDR = 0;                  /* disable all rows */
				PTC->PDDR |= row_select[row];   /* enable one row */
				PTC->PCOR = row_select[row];    /* drive the active row low */
				Delay(500);                     /* wait for signal to settle */
				col = PTC->PDIR & 0xF0UL;         /* read all columns */
				if (col != 0xF0UL) break;         /* if one of the input is low, some key is pressed. */
		}
		PTC->PDDR = 0;                      /* disable all rows */
		if (row == 4) 
				return 0;                       /* if we get here, no key is pressed */
 
		/* gets here when one of the rows has key pressed, check which column it is */
		if (col == 0xE0UL) return row * 4 + 1;    /* key in column 0 */
		if (col == 0xD0UL) return row * 4 + 2;    /* key in column 1 */
		if (col == 0xB0UL) return row * 4 + 3;    /* key in column 2 */
		if (col == 0x70UL) return row * 4 + 4;    /* key in column 3 */

		return 0;   /* just to be safe */
}
int reverse(int number){
	int reversed = 0; // Input a number from user
					while(number != 0) //Repeat the till number becomes 0
		{
				reversed = (reversed * 10) + (number % 10);  // Remove last digit from number
				number /= 10;
		}
		return reversed;
}
	
void iToc(int c) {
	
	char buffer[20];
	int length_dec,l;
	length_dec = sprintf(buffer, "%d", c);
	
	for(l=0;l<length_dec;++l)
				{
					LCD_data(buffer[l]);
				}
	}

int cToi(char c){
	int num = 0;
	num = c - '0';

	return num;
			 }

int operations(int number_1, int number_2, char operation) {
	int result;
	if (operation == '+') {
		result = number_1  + number_2;
	}
	else if (operation == '-') {
		result = number_1  - number_2;
	}
	else if (operation == 'x')  {
		result = number_1  * number_2;
	}
	else{
		result = number_1  / number_2;
	}
	return result;
	}	

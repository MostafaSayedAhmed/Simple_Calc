#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "MCAL/DIO/DIO.h"
#include "HAL/LCD/LCD.h"
#include "HAL/Keypad/Keypad.h"
#include "MCAL/Interrupt/Interrupt.h"
//#include "MCAL/7Seg/7Seg.h"

#define Password "1234"

int KEY2NUM(unit8 num);
void NUM2KEY(int x);
void operation(float a,unit8 op,float b);

unit8 flag = 0;


void Toggle()
{
	TOG_BIT(flag, 0);
	DIO_Write(PORTD_1,flag);
}

unit8 button = NO_KEY;

int main()
{


	Interrupt_Enable();
	SetCallbackFunction_INT0(Toggle);

	// Definition of Important Variables
	char PasswordCorrect[] = Password;
	char PaswordEnter [5];
	unit8 PWflag = 0;
	float a = 0 , b = 0 ;
	int j = 0;
	unit8 op = 0;

	LCD_init();
	while(1)
	{
		// Password Entry Section
		LCD_SendCMD(CLEAR_DISPLAY);
		LCD_SendString("Welcome to CAL");
		_delay_ms(1000);
		while(PWflag == 0)
		{
			_delay_ms(500);
		LCD_SendCMD(CLEAR_DISPLAY);
		PWflag = 1;
		LCD_SendString("Password : ");
		for(int i=0;i<4;i++)
		{
			button = Keypad_Read();
			if(button != NO_KEY) {
				PaswordEnter[i] = button;
				LCD_SendData(button);
			}
			else i--;
			button = NO_KEY;
			_delay_ms(200);
		}

		while(PWflag == 1 && j < 4)
		{
			if(PaswordEnter[j] != PasswordCorrect[j] ) PWflag = 0;
			j++;
		}
		if(PWflag) {
			LCD_SendCMD(CLEAR_DISPLAY);
			LCD_SendString("Valid Password");
			LCD_SendStringxy("Press C to cont",0,1);
		}
		else
		{
			LCD_SendCMD(CLEAR_DISPLAY);
		    LCD_SendString("invalid Password");
		}
		}
		while (button != 'C')
		button = Keypad_Read();
		_delay_ms(200);
      // Calculator Section
		while(flag == 0)
		{
			while (button != 'C' )
			button = Keypad_Read();
	  while(button == 'C')
		{
		button  = NO_KEY;
		LCD_SendCMD(CLEAR_DISPLAY);
		//LCD_SendString("EQN : ");
		while(op == 0)
		{
			a *=10;
		while (button == NO_KEY)
		button = Keypad_Read();
		_delay_ms(200);

		switch(button)
		{ case '0':case '1':case '2':case '3':case '4':
		  case '5':case '6':case '7':case '8':case '9':
			  a += KEY2NUM(button);LCD_SendData(button); break;

		  case '+':case '*':case '/':case '-':
			  op = button;LCD_SendData(button); break;

		}
		button  = NO_KEY;
	    }

		while(button != '=')
		{
			b *=10;
		button  = NO_KEY;
		while (button == NO_KEY)
		button = Keypad_Read();
		_delay_ms(200);
		switch(button)
				{ case '0':case '1':case '2':case '3':case '4':
				  case '5':case '6':case '7':case '8':case '9':
					  b += KEY2NUM(button);LCD_SendData(button); break;
				}
		}
		a/=10;b/=10;
	    LCD_SendString(" = ");
	    LCD_SendCMD(CLEAR_DISPLAY);
	   // LCD_SendString("Result = ");
		operation(a,op,b);
		LCD_SendStringxy("C cont,= reset",0,1);
		button = NO_KEY;
		op = 0; a=0 ; b=0;PWflag = 0;j=0;
		while (button == NO_KEY)
		button = Keypad_Read();
		}
	  if(button == '=') break;
	}
	while(flag == 1){
			DIO_Write(PORTD_0,HIGH);
			_delay_ms(1000);
			DIO_Write(PORTD_0,LOW);
			_delay_ms(1000);
			button = NO_KEY;
			op = 0; a=0 ; b=0;PWflag = 0;j=0;
		}
	}
}

int KEY2NUM(unit8 num)
{
	switch(num)
	{
	case '0': num = 0; break;
	case '1': num = 1; break;
	case '2': num = 2; break;
	case '3': num = 3; break;
	case '4': num = 4; break;
	case '5': num = 5; break;
	case '6': num = 6; break;
	case '7': num = 7; break;
	case '8': num = 8; break;
	case '9': num = 9; break;
	}
	return num;
}

void NUM2KEY(int x)
{
	switch(x)
	{
	case 0:  LCD_SendData('0'); break;
	case 1:  LCD_SendData('1'); break;
	case 2:  LCD_SendData('2'); break;
	case 3:  LCD_SendData('3'); break;
	case 4:  LCD_SendData('4'); break;
	case 5:  LCD_SendData('5'); break;
	case 6:  LCD_SendData('6'); break;
	case 7:  LCD_SendData('7'); break;
	case 8:  LCD_SendData('8'); break;
	case 9:  LCD_SendData('9'); break;
	}
}

void operation(float a,unit8 op,float b)
{
	float ans;
	int count = 0;
	int mul = 1;
	switch(op)
	{
	case '+': ans = a + b ; break;
	case '-':
		ans = a - b ;
	    if(ans < 0)
	    	{
	    	LCD_SendData('-');
	    	ans*=-1;
	    	}
	     break;
	case '*': ans = a * b ; break;
	case '/': ans = a / b ; break;
	}

   long int temp = ans*100;

	while(temp!=0)
	{
		count++;
		temp/=10;
	}

	for(;count!=1;count--) mul*=10;
	temp = ans*100;
	while(mul!=0)
	{
		if(mul == 10) LCD_SendData('.');
		NUM2KEY((temp/mul)%10);
		mul/=10;

	}
}


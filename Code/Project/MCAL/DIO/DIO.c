#include "DIO.h"





void DIO_init()
{
	int i = 0;
	for(i = 0 ; i < PIN_COUNT ;i++)
	{
		if(Pins_list[i].Port == PORT_A )
		{
			if(Pins_list[i].Dir == OUTPUT)
				{
				SET_BIT(DDRA,Pins_list[i].Pin);
				}
			else
				{
				CLR_BIT(DDRA,Pins_list[i].Pin);
				if(Pins_list[i].Pullup == PULLUP_ON){
					SET_BIT(PORTA,Pins_list[i].Pin);
				}
				else
				{
					CLR_BIT(PORTA,Pins_list[i].Pin);
				}
				}
		}
		else if(Pins_list[i].Port == PORT_B )
		{
			if(Pins_list[i].Dir == OUTPUT)
				{
			     SET_BIT(DDRB,Pins_list[i].Pin);
				}
			else
				{
				CLR_BIT(DDRB,Pins_list[i].Pin);
				if(Pins_list[i].Pullup == PULLUP_ON){
					SET_BIT(PORTB,Pins_list[i].Pin);
				}
				else
				{
					CLR_BIT(PORTB,Pins_list[i].Pin);
				}
				}
		}
		else if(Pins_list[i].Port == PORT_C )
		{
			if(Pins_list[i].Dir == OUTPUT)
				{
				SET_BIT(DDRC,Pins_list[i].Pin);
				}
			else
				{
				CLR_BIT(DDRC,Pins_list[i].Pin);
				if(Pins_list[i].Pullup == PULLUP_ON){
					SET_BIT(PORTC,Pins_list[i].Pin);
				}
				else
				{
					CLR_BIT(PORTC,Pins_list[i].Pin);
				}
				}
		}
		else if(Pins_list[i].Port == PORT_D )
		{
			if(Pins_list[i].Dir == OUTPUT)
				{
				SET_BIT(DDRD,Pins_list[i].Pin);
				}
			else
				{
				CLR_BIT(DDRD,Pins_list[i].Pin);
				if(Pins_list[i].Pullup == PULLUP_ON){
					SET_BIT(PORTD,Pins_list[i].Pin);
				}
				else
				{
					CLR_BIT(PORTD,Pins_list[i].Pin);
				}
				}
		}
	}
}

void DIO_Write(channel_type channel, DIO_Level level )
{
	DIO_Port Port = channel/8;
	DIO_Pin Pin = channel%8;
	if(Port == PORT_A)
	{
	if(level == HIGH) SET_BIT(PORTA,Pin);
	else CLR_BIT(PORTA,Pin);
	}
	if(Port == PORT_B)
	{
	if(level == HIGH) SET_BIT(PORTB,Pin);
	else CLR_BIT(PORTB,Pin);
	}
	if(Port == PORT_C)
	{
	if(level == HIGH) SET_BIT(PORTC,Pin);
	else CLR_BIT(PORTC,Pin);
	}
	if(Port == PORT_D)
	{
	if(level == HIGH) SET_BIT(PORTD,Pin);
	else CLR_BIT(PORTD,Pin);
	}
}


DIO_Level DIO_Read(channel_type channel)
{
	DIO_Port Port = channel/8;
	DIO_Pin Pin = channel%8;
	if      (Port == PORT_A)
	{
		if(GET_BIT(PINA,Pin) == 0) return LOW;
		else                        return HIGH;
	}

	else if (Port == PORT_B)
	{
		if(GET_BIT(PINB,Pin) == 0)  return LOW;
		else                        return HIGH;
	}
	else if (Port == PORT_C)
	{
		if(GET_BIT(PINC,Pin) == 0) return LOW;
		else                        return HIGH;
	}
	else
	{
		if(GET_BIT(PIND,Pin) == 0) return LOW;
		else                        return HIGH;
	}
}

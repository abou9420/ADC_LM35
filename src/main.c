#include "lpc17xx_gpio.h"
#include "lpc17xx_adc.h"
#include "lpc17xx_pinsel.h"

/* Char LCD definition */
#define LCD_LPC1768       
#define LCD_PORT_2
#define LCD_RS     0
#define LCD_RW     1
#define LCD_E      2
#define LCD_DB4    4
#define LCD_DB5    5
#define LCD_DB6    6
#define LCD_DB7    7

#include "lcd.h"
#include<stdio.h>
// Delay 
void Delay(uint8_t delay)
{
	for(uint16_t i=0;i< UINT16_MAX;i++)
	{
		for(uint8_t j=0;j<delay;j++)
		{
		}
	}
}


int main()
{
	// variable 
	uint16_t voltage=0;
  char	temper[5];
	float calVoltage=0, temp=0;
	lcd_init();
	lcd_clear();
	// pinsel difenation
	PINSEL_CFG_Type adcpin;
	adcpin.Funcnum = PINSEL_FUNC_1;
	adcpin.OpenDrain = PINSEL_PINMODE_NORMAL;
	adcpin.Pinmode = PINSEL_PINMODE_TRISTATE;
	adcpin.Pinnum = PINSEL_PIN_24;
	adcpin.Portnum =PINSEL_PORT_0;
	
	PINSEL_ConfigPin(&adcpin);
	
	// adc prepheral init
	ADC_Init(LPC_ADC,200000);
	ADC_ChannelCmd(LPC_ADC,ADC_CHANNEL_1, ENABLE);
	//
	lcd_gotoxy(1,4);
	lcd_putsf("Temperatuer");
	while(1)
	{
		ADC_StartCmd(LPC_ADC,ADC_START_NOW);
		while(ADC_ChannelGetStatus(LPC_ADC,ADC_CHANNEL_1,ADC_DATA_DONE)==0)
		{}
    voltage = ADC_ChannelGetData(LPC_ADC,ADC_CHANNEL_1);
		/*
			3.2volt    4096 digit
			x          voltage 
			x=(3.2*voltage)/4096
    */			
		calVoltage = ( 3.2F * voltage ) / 4096;
		//temp = (calVoltage*1000 /10);
		temp = calVoltage*100;
		lcd_gotoxy(2,7);
		sprintf(temper ,"T=%0.0f",temp);
		lcd_putsf(temper);		
	}
	
}

#include "lpc17xx_gpio.h"
#include "ADC.h"
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

void ADC_PIN_Difenation(uint8_t OpenDrain_status, uint8_t Pinmode_status, uint8_t PinNum);
void ADC_INIT(uint32_t Rate, uint8_t CHANNEL, FunctionalState State);
int main()
{
	// variable 
	uint16_t voltage=0;
  char	temper[5];
	float calVoltage=0, temp=0;
	lcd_init();
	lcd_clear();
	// pinsel difenation
	 ADC_PIN_Difenation(NORMAL, PINMODE_TRISTATE, 30);
	// adc prepheral init
   ADC_INIT(200000, CHANNEL_4, ENABLE);
	//
	lcd_gotoxy(1,4);
	lcd_putsf("Temperatuer");
	while(1)
	{
		ADC_StartCmd(LPC_ADC,ADC_START_NOW);
		while(ADC_ChannelGetStatus(LPC_ADC,ADC_CHANNEL_4,ADC_DATA_DONE)==0)
		{}
    voltage = ADC_ChannelGetData(LPC_ADC,ADC_CHANNEL_4);
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
 

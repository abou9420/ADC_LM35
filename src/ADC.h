 // 
#include "lpc17xx_adc.h"
#include "lpc17xx_pinsel.h"

 /* Pin mode **********************************************************************/
#define PINMODE_PULLUP		((0))	/* Internal pull-up resistor*/
#define PINMODE_TRISTATE 	((2))	/* Tri-state */
#define PINMODE_PULLDOWN 	((3)) 	/* Internal pull-down resistor */

/* **********************************************************************
 * open drain status
 **********************************************************************/
#define	NORMAL		((0))	/**< Pin is in the normal (not open drain) mode.*/
#define	OPENDRAIN	((1)) 	/**< Pin is in the open drain mode */

   // pinsel difenation for ADC
    /* Pin Mode, should be:
      PINMODE_PULLUP: Internal pull-up resistor 
      PINMODE_TRISTATE: Tri-state
      PINMODE_PULLDOWN: Internal pull-down resistor
	*/
	/* OpenDrain mode, should be:
	- NORMAL: Pin is in the normal (not open drain) mode
	- OPENDRAIN: Pin is in the open drain mode 
	*/
/*  CHANNEL_0 AD0 PIN 0.23 
	  CHANNEL_1 AD1 PIN 0.24 
	  CHANNEL_2 AD2 PIN 0.25 
	  CHANNEL_3 AD3 PIN 0.26 
	  CHANNEL_4 AD4 PIN 1.30 
	  CHANNEL_5 AD5 PIN 1.31 
	  CHANNEL_6 AD6 PIN 0.3 
	  CHANNEL_7 AD7 PIN 0.2 
	*/
	
void ADC_PIN_Difenation(uint8_t OpenDrain_status, uint8_t Pinmode_status, uint8_t PinNum)
{
	PINSEL_CFG_Type    adcpin;
	adcpin.OpenDrain = OpenDrain_status;
  adcpin.Pinmode   = Pinmode_status;
        
	if((PinNum==30)|(PinNum==31))
	{
        adcpin.Funcnum   = PINSEL_FUNC_3;
        adcpin.Pinnum    = PinNum;
        adcpin.Portnum   = PINSEL_PORT_1;
	}
    else if((PinNum==2)|(PinNum==3))
	{
		adcpin.Funcnum   = PINSEL_FUNC_2;
		adcpin.Pinnum    = PinNum;
		adcpin.Portnum   = PINSEL_PORT_0;
	}
	else if((PinNum==23)|(PinNum==24)|(PinNum==25)|(PinNum==26))
	{
		adcpin.Funcnum   = PINSEL_FUNC_1;
		adcpin.Pinnum    = PinNum;
		adcpin.Portnum   = PINSEL_PORT_0;
	}
    PINSEL_ConfigPin(&adcpin);
}

    // adc prepheral init
// Rate: rate ADC conversion rate, should be <=200KHz
// channel: channel number, should be 0..7 
// Status : Enable or Disable
/*  CHANNEL_0 AD0 PIN 0.23 
	  CHANNEL_1 AD1 PIN 0.24 
	  CHANNEL_2 AD2 PIN 0.25 
	  CHANNEL_3 AD3 PIN 0.26 
	  CHANNEL_4 AD4 PIN 1.30 
	  CHANNEL_5 AD5 PIN 1.31 
	  CHANNEL_6 AD6 PIN 0.3 
	  CHANNEL_7 AD7 PIN 0.2 
	*/
/* ChannelNumber*/
#define CHANNEL_0	((0))
#define CHANNEL_1	((1))
#define CHANNEL_2	((2))
#define CHANNEL_3	((3))
#define CHANNEL_4	((4))
#define CHANNEL_5	((5))
#define CHANNEL_6	((6))
#define CHANNEL_7	((7))
/* Status */
// #define Enable	((1))
// #define Disable	((0))

void ADC_INIT(uint32_t Rate, uint8_t CHANNEL, FunctionalState State)
{
	ADC_Init(LPC_ADC,Rate);
	ADC_ChannelCmd(LPC_ADC,CHANNEL, State);
  ADC_IntConfig(LPC_ADC,CHANNEL,DISABLE);	
}

#include "include.h"

MessageBufferHandle_t PowerReadingBuffer;

MessageBufferHandle_t InputDataBuffer;

MessageBufferHandle_t CurrentQuoteBuffer;
MessageBufferHandle_t CurrentPowerConsumptionBuffer;
MessageBufferHandle_t CurrentChargeBuffer;

int main(void)
{
	/*system clock initialization*/
	MRCC_enuInitSysClock();

	/*global data containers initializations*/
	PowerReadingBuffer = xMessageBufferCreate(POWER_METER_MSG_LENGTH);

	InputDataBuffer = xMessageBufferCreate(sizeof(InputData));

	CurrentChargeBuffer = xMessageBufferCreate(sizeof(Tariff));
	CurrentQuoteBuffer = xMessageBufferCreate(sizeof(Quote));
	CurrentPowerConsumptionBuffer = xMessageBufferCreate(sizeof(u16));

	/*Initialization of modules*/
	PowerMeasureModule_voidInit();
	ActivateSerialModule_voidInit();
	UserInteractModule_voidInit();
	DisplayModule_voidInit();
	StatusModule_voidInit();
	RegistryModule_voidInit();

	/*OS Scheduler start*/
	vTaskStartScheduler();

	while(1)
	{
	}
	return 0;
}

/*#include "include.h"

int main(void)
{
	MRCC_enuInitSysClock();
	MRCC_enuEnableClock(APB1_BUS, TIM4_RCC);
	MRCC_enuEnableClock(APB2_BUS, GPIOA_RCC);
	MRCC_enuEnableClock(APB2_BUS, GPIOB_RCC);
	MRCC_enuEnableClock(APB2_BUS, USART1_RCC);
	HLCD_enuInit();

	GPIO_t Tx , Rx , led;
	led.GPIO_Pin = PIN6;
	led.GPIO_Port = GPIOB_Port;
	MGPIO_voidSetPinDirection(led, OUTPUT_SPEED_2MHZ_PP);
	Tx.GPIO_Pin = PIN9;
	Tx.GPIO_Port = GPIOA_Port;

	Rx.GPIO_Pin = PIN10;
	Rx.GPIO_Port = GPIOA_Port;

	MGPIO_voidSetPinDirection(Tx, OUTPUT_SPEED_2MHZ_AFPP);
	MGPIO_voidSetPinDirection(Rx, INPUT_FLOATING);
	u8 t;
	pu8 x = NULL;
	MUSART1_voidInit();

	MUSART1_voidTransmitStringln((pu8)"Date       Time 	 Power Consumed(KWm)	Price(L.E)");

	x = NULL;
	x = MUSART1_pu8ReceiveString(1000);
	HLCD_voidDisplayString(x, HLCD_u8NUmber_1);
	MUSART1_voidTransmitStringln(x);

	while(1)
	{

		if(t == 'E')
		{

			MGPIO_voidSetPinValue(led, HIGH);
			HLCD_enuWriteData(t, HLCD_u8NUmber_1);
			MUSART1_voidTransmitChar('*');
			MUSART1_voidTransmitChar(t);
			MUSART1_voidTransmitChar('*');
		}
		else if(t == 'D')
		{
			MGPIO_voidSetPinValue(led, LOW);
			HLCD_enuWriteData(t, HLCD_u8NUmber_1);
			MUSART1_voidTransmitChar('*');
			MUSART1_voidTransmitChar(t);
			MUSART1_voidTransmitChar('*');
		}

		//MUSART1_voidTransmit(t);
	}
	return 0;
}*/


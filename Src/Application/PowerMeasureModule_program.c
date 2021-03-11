/* Libraries */
#include "Libraries/LIB_STDTypes.h"

/*Application*/
#include <Application/PowerMeasureModule_interface.h>

/*FreeRtos*/
#include "FreeRtos/FreeRTOS.h"
#include "FreeRtos/task.h"
#include "FreeRtos/message_buffer.h"
#include "FreeRtos/stream_buffer.h"

/*HAL*/

/*MCAL*/
#include "MCAL/ADC_interface.h"
#include "MCAL/GPIO_interface.h"
#include "MCAL/RCC_interface.h"

extern MessageBufferHandle_t PowerReadingBuffer;

void PowerMeasureModule_voidInit(void)
{
	/*ADC H.W Initialization*/
	MRCC_enuEnableClock(APB2_BUS, ADC1_RCC);
	MRCC_enuEnableClock(APB2_BUS, GPIOA_RCC);
	MADC_voidInit();

	/*ADC Channel Init*/
	GPIO_t Pot_pin;
	Pot_pin.GPIO_Pin = PIN0; // ADC channel0
	Pot_pin.GPIO_Port = GPIOA_Port;
	MGPIO_voidSetPinDirection(Pot_pin, INPUT_ANALOG);

	MADC_voidStartConversion();//because in continous mood

	TaskHandle_t UpdateReadingTaskHandle;

	xTaskCreate(PowerMeasureModule_voidUpdateReadingEachSecond, "UpdateReading", configMINIMAL_STACK_SIZE, NULL, configMAX_PRIORITIES - 1, &UpdateReadingTaskHandle);
}

void PowerMeasureModule_voidUpdateReadingEachSecond(void* pvParameters)
{
	u16 u16Potentiometer = 0;
	Bool_t returnState = False;
	while(1)
	{
		u16Potentiometer = MADC_u16ReadConvertedData();
		returnState = xMessageBufferSend(PowerReadingBuffer ,(void*)u16Potentiometer ,sizeof(u16Potentiometer) ,0);
		/*check return status*/
		vTaskDelay(1000);
	}
}



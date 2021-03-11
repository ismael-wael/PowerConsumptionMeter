/* Libraries */
#include "Libraries/LIB_STDTypes.h"
#include "Libraries/LIB_BMNP.h"

/*Application*/
#include "Application/DisplayModule_interface.h"
#include "Application/UserInteractModule_interface.h"

/*FreeRtos*/
#include "FreeRtos/FreeRTOS.h"
#include "FreeRtos/task.h"
#include "FreeRtos/message_buffer.h"
#include "FreeRtos/stream_buffer.h"

/*HAL*/
#include "HAL/HLCD_config.h"
#include "HAL/HLCD_interface.h"
#include "HAL/HLCD_private.h"

/*MCAL*/
#include "MCAL/RCC_interface.h"

extern MessageBufferHandle_t CurrentQuoteBuffer;
extern MessageBufferHandle_t CurrentPowerConsumptionBuffer;
extern MessageBufferHandle_t CurrentChargeBuffer;

void DisplayModule_voidInit(void)
{
	HLCD_enuInit();

	TaskHandle_t DisplayCurrentData;

	xTaskCreate(DisplayModule_voidDisplayCurrentDataTask, "CurrentData", configMINIMAL_STACK_SIZE, NULL, 2, &DisplayCurrentData);

}

void DisplayModule_voidDisplayCurrentDataTask(void* pvParameters)
{
	size_t msgSize;
	Quote* Local_currentQuote;
	u16* Local_currentPowerConsumption;
	Tariff* Local_currentCharge;
	while(1)
	{
		msgSize = xMessageBufferReceive(CurrentQuoteBuffer ,(void*)Local_currentQuote ,sizeof(Quote) ,10);

		if( msgSize > 0 )
		{
			HLCD_enuGoToXY(HLCD_u8FirstRow,HLCD_u8FirstCol , HLCD_u8NUmber_1);
			HLCD_voidIntegerToString((u32)Local_currentQuote->u16LE, HLCD_u8NUmber_1);
			HLCD_enuWriteData('.', HLCD_u8NUmber_1);
			HLCD_voidIntegerToString((u32)Local_currentQuote->u16PT, HLCD_u8NUmber_1);
		}

		msgSize = xMessageBufferReceive(CurrentPowerConsumptionBuffer ,(void*)Local_currentPowerConsumption ,sizeof(u16) ,10);


		if( msgSize > 0 )
		{
			HLCD_enuGoToXY(HLCD_u8FirstRow,8 , HLCD_u8NUmber_1);
			HLCD_voidIntegerToString((u32)Local_currentPowerConsumption, HLCD_u8NUmber_1);
		}

		msgSize = xMessageBufferReceive(CurrentPowerConsumptionBuffer ,(void*)Local_currentCharge ,sizeof(Tariff) ,10);

		if( msgSize > 0 )
		{
			HLCD_enuGoToXY(HLCD_u8SecRow,HLCD_u8FirstCol , HLCD_u8NUmber_1);
			HLCD_voidIntegerToString((u32)Local_currentCharge->u8LE, HLCD_u8NUmber_1);
			HLCD_enuWriteData('.', HLCD_u8NUmber_1);
			HLCD_voidIntegerToString((u32)Local_currentCharge->u8PT, HLCD_u8NUmber_1);
		}

		vTaskDelay(1000);
	}
}





/* Libraries */
#include "Libraries/LIB_STDTypes.h"
#include "Libraries/LIB_BMNP.h"

/*Application*/
#include "Application/StatusModule_interface.h"

/*FreeRtos*/
#include "FreeRtos/FreeRTOS.h"
#include "FreeRtos/queue.h"
#include "FreeRtos/task.h"
#include "FreeRtos/semphr.h"

/*HAL*/
#include "HAL/Led_interface.h"
#include "HAL/Led_config.h"

/*MCAL*/
#include "MCAL/GPIO_interface.h"
#include "MCAL/RCC_interface.h"

static u8 u8Status;

void StatusModule_voidInit(void)
{
	u8Status = NORMAL;

	Hled_voidInit();

	TaskHandle_t CurrConsumptionTask;
	xTaskCreate(StatusModule_voidCurrentConsumptionStatusTask, "StatusTask", configMINIMAL_STACK_SIZE, NULL, 1, &CurrConsumptionTask);
}

void StatusModule_voidCurrentConsumptionStatusTask(void* pvParameters)
{
	while(1)
	{
		switch(u8Status)
		{
			case NORMAL :
				Hled_voidToggleLed(HLED_GREEN_NORMAL);
				Hled_voidLedOff(HLED_YELLOW_MODERATE);
				Hled_voidLedOff(HLED_RED_HIGH);
				Hled_voidLedOff(HBUZZER);
				break;

			case MODERATE :
				Hled_voidToggleLed(HLED_YELLOW_MODERATE);
				Hled_voidLedOff(HLED_GREEN_NORMAL);
				Hled_voidLedOff(HLED_RED_HIGH);
				Hled_voidLedOff(HBUZZER);
				break;

			case HIGH :
				Hled_voidToggleLed(HLED_RED_HIGH);
				Hled_voidToggleLed(HBUZZER);
				Hled_voidLedOff(HLED_GREEN_NORMAL);
				Hled_voidLedOff(HLED_YELLOW_MODERATE);
				break;

			default :
				break;
		}
		vTaskDelay(1000);
	}
}

void StatusModule_voidStatusSetter(u8 Local_u8Status)
{
	u8Status = Local_u8Status;
}

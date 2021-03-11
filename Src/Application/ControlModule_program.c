/* Libraries */
#include "Libraries/LIB_STDTypes.h"

/*Application*/
#include <Application/ControlModule_interface.h>

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

void ControlModule_voidInit(void)
{
	TaskHandle_t UpdateTaskHandle;
	xTaskCreate(ControlModule_voidUpdateTask, "UpdateTask", configMINIMAL_STACK_SIZE, NULL, configMAX_PRIORITIES-1, &UpdateTaskHandle);
	vTaskSuspend( ControlModule_voidUpdateTask );
}

void ControlModule_voidUpdateTask(void* pvParameters)
{
	while(1)
	{

	}
}




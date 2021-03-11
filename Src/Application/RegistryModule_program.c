/* Libraries */
#include "Libraries/LIB_STDTypes.h"
#include "Libraries/LIB_BMNP.h"

/*Application*/
#include "Application/RegistryModule_interface.h"

/*FreeRtos*/
#include "FreeRtos/FreeRTOS.h"
#include "FreeRtos/task.h"
#include "FreeRtos/message_buffer.h"
#include "FreeRtos/stream_buffer.h"

/*HAL*/

/*MCAL*/
#include "MCAL/RCC_interface.h"

void RegistryModule_voidInit(void)
{

}

void RegistryModule_voidSaveLastMinuteDataTask(void* pvParameters)
{
	while(1)
	{

	}
}



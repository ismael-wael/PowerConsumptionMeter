#ifndef INCLUDE_H_
#define INCLUDE_H_

/* Libraries */
#include "Libraries/LIB_STDTypes.h"
#include "Libraries/LIB_BMNP.h"
#include "Libraries/LIB_Macros.h"

/*Applicatin*/
#include <Application/ActivateSerialModule_interface.h>
#include <Application/DisplayModule_interface.h>
#include <Application/PowerMeasureModule_interface.h>
#include <Application/UserInteractModule_interface.h>

/*FreeRtos*/
#include "FreeRtos/FreeRTOS.h"
#include "FreeRtos/event_groups.h"
#include "FreeRtos/queue.h"
#include "FreeRtos/semphr.h"
#include "FreeRtos/task.h"
#include "FreeRtos/timers.h"
#include "FreeRtos/message_buffer.h"
#include "FreeRtos/stream_buffer.h"

/*HAL*/
#include "HAL/HLCD_config.h"
#include "HAL/HLCD_interface.h"
#include "HAL/Led_config.h"
#include "HAL/Led_interface.h"
#include "HAL/Hswitch_interface.h"

/*MCAL*/
#include "MCAL/ADC_interface.h"
#include "MCAL/AFIO_interface.h"
#include "MCAL/EXTI_interface.h"
#include "MCAL/GPIO_interface.h"
#include "MCAL/NVIC_interface.h"
#include "MCAL/RCC_interface.h"
#include "MCAL/Timer_interface.h"
#include "MCAL/USART_interface.h"

#endif /* INCLUDE_H_ */

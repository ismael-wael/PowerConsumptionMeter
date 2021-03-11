/* Libraries */
#include "Libraries/LIB_STDTypes.h"
#include "Libraries/LIB_BMNP.h"

/*Application*/
#include <Application/ActivateSerialModule_interface.h>
#include <Application/UserInteractModule_interface.h>

/*FreeRtos*/
#include "FreeRtos/FreeRTOS.h"
#include "FreeRtos/queue.h"
#include "FreeRtos/task.h"
#include "FreeRtos/semphr.h"

/*HAL*/
#include "HAL/Hswitch_interface.h"

/*MCAL*/
#include "MCAL/AFIO_interface.h"
#include "MCAL/EXTI_interface.h"
#include "MCAL/NVIC_interface.h"
#include "MCAL/GPIO_interface.h"
#include "MCAL/RCC_interface.h"

void ActivateSerialModule_voidInit(void)
{
	MRCC_enuEnableClock(APB2_BUS, GPIOB_RCC);
	MRCC_enuEnableClock(APB2_BUS, AFIO_RCC);

	Hswitch_voidInit();

	/*Enable Interrupt for Button*/
	MEXTI_voidEnableEXTI(LINE5);
	MNVIC_voidEnableInterrupt(EXTI5);
	AFIO_voidSetEXTIConfiguration(AFIO_EXTI5 ,GPIOB_Port);
	MEXTI_voidSetCallBack(ActivateSerialModule_voidActivateIsButtonStillPressedTask , LINE5);
	MEXTI_voidInit(LINE5, FALLING_EDGE);

	TaskHandle_t IsButtonPressed;
	xTaskCreate(ActivateSerialModule_voidIsButtonStillPressed, "CheckButton", configMINIMAL_STACK_SIZE, NULL, configMAX_PRIORITIES - 1, &IsButtonPressed);
	vTaskSuspend( IsButtonPressed );
}

void ActivateSerialModule_voidIsButtonStillPressed(void* pvParameters)
{
	u32 u32Counter = 0;
	ToggleState_t SwitchState = On;

	/*To make the task handle local, so that no one else can use it*/
	TaskHandle_t ThisTaskHandle = xTaskGetHandle((pu8)"CheckButton");
	TaskHandle_t InputTaskHandle = xTaskGetHandle((pu8)"UserInput");

	while(1)
	{
		SwitchState = Hswitch_voidGetSwitchState(SERIAL_SWITCH);
		if(SwitchState == Off)/*still pressed*/
		{
			u32Counter++;
			if(u32Counter == 150) /*if user kept pressing the button for 3 seconds [150 * 20 ms (periodicity)]*/
			{
				/*Enable USART CLK*/
				MRCC_enuEnableClock(APB2_BUS, USART1_RCC);
				u32Counter = 0;
				SwitchState = On; /*not pressed - default - pullup button*/

				/*Start Input Task*/
				vTaskResume( InputTaskHandle );
				vTaskSuspend( ThisTaskHandle );
			}
		}
		else
		{
			u32Counter = 0;
			vTaskSuspend( ThisTaskHandle );
		}
		vTaskDelay(20);//periodicity 20 msec
	}
}

/*if pushButton is pressed, an interrupt to EXTI9_5_IRQHandler will occur,
 * that function will be called when the interrupt occur
 * the function Activate : "ActivateCheckButtonStatus" Task*/
void ActivateSerialModule_voidActivateIsButtonStillPressedTask(void)
{
	/*To make the task handle local, so that no one else can use it*/
	TaskHandle_t IsButtonStillPressedTaskHandle = xTaskGetHandle( "CheckButton" );
	vTaskResume(IsButtonStillPressedTaskHandle);
}



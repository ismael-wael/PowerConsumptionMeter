/* Libraries */
#include "Libraries/LIB_STDTypes.h"
#include "Libraries/LIB_BMNP.h"

/*Application*/
#include <Application/UserInteractModule_interface.h>
#include <Application/ControlModule_interface.h>

/*FreeRtos*/
#include "FreeRtos/FreeRTOS.h"
#include "FreeRtos/task.h"
#include "FreeRtos/message_buffer.h"
#include "FreeRtos/stream_buffer.h"

/*HAL*/

/*MCAL*/
#include "MCAL/GPIO_interface.h"
#include "MCAL/RCC_interface.h"
#include "MCAL/USART_interface.h"

extern MessageBufferHandle_t InputDataBuffer;

void UserInteractModule_voidInit(void)
{
	MRCC_enuEnableClock(APB2_BUS, GPIOA_RCC);
	MRCC_enuEnableClock(APB2_BUS, USART1_RCC);
	/*UART Pin Initialization*/
	GPIO_t Tx , Rx;

	Tx.GPIO_Pin = PIN9;
	Tx.GPIO_Port = GPIOA_Port;

	Rx.GPIO_Pin = PIN10;
	Rx.GPIO_Port = GPIOA_Port;

	MGPIO_voidSetPinDirection(Tx, OUTPUT_SPEED_2MHZ_AFPP);
	MGPIO_voidSetPinDirection(Rx, INPUT_FLOATING);

	MUSART1_voidInit();

	TaskHandle_t InputTaskHandle;
	xTaskCreate(UserInteractModule_voidInput, "UserInput", configMINIMAL_STACK_SIZE, NULL, configMAX_PRIORITIES-1, &InputTaskHandle);
	vTaskSuspend( InputTaskHandle );

	TaskHandle_t PrintRetrievedDataHandle;
	xTaskCreate(UserInteractModule_voidPrintRetrievedData, "RetrievedData", configMINIMAL_STACK_SIZE, NULL, configMAX_PRIORITIES-1, &PrintRetrievedDataHandle);
	vTaskSuspend( PrintRetrievedDataHandle );

	MRCC_enuDisableClock(APB2_BUS, USART1_RCC);
}

void UserInteractModule_voidInput(void* pvParameters)
{
	pu8 pu8UserInput  = NULL;

	u8 u8Counter = 0;

	TaskHandle_t ThisTaskHandle;
	ThisTaskHandle = xTaskGetHandle( "UserInput" );

	while(1)
	{
		if(u8Counter == 0)
		{
			UserInteractModule_voidParseInputData((pu8)"1");
		}
		else if(u8Counter == 20)
		{
			/*Serial Port TimeOut mechanism : if no input for 20 seconds, serial port will shut down*/
			u8Counter = 0;//for the next time the task be called
			MRCC_enuDisableClock(APB2_BUS, USART1_RCC);/*disable UART : Saves power*/
			vTaskSuspend(ThisTaskHandle);
		}
				/*1 second timeout nearly*/
		pu8UserInput = MUSART1_pu8ReceiveString(1000);

		if(pu8UserInput[0] != '!')
		{
			u8Counter = 1; //reset the counter as long as user input data
			UserInteractModule_voidParseInputData(pu8UserInput);
		}
		else
		{
			u8Counter++;
		}

		vTaskDelay(1);//check input frequently [the more frequent the more chance to catch input as it's polling]
	}
}

void UserInteractModule_voidParseInputData(pu8 pu8InputString)
{
	static u16 u16PreviousInputs = NON;

	u8 u8FirstChar = pu8InputString[0] - 48;
	u16PreviousInputs = u16PreviousInputs*10 + u8FirstChar;

	switch(u16PreviousInputs)
	{
		case INTRO_DATA:
		case USER_MODE :
		case PRIVATE_MODE :
		case RECHARGE :
		case RETRIEVE_DATA :
		case ADJUST_POWER_LEVELS :
		case ADJUST_KWM_TARIFF :
		case ADJUST_TIME :
		case ADJUST_DATE :

			UserInteractModule_voidPrintData( u16PreviousInputs );
			break;
		default ://previous command

			if( u16PreviousInputs == RETRIEVE_DATA || u16PreviousInputs == ADJUST_KWM_TARIFF
			  || u16PreviousInputs == ADJUST_DATE || u16PreviousInputs == ADJUST_TIME )
			{
				u16PreviousInputs = u16PreviousInputs/10;
			}
			UserInteractModule_voidProcessInputData(pu8InputString , u16PreviousInputs);
			break;
	}
}

void UserInteractModule_voidProcessInputData(pu8 Local_pu8InputString , u16 u16CommandID)
{
	InputData QueueItem;
	TaskHandle_t RetrievedDataTaskHandle;

	/*Declared here because can't declare them inside cases
	 * only one of them will be actually used, others will be destroyed -local and it's a func not task-*/
	PowerLevel* powerLevelValuePtr;
	Tariff* tariffValuePtr;
	Date_t* datePtr;
	Time_t* timePtr;
	Quote* quoteptr;

	switch(u16CommandID)
	{
		case RETRIEVE_DATA :

			RetrievedDataTaskHandle = xTaskGetHandle( "RetrievedData" );
			vTaskResume(RetrievedDataTaskHandle);
			break;
		case ADJUST_LOW_POWER_LVL :

			powerLevelValuePtr = pvPortMalloc(sizeof(PowerLevel));
			powerLevelValuePtr->u16Start = UserInteractModule_boolExtractData(0 ,3, Local_pu8InputString);
			powerLevelValuePtr->u16End = UserInteractModule_boolExtractData(5 ,8, Local_pu8InputString);

			QueueItem.u16InputID = ADJUST_LOW_POWER_LVL;
			QueueItem.Value = powerLevelValuePtr;
			break;
		case ADJUST_MID_POWER_LVL :

			powerLevelValuePtr = pvPortMalloc(sizeof(PowerLevel));
			powerLevelValuePtr->u16Start = UserInteractModule_boolExtractData(0 ,3, Local_pu8InputString);
			powerLevelValuePtr->u16End = UserInteractModule_boolExtractData(5 ,8, Local_pu8InputString);

			QueueItem.u16InputID = ADJUST_MID_POWER_LVL;
			QueueItem.Value = powerLevelValuePtr;
			break;
		case ADJUST_HIGH_POWER_LVL :

			powerLevelValuePtr = pvPortMalloc(sizeof(PowerLevel));
			powerLevelValuePtr->u16Start = UserInteractModule_boolExtractData(0 ,3, Local_pu8InputString);
			powerLevelValuePtr->u16End = UserInteractModule_boolExtractData(5 ,8, Local_pu8InputString);

			QueueItem.u16InputID = ADJUST_HIGH_POWER_LVL;
			QueueItem.Value = powerLevelValuePtr;
			break;
		case ADJUST_KWM_TARIFF :

			tariffValuePtr = pvPortMalloc(sizeof(Tariff));
			tariffValuePtr->u8LE = UserInteractModule_boolExtractData(0 ,2, Local_pu8InputString);
			tariffValuePtr->u8PT = UserInteractModule_boolExtractData(4 ,6, Local_pu8InputString);

			QueueItem.u16InputID = ADJUST_KWM_TARIFF;
			QueueItem.Value = tariffValuePtr;
			break;
		case ADJUST_DATE :

			datePtr = pvPortMalloc(sizeof(Date_t));
			datePtr->u8Year = UserInteractModule_boolExtractData(0 ,3, Local_pu8InputString);
			datePtr->u8Month = UserInteractModule_boolExtractData(5 ,6, Local_pu8InputString);
			datePtr->u8Day = UserInteractModule_boolExtractData(8 ,9, Local_pu8InputString);

			QueueItem.u16InputID = ADJUST_DATE;
			QueueItem.Value = datePtr;
			break;
		case ADJUST_TIME :

			timePtr = pvPortMalloc(sizeof(Time_t));
			timePtr->u8Hour = UserInteractModule_boolExtractData(0 ,1, Local_pu8InputString);
			timePtr->u8Minute = UserInteractModule_boolExtractData(3 ,4, Local_pu8InputString);
			timePtr->u8Second = UserInteractModule_boolExtractData(6 ,7, Local_pu8InputString);

			QueueItem.u16InputID = ADJUST_TIME;
			QueueItem.Value = timePtr;
			break;
		case RECHARGE_20_LE :

			quoteptr = pvPortMalloc(sizeof(Quote));
			quoteptr->u16LE = UserInteractModule_boolExtractData(0 ,2, Local_pu8InputString);
			quoteptr->u16PT = UserInteractModule_boolExtractData(4 ,6, Local_pu8InputString);

			QueueItem.u16InputID = RECHARGE_20_LE;
			QueueItem.Value = quoteptr;
			break;
		case RECHARGE_50_LE :

			quoteptr = pvPortMalloc(sizeof(Quote));
			quoteptr->u16LE = UserInteractModule_boolExtractData(0 ,2, Local_pu8InputString);
			quoteptr->u16PT = UserInteractModule_boolExtractData(4 ,6, Local_pu8InputString);

			QueueItem.u16InputID = RECHARGE_50_LE;
			QueueItem.Value = quoteptr;
			break;
		case RECHARGE_100_LE :

			quoteptr = pvPortMalloc(sizeof(Quote));
			quoteptr->u16LE = UserInteractModule_boolExtractData(0 ,2, Local_pu8InputString);
			quoteptr->u16PT = UserInteractModule_boolExtractData(4 ,6, Local_pu8InputString);

			QueueItem.u16InputID = RECHARGE_100_LE;
			QueueItem.Value = quoteptr;
			break;
		default :

			UserInteractModule_voidPrintData(WRONG_DATA );
			break;
	}

	/*Make Sure Sth is written to message buffer*/
	xMessageBufferSend(InputDataBuffer ,(void*)QueueItem.Value ,QueueItem.u16InputID ,0);
	vTaskResume( ControlModule_voidUpdateTask );
}

void UserInteractModule_voidPrintData(u16 Local_u16Input )
{
	switch(Local_u16Input)
	{
		case INTRO_DATA:
			MUSART1_voidTransmitStringln((pu8)"*** Welcome ***");
			MUSART1_voidTransmitStringln((pu8)"1 - User Mode.");
			MUSART1_voidTransmitStringln((pu8)"2 - Private Mode.");
			MUSART1_voidTransmitStringln((pu8)"Enter your selected choice : ");
			break;

		case USER_MODE:
			MUSART1_voidTransmitStringln((pu8)"1 - Recharge.");
			MUSART1_voidTransmitStringln((pu8)"2 - Retrieve your power Consumption details since last charge.");
			MUSART1_voidTransmitStringln((pu8)"3 - Adjust Power Consumption Use Levels.");
			//MUSART1_voidTransmitStringln((pu8)"4 - Back.");
			MUSART1_voidTransmitStringln((pu8)"Enter your selected choice : ");
			break;

		case PRIVATE_MODE:
			MUSART1_voidTransmitStringln((pu8)"1 - Adjust KWm tariff.");
			MUSART1_voidTransmitStringln((pu8)"2 - Adjust Time.");
			MUSART1_voidTransmitStringln((pu8)"3 - Adjust Date.");
			//MUSART1_voidTransmitStringln((pu8)"4 - Back.");
			MUSART1_voidTransmitStringln((pu8)"Enter your selected choice : ");
			break;

/*		case PASSWORD:
			MUSART1_voidTransmitStringln((pu8)"Password : ");
			break;*/

		case RECHARGE :
			MUSART1_voidTransmitStringln((pu8)"1 - 20 L.E ");
			MUSART1_voidTransmitStringln((pu8)"2 - 50 L.E ");
			MUSART1_voidTransmitStringln((pu8)"3 - 100 L.E ");
			//MUSART1_voidTransmitStringln((pu8)"4 - Back.");
			MUSART1_voidTransmitStringln((pu8)"Enter Value (L.E) : ");
			break;

		case RETRIEVE_DATA :
			MUSART1_voidTransmitStringln((pu8)"Date    |  Time | Power Consumed(KWm) |	Price(L.E)");
			MUSART1_voidTransmitStringln((pu8)"___________________________________________________");
			break;

		case ADJUST_POWER_LEVELS :
			MUSART1_voidTransmitStringln((pu8)"1 - Normal use.");
			MUSART1_voidTransmitStringln((pu8)"2 - Moderate use.");
			MUSART1_voidTransmitStringln((pu8)"3 - High use.");
			//MUSART1_voidTransmitStringln((pu8)"4 - Back.");
			break;

		case ADJUST_KWM_TARIFF :
			MUSART1_voidTransmitStringln((pu8)"Power Consumption Tariff in(L.E,	P.T) fotmat: ");
			break;

		case ADJUST_TIME :
			MUSART1_voidTransmitStringln((pu8)"Time in(hour[0 -> 23] : minute[0 -> 59]) fotmat: ");
			break;

		case ADJUST_DATE :
			MUSART1_voidTransmitStringln((pu8)"Date in(Year / month / day) fotmat: ");
			break;

		default :
			MUSART1_voidTransmitStringln((pu8)"Wrong Input. please Try Again.");
			break;
	}
}

void UserInteractModule_voidPrintRetrievedData(void* pvParameters)
{
	while(1)
	{

	}
}

Bool_t UserInteractModule_boolStringCompare(pu8 pu8Src ,pu8 pu8Des)
{
	u8 u8Iterator = 0;
	while(pu8Des[u8Iterator] != '\0' && pu8Src[u8Iterator] != '\0' && pu8Src[u8Iterator] == pu8Des[u8Iterator])
	{
		asm("NOP");
	}

	if(pu8Des[u8Iterator] == '\0' && pu8Src[u8Iterator] == '\0')
		return True;
	else
		return False;
}

u32 UserInteractModule_boolExtractData(u8 u8Start ,u8 u8End, pu8 pu8String)
{
	u32 u32value = 0;
	for(u8 u8i = u8Start ; u8i <= u8End ; u8i++ )
	{
		u32value = u32value*10 + (pu8String[u8i] - 48);
	}
	return u32value;
}


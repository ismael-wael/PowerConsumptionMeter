/****************************************************************/
/*   Author             :    Ismael Wael 				    	*/
/*	 Date 				:    29 October 2020 					*/
/*	 Version 			:    1.0V 							 	*/
/*	 Description 		:    contain LCD Pins configuration		*/
/*             							[config.c] 				*/
/*								Link time configuration	in 		*/
/*									   build process			*/
/****************************************************************/

//GPIO
#include "MCAL/GPIO_interface.h"

//LCD
#include "HAL/HLCD_interface.h"
#include "HAL/HLCD_config.h"
#include "HAL/HLCD_private.h"

HLCD HLCDArrayOfLCD [ HLCD_u8NumberOfLCD ] =
{
	{ HLCD_u8MODE_4BIT  ,
	  0 ,0 ,0 ,0,
	  .HLCD_u8DataPin_4 = {PIN8 , GPIOA_Port},
	  .HLCD_u8DataPin_5 = {PIN9 , GPIOA_Port},
	  .HLCD_u8DataPin_6 = {PIN10 , GPIOA_Port},
	  .HLCD_u8DataPin_7 = {PIN11 , GPIOA_Port},

	  .HLCD_u8RegSelectPin = {PIN12 , GPIOB_Port},
	  .HLCD_u8ReadWritePin = {PIN13 , GPIOB_Port},
	  .HLCD_u8EnablePin    = {PIN14 , GPIOB_Port}
	}
};

/*****************************************************************/
/*********************** END OF PROGRAM **************************/
/*****************************************************************/



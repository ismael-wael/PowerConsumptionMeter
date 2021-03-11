#include <HAL/Hswitch_config.h>
#include <HAL/Hswitch_interface.h>
#include <Libraries/LIB_BMNP.h>
#include <Libraries/LIB_STDTypes.h>
#include <MCAL/GPIO_interface.h>



Hswitch_t const ArrOfSwitches[NO_OF_SWITCHES] =
{
		[SERIAL_SWITCH] = {
							.GPIO_tSwitch = {PIN8 , GPIOB_Port},
							.u8SwitchMode = INPUT_PULL_UP_OR_DOWN
					  }


};

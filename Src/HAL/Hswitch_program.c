#include <HAL/Hswitch_config.h>
#include <HAL/Hswitch_interface.h>
#include <Libraries/LIB_BMNP.h>
#include <Libraries/LIB_STDTypes.h>
#include <MCAL/GPIO_interface.h>


void Hswitch_voidInit(void)
{
	u8 u8Iterator;

	for(u8Iterator = 0 ; u8Iterator < NO_OF_SWITCHES ; u8Iterator++)
	{
		MGPIO_voidSetPinDirection(ArrOfSwitches[u8Iterator].GPIO_tSwitch, ArrOfSwitches[u8Iterator].u8SwitchMode);
	}
}

ToggleState_t Hswitch_voidGetSwitchState(u8 u8SwithID)
{
	ToggleState_t SwitchValue = MGPIO_u8GetPinValue(ArrOfSwitches[u8SwithID].GPIO_tSwitch);

	return	SwitchValue;
}




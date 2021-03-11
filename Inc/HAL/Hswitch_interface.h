#ifndef HAL_HSWITCH_INTERFACE_H_
#define HAL_HSWITCH_INTERFACE_H_

#include <HAL/Hswitch_config.h>
#include <MCAL/GPIO_interface.h>

typedef struct{
    GPIO_t GPIO_tSwitch;

    u8 u8SwitchMode;        // INPUT_ANALOG
}Hswitch_t;                 // INPUT_FLOATING
                            // INPUT_PULL_UP_OR_DOWN

extern const Hswitch_t ArrOfSwitches[NO_OF_SWITCHES];

void Hswitch_voidInit(void);

ToggleState_t Hswitch_voidGetSwitchState(u8 u8SwithID);

#endif

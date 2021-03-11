#ifndef APPLICATION_STATUSMODULE_INTERFACE_H_
#define APPLICATION_STATUSMODULE_INTERFACE_H_

#define NORMAL		0
#define MODERATE	100
#define HIGH		200

void StatusModule_voidInit(void);

void StatusModule_voidCurrentConsumptionStatusTask(void* pvParameters);

void StatusModule_voidStatusSetter(u8 Local_u8Status);

#endif /* APPLICATION_STATUSMODULE_INTERFACE_H_ */

#ifndef APPLICATION_REGISTRYMODULE_INTERFACE_H_
#define APPLICATION_REGISTRYMODULE_INTERFACE_H_

void RegistryModule_voidInit(void);

void RegistryModule_voidSaveLastMinuteDataTask(void* pvParameters);

void RegistryModule_voidRetrieveOldDataTask(void* pvParameters);

#endif /* APPLICATION_REGISTRYMODULE_INTERFACE_H_ */

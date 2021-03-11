#ifndef APPLICATION_USERINTERACTMODULE_INTERFACE_H_
#define APPLICATION_USERINTERACTMODULE_INTERFACE_H_

#define NON						0
#define INTRO_DATA				1
										/*User Mode*/
#define USER_MODE				11
//Recharge
#define RECHARGE				111
#define RECHARGE_20_LE			1111
#define RECHARGE_50_LE			1112
#define RECHARGE_100_LE			1113
#define RECHARGE_200_LE			1114
//Retrieve Data
#define RETRIEVE_DATA			112
//Adjust Power Levels
#define ADJUST_POWER_LEVELS		113
#define ADJUST_LOW_POWER_LVL	1131
#define ADJUST_MID_POWER_LVL	1132
#define ADJUST_HIGH_POWER_LVL	1133
										/*Private Mode*/
#define	PRIVATE_MODE			12
#define PASSWORD				120
#define ADJUST_KWM_TARIFF		121
#define ADJUST_TIME				122
#define ADJUST_DATE				123

#define WRONG_DATA				0xff

#define UI_QUEUE_SIZE			1

typedef struct{
	u16 u16InputID;
	void* Value;
}InputData;

typedef struct{
	u16 u16Start;
	u16 u16End;
}PowerLevel;

typedef struct{
	u8 u8PT;
	u8 u8LE;
}Tariff;

typedef struct{
	u16 u16PT;
	u16 u16LE;
}Quote;

void UserInteractModule_voidInit(void);

void UserInteractModule_voidInput(void* pvParameters);

void UserInteractModule_voidParseInputData(pu8 pu8InputString);
void UserInteractModule_voidProcessInputData(pu8 Local_pu8InputString , u16 u16CommandID);
void UserInteractModule_voidPrintData(u16 Local_u16Input );
void UserInteractModule_voidPrintRetrievedData(void* pvParameters);

Bool_t UserInteractModule_boolStringCompare(pu8 pu8Src ,pu8 pu8Des);
u32 UserInteractModule_boolExtractData(u8 u8Start ,u8 u8End, pu8 pu8String);

#endif /* APPLICATION_USERINTERACTMODULE_INTERFACE_H_ */

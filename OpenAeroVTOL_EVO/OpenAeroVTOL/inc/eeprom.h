/*********************************************************************
 * eeprom.h
 ********************************************************************/

//***********************************************************
//* Externals
//***********************************************************

extern bool Initial_EEPROM_Config_Load(void);
extern void Save_Config_to_EEPROM(void);
extern void Set_EEPROM_Default_Config(void);
extern void Load_eeprom_preset(uint8_t preset);

extern uint8_t JR[];
extern uint8_t FUTABA[];

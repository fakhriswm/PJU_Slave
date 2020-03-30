#include <Arduino.h>
#include <eeprom328.h>

class ConfigManager {
    
public :
    eeprom328 EEPROM328;

    uint8_t set_dim (uint8_t payload);
    uint8_t set_control (uint8_t payload);
    uint8_t read_dimmer();
    uint8_t read_control();
    void erase_all();
};
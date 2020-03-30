#include <ConfigManager.h>


uint8_t ConfigManager::set_dim (uint8_t payload){
    uint8_t value = payload;
    if((value>0) && (value<=100)){
        EEPROM328.set_dimmer(value);
        return value;
    }
    else {
        return 0;
    }
};

uint8_t ConfigManager::set_control (uint8_t payload){
    if(payload==0 || payload==1){
        EEPROM328.set_control(payload);
        delay(10);
        return payload;
  }
  else {
      return 0;
  }
}

uint8_t ConfigManager::read_dimmer(){
    uint8_t value = EEPROM328.read_dimmer();
    return value;
}

uint8_t ConfigManager::read_control(){
    uint8_t value = EEPROM328.read_control();
    return value;
}

void ConfigManager::erase_all(){
    EEPROM328.erase_all();
}
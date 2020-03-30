#include <Arduino.h>
#include <EEPROM.h>

class eeprom328 {
    
    public :
        void write_str(size_t addr, const String& value);
        String read_str(size_t addr);

        void erase(size_t addr, size_t len);
        void erase_all();

        void write_byte(size_t addr, uint8_t value);
        uint8_t read_byte(size_t addr);

        void set_control(uint8_t value);
        uint8_t read_control();
        void set_dimmer(uint8_t value);
        uint8_t read_dimmer();


          
        
};

// void write_str(size_t addr, const String& value, size_t len);  
// String read_str(size_t addr, const String& output, size_t len);    
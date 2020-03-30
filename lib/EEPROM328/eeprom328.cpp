#include <eeprom328.h>
#include <eeprom_table.h>

void eeprom328::erase_all(){
	for(int i=0; i<=EEPROM.length(); i++){
		EEPROM.write(i,0);
	}
}

void eeprom328::erase(size_t addr, size_t len)
{
	for(int i = 0; i < len; i++)
	{
		EEPROM.write(i,0);
	}
}

void eeprom328::write_byte(size_t addr, uint8_t value)
{
	EEPROM.write(addr, value);
}

uint8_t eeprom328::read_byte(size_t addr)
{
	return EEPROM.read(addr);
}

void eeprom328::write_str(size_t addr, const String& str){
	int idx = addr;
	erase(addr, str.length() + 1);
	for(int i=0; i<str.length(); i++){
		EEPROM.write(idx+i,str.charAt(i));
	}
}

String eeprom328::read_str(size_t addr){
	int idx = addr;
	String s = "";
	int i = 0;
	char d;
	do{
		d = EEPROM.read(idx+i);
		s+=String(d);
		i++;
		
	}while(d);
	return s;
}

//////////////////////////////// deprecated //////////////////////////////////////

void eeprom328::set_control(uint8_t value)
{
    write_byte(ee_control, value);
}

uint8_t eeprom328::read_control()
{
    return read_byte(ee_control);
}
void eeprom328::set_dimmer(uint8_t value)
{
    write_byte(ee_dimmer, value);
}

uint8_t eeprom328::read_dimmer()
{
    return read_byte(ee_dimmer);
};
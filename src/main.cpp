#include <Arduino.h>
#include <PZEM004Tv30.h>
#include <avr/wdt.h>
#include <ConfigManager.h>

ConfigManager confmanager;
PZEM004Tv30 pzem(6,7);

void(* resetFunc)(void) = 0;
String parse_string(String data, char separator, int index);
String get_data();

bool state = false;
uint8_t dimmer = 0;

void setup() {
  // put your setup code here, to run once:
   Serial.begin(115200);
   pinMode(5,OUTPUT);
   pinMode(13,OUTPUT);
   Serial.println("$RESTART");
   state = confmanager.read_control();
   digitalWrite(5,state);
   //Serial.println("control ="+(String)state);
   dimmer = confmanager.read_dimmer();
   //Serial.println("dimmer ="+(String)dimmer);  
   digitalWrite(13,LOW);
   wdt_enable(WDTO_2S);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    char c = Serial.read();
    if(c == '#'){
      String serial_string = Serial.readStringUntil('\r');
      String command = parse_string(serial_string,'?',0);
      uint8_t command_value = parse_string(serial_string,'?',1).toInt();
      if(command == "COM"){
        if(command_value == 0||command_value == 1){
          digitalWrite(5,command_value);
          if(command_value != confmanager.read_control()){
            confmanager.set_control(command_value);
          }
        }
      }
      else if(command == "GET"){
        if (command_value == "sensor"){
          String pzem_data = get_data();
          delay(10);
          if(pzem_data.length()>15){
            Serial.println("$POST?" + pzem_data);
          }
          else if(pzem_data == ""){
            Serial.println("$POST?");
          }
      }
    }
    else if(command == "RSTWH"){
      pzem.resetEnergy();
    }
    else if(command == "RSTMCU"){
      resetFunc();
    }
    delay(10);
    }
    else{
      return;
    }
  }
  digitalWrite(13,HIGH);
  delay(100);
  digitalWrite(13,LOW);
  delay(100);
  wdt_reset();
}

String parse_string(String data, char separator, int index){
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

String get_data(){
  String pzem_data = "";
  float voltage = pzem.voltage();
  if( !isnan(voltage) ){
    pzem_data += String(voltage);
    pzem_data += "|";
  }
  else{
    return "";
  }
  float current = pzem.current();
    if( !isnan(current) ){
      pzem_data += String(current);
      pzem_data += "|";
    } 
    else {
      return "";
    }
   float power = pzem.power();
    if( !isnan(power) ){
      pzem_data += String(power);
      pzem_data += "|";
    } 
    else {
      return "";
    }
   float energy = pzem.energy();
    if( !isnan(energy) ){
      pzem_data += String(energy);
      pzem_data += "|";
    } 
    else {
      return "";
    }
   float frequency = pzem.frequency();
    if( !isnan(frequency) ){
      pzem_data += String(frequency);
      pzem_data += "|";
    } 
    else {
      return "";
    }
   float pf = pzem.pf();
    if( !isnan(pf) ){
      pzem_data += String(pf);
    } 
    else {
      return "";
    }
    delay(10);
    return pzem_data;
}
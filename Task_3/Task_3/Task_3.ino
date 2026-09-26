#include "arduino_secrets.h" 
#include "thingProperties.h"

bool Red;
bool Green;
bool Blue;

void setup() {
  Serial.begin(9600);
  delay(1500); 
  initProperties();
  
  PinMode(Red, OUTPUT);
  PinMode(Green, OUTPUT);
  PinMode(Blue, OUTPUT);

  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
}

void onRedChange()  {
digitalWrite(Red, red);
}

void onBlueChange()  {
digitalWrite(Green, green);
}


void onGreenChange()  {
digitalWrite(Blue, blue);
}

-------------------------#include"arduino_Secrets.h"---------------------------

#define SECRET_SSID ""
#define SECRET_OPTIONAL_PASS ""
#define SECRET_DEVICE_KEY ""

-------------------------#include"thingProperties.h"---------------------------
#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

const char DEVICE_LOGIN_NAME[]  = "732bb388-82ae-468e-8ee5-af94cb49f150";

const char SSID[]               = SECRET_SSID;    
const char PASS[]               = SECRET_OPTIONAL_PASS;    
const char DEVICE_KEY[]  = SECRET_DEVICE_KEY;    

void onBlueChange();
void onGreenChange();
void onRedChange();

bool blue;
bool green;
bool red;

void initProperties(){

  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);
  ArduinoCloud.addProperty(blue, READWRITE, ON_CHANGE, onBlueChange);
  ArduinoCloud.addProperty(green, READWRITE, ON_CHANGE, onGreenChange);
  ArduinoCloud.addProperty(red, READWRITE, ON_CHANGE, onRedChange);

}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);

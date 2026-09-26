#include "arduino_secrets.h"
#include "thingProperties.h"
int LED = 0;

void setup() {
  Serial.begin(9600);
  delay(1500); 
  initProperties();
  pinMode(LED, OUTPUT);
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
}

void onLEDChange()  {
  digitalWrite(LED, lED);
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

void onLEDChange();

bool lED;

void initProperties(){

  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);
  ArduinoCloud.addProperty(lED, READWRITE, ON_CHANGE, onLEDChange);

}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);

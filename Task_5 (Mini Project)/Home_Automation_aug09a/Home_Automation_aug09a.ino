#include "arduino_secrets.h"  
#include "thingProperties.h"


Servo myservo;// create servo object to control a servo
// twelve servo objects can be created on most boards

// define the GPIO connected with Relays
#define RelayPin1 13  //D1
#define RelayPin2 4  //D2
#define RelayPin3 14 //D5
#define RelayPin4 12 //D6
#define Safty 10 //SD3

#define wifiLed   16   //D0

const int sensorPin = A0;
 
void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500); 

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  myservo.attach(15);  // attaches the servo on GIO2 to the servo object
  
  pinMode(RelayPin1, OUTPUT);
  pinMode(RelayPin2, OUTPUT);
  pinMode(RelayPin3, OUTPUT);
  pinMode(RelayPin4, OUTPUT);
  pinMode(Safty, OUTPUT);

  pinMode(wifiLed, OUTPUT);

  // Set up the sensor pin as an input
  pinMode(sensorPin, INPUT);

  //During Starting all Relays should TURN OFF
  digitalWrite(RelayPin1, HIGH);
  digitalWrite(RelayPin2, HIGH);
  digitalWrite(RelayPin3, HIGH);
  digitalWrite(RelayPin4, HIGH);

  digitalWrite(wifiLed, HIGH);  //Turn OFF WiFi LED
}

void loop() {
  ArduinoCloud.update();
  
//    manual_control(); Control relays manually

  int sensorValue = analogRead(sensorPin);
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);
  gAS = sensorValue;

  //Sensor Safty
  if (sensorValue > 75) { 
    switch_1 = false;
    switch_2 = false;
    switch_3 = false;
    switch_4 = false;
    digitalWrite(RelayPin1, LOW);
    digitalWrite(RelayPin2, LOW);
    digitalWrite(RelayPin3, LOW);
    digitalWrite(RelayPin4, LOW);
    myservo.write(180);
    delay(2000);
    digitalWrite(Safty, LOW);
  }
  else{
    digitalWrite(Safty, HIGH);
    myservo.write(0);
  }
  
  if (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(wifiLed, HIGH); //Turn OFF WiFi LED
  }
  else{
    digitalWrite(wifiLed, LOW); //Turn ON WiFi LED
  }
}



void onSwitch1Change()  {
    if (switch_1 == 1)
  {
    digitalWrite(RelayPin1, HIGH);
    Serial.println("Device1 ON");
  }
  else
  {
    digitalWrite(RelayPin1, LOW);
    Serial.println("Device1 OFF");
  }
}

void onSwitch2Change()  {
  if (switch_2 == 1)
  {
    digitalWrite(RelayPin2, HIGH);
    Serial.println("Device2 ON");
  }
  else
  {
    digitalWrite(RelayPin2, LOW);
    Serial.println("Device2 OFF");
  }
}


void onSwitch3Change()  {
  if (switch_3 == 1)
  {
    digitalWrite(RelayPin3, HIGH);
    Serial.println("Device2 ON");
  }
  else
  {
    digitalWrite(RelayPin3, LOW);
    Serial.println("Device3 OFF");
  }
}


void onSwitch4Change()  {
  if (switch_4 == 1)
  {
    digitalWrite(RelayPin4, HIGH);
    Serial.println("Device4 ON");
  }
  else
  {
    digitalWrite(RelayPin4, LOW);
    Serial.println("Device4 OFF");
  }
}

void onGASChange()  {
  // Add your code here to act upon GAS change
}

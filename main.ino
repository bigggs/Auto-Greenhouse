

#define WIFI_SSID "YOUR WIFI SSID HERE"
#define WIFI_PASSWORD "YOUR WIFI PASSWORD HERE"
#define FIREBASE_HOST "YOUR FIREBASE DB ID"
#define FIREBASE_AUTH "YOUR FIREBASE DB SECRET"
#include <ESP8266WiFi.h>                                                // esp8266 library
#include <FirebaseArduino.h>                                             // firebase library


int waterVal, manualIrrigation, manualSun, manualFan; //sensor value, manual watering, manual lighting, manual fans





void setup() {

//set range and frequency
 analogWriteRange(100); //instead of 0 - 1024
   analogWriteFreq(10000);
   
  //GPIO
  pinMode(16,INPUT); //Sensor (D0)
  pinMode(5,OUTPUT); //Relay IN1 (D1)
  pinMode(2,OUTPUT); //Relay IN4 (D2)


    
  Serial.begin(9600);
   //connect to wifi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  //sucess
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                                                      //print local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                                       // connect to firebase
  Serial.print("Connected to ");
  Serial.println(FIREBASE_HOST);
                 
                                        

}


void loop() {
  //Grab DB values
  Serial.println("Grabbing DB values");
  manualIrrigation = Firebase.getInt("manualWater");
  manualSun = Firebase.getInt("manualLight");
  manualFan = Firebase.getInt("manualWind");


          //Irrigation
  waterVal = digitalRead(16);  //Read data from soil moisture sensor  
  if(waterVal == LOW) 
  {
    //Pump ON
  digitalWrite(5,LOW); 
  }
  else
  {
    //Pump OFF
  digitalWrite(5,HIGH); 
  }
  delay(400);   
     
        //D2
        //light
    if (manualSun == 0) {                                                          // compare the input of led status received from firebase
    Serial.println("Manually turning light ON");   
        digitalWrite(2, HIGH);   
   
  }
  else   if (manualSun == 1) {                                                  // compare the input of led status received from firebase
    Serial.println("Manually turning light OFF"); 
    digitalWrite(2, LOW);  

  }
  /*
          //D1
        //manual watering
    if (manualIrrigation == 0) {                                                          // compare the input of led status received from firebase
    Serial.println("Manually filling tank with water");   
        digitalWrite(5, HIGH);   
   
  }
  else   if (manualIrrigation == 1) {                                                  // compare the input of led status received from firebase
    Serial.println("Manually watering turned off"); 
    digitalWrite(5, LOW);  

  }
  */

}

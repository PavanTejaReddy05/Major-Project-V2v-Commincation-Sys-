//#include <WiFi.h>
#include<SPI.h>
#include<LoRa.h>
#define SS 5
#define RST 14
#define DIO0 2


int gas=36;
int accelrometer=39;
int fire=17;
int button=4;
int buzzer=22;

void setup()
{
    pinMode(gas,INPUT);
    pinMode(fire,INPUT);
    pinMode(accelrometer,INPUT);
     pinMode(button,OUTPUT);
     pinMode(buzzer,OUTPUT);
   Serial.begin(9600);
  // Initialize the sensor (it is important to get calibration values stored on the device).

    while (!Serial);
   LoRa.setPins(SS, RST, DIO0);
  Serial.println("LoRa Sender"); 

  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  
  }  
}

void loop()
{
  int x = analogRead(gas);
  Serial.print("gas value: ");
  Serial.println(x);
  delay(1000);
  if(x>3300){
  Serial.println("FUEL LECKAGE");
  digitalWrite(buzzer,HIGH);
  delay(1000);
  }
  else{
     digitalWrite(buzzer,LOW);
  delay(1000);
  }
  
  int b=digitalRead(button);
  Serial.print("button value: ");
  Serial.println(b);
  delay(1000);
  if(b==1){
  Serial.println("EMERGENCY");
   digitalWrite(buzzer,HIGH);
  delay(1000);
  }
  else{
     digitalWrite(buzzer,LOW);
  delay(1000);
  }
 
  int y=digitalRead(fire);
  Serial.print("fire value: ");
  Serial.println(y);
  delay(1000);
   if(y==0){
  Serial.println("FIRE ALERT");
   digitalWrite(buzzer,HIGH);
  delay(1000);
  }
  else{
     digitalWrite(buzzer,LOW);
  delay(1000);
  }
   
int a = analogRead(accelrometer);
  Serial.print("accelrometer value: ");
  Serial.println(a);
  delay(1000);
if(a>3000){
  Serial.println("ACCDIENT");
   digitalWrite(buzzer,HIGH);
  delay(1000);
  }
  else{
     digitalWrite(buzzer,LOW);
  delay(1000);
  }
  

  String data = String(x)+":"+String(b)+":"+String(y)+":"+String(a);
  LoRa.beginPacket();
  LoRa.println(data);
  Serial.println(data);
  LoRa.endPacket();
  delay(1000);
}
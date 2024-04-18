#include<SPI.h>
#include<LoRa.h>

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#define SS D8
#define RST D0
#define DIO0 D3
int buzzer=D4;

String rcv,x,b,y,a;

String getStringPartByNr(String data, char separator, int index)
{
  int stringdata = 0;
  String datapart ="";
  for (int i=0; i<data.length()-1; i++)
  {
    if(data[i]==separator)
    {
      stringdata++;
    }
    else if (stringdata== index)
    {
      datapart.concat(data[i]);
    }
    else if (stringdata>index)
    {
      return datapart;
      break;
    }
  }
  return datapart;
}


void setup()
{
  pinMode(buzzer,OUTPUT);
  Serial.begin(9600);
  lcd.begin();
  // Turn on the blacklight and print a message.
 lcd.backlight();
 lcd.print(" MONITORING");
 delay(1000);

  // Turn on the blacklight and print a message.
  
  while(!Serial);
  Serial.println("LORA RECIEVER");
  LoRa.setPins(SS, RST, DIO0);
  if(!LoRa.begin(433E6))
  {
    Serial.println("STARTING LORA FAILED");
    while(1);
  }
 
}

void loop()
{
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet '");

    // read packet
    while (LoRa.available()) {
      //Serial.print((char)LoRa.read());
      
      String rcv = LoRa.readStringUntil('\n');
      Serial.println(rcv);
      
//        Serial.print("' with RSSI ");
  //  Serial.println(LoRa.packetRssi());
   String x = getStringPartByNr(rcv,':',0);
   String b = getStringPartByNr(rcv,':',1);
   String y = getStringPartByNr(rcv,':',2);
   String a = getStringPartByNr(rcv,':',3);
   
   //int mems = value1.toInt();
   int x1 = x.toInt(); 
   int b1 = b.toInt(); 
   int y1 = y.toInt();
   int a1 = a.toInt(); 
   
  Serial.print("gas value: ");
  Serial.println(x1);
  lcd.clear();
  lcd.print("gas: ");
  lcd.print(x1);
  delay(1000);
  Serial.print("button: ");
  Serial.println(b1);
  lcd.clear();
  lcd.print("button: ");
  lcd.print(b1);
  delay(1000);
  Serial.print("fire value: ");
  Serial.println(y1);
  lcd.clear();
  lcd.print("fire:");
  lcd.print(y1);
  delay(1000);
  Serial.print("angle: ");
  Serial.println(a1);
  lcd.clear();
  lcd.print("angle:");
  lcd.print(a1);
  delay(1000);
  if(x1>2500){
  Serial.println("gas leackage");
  lcd.clear();
  lcd.print("gas leackage:");
  digitalWrite(buzzer,HIGH);
  }
  else{
    digitalWrite(buzzer,LOW);
  }
  if(b1==1){
    Serial.println("EMERGENCY");
  lcd.clear();
  lcd.print("EMERGENCY");
  digitalWrite(buzzer,HIGH);
  delay(1000);
   digitalWrite(buzzer,LOW);
   delay(1000);
  }
  else{
    digitalWrite(buzzer,LOW);
     delay(1000);
  }
  if(y1==0){
   Serial.println("fire alert");
  lcd.clear();
  lcd.print("fire alert");
  digitalWrite(buzzer,HIGH);
  delay(1000);
   digitalWrite(buzzer,LOW);
   delay(1000);
  }
  else{
    digitalWrite(buzzer,LOW);
    delay(1000);
  }
  if(a1>3000){
   Serial.println("ACCDIENT");
  lcd.clear();
  lcd.print("ACCDIENT");
  digitalWrite(buzzer,HIGH);
  }
  else{
    digitalWrite(buzzer,LOW);
  }
 
   }
 }
}
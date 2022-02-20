//Sender 2
#include <Wire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup()
{
  Serial.begin(9600);
  Wire.begin(9); // join i2c bus on address 9
  Wire.onRequest(requestEvent); //method to send P2 guess to judge
  
}

void loop()
{
  delay(200);
}

void requestEvent()
{
  if (Serial.available() == 0){  //if there is no serial input
  	return;
  }
  while(Serial.available() > 0){ //if there is serial input
    char c = Serial.read();		 //read serial input from P2
    Serial.print("Input: ");
    Serial.println(c);			 //print P2 guess to serial monitor
    Wire.write(c); 				 //send over number
  }
  delay(500);

}


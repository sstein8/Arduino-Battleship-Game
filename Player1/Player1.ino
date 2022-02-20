//Sender 1
#include <Wire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //initialize lcd screen

void setup()
{
  Serial.begin(9600); //begin serial monitor
  Wire.begin(8); // join i2c bus on address 8
  Wire.onRequest(requestEvent); //method to send P1 guess to judge
}

void loop()
{
  delay(200);
}


void requestEvent()
{
  if (Serial.available() == 0) {	//if there is no serial input
  	return;
  }
  while(Serial.available() > 0){ 	//if there is serial input
    char c = Serial.read(); 		//read serial input from P1
    Serial.print("Input: ");
    Serial.println(c);				//print P1 guess to serial monitor
    Wire.write(c); 					//Send over that guess to the judge
  }
  
  delay(500);
  
}

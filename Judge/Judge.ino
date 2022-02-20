//Receiver / slave
#include <Wire.h>
#include <LiquidCrystal.h>

int receivedInt;
int hitCountP1 = 0;	//keeps track of how many boats P1 has sunk
int hitCountP2 = 0;	//keeps track of how many boats P1 has sunk


//Different states. Allows 2 players take one stpe each time

typedef enum STATES {
  PLAYER1,	//P1 turn
  PLAYER2,	//P2 turn
  DONE		//game over
} STATE;

STATE state;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);	//initialize lcd screem

void setup()
{
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  Wire.begin(8);				//P1 address
  Wire.begin(9);				//P2 address
  Serial.begin(9600);           // start serial for output
  //Wire.onRequest(requestEvent); // register event
  setShips();					//Method to initialize pre-made boards for each plauer (3x3 board)
  lcd.begin(16, 2);				//turn on screen
  lcd.setCursor(0,0);
  lcd.print("!Battle Ship!");	//Print starting message to lcd
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Guess positions btw");	//Display game instructions
  lcd.setCursor(0,1);
  lcd.print("1-9 on 3x3 board");
  delay(4000);
  state = PLAYER1;				//Begin with player 1's turn
}

void loop()
{
  
  //cases for players
   switch (state) {
   
     case PLAYER1:
     	request1();
     	break;
     case PLAYER2:
     	request2();
     	break;
     
     case DONE:
     
     lcd.clear();
  	 lcd.setCursor(0,0);
     lcd.print("GAME OVER");	//When the game is over, this message will be displayed on lcd
     delay(500);
     break;
   
   }
}

void setShips()
{
  //create premade boards for each player
  int board1[3] = {2,4,7}; //player 1's "ship positions"
  int board2[3] = {1,3,6}; //player 2's "ship positions"  
}


void request1()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Player 1 move");
  
  Wire.requestFrom(8, 1); 			//signaling P1 to send over a number 1-9
  int available = Wire.available();	
  if(available == 1)				//received the number from P1
  {
    receivedInt = Wire.read();
  	receivedInt -= 48;				//convert to int
  }
  if(receivedInt >0 && receivedInt < 9)
  {
  	Serial.print("Player 1 Guesses: ");	//Display what P1 Guessed
  	Serial.println(receivedInt);		
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Player 1 Guesses");
    lcd.setCursor(0,1);
    lcd.print(receivedInt);
    delay(2000); 
  }
  if(receivedInt == 1 || receivedInt == 3 || receivedInt == 6)
  {
    Serial.print("Player 2's Ship hit at position ");
    Serial.println(receivedInt);
    hitCountP1++; //increase the count of ships P1 hit
    lcd.clear();
  	lcd.setCursor(0,0);
  	lcd.print("P2 Ship Hit!");
    digitalWrite(9, HIGH);		//When P2's boat is hit, flash green LED
    delay(1000);
    digitalWrite(9, LOW);
    delay(400);
    state = PLAYER2;			//Now P2's turn
  }
  else if(receivedInt == 2 || receivedInt == 4 || receivedInt == 5 || receivedInt == 7 || receivedInt == 8 || receivedInt == 9)
  {
    Serial.println("Player 1 Missed");
    lcd.clear();
  	lcd.setCursor(0,0);
  	lcd.print("P1 Missed");
    delay(400);
    state = PLAYER2;			//Now P2's Turn
  }
  else{
  	state = PLAYER1;
  }
  if(hitCountP1 == 3)	//All boats have been hit
  {
    Serial.println("ALL OF PLAYER 2's BOATS SUNK");
    Serial.println("PLAYER 1 WINS");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("PLAYER 1 WINS");
    delay(1000);
    state = DONE;
  }
  
  delay(500);
}

void request2()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Player 2 move");
  
  Wire.requestFrom(9, 1);			//Request input from P2
  int available = Wire.available();
  if(available == 1)				//If an int has been sent over from P2
  {
    receivedInt = Wire.read();
  	receivedInt -= 48;				//Convert to int
  }
  if(receivedInt >0 && receivedInt < 9)
  {
  	Serial.print("Player 2 Guesses: ");	//Display what P2 Guessed
  	Serial.println(receivedInt);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Player 2 Guesses");
    lcd.setCursor(0,1);
    lcd.print(receivedInt);
    delay(2000); 
  }
  if(receivedInt == 2 || receivedInt == 4 || receivedInt == 7)
  {
    Serial.print("Player 1's Ship hit at position ");
    Serial.println(receivedInt);
    hitCountP2++;		//increase the count of ships P2 hit
    lcd.clear();
  	lcd.setCursor(0,0);
  	lcd.print("P1 Ship Hit!");		//Display when P2 hits P1's ship
    digitalWrite(10, HIGH);			//Flash red LED when P2 hits P1's ship
    delay(1000);
    digitalWrite(10, LOW);
    delay(400);
    state = PLAYER1;
  }
  else if(receivedInt == 1 || receivedInt == 3 || receivedInt == 5 || receivedInt == 6 || receivedInt == 8 || receivedInt == 9)
  {
    Serial.println("Player 2 Missed");
    lcd.clear();
  	lcd.setCursor(0,0);
  	lcd.print("P2 Missed");
    delay(400);
    state = PLAYER1;		//P1 turn now
  }
  else{
  	state = PLAYER2;
  }
  
  if(hitCountP2 == 3)		//P2 wins by hitting all P1's boats
  {
    Serial.println("ALL OF PLAYER 1's BOATS SUNK");
    Serial.println("PLAYER 2 WINS");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("PLAYER 2 WINS");
    delay(1000);
    state = DONE;			//game over
  }
  
  delay(500);

}

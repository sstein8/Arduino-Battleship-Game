Arduino Battleship Game

<img width="818" alt="Screen Shot 2022-02-20 at 12 24 36 AM" src="https://user-images.githubusercontent.com/76801679/154829709-42a3b759-e394-484d-b2a4-220404502b92.png">

The purpose of this game is to guess the other player’s positioning of the ships to sink them. The first player that sinks the other player’s three boats wins.
To implement this game we have two player arduinos and one judge. The player’s will send guesses to the judge and the judge will analyze the inputs as a hit or miss. The game begins at player 1. If player 1 guesses a position where player 2 has a ship placed, it will display on the lcd that player 2’s ship has been hit. If a ship is hit then a corresponding LED will also light up. If Player 2 is hit, the green LED will light up, and if Player 1 is hit, the red LED will light up. There is also a counter for each player of how many of their opponents ships they have destroyed. If player one guesses a position where player 2 does not have any boats placed, it will display on the lcd that they missed. After player 1 goes, it is player 2’s turn where they will perform the same actions. The game will continue until one of the players wins (having destroyed all 3 of the opponents’ boats).

# Szemeredi

## Overview 

Szemeredi's game is a 2-player colouring game played on a subset of natural numbers {1,...,N}.

This software is used to test strategies in Computer vs Computer scenarios, which was developed originally for a course 
"Combinatorial Number Theory" at Warsaw University of Technology but it got expanded later.

## Game rules

Each round first player picks a pair of numbers from the subset, then second player colors one of them in their own color.

Roles are reversed and next round starts.

Game is played until there is a valid move( there are at least two numbers that hasn't been already coloured) or until
there isn't a monochromatic arithmetic sequence of length K.

If there is no valid move, game is drawn.
If there is a winning sequence then player who last coloured wins.

If you know what is the actual name of this game feel free to hit me up I would love to know.
## How to use

To add a new strategy you have to add a derived class of ColorAI/ChooseAI, which overrides a base function ```GetMove()```.
Then add it to colorArray/chooseArray as ```make<*>``` function so that it will be displayed when ```SetUpGame()``` is called.

```SetUpGame()``` takes input at runtime about size of board and lenght of monochromatic sequence, which AI each player will choose,
as well as number of rounds that should be played.

```Game::PlayAllGame()``` should be then called. It will return ```GameData``` with a history of all games.

```GameData``` has few statistical functions such as number of games won by given player, number of draws, average length of game.

Szemeredi.cpp contains a example program that gets game parameters then displays scores for each player.

/*
Author: alesbe
Date: April 2022

Description: Classic blackjack made in a C++ console. This project was made to practice classes
and general concepts.

License: No licence, totally free!

Observations: At this moment is not very well optimized and has some bugs, sometimes the program tries to acces a vector index out of range
but im trying to figure out why atm.

TODO:
- Fix bugs: Out of range vectors, sometimes method calculateDeckValue() gives an incorrect value (maybe the mistake is in the ace calculation)
- Add save/load system (Save current purse in a file, maybe add stadistics?)
- dealerBank is not being used actually
- Check if the user has enough purse to bet
- Maybe change how the dealer round is displayed
- Check if player's bet is higher than minBet
*/

#include <iostream>
#include "Game.h"

// Clear console
#if defined (_WIN32)
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

using namespace std;

int main() {

	int option;

	cout << R"(  ____  _            _    _            _    
 |  _ \| |          | |  (_)          | |   
 | |_) | | __ _  ___| | ___  __ _  ___| | __
 |  _ <| |/ _` |/ __| |/ / |/ _` |/ __| |/ /
 | |_) | | (_| | (__|   <| | (_| | (__|   < 
 |____/|_|\__,_|\___|_|\_\ |\__,_|\___|_|\_\
                        _/ |                
                       |__/                 )" << "\n\n";

	cout << "Welcome to Blackjack in C++, please select an option: \n\n";

	cout << "1.- New game\n";
	cout << "2.- Load game\n";
	cout << "3.- Exit\n\n";

	cout << "Option number: ";
	cin >> option;

	system(CLEAR);

	if (option == 1) {
		cout << "Do you want to configure the game or play with defaults? \n\n";

		cout << "1.- Default\n";
		cout << "2.- Custom\n\n";

		cout << "Option: ";
		cin >> option;

		system(CLEAR);

		// Default game
		if (option == 1) {
			Game game;
			game.startGame();
		}

		// Custom game
		else {
			int playerBank, dealerBank, minBet;

			cout << "Player bank: ";
			cin >> playerBank;

			cout << "Dealer bank: ";
			cin >> dealerBank;

			cout << "Minimum bet: ";
			cin >> minBet;

			Game game(playerBank, dealerBank, minBet);
			game.startGame();
		}
	}

	if (option == 2) {
		cout << "Load game";
	}

	if (option == 3) {
		return 0;
	}

	return 0;
}
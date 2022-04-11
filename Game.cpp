#include "Game.h"

/*
================
Constructor
================
*/
Game::Game(int playerBank, int dealerBank, int minBet, bool singleDeck) {
	this->playerBank = playerBank;
	this->dealerBank = dealerBank;
	this->minBet = minBet;
	this->singleDeck = singleDeck;
}

/*
================
Private methods
================
*/

// Game state
void Game::resetGame() {
	// Reset decks
	deck.clear();
	playerDeck.clear();
	dealerDeck.clear();

	// Populate main deck
	for (int card : cards) {
		deck.push_back(card);
	}

	// Reset state
	currBet = 0;
	firstRound = true;
	roundFinished = false;
	playerLost = false;
	playerValue = 0;
	dealerValue = 0;
}

void Game::playerWins() {
	system(CLEAR);
	int option;

	std::cout << "You won " << currBet << "$!\n\n";
	playerBank += currBet*2;
	dealerBank -= currBet;

	std::cout << "Your deck: ";
	for (int card : playerDeck) {
		std::cout << " [" << parseCards(card) << "]";
	}
	std::cout << "\nDeck value: " << playerValue << "\n\n";

	std::cout << "Dealer's deck: ";
	for (int card : dealerDeck) {
		std::cout << " [" << parseCards(card) << "]";
	}
	// Only show dealer deck value if he played too (player loses without dealer playing if he went over 21)
	if (dealerDeck.size() > 1) {
		std::cout << "\nDeck value: " << dealerValue;
	}

	std::cout << "\n\n1.- Play again\n";
	std::cout << "2.- Exit\n\n";

	std::cout << "Option: ";
	std::cin >> option;

	switch (option)
	{
	case 1:
		return;
	case 2:
		playAgain = false;
		return;
	default:
		break;
	}
}

void Game::dealerWins() {
	system(CLEAR);
	int option;

	playerLost = true;

	std::cout << "Oh no! You lost " << currBet << "$!\n\n";
	dealerBank += currBet;

	std::cout << "Your deck: ";
	for (int card : playerDeck) {
		std::cout << " [" << parseCards(card) << "]";
	}
	std::cout << "\nDeck value: " << calculateDeckValue(playerDeck) << "\n\n";

	std::cout << "Dealer's deck: ";
	for (int card : dealerDeck) {
		std::cout << " [" << parseCards(card) << "]";
	}
	// Only show dealer deck value if he played too (player loses without dealer playing if he went over 21)
	if (dealerDeck.size() > 1) {
		std::cout << "\nDeck value: " << calculateDeckValue(dealerDeck);
	}

	std::cout << "\n\n1.- Play again\n";
	std::cout << "2.- Exit\n\n";

	std::cout << "Option: ";
	std::cin >> option;

	switch (option)
	{
	case 1:
		return;
	case 2:
		playAgain = false;
		return;
	default:
		break;
	}
}

void Game::tieWins() {
	system(CLEAR);
	int option;

	std::cout << "It was a tie! You recover your bet\n\n";
	playerBank += currBet;

	std::cout << "Your deck: ";
	for (int card : playerDeck) {
		std::cout << " [" << parseCards(card) << "]";
	}
	std::cout << "\nDeck value: " << calculateDeckValue(playerDeck) << "\n\n";

	std::cout << "Dealer's deck: ";
	for (int card : dealerDeck) {
		std::cout << " [" << parseCards(card) << "]";
	}
	std::cout << "\nDeck value: " << calculateDeckValue(dealerDeck);

	std::cout << "\n\n1.- Play again\n";
	std::cout << "2.- Exit\n\n";

	std::cout << "Option: ";
	std::cin >> option;

	switch (option)
	{
	case 1:
		return;
	case 2:
		playAgain = false;
		return;
	default:
		break;
	}
}

// Utils
int Game::pickRandomCard() {
	int randomNum, pickedCard;

	randomNum = randomNumRange(0, deck.size());
	pickedCard = deck[randomNum];
	deck.erase(deck.begin() + randomNum);

	return pickedCard;
}

int Game::randomNumRange(int min, int max) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(min, max);

	return distr(gen);
}

std::string Game::parseCards(int card) {
	std::string parsedCard;

	// If card is a letter
	if (card > 10) {
		parsedCard = char(card);
		return parsedCard;
	}
	else {
		parsedCard = std::to_string(card);
		return parsedCard;
	}
}

int Game::calculateDeckValue(std::vector<int> deck) {
	int totalValue = 0, numOfAces = 0;

	for (int card : deck) {
		// 65 = A ("A" could be 1 or 11)
		if (card == 65) {
			numOfAces++;
			continue;
		}

		if (card >= 10) {
			totalValue += 10;
		}
		else {
			totalValue += card;
		}
	}

	// Check for aces
	if (numOfAces) {
		switch (numOfAces)
		{
		// If there is only 1 ace, check if fits with value 11, else fit with value 1
		case 1:
			if ((totalValue + numOfAces * 11) <= 21) {
				totalValue += 21;
			}
			else {
				totalValue += 1;
			}
			break;
		case 2:
			// If there is only 2 aces in the deck and no more cards sum the 2 aces as 11s, else calculate the best fit
			if (totalValue == 0) {
				totalValue += 11 * numOfAces;
			}
			else {
				if (totalValue + 11 + 1 <= 21) {
					totalValue += 11 + 1;
				}
				else {
					totalValue += 1 + 1;
				}
			}
			break;
		default:
			break;
		}
	}
	
	return totalValue;
}

int Game::checkHighestDeck(std::vector<int> firstDeck, std::vector<int> secondDeck) {
	if (calculateDeckValue(firstDeck) > calculateDeckValue(secondDeck)) {
		return 1;
	}
	else {
		return 2;
	}
}

// Rounds
void Game::playerRound() {
	int option;

	system(CLEAR);
	std::cout << "Purse: " << playerBank << "$ \n";
	std::cout << "Bet: " << currBet << "$ \n\n";

	std::cout << "==============================\n\n";

	if (firstRound) {
		std::cout << "Minimum bet: " << minBet << "$ \n\n";

		std::cout << "Bet: ";
		std::cin >> currBet;
		playerBank -= currBet;

		// Give player first 2 cards
		playerDeck.push_back(pickRandomCard());
		playerDeck.push_back(pickRandomCard());

		// Give dealer one card covered and one uncovered
		dealerDeck.push_back(pickRandomCard());

		firstRound = false;

		return;
	}

	std::cout << "Dealer hand: " << "[" << parseCards(dealerDeck[0]) << "] [" << "?]\n"; // We add ? to simulate the hidden card
	std::cout << "Your hand: ";
	for (int card : playerDeck) {
		std::cout << "[" << parseCards(card) << "] ";
	}

	std::cout << "\n\n1.- Hit\n";
	std::cout << "2.- Stand\n";
	std::cout << "3.- Double \n\n";

	std::cout << "Option: ";
	std::cin >> option;

	switch (option)
	{
	case 1:
		actHit();
		break;
	case 2:
		actStand();
		break;
	case 3:
		actDouble();
		break;
	default:
		break;
	}

	return;
}

void Game::dealerRound() {
	int option;

	// Round loop
	do
	{
		system(CLEAR);

		std::cout << "- Dealer round -\n\n";

		std::cout << "Dealer's deck: ";
		for (int card : dealerDeck) {
			std::cout << "[" << parseCards(card) << "] ";
		}

		std::cout << "\n\nPress enter to show the next card...";
		getchar();

		dealerDeck.push_back(pickRandomCard());
	} while (calculateDeckValue(dealerDeck) < 17);

	// When deck value is over 17, check win, lose or tie
	playerValue = calculateDeckValue(playerDeck);
	dealerValue = calculateDeckValue(dealerDeck);

	if (dealerValue > 21) {
		playerWins();
	}

	if (playerValue == dealerValue) {
		tieWins();
	}

	if (checkHighestDeck(playerDeck, dealerDeck) == 1) {
		playerWins();
	}
	else {
		dealerWins();
	}

	return;
}

// Actions
void Game::actHit() {
	playerDeck.push_back(pickRandomCard());

	playerValue = calculateDeckValue(playerDeck);

	if (playerValue > 21) {
		dealerWins();
		roundFinished = true;
	}
	else if (playerValue == 21) {
		playerWins();
		roundFinished = true;
	}

	return;
};

void Game::actDouble() {
	currBet *= 2;
	playerDeck.push_back(pickRandomCard());

	playerValue = calculateDeckValue(playerDeck);

	if (playerValue > 21) {
		dealerWins();
		roundFinished = true;
	}
	else if (playerValue == 21) {
		playerWins();
		roundFinished = true;
	}

	roundFinished = true;
};

void Game::actStand() {
	playerValue = calculateDeckValue(playerDeck);

	if (playerValue > 21) {
		dealerWins();
		roundFinished = true;
	}
	else if (playerValue == 21) {
		playerWins();
		roundFinished = true;
	}

	roundFinished = true;
};
/*
================
Public methods
================
*/

void Game::startGame() {
	do
	{
		system(CLEAR);

		// Clear game before starting a new game
		resetGame();

		// Player round loop
		do
		{
			playerRound();
		} while (!roundFinished);

		// Check if player already lost before dealer round
		if (playerLost) {
			continue;
		}

		// Do dealer round
		dealerRound();
	} while (playAgain);

	return;
}
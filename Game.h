#pragma once
#include <array>
#include <vector>
#include <iostream>
#include <random>
#include <string>

// Clear console
#if defined (_WIN32)
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

class Game
{
private:
	// Consts
	const std::array<int, 52> cards{ 2, 3, 4, 5, 6, 7, 8, 9, 10, 'J', 'Q', 'K', 'A', 2, 3, 4, 5, 6, 7, 8, 9, 10, 'J', 'Q', 'K', 'A' , 2, 3, 4, 5, 6, 7, 8, 9, 10, 'J', 'Q', 'K', 'A' , 2, 3, 4, 5, 6, 7, 8, 9, 10, 'J', 'Q', 'K', 'A' };
	
	// Initialization
	bool singleDeck;
	int playerBank, dealerBank, minBet;

	// Game vars
	std::vector<int> deck, playerDeck, dealerDeck;
	bool firstRound = true;
	int currBet = 0;
	int playerValue = 0, dealerValue = 0;

	// Game state
	int playAgain = true;
	bool roundFinished = false;
	bool playerLost = false;
	void resetGame();
	void playerWins();
	void dealerWins();
	void tieWins();

	// Utils
	std::string parseCards(int card);
	int pickRandomCard();
	int randomNumRange(int min, int max);
	int calculateDeckValue(std::vector<int> deck);
	int checkHighestDeck(std::vector<int> firstDeck, std::vector<int> secondDeck);


	// Rounds
	void playerRound();
	void dealerRound();

	// Actions
	void actHit();
	void actDouble();
	void actStand();

public:
	Game(int playerBank = 3000, int dealerBank = 10000, int minBet = 50, bool singleDeck = true);
	void startGame();
};


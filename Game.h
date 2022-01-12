#pragma once

#include"Player.h"
#include"Space.h"
#include <vector>
#include <string>

class Game {
public:
	Game();

	void initializeBoard();

	void initializeSpaces();

	void displayBoard();
	void displayRules();
	void setInfo(Player player);
	void doStuffBeforeRoll(Player& player);
	std::vector<Player> setup();
	int setupAI(int possibleAI);
	bool setupCheats();

	void enableAlwaysRollDoubles();
	void enableRollOneTwo();
	void assignPropRandomly();
	void assignPropFirstPlayer();

	void generateAI(int numAI);
	void askForPlayerNames(int numPlayers);
	void setCards();
	void setGameOutput(std::vector<std::string> newOutput);
	int getNumPlayers();
	int rollDie();
	Player play();
	void runPlayerTurn(Player& player);
	void letPlayerRoll(Player& player);
	void movePlayer(Player& player);
	bool runDoublesCase(Player& player, int jail);
	void runPlayerTurnJail(Player& player);
	int calculateAssets(Player& player);
	std::vector<Space*> getSpaces();
	void battle(Player& player1, Player& player2);
	void attackProp(Player& player1, Player& propOwner);

private:
	std::string board;
	std::vector<std::string> boardInfo;
	std::vector<std::string> playerInfo;
	std::vector<std::string> gameOutput;
	std::string rules;
	std::vector<Space*> spaces;
	std::vector<std::string> colorSets;
	int inGame;
	std::vector<Player> curPlayers;
};

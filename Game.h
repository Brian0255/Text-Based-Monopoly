#pragma once

#include"Player.h"
#include"Space.h"
#include <vector>
#include <string>

class Game
{
public:
	Game();
	
	void displayBoard();
	void displayRules();
	void setInfo(Player player);
	void doStuffBeforeRoll(Player& player,std::vector<Player>& players);
	std::vector<Player> setup();
	void setCards();
	void setGameOutput(std::vector<std::string> newOutput);
	int getNumPlayers(std::vector<Player>& players);
	int rollDie();
	Player play(std::vector<Player>& curPlayers);
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
};

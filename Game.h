#pragma once

#include"Player.h"
#include"Space.h"
#include <vector>
#include <string>

class Game {
public:
	Game();

	static std::vector<std::string> playerMobChoices;
	static std::vector<std::string> mobChoices;
	static std::vector<std::string> battleDialogChoices;

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
	bool runPlayerBattleTurn(Player& player2, Player& player1, bool player1Turn);
	void rewardBattleWinner(Player& player2, Player& player1);
	void preBattleDialog(Player& player1, Player& player2, bool mobAttack = false);
	void setupHPDefense(Player& player1, Player& player2);
	void attackProp(Player& player1, Player& propOwner);

	bool runMobBattleTurn(bool& playerTurn, Player& mob, Player& player, Space* prop);

	void awardMobDefending(Player& player);

	void attackPlayerAsMob(Player& player, Player& mob, Space* prop);

	void awardPlayerMobProperty(Player& player, Space* prop);

	void damageMob(Player& mob, Player& player);

	void setupHPDefensePropAttack(Player& player, Player& mob);

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

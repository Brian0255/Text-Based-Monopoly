#pragma once

#include"Player.h"
#include"Space.h"
#include <vector>
#include <string>

class Game
{
public:
	//the default constructor for the game
	Game();

	//flushes the output, then displays the board using the player info it was las set to with setInfo(player)
	void displayBoard();

	//displays text which refers the player to "RULES.TXT"
	void displayRules();

	//sets the Player Information section correctly
	void setInfo(Player player);

	//brings up a menu with several choices that the player can do before their turn starts
	void doStuffBeforeRoll(Player& player,std::vector<Player>& players);

	//sets up the game and returns a vector of players in the current game
	std::vector<Player> setup();

	//sets up all the community, chance, and collectable cards using the CardHandler class and its static attributes
	void setCards();

	//sets the game output to a vector of strings
	void setGameOutput(std::vector<std::string> newOutput);

	//gets the number of players currently not bankrupt
	int getNumPlayers(std::vector<Player>& players);

	//returns a random number from 1-6
	int rollDie();

	//plays the game and returns the winner
	Player play(std::vector<Player>& curPlayers);

	//calculates the assets on the player(10% on cash, houses, hotels, and turrets)
	int calculateAssets(Player& player);

	//gets the vector of board spaces
	std::vector<Space*> getSpaces();

	//allows battle between 2 players
	void battle(Player& player1, Player& player2);

	//allows the battling between a player and a property
	void attackProp(Player& player1, Player& propOwner);

private:
	//a long string of ASCII art with a bunch of newline characters
	std::string board;

	//the information about the current space the player is on
	std::vector<std::string> boardInfo;

	//the information about the player whose turn it is
	std::vector<std::string> playerInfo;

	//the output which is below the board and player info
	std::vector<std::string> gameOutput;

	//just a very short string of rules(idk if I actually ended up using this)
	std::string rules;

	//a vector of pointers to the parent class Space, which Property and TaxSpace inherit from
	std::vector<Space*> spaces;

	//a vector of string representing the color sets for properties(MAGENTA, BLUE, etc.)
	std::vector<std::string> colorSets;
};
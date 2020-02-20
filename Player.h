#pragma once
#include<vector>
#include<string>
#include"Card.h"

class Player
{
public:
	//the constructor for player
	Player(std::string name, int cash, int currentSpot, bool inJail, bool onRailroad, bool AI);

	//default constructor for properties not yet owned by an actual player
	Player();

	//everything below are various getters and setters for the attributes in the player
	int getCurrentSpot();
	void setCurrentSpot(int newSpot);

	int getRoll();
	void setRoll(int newRoll);

	std::string getName();

	int getCash();
	void setCash(int newCash);

	std::vector<Card> getCards();
	void setCards(std::vector<Card> newCards);

	void addCash(int amt);
	void deductCash(int amt);
	bool canDeduct(int amt);

	void setBankruptcy(bool newBankruptcy);
	bool isBankrupt();

	bool isAI();

	int getDoublesRolled();
	void setDoublesRolled(int newRoll);

	int getJailAttempts();
	void addJailAttempt();

	bool canRoll();
	void setRolling(bool newRolling);

	bool isInJail();
	void setJail(bool newJail);

	int getDefense();
	void setDefense(int newDefense);

	int getHP();
	void setHP(int newHP);

	bool isBidding();
	void setBidding(bool newBidding);

	void setOneTwo(bool newOneTwo);
	bool getOneTwo();

	void setAlwaysDoubles(bool newDoubles);
	bool getAlwaysDoubles();

	bool canDoubleRoll();
	void setDoubleRoll(bool newDoubleRoll);
private:
	//the player's name
	std::string name;

	//the player's cash on hand
	int cash;

	//where the player is
	int currentSpot;

	//the player's HP
	int hp;

	//the player's defense
	int defense;

	//the player's roll(1-6)
	int roll;

	//how many times the player has tried to roll doubles to get out of jail
	int jailAttempts;

	//how many times the player has rolled doubles
	int doublesRolled;

	//represents if the player is in jail
	bool inJail;

	//represents if the player is on a railroad
	bool onRailroad;

	//represents if the player is AI controlled
	bool AI;

	//represents if the player can roll
	bool doRoll;

	//represents if the player is bankrupt
	bool bankrupt;

	//represents if the player is currently bidding
	bool bidding;

	//represents if the always roll doubles cheat is active
	bool alwaysDoubles;

	//represents if the roll a 1 and a 2 cheat is active
	bool alwaysOneTwo;

	//represents if the player's roll should be doubled from using a collectable
	bool doubleRoll;

	//a vector of collectable cards the player has
	std::vector<Card> cards;
};
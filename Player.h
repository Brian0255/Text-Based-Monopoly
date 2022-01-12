#pragma once
#include<vector>
#include<string>
#include"Card.h"

class Player {
public:
	Player(std::string name, int cash, int currentSpot, bool inJail, bool onRailroad, bool AI);
	Player();


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
	std::string name;
	int cash;
	int currentSpot;
	int hp;
	int defense;
	int roll;
	int jailAttempts;
	int doublesRolled;
	bool inJail;
	bool onRailroad;
	bool AI;
	bool doRoll;
	bool bankrupt;
	bool bidding;
	bool alwaysDoubles;
	bool alwaysOneTwo;
	bool doubleRoll;
	std::vector<Card> cards;
};

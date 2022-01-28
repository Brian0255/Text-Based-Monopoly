#pragma once
#include"Space.h"
#include"Player.h"
#include<string>
#include"Game.h"

class SpaceHandler {
public:
	SpaceHandler(Game&, Player&, std::vector<Player>&, Space*);

	void handle();

	void handleJailSpace();

	void handleTaxSpace();
	void handleLuxuryTax();

	void handleIncomeTax();
	void handleIncomeTaxAI();
	void handleIncomeTaxPlayer(int assets);

	bool checkPlayerBankrupt(Player& player);

	void handlePropertySpace(int cost);
	void handleUnownedProperty(int cost);

	void doBid(int cost);
	void runBidCycle(std::vector<Player*>& bidders, int& currentBid, bool& doneBidding, int cost);
	void askAIKeepBidding(int cost, int& currentBid, Player& bidder);
	void askPlayerKeepBidding(int& currentBid, Player& bidder);
	void setBidWinner(Player& bidder, int& currentBid, bool& doneBidding);
	void askAIParticipateBid(Player& other, int currentBid, std::vector<Player*>& bidders);
	void askPlayerParticipateBid(Player& other, int currentBid, std::vector<Player*>& bidders);

	void askAIToPurchase(int cost, bool& biddable);
	void askPlayerToPurchase(int cost, bool& biddable);

	void handleOwnedProperty(int cost);
	void handleOwnedByAnother(int cost);
	void ownedByAnotherAIChoice(int rent);
	void ownedByAnotherPlrChoice(int cost, int rent, Player* owner);

	void attackProperty();

	void payRent(int rent, Player* owner);
	int getRent(Player* owner, std::vector<Space*> spaces);

	void checkForABattle();
private:
	Game& game;
	Player& curPlayer;
	std::vector<Player>& curPlayers;
	Space* curSpace;
};

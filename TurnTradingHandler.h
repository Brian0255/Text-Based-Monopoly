#pragma once
#include "TurnHandler.h"
#include"Trade.h"
#include<vector>
class TurnTradingHandler {
public:
	TurnTradingHandler(Game& game, Player& player, std::vector<Player>& curPlayers, std::vector<Space*>& spaces,
		std::vector<std::string>& gameOutput, std::vector<std::string>& colorSets);

	void handle();
	bool tradeWithPlayer(std::vector<Player>& tradeable, int choice);
	void askAIAcceptTrade(Trade& trade);
	void askPlayerAcceptTrade(Trade& trade);
	void displayCompleteTradeOffer(Trade& trade);
	void selectPropertiesToGet(Trade& trade);
	void selectPropertyGet(Trade& trade, int toRemove);
	void selectPropertiesToOffer(Trade& trade);
	void selectPropertyOffer(Trade& trade, int toRemove);
	void displayCurrentlyOfferingProperties(Trade trade);
	void displayOtherPlayerProperties(Trade trade);
	void displayTradeablePlayers(std::vector<Player>& tradeable);
private:
	Game& game;
	Player& player;
	std::vector<Player>& curPlayers;
	std::vector<Space*>& spaces;
	std::vector<std::string>& gameOutput;
	std::vector<std::string>& colorSets;
};


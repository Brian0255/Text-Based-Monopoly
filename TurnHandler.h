
#pragma once

#include"Game.h"
#include<vector>
class TurnHandler {
public:
	void handle();

	bool handleTurnAI();
	bool handleTurnPlayer();

	void handleCollectableUsagePlayer();
	void handleCollectableCard(Card& toUse, std::vector<Card>& collectables, int ans);
	void displayCollectableCards(std::vector<Card>& collectables);

	void handleRailroadChoicePlayer();
	void warpPlayerByRailroad(std::vector<Space*>& availRailroads, int ans);
	void setupAvailableRailroads(std::vector<Space*>& railroads, std::vector<Space*>& availRailroads);
	void displayRailroadChoices(std::vector<Space*>& availRailroads);

	void handleMortgageLiftingPlayer();
	void liftMortgage(int cost, std::vector<Space*>& mortProp, int choice);
	void displayMortgagedProperty(std::vector<Space*>& mortProp);

	void handlePropertyMortgagingPlayer();
	void mortgageProperty(std::vector<Space*>& prop, int choice, int mortValue);
	int calculateMortgageValue(std::vector<Space*>& prop, int choice);

	void displayOwnedProperties(std::vector<Space*>& prop);

	void displayChoices();

	TurnHandler(Game& game, Player& player, std::vector<Player>& curPlayers, std::vector<Space*>& spaces,
		std::vector<std::string>& gameOutput, std::vector<std::string>& colorSets);
private:
	Game& game;
	Player& player;
	std::vector<Player>& curPlayers;
	std::vector<Space*>& spaces;
	std::vector<std::string>& gameOutput;
	std::vector<std::string>& colorSets;
};

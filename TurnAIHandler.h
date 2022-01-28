#pragma once
#include "TurnHandler.h"
class TurnAIHandler {
public:
	TurnAIHandler(Game& game, Player& player, std::vector<Player>& curPlayers, std::vector<Space*>& spaces,
		std::vector<std::string>& gameOutput, std::vector<std::string>& colorSets);

    bool handle();

	void useCollectables();
	void useCollectable(Card& card, std::vector<Card>& AIcards);

	void buildTurrets();
	void buildTurret(Space*& prop);

	void buildHotels();
	void buildHotel(Space*& prop);

	void buildHouses();
	void buildHousesOnSet(std::vector<Space*>& propSet);
	void buildHouse(Space*& prop);

	void liftMortgages();
	void liftMortgage(int cost, Space*& prop);

	void mortgageProperties();
	void mortgageProperty(std::vector<Space*>& AIprop, int randIndex, int AImortValue);
	int calculateMortgageValue(std::vector<Space*>& AIprop, int randIndex);

private:
	Game& game;
	Player& player;
	std::vector<Player>& curPlayers;
	std::vector<Space*>& spaces;
	std::vector<std::string>& gameOutput;
	std::vector<std::string>& colorSets;
};


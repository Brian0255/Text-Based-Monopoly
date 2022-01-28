#pragma once
#include "TurnHandler.h"
#include<vector>
class TurnBuildingHandler {
public:
    void handle();
	bool handleTurretBuildingPlayer();

	void buildTurretPlayer(int costToBuild, Space* toBuild);
	void displayTurretBuildingChoices(std::vector<Space*>& prop);

	bool handleHotelBuildingPlayer();
	void handleHotelSetBuildingPlayer(std::vector<std::vector<Space*>>& sets, int ans);
	void displayHotelSetChoicesPlayer(std::vector<Space*>& propSet);
	void buildHotelPlayer(int costToBuild, Space* toBuild);
	bool checkIfHotelExists(Space* toBuild);

	void displayBuildableSetsPlayer(std::vector<std::vector<Space*>>& sets);
	bool handleHouseBuildingPlayer();
	void handleHouseSetBuildingPlayer(std::vector<std::vector<Space*>>& sets, int ans);
	void buildHousePlayer(int costToBuild, Space* toBuild);
	bool checkIfEvenBuilding(std::vector<Space*>& propSet, Space* toBuild);
	void displayBuildableHousesInSet(std::vector<Space*>& propSet);

	void displayedOwnedSetsPlayer();
	void displayBuildingChoices();

	TurnBuildingHandler(Game& game, Player& player, std::vector<Player>& curPlayers, std::vector<Space*>& spaces,
		std::vector<std::string>& gameOutput, std::vector<std::string>& colorSets);
private:
	Game& game;
	Player& player;
	std::vector<Player>& curPlayers;
	std::vector<Space*>& spaces;
	std::vector<std::string>& gameOutput;
	std::vector<std::string>& colorSets;
};


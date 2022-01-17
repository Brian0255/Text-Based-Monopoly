
#pragma once

#include<vector>

class TurnHandler {
public:
	void handle();
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

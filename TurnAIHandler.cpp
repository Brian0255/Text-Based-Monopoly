#include "TurnAIHandler.h"
#include<iostream>
#include"Windows.h"
#include"Utilities.h"
#include"CardHandler.h"
using namespace std;

bool TurnAIHandler::handle() {
	game.displayBoard();
	std::cout << "AI " << player.getName() << " is deciding what to do before they roll..." << endl;
	Sleep(3000);
	mortgageProperties();
	liftMortgages();
	buildHouses();
	buildHotels();
	buildTurrets();
	useCollectables();
	return true;
}

void TurnAIHandler::useCollectables() {
	vector<Card> AIcards = player.getCards();
	if (!AIcards.empty()) {
		for (auto& card : AIcards) {
			if (card.getEffect() != "getOutJail" || card.getEffect() != "doubleRoll") {
				useCollectable(card, AIcards);
			}
			else if (card.getEffect() == "getOutJail" && player.isInJail()) {
				useCollectable(card, AIcards);
			}
			else if (card.getEffect() == "doubleRoll" && !player.isInJail()) {
				useCollectable(card, AIcards);
			}
			AIcards.clear();
			player.setCards(AIcards);
		}
	}
}

void TurnAIHandler::useCollectable(Card& card, std::vector<Card>& AIcards) {
	std::cout << player.getName() << " is going to use a collectable." << endl;
	Sleep(3000);
	CardHandler handler = CardHandler(curPlayers, game, player, card);
	handler.handle();
	player.setCards(AIcards);
}

void TurnAIHandler::buildTurrets() {
	game.displayBoard();
	vector<Space*> properties = Utilities::getProperty(player, spaces);
	if (!properties.empty()) {
		//AI only builds a turret if they have at least 3* the cost of a turret
		for (auto& prop : properties) {
			//3 * the turret cost is the same as 6 * the house cost
			bool enoughCash{ player.getCash() > prop->getHouseCost() * 6 };
			bool hasTurretAlready{ prop->getNumTurrets() == 1 };
			if (enoughCash && !hasTurretAlready)
				buildTurret(prop);
		}
	}
}

void TurnAIHandler::buildTurret(Space*& prop) {
	prop->setNumTurrets(1);
	player.deductCash(prop->getHouseCost() * 2);
	game.setInfo(player);
	game.displayBoard();
	std::cout << player.getName() << " built a turret on " << prop->getName() << ".\n";
	Sleep(2000);
}

void TurnAIHandler::buildHotels() {
	game.displayBoard();
	vector<vector<Space*>> AIhotSets = Utilities::getHotellableSets(player, spaces, colorSets);
	if (!AIhotSets.empty()) {
		//AI only builds a hotel if they have at least 3* the cost of the house
		for (auto& propSet : AIhotSets) {
			for (auto& prop : propSet) {
				if (prop->getNumHotels() < 1) {
					//houses cost the same as hotels
					bool enoughCash{ player.getCash() > prop->getHouseCost() * 3 };
					bool hasHotelAlready{ prop->getNumHotels() == 1 };
					if (enoughCash && !hasHotelAlready)
						buildHotel(prop);
				}
			}
		}
	}
}

void TurnAIHandler::buildHotel(Space*& prop) {
	prop->addHotel();
	player.deductCash(prop->getHouseCost());
	game.setInfo(player);
	game.displayBoard();
	std::cout << player.getName() << " built a hotel on " << prop->getName() << ".\n";
	Sleep(2000);
}

void TurnAIHandler::buildHouses() {
	bool doneHousing{ false };
	game.displayBoard();
	vector<vector<Space*>> AIsets = Utilities::getOwnedSets(player, spaces, colorSets);
	if (!AIsets.empty()) {
		for (auto& propSet : AIsets) {
			doneHousing = true;
			for (auto& prop : propSet) {
				if (prop->getNumHouses() < 4) {
					doneHousing = false;
				}
			}
			buildHousesOnSet(propSet);
		}
	}
}

void TurnAIHandler::buildHousesOnSet(std::vector<Space*>& propSet) {
	bool doneBuildingHouses{ false };
	while (!doneBuildingHouses) {
		for (auto& prop : propSet) {
			if (prop->getNumHouses() < 4) {
				bool canBuild{ true };
				if (player.getCash() > prop->getHouseCost() * 3) {
					for (auto& otherProp : propSet) {
						bool different{ otherProp->getName() != prop->getName() };
						bool unevenBuilding{ otherProp->getNumHouses() < prop->getNumHouses() };
						if (different && unevenBuilding)
							canBuild = false;
					}
					if (canBuild) {
						buildHouse(prop);
					}
				}
				else {
					doneBuildingHouses = true;
				}
			}
			else {
				doneBuildingHouses = true;
			}
		}
	}
}

void TurnAIHandler::buildHouse(Space*& prop) {
	prop->addHouse();
	player.deductCash(prop->getHouseCost());
	game.setInfo(player);
	game.displayBoard();
	std::cout << player.getName() << " built a house on " << prop->getName() << ".\n";
	Sleep(2000);
}

void TurnAIHandler::liftMortgages() {
	bool doneLiftingMortgages{ false };
	vector<Space*> AImortProp = Utilities::getMortgagedProperty(player, spaces);
	if (!AImortProp.empty()) {
		//AI only lifts mortgage if they have 5* the cost to lift it
		for (auto& prop : AImortProp) {
			int cost = (prop->getCost() / 2) + (prop->getCost() / 10);
			if (player.getCash() > (cost * 5)) {
				liftMortgage(cost, prop);
			}
		}
	}
}

void TurnAIHandler::liftMortgage(int cost, Space*& prop) {
	std::cout << player.getName() << " is going to lift a mortgage." << endl;
	Sleep(2000);
	player.deductCash(cost);
	prop->setMortgage();
	game.setInfo(player);
	game.displayBoard();
	std::cout << player.getName() << " lifted their mortgage on " << prop->getName() << ".\n";
	Sleep(3000);
}

void TurnAIHandler::mortgageProperties() {
	vector<Space*> AIprop = Utilities::getProperty(player, spaces);
	game.displayBoard();
	bool  broke{ player.getCash() < 100 };
	bool doneMortgaging{ AIprop.empty() || !broke };
	while (!doneMortgaging) {
		std::cout << player.getName() << " is going to mortgage a property." << endl;
		Sleep(2000);
		int randIndex = (AIprop.size() > 1) ? rand() % (AIprop.size() - 1) : 0;
		int AImortValue = calculateMortgageValue(AIprop, randIndex);
		mortgageProperty(AIprop, randIndex, AImortValue);
		doneMortgaging = (AIprop.empty() || !broke);
	}
}

void TurnAIHandler::mortgageProperty(std::vector<Space*>& AIprop, int randIndex, int AImortValue) {
	AIprop[randIndex]->setMortgage();
	player.addCash(AImortValue);
	AIprop[randIndex]->setNumHouses(0);
	AIprop[randIndex]->setNumHotels(0);
	AIprop[randIndex]->setNumTurrets(0);
	game.setInfo(player);
	game.displayBoard();
	std::cout << player.getName() << " received " << AImortValue << " dollars for mortgaging " << AIprop[randIndex]->getName() << ".\n";
	Sleep(3000);
}

int TurnAIHandler::calculateMortgageValue(std::vector<Space*>& AIprop, int randIndex) {
	int AImortValue = AIprop[randIndex]->getCost() / 2;
	int numHouses = AIprop[randIndex]->getNumHouses();
	int numHotels = AIprop[randIndex]->getNumHotels();
	int numTurrets = AIprop[randIndex]->getNumTurrets();
	for (int i{ 0 }; i < numHouses; ++i) {
		AImortValue += AIprop[randIndex]->getHouseCost() / 2;
	}
	for (int i{ 0 }; i < numHotels; ++i) {
		AImortValue += AIprop[randIndex]->getHouseCost() / 2;
	}
	for (int i{ 0 }; i < numTurrets; ++i) {
		AImortValue += AIprop[randIndex]->getHouseCost();
	}
	return AImortValue;
}

TurnAIHandler::TurnAIHandler(Game& g, Player& plr, std::vector<Player>& curPlrs, std::vector<Space*>& s, std::vector<std::string>& gameOut, std::vector<std::string>& cSets)
	: game(g), player(plr), curPlayers(curPlrs), spaces(s), gameOutput(gameOut), colorSets(cSets) {
}
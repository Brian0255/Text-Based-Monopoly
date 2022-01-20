#include "TurnBuildingHandler.h"
#include"TurnHandler.h"
#include"Utilities.h"
#include"Windows.h"
#include<iostream>

using namespace std;

void TurnBuildingHandler::handle() {
	bool doneEditing{ false };
	while (!doneEditing) {
		displayBuildingChoices();
		int choice = Utilities::getIntInRange("Please choose an option. If you want to exit, type 0: ", 0, 3);
		switch (choice) {
		case 0: //exit
			doneEditing = true;
			break;
		case 1:
			doneEditing = handleHouseBuildingPlayer();
			break;
		case 2:
			doneEditing = handleHotelBuildingPlayer();
			break;
		case 3:
			doneEditing = handleTurretBuildingPlayer();
		}
	}
}

bool TurnBuildingHandler::handleTurretBuildingPlayer() {
	bool doneEditing{ false };
	vector<Space*> prop = Utilities::getProperty(player, spaces);
	if (prop.empty()) {
		std::cout << "You do not have any property to build turrets on..." << endl;
		Sleep(6000);
	}
	else {
		bool doneTurreting{ false };
		while (!doneTurreting) {
			displayTurretBuildingChoices(prop);
			int ans = Utilities::getIntInRange("Please select which property you want to build a turret on.\nIf you wish to exit, type 0: ", 0, prop.size());
			doneTurreting = (ans == 0);
			if (!doneTurreting) {
				Space* toBuild = prop[ans - 1];
				if (toBuild->getNumTurrets() == 0) {
					int costToBuild = toBuild->getHouseCost() * 2;
					if (player.canDeduct(costToBuild)) {
						buildTurretPlayer(costToBuild, toBuild);
					}
					else {
						std::cout << "\nYou lack sufficient funds to build a turret. Please select another property." << endl;
						Sleep(3000);
					}
				}
				else {
					std::cout << "\nTurret already built on that property.\nPlease select another." << endl;
					Sleep(3000);
				}
			}
		}
	}
	return doneEditing;
}

void TurnBuildingHandler::buildTurretPlayer(int costToBuild, Space* toBuild) {
	player.deductCash(costToBuild);
	toBuild->setNumTurrets(1);
	std::cout << "\nTurret was successfully built." << endl;
	Sleep(2000);
}

void TurnBuildingHandler::displayTurretBuildingChoices(std::vector<Space*>& prop) {
	system("CLS");
	std::cout << "Here are the properties you can build turrets on:" << endl;
	for (size_t i{ 0 }; i < prop.size(); ++i) {
		std::cout << to_string(i + 1) << " - " << prop[i]->toString() << "Number of turrets: " << prop[i]->getNumTurrets() << "|" << endl << endl;
	}
}

bool TurnBuildingHandler::handleHotelBuildingPlayer() {
	vector<vector<Space*>> sets = Utilities::getHotellableSets(player, spaces, colorSets);
	bool doneEditing{ false };
	if (sets.empty()) {
		std::cout << "You do not own any sets of properties that have the max number of houses built on every property..." << endl;
		Sleep(6000);
	}
	else {
		bool doneWithHotels{ false };
		while (!doneWithHotels) {
			system("CLS");
			bool doneBuildingHotelsOnSet{ false };
			displayBuildableSetsPlayer(sets);
			int ans = Utilities::getIntInRange("Please select which color of property you want to build a hotel on.\nIf you wish to exit, type 0: ", 0, sets.size());
			if (ans == 0) {
				doneWithHotels = true;
				doneBuildingHotelsOnSet = true;
			}
			else {
				handleHotelSetBuildingPlayer(sets, ans);
			}
		}
	}
	return doneEditing;
}

void TurnBuildingHandler::handleHotelSetBuildingPlayer(std::vector<std::vector<Space*>>& sets, int ans) {
	bool doneBuildingHotelsOnSet{ false };
	while (!doneBuildingHotelsOnSet) {
		system("CLS");
		vector<Space*> propSet = sets[ans - 1];
		displayHotelSetChoicesPlayer(propSet);
		int ans = Utilities::getIntInRange("Please select which property you wish to build hotels for.\nIf you wish to exit, type 0: ", 0, propSet.size());
		if (ans == 0) {
			doneBuildingHotelsOnSet = true;
		}
		else {
			Space* toBuild = propSet[ans - 1];
			if (toBuild->getNumHotels() == 0) {
				int costToBuild = toBuild->getHouseCost();
				if (player.canDeduct(costToBuild)) {
					buildHotelPlayer(costToBuild, toBuild);
				}
				else {
					std::cout << "\nYou lack sufficient funds to build a hotel. Please select another property." << endl;
					Sleep(3000);
				}
			}
			else {
				std::cout << "\nHotel already built on that property.\nPlease select another." << endl;
				Sleep(3000);
			}
		}
	}
}

void TurnBuildingHandler::displayHotelSetChoicesPlayer(std::vector<Space*>& propSet) {
	std::cout << "Here are the properties in that set you can build hotels for: " << endl;
	for (size_t i{ 0 }; i < propSet.size(); ++i) {
		std::cout << to_string(i + 1) << " - " << propSet[i]->toString() << "Number of hotels: " << propSet[i]->getNumHotels() << "|" << endl << endl;
	}
}

void TurnBuildingHandler::buildHotelPlayer(int costToBuild, Space* toBuild) {
	player.deductCash(costToBuild);
	toBuild->addHotel();
	toBuild->setNumHouses(0);
	std::cout << "\nHotel was successfully built." << endl;
	Sleep(2000);
}

void TurnBuildingHandler::displayBuildableSetsPlayer(std::vector<std::vector<Space*>>& sets) {
	std::cout << "Here are the sets you own which you can build hotels: " << endl;
	for (size_t i{ 0 }; i < sets.size(); ++i) {
		std::cout << to_string(i + 1) << " - " << sets[i][0]->getColor() << ":" << endl;
	}
}

bool TurnBuildingHandler::handleHouseBuildingPlayer() {
	bool doneEditing{ false };
	vector<vector<Space*>> sets = Utilities::getOwnedSets(player, spaces, colorSets);
	if (sets.empty()) {
		std::cout << "You do not own any sets of properties..." << endl;
		Sleep(3000);
		doneEditing = true;
	}
	else {
		bool doneWithHouses{ false };
		while (!doneWithHouses) {
			displayedOwnedSetsPlayer();
			int ans = Utilities::getIntInRange("Please select which color of property you want to build houses on.\nIf you wish to exit, type 0: ", 0, sets.size());
			if (ans == 0) //exit
			{
				doneWithHouses = true;
				doneEditing = true;
			}
			else {
				handleHouseSetBuildingPlayer(sets, ans);
			}
		}
	}
	return doneEditing;
}

void TurnBuildingHandler::handleHouseSetBuildingPlayer(std::vector<std::vector<Space*>>& sets, int ans) {
	bool doneBuildingHouses{ false };
	while (!doneBuildingHouses) {
		vector<Space*>propSet = sets[ans - 1];
		displayBuildableHousesInSet(propSet);
		int ans = Utilities::getIntInRange("Please select which property you wish to build houses for.\nIf you wish to exit, type 0: ", 0, propSet.size());
		if (ans == 0) {
			doneBuildingHouses = true;
		}
		else {
			bool canBuild{ true };
			Space* toBuild = propSet[ans - 1];
			if (toBuild->getNumHouses() < 4) {
				canBuild = checkIfHotelExists(toBuild) && checkIfEvenBuilding(propSet, toBuild);
				if (canBuild) {
					int costToBuild = toBuild->getHouseCost();
					if (player.canDeduct(costToBuild)) {
						buildHousePlayer(costToBuild, toBuild);
					}
					else {
						std::cout << "\nYou lack sufficient funds to build a house. Please select another property." << endl;
						Sleep(3000);
					}
				}
			}
			else {
				std::cout << "\nNumber of houses on that property is already at max.\nPlease select another. " << endl;
				Sleep(3000);
			}
		}
	}
}

bool TurnBuildingHandler::checkIfHotelExists(Space* toBuild) {
	bool canBuild{ true };
	if (toBuild->getNumHotels() > 0) {
		std::cout << "A hotel exists on that property. You may not build houses while a hotel is there.\nPlease select another." << endl;
		canBuild = false;
		Sleep(4000);
	}
	return canBuild;
}

void TurnBuildingHandler::buildHousePlayer(int costToBuild, Space* toBuild) {
	player.deductCash(costToBuild);
	toBuild->addHouse();
	std::cout << "\nHouse was successfully built." << endl;
	Sleep(2000);
}

bool TurnBuildingHandler::checkIfEvenBuilding(std::vector<Space*>& propSet, Space* toBuild) {
	bool canBuild{ true };
	for (auto& prop : propSet) {
		bool diffProp{ prop->getName() != toBuild->getName() };
		bool lessHouses{ prop->getNumHouses() < toBuild->getNumHouses() };
		if (diffProp && lessHouses)
			canBuild = false;
	}
	if (!canBuild) {
		std::cout << "\nYou are attempting to build unevenly. Please select another property." << endl;
		Sleep(3000);
	}
	return canBuild;
}

void TurnBuildingHandler::displayBuildableHousesInSet(std::vector<Space*>& propSet) {
	system("CLS");
	std::cout << "Here are the properties in that set you can build houses for: " << endl << endl;;
	for (size_t i{ 0 }; i < propSet.size(); ++i) {
		std::cout << to_string(i + 1) << " - " << propSet[i]->toString() << "Number of houses: " << propSet[i]->getNumHouses()
			<< "|Number of hotels: " << propSet[i]->getNumHotels() << "|" << endl << endl;
	}
}

void TurnBuildingHandler::displayedOwnedSetsPlayer() {
	vector<vector<Space*>> sets = Utilities::getOwnedSets(player, spaces, colorSets);
	system("CLS");
	std::cout << "Here are the sets you own: " << endl;
	for (size_t i{ 0 }; i < sets.size(); ++i) {
		std::cout << to_string(i + 1) << " - " << sets[i][0]->getColor() << ":" << endl;
	}
}

TurnBuildingHandler::TurnBuildingHandler(Game& g, Player& plr, std::vector<Player>& curPlrs, std::vector<Space*>& s, std::vector<std::string>& gameOut, std::vector<std::string>& cSets)
	: game(g), player(plr), curPlayers(curPlrs), spaces(s), gameOutput(gameOut), colorSets(cSets) {}

void TurnBuildingHandler::displayBuildingChoices() {
	system("CLS");
	std::cout << "Here are your options:" << endl;
	std::cout << "1 - Build house" << endl;
	std::cout << "2 - Build hotel" << endl;
	std::cout << "3 - Build turret" << endl;
}

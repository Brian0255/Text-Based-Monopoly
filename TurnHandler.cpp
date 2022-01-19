
#include "TurnHandler.h"
#include"TurnBuildingHandler.h"
#include"TurnTradingHandler.h"
#include"TurnAIHandler.h"
#include "CardHandler.h"
#include"Windows.h"
#include<iostream>

using namespace std;

void TurnHandler::handle() {
	bool done{ false };
	player.setRolling(true);
	while (!done) {
		if (game.getNumPlayers() == 1) {
			std::cout << player.getName() << " has won the game! Congratulations!" << endl;
			Sleep(5000);
			done = true;
		}
		else {
			gameOutput.clear();
			game.setInfo(player);
			if (!player.isAI())
				done = handleTurnPlayer();
			else {
				done = handleTurnAI();
			}
		}
	}
}

bool TurnHandler::handleTurnAI() {
	TurnAIHandler turnAIHandler = TurnAIHandler(game, player, curPlayers, spaces, gameOutput, colorSets);
	bool done = turnAIHandler.handle();
	return done;
}

bool TurnHandler::handleTurnPlayer() {
	bool done{ false };
	displayChoices();

	int ans = Utilities::getIntInRange("Please enter an option. If you wish to roll, type 0: ", 0, 6);

	Space* currentSpace = spaces[player.getCurrentSpot()];
	vector<Space*> prop = Utilities::getProperty(player, spaces);
	vector<Space*> railroads = Utilities::getOwnedRailroads(player, spaces);
	vector<vector<Space*>> sets;
	vector<Player>tradeable = curPlayers;
	Utilities::removeObjectByValue(tradeable, player); //avoid player trading with themselves
	TurnBuildingHandler turnBuildingHandler = TurnBuildingHandler(game, player, curPlayers, spaces, gameOutput, colorSets);
	TurnTradingHandler turnTradingHandler = TurnTradingHandler(game, player, curPlayers, spaces, gameOutput, colorSets);
	switch (ans) {
	case 0: //exit
		done = true;
		break;
	case 1:
		handlePropertyMortgagingPlayer();
		break;
	case 2:
		handleMortgageLiftingPlayer();
		break;
	case 3:
		turnTradingHandler.handle();
		break;
	case 4:

		turnBuildingHandler.handle();
		break;
	case 5:
		handleRailroadChoicePlayer();
		break;
	case 6:
		handleCollectableUsagePlayer();
		break;
	}
	return done;
}
void TurnHandler::handleCollectableUsagePlayer() {
	vector<Card> collectables = player.getCards();
	if (collectables.empty()) {
		std::cout << "You do not have any collectable cards. Please select another option." << endl;
		Sleep(3000);
	}
	else {
		displayCollectableCards(collectables);
		int ans = Utilities::getIntInRange("Please select a card to use. If you would like to exit, type 0:", 0, collectables.size());
		if (ans != 0) {
			Card toUse = collectables[ans - 1];
			if (toUse.getEffect() == "getOutJail") {
				if (player.getCurrentSpot() == 10) {
					handleCollectableCard(toUse, collectables, ans);
				}
				else {
					std::cout << "You are not currently in jail!" << endl;
					Sleep(3000);
				}
			}
			else {
				handleCollectableCard(toUse, collectables, ans);
			}
		}
	}
}

void TurnHandler::handleCollectableCard(Card& toUse, std::vector<Card>& collectables, int ans) {
	CardHandler handler = CardHandler(curPlayers, game, player, toUse);
	handler.handle();
	collectables.erase(collectables.begin() + (ans - 1));
	player.setCards(collectables);
}

void TurnHandler::displayCollectableCards(std::vector<Card>& collectables) {
	system("CLS");
	std::cout << "Here are your collectable cards: " << endl << endl;
	for (size_t i{ 0 }; i < collectables.size(); ++i) {
		std::cout << to_string(i + 1) << " - " << collectables[i].getDesc() << endl;
	}
}

void TurnHandler::handleRailroadChoicePlayer() {
	Space* currentSpace = spaces[player.getCurrentSpot()];
	vector<Space*> railroads = Utilities::getOwnedRailroads(player, spaces);

	if (currentSpace->getPropertyType() == "RAILROAD") {
		vector<Space*> availRailroads;
		setupAvailableRailroads(railroads, availRailroads);
		if (availRailroads.empty()) {
			std::cout << "You do not own any other railroads." << endl;
			Sleep(3000);
		}
		else {
			displayRailroadChoices(availRailroads);
			int ans = Utilities::getIntInRange("Please select a railroad. If you would like to exit, type 0:", 0, railroads.size());
			if (ans != 0) {
				warpPlayerByRailroad(availRailroads, ans);
			}
		}
	}
	else {
		std::cout << "You are not currently on a railroad. Please select another option." << endl;
		Sleep(3000);
	}
}

void TurnHandler::warpPlayerByRailroad(std::vector<Space*>& availRailroads, int ans) {
	Space* toWarp = availRailroads[ans - 1];
	player.setCurrentSpot(Utilities::getIndexPtrObj(spaces, toWarp));
	game.setInfo(player);
	game.displayBoard();
	std::cout << "You have successfully warped to " << toWarp->getName() << "." << endl;
	player.setRolling(false);
	Sleep(3000);
}

void TurnHandler::setupAvailableRailroads(std::vector<Space*>& railroads, std::vector<Space*>& availRailroads) {
	for (auto& rail : railroads) {
		if (rail->getName() != spaces[player.getCurrentSpot()]->getName()) {
			availRailroads.push_back(rail);
		}
	}
}

void TurnHandler::displayRailroadChoices(std::vector<Space*>& availRailroads) {
	system("CLS");
	std::cout << "Here are the railroads you can warp to: \n\n";
	for (size_t i{ 0 }; i < availRailroads.size(); ++i) {
		std::cout << to_string(i + 1) << " - " << availRailroads[i]->toString() << endl;
	}
}

void TurnHandler::handleMortgageLiftingPlayer() {
	vector<Space*> mortProp = Utilities::getMortgagedProperty(player, spaces);
	if (mortProp.empty()) {
		std::cout << "You do not have any mortgages..." << endl;
		Sleep(3000);
	}
	else {
		displayMortgagedProperty(mortProp);
		int choice = Utilities::getIntInRange("Please type the number for the mortgage you wish to lift.\nIf you want to exit, type 0: ", 0, mortProp.size());
		if (choice != 0) {
			int cost = (mortProp[choice - 1]->getCost() / 2) + (mortProp[choice - 1]->getCost() / 10);
			std::cout << "Lifting this mortgage will cost " << to_string(cost) << " dollars.";
			string answer = Utilities::getStringYesNo("Are you sure ?(y/n): ");
			if (answer == "y" || answer == "Y") {
				if (player.canDeduct(cost)) {
					liftMortgage(cost, mortProp, choice);
				}
				else {
					std::cout << "You do not have enough money..." << endl;
					Sleep(3000);
				}
			}
		}
	}
}

void TurnHandler::liftMortgage(int cost, std::vector<Space*>& mortProp, int choice) {
	player.deductCash(cost);
	mortProp[choice - 1]->setMortgage();//set the mortgage value to false
	std::cout << "Property successfully bought back." << endl;
	Sleep(3000);
}

void TurnHandler::displayMortgagedProperty(std::vector<Space*>& mortProp) {
	system("CLS");
	std::cout << "Here are your mortgaged properties: " << endl;
	for (size_t i{ 0 }; i < mortProp.size(); ++i) {
		std::cout << to_string(i + 1) << " - " << mortProp[i]->toString() << endl;
	}
}

void TurnHandler::handlePropertyMortgagingPlayer() {
	vector<Space*> prop = Utilities::getProperty(player, spaces);
	if (prop.empty()) {
		std::cout << "You do not own any property to mortgage..." << endl;
		Sleep(3000);
	}
	else {
		displayOwnedProperties(prop);
		int choice = Utilities::getIntInRange("Please type the number for which property you want to mortgage.\nIf you want to exit, type 0: ", 0, prop.size());
		if (choice != 0) {
			int mortValue = calculateMortgageValue(prop, choice);
			std::cout << "Mortgaging this property will give you " << to_string(mortValue) << " dollars." << endl;
			std::cout << "This value includes half the cost back for any houses, hotels, and turrets you bought, but they will be removed." << endl;
			string answer = Utilities::getStringYesNo("Are you sure ?(y/n): ");
			if (answer == "y" || answer == "Y") {
				mortgageProperty(prop, choice, mortValue);
			}
		}
	}
}

void TurnHandler::mortgageProperty(std::vector<Space*>& prop, int choice, int mortValue) {
	prop[choice - 1]->setNumHouses(0);
	prop[choice - 1]->setNumHotels(0);
	prop[choice - 1]->setNumTurrets(0);
	player.addCash(mortValue);
	prop[choice - 1]->setMortgage();
	std::cout << "Property successfully mortgaged." << endl;
	Sleep(3000);
}

int TurnHandler::calculateMortgageValue(std::vector<Space*>& prop, int choice) {
	int mortValue = prop[choice - 1]->getCost() / 2;
	int numHouses = prop[choice - 1]->getNumHouses();
	int numHotels = prop[choice - 1]->getNumHotels();
	int numTurrets = prop[choice - 1]->getNumTurrets();
	for (int i{ 0 }; i < numHouses; ++i) {
		mortValue += prop[choice - 1]->getHouseCost() / 2;
	}
	for (int i{ 0 }; i < numHotels; ++i) {
		mortValue += prop[choice - 1]->getHouseCost() / 2;
	}
	for (int i{ 0 }; i < numTurrets; ++i) {
		mortValue += prop[choice - 1]->getHouseCost();
	}
	return mortValue;
}

void TurnHandler::displayOwnedProperties(std::vector<Space*>& prop) {
	system("CLS");
	std::cout << "Here are your owned properties: " << endl;
	for (size_t i{ 0 }; i < prop.size(); ++i) {
		std::cout << to_string(i + 1) << " - " << prop[i]->toString() << endl << endl;
	}
}

void TurnHandler::displayChoices() {
	gameOutput.push_back("Here are your options before you roll: ");
	gameOutput.push_back("1 - Mortgage owned property");
	gameOutput.push_back("2 - Lift mortgages");
	gameOutput.push_back("3 - Trade with another player");
	gameOutput.push_back("4 - Build houses/hotels/turrets");
	gameOutput.push_back("5 - Warp via railroad(you must be on one and own a different one)");
	gameOutput.push_back("6 - Use Collectable Card");
	game.displayBoard();
}

TurnHandler::TurnHandler(Game& g, Player& p, std::vector<Player>& curPlrs, std::vector<Space*>& s,
	std::vector<std::string>& gameOut, std::vector<std::string>& cSets)
	: game( g ), player( p ), curPlayers( curPlrs ), spaces( s ), gameOutput( gameOut ), colorSets( cSets ) {}



	

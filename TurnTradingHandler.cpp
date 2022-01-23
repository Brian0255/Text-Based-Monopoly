#include "TurnTradingHandler.h"
#include"Utilities.h"
#include<iostream>
#include"Windows.h"
#include"Trade.h"

using namespace std;

TurnTradingHandler::TurnTradingHandler(Game& g, Player& plr, std::vector<Player>& curPlrs, std::vector<Space*>& s, std::vector<std::string>& gameOut, std::vector<std::string>& cSets)
	: game(g), player(plr), curPlayers(curPlrs), spaces(s), gameOutput(gameOut), colorSets(cSets) {
}

void TurnTradingHandler::handle() {
	bool doneTrading{ false };
	vector<Space*> prop = Utilities::getProperty(player, spaces);
	vector<Player>tradeable = curPlayers;
	Utilities::removeObjectByValue(tradeable, player); //avoid player trading with themselves
	while (!doneTrading) {
		if (prop.empty()) {
			std::cout << "You do not have any property to trade with..." << endl;
			Sleep(3000);
			doneTrading = true;
		}
		else {
			displayTradeablePlayers(tradeable);
			int choice = Utilities::getIntInRange("Please type the number for the player you wish to trade with.\nIf you want to exit, type 0: ", 0, tradeable.size());
			if (choice != 0) {
				doneTrading = tradeWithPlayer(tradeable, choice);
			}
			else {
				doneTrading = true;
			}
		}
	}
}

bool TurnTradingHandler::tradeWithPlayer(std::vector<Player>& tradeable, int choice) {
	bool doneTrading{ false };
	Player toTrade = tradeable[choice - 1];
	vector<Space*> prop = Utilities::getProperty(player, spaces);
	vector<Space*> prop2 = Utilities::getProperty(toTrade, spaces);
	if (prop2.empty()) {
		std::cout << toTrade.getName() << " has no property..." << endl;
		Sleep(3000);
	}
	else {
		vector<Space*> playerGive;
		vector<Space*> playerGet;
		Trade trade{ player, toTrade, prop, prop2, playerGive, playerGet, false };
		bool doneSelecting{ false };
		selectPropertiesToOffer(trade);
		doneTrading = trade.exitTrade;
		if (!trade.exitTrade)
			selectPropertiesToGet(trade);
		doneTrading = trade.exitTrade;
		if (!doneTrading) {
			displayCompleteTradeOffer(trade);
			if (!toTrade.isAI()) {
				askPlayerAcceptTrade(trade);
			}
			else {
				askAIAcceptTrade(trade);
			}
			doneTrading = true;
		}
	}
	return doneTrading;
}

void TurnTradingHandler::askAIAcceptTrade(Trade& trade) {
	std::cout << "\nThe AI is making a decision based on your offer..." << endl;
	Sleep(4000);
	if (trade.player1Offer.size() > trade.player1Get.size()) {
		std::cout << "AI " << trade.player2.getName() << " agreed to your trade." << endl;
		for (auto& property : trade.player1Offer) {
			property->setOwner(trade.player2.getName());
		}
		for (auto& property : trade.player1Get) {
			property->setOwner(trade.player1.getName());
		}
		Sleep(2000);
		std::cout << "Trade was successful. Now returning to main menu..." << endl;
		Sleep(4000);
	}
	else {
		std::cout << "The AI " << trade.player2.getName() << " has rejected your offer." << endl;
		Sleep(1000);
		std::cout << "Now returning to main menu..." << endl;
		Sleep(3000);
	}
}

void TurnTradingHandler::askPlayerAcceptTrade(Trade& trade) {
	string doTheTrade = Utilities::getStringYesNo(trade.player2.getName() + ", do you accept this offer by " + trade.player1.getName() + "?(y/n)");
	if (doTheTrade == "y" || doTheTrade == "Y") {
		for (auto& property : trade.player1Offer) {
			property->setOwner(trade.player2.getName());
		}
		for (auto& property : trade.player1Get) {
			property->setOwner(trade.player1.getName());
		}
		std::cout << "Trade was successful. Now returning to main menu..." << endl;
		Sleep(3000);
	}
	else if (doTheTrade == "n" || doTheTrade == "N") {
		std::cout << "Trade was rejected! Nothing will happen between both players." << endl;
		Sleep(1000);
		std::cout << "Returning to main menu..." << endl;
		Sleep(3000); 
	}
}

void TurnTradingHandler::displayCompleteTradeOffer(Trade& trade) {
	system("CLS");
	std::cout << trade.player1.getName() << " will give the following properties:" << endl;
	for (auto& property : trade.player1Offer) {
		std::cout << property->toString() << endl;
	}
	std::cout << endl << trade.player2.getName() << ", you will give the following properties:" << endl;
	for (auto& property : trade.player1Get) {
		std::cout << property->toString() << endl;
	}
	std::cout << endl;
}

void TurnTradingHandler::selectPropertiesToGet(Trade& trade) {
	bool doneSelecting{ false };
	while (!doneSelecting) {
		if (trade.prop2.empty()) {
			std::cout << "No more properties exist to select..." << endl;
			Sleep(3000);
			doneSelecting = true;
		}
		else {
			displayOtherPlayerProperties(trade);
			int toRemove = Utilities::getIntInRange("Enter the corresponding number for the properties you want."
				"When you are done, hit 0.\n If you want to exit the entire trade, enter -1: ", -1, trade.prop2.size());
			if (toRemove == -1) {
				doneSelecting = true;
				trade.exitTrade = true;
			}
			else if (toRemove == 0) {
				if (trade.player1Get.empty()) {
					std::cout << "You did not select any properties! Please select at least 1 property to take." << endl;
				}
				else {
					doneSelecting = true;
				}
			}
			else {
				selectPropertyGet(trade, toRemove);
			}
		}
	}
}

void TurnTradingHandler::selectPropertyGet(Trade& trade, int toRemove) {
	trade.player1Get.push_back(trade.prop2[toRemove - 1]);
	trade.prop2.erase(trade.prop2.begin() + (toRemove - 1));
	std::cout << "Property was successfully selected for trade." << endl;
	Sleep(3000);
}

void TurnTradingHandler::selectPropertiesToOffer(Trade& trade) {
	bool doneSelecting{ false };
	while (!doneSelecting) {
		if (trade.prop1.empty()) {
			std::cout << "No more properties exist to select..." << endl;
			Sleep(3000);
			doneSelecting = true;
		}
		else {
			displayOtherPlayerProperties(trade);
			displayCurrentlyOfferingProperties(trade);
			int toRemove = Utilities::getIntInRange("Enter the corresponding number for the properties you wish to offer."
				"When you are done, hit 0.\n If you want to exit the entire trade, enter -1: ", -1, trade.prop1.size());
			if (toRemove == -1) {
				doneSelecting = true;
				trade.exitTrade = true;
			}
			else if (toRemove == 0) {
				if (trade.player1Offer.empty()) {
					std::cout << "\nYou did not select any properties! Please select at least 1 property to offer." << endl;
					Sleep(3000);
				}
				else {
					doneSelecting = true;
				}
			}
			else {
				selectPropertyOffer(trade, toRemove);
			}
		}
	}
}

void TurnTradingHandler::selectPropertyOffer(Trade& trade, int toRemove) {
	trade.player1Offer.push_back(trade.prop1[toRemove - 1]);
	trade.prop1.erase(trade.prop1.begin() + (toRemove - 1));
	std::cout << "Property was successfully selected for trade." << endl;
	Sleep(3000);
}

void TurnTradingHandler::displayCurrentlyOfferingProperties(Trade trade) {
	vector<Space*> offerings = trade.prop1;
	system("CLS");
	std::cout << "Here are your properties: " << endl;
	for (size_t i{ 0 }; i < trade.prop1.size(); ++i) {
		std::cout << to_string(i + 1) << " - " << offerings[i]->toString() << endl << endl;
	}
}

void TurnTradingHandler::displayOtherPlayerProperties(Trade trade) {
	vector<Space*> available = trade.prop2;
	system("CLS");
	std::cout << "\nHere are " << trade.player2.getName() << "'s" << " properties: " << endl;
	for (size_t i{ 0 }; i < available.size(); ++i) {
		std::cout << to_string(i + 1) << " - " << available[i]->toString() << endl << endl;
	}
}

void TurnTradingHandler::displayTradeablePlayers(std::vector<Player>& tradeable) {
	system("CLS");
	std::cout << "Here are the players you can trade with: " << endl;
	for (size_t i{ 0 }; i < tradeable.size(); ++i) {
		std::cout << to_string(i + 1) << " - " << tradeable[i].getName() << endl;
	}
}

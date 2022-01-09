#include "Utilities.h"
#include<iostream>
#include<stdlib.h>

using namespace std;

int Utilities::getIntInRange(std::string prompt, int low, int high) {
	bool valid{ false };
	int res;
	while (!valid) {
		cout << prompt;
		cin >> res;
		if (cin.fail()) {
			cout << "Error! Entry must be an integer." << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		else {
			if (res >= low && res <= high) {
				valid = true;
			}
			else {
				cout << "Error! Entry must be from " << low << " to " << high << endl;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
			}
		}
	}
	return res;
}

int Utilities::getInt(std::string prompt) {
	bool valid{ false };
	int res;
	while (!valid) {
		cout << prompt;
		cin >> res;
		if (cin.fail()) {
			cout << "Error! Entry must be an integer." << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		else {
			valid = true;
			return res;
		}
	}
	return res;
}

std::string Utilities::getStringYesNo(std::string prompt) {
	bool valid{ false };
	string res;
	while (!valid) {
		cout << prompt;
		cin >> res;
		if (res == "y" || res == "n" || res == "Y" || res == "N") {
			valid = true;
			return res;
		}
		else {
			cout << "Error! Answer must be \"y\" or \"n\"." << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
	}
	return res;
}

std::string Utilities::getStringLimit(std::string prompt, int max) {
	bool valid{ false };
	string res;
	while (!valid) {
		cout << prompt;
		cin >> res;
		if (res.length() > max) {
			cout << "Error! Name exceeds character limit." << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		else {
			valid = true;
			return res;
		}
	}
	return res;
}

vector<Space*> Utilities::getProperty(Player& player, vector<Space*> spaces) {
	vector<Space*> owned;
	for (auto& space : spaces) {
		bool correctSpaceType{ (space->getType() == "PROPERTY") };
		bool correctOwner{ (space->getOwner() == player.getName()) };
		bool mortgaged{ (space->isMortgaged()) };

		if (correctSpaceType && correctOwner && !mortgaged) {
			owned.push_back(space);
		}
	}
	return owned;
}

vector<Space*> Utilities::getMortgagedProperty(Player& player, vector<Space*> spaces) {
	vector<Space*> owned;
	for (auto& space : spaces) {
		bool correctSpaceType{ (space->getType() == "PROPERTY") };
		bool correctOwner{ (space->getOwner() == player.getName()) };
		bool mortgaged{ (space->isMortgaged()) };

		if (correctSpaceType && correctOwner && mortgaged) {
			owned.push_back(space);
		}
	}
	return owned;
}

vector<Space*> Utilities::getOwnedRailroads(Player& player, vector<Space*> spaces) {
	vector<Space*> owned;
	for (auto& space : spaces) {
		bool correctSpaceType{ (space->getType() == "PROPERTY") };
		bool correctPropertyType{ (space->getPropertyType() == "RAILROAD") };
		bool correctOwner{ (space->getOwner() == player.getName()) };

		if (correctSpaceType && correctPropertyType && correctOwner) {
			owned.push_back(space);
		}
	}
	return owned;
}

std::vector<Space*> Utilities::getOwnedUtilities(Player& player, std::vector<Space*> spaces) {
	vector<Space*> owned;
	for (auto& space : spaces) {
		bool correctSpaceType{ (space->getType() == "PROPERTY") };
		bool correctPropertyType{ (space->getPropertyType() == "UTILITY") };
		bool correctOwner{ (space->getOwner() == player.getName()) };

		if (correctSpaceType && correctPropertyType && correctOwner) {
			owned.push_back(space);
		}
	}
	return owned;
}

std::vector<vector<Space*>> Utilities::getOwnedSets(Player& player, std::vector<Space*> spaces, vector<string> colors) {
	bool ownsSet{ true };
	vector<vector<Space*>> ownedSets;

	for (string color : colors) {
		ownsSet = true;
		vector<Space*> set;
		for (auto& property : spaces) {
			bool correctType{ (property->getType() == "PROPERTY") };
			bool correctColor{ (property->getColor() == color) };
			bool correctOwner{ (property->getOwner() == player.getName()) };
			bool mortgaged{ (property->isMortgaged()) };

			if (correctType && correctColor) {
				if (mortgaged || !correctOwner) {
					ownsSet = false;
					break;
				}
				set.push_back(property);
			}
		}
		if (ownsSet) {
			ownedSets.push_back(set);
		}
	}
	return ownedSets;
}

vector<vector<Space*>> Utilities::getHotellableSets(Player& player, vector<Space*> spaces, vector<string> colors) {
	vector <vector<Space*>> hotellable;
	vector<vector<Space*>> ownedSets = getOwnedSets(player, spaces, colors);
	bool canHotel{ true };
	for (auto& propSet : ownedSets) {
		canHotel = true;
		for (auto& prop : propSet) {
			if (prop->getNumHouses() < 4) {
				canHotel = false;
			}
		}
		if (canHotel) {
			hotellable.push_back(propSet);
		}
	}
	return hotellable;
}

void Utilities::resetOwnership(Player& player, vector<Space*> spaces) {
	vector<Space*> prop = getProperty(player, spaces);
	for (auto& toReset : prop) {
		toReset->setOwner("None");
		toReset->setNumHouses(0);
		toReset->setNumTurrets(0);
		toReset->setNumHotels(0);
		if (toReset->isMortgaged()) {
			toReset->setMortgage();
		}
	}
}



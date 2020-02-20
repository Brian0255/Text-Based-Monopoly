#include "Utilities.h"
#include<iostream>
#include<stdlib.h>

using namespace std;

int Utilities::getIntInRange(std::string prompt, int low, int high)
{
	bool valid{ false };
	int res;
	while (!valid)
	{
		cout << prompt;//prompt them
		cin >> res;
		if (cin.fail())//couldn't cast into an int
		{
			cout << "Error! Entry must be an integer." << endl;

			//clear everything, and ignore the largest possible size of stream input, and move to the next line
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		else
		{
			if (res >= low && res <= high)//if it's a valid int but not in range
			{
				valid = true;
			}
			else
			{
				cout << "Error! Entry must be from " << low << " to " << high << endl;

				//same as line 19 above
				cin.clear();
				cin.ignore(INT_MAX, '\n');
			}
		}
	}
	return res;
}

int Utilities::getInt(std::string prompt)
{
	//same as getIntInRange, but doesn't check range after successful cast into an int
	bool valid{ false };
	int res;
	while (!valid)
	{
		cout << prompt;
		cin >> res;
		if (cin.fail())
		{
			cout << "Error! Entry must be an integer." << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		else
		{
			valid = true;
			return res;
		}
	}
	return res;
}

std::string Utilities::getStringYesNo(std::string prompt)
{
	//prints prompt, then make sure the answer was "y" or "n"(capitals included just because)
	bool valid{ false };
	string res;
	while (!valid)
	{
		cout << prompt;
		cin >> res;
		if (res=="y" || res == "n" || res == "Y" || res == "N")
		{
			valid = true;
			return res;
		}
		else
		{
			cout << "Error! Answer must be \"y\" or \"n\"." << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
	}
	return res;
}

std::string Utilities::getStringLimit(std::string prompt, int max)
{
	//same as above, but instead of checking what the string is, just checks the length
	bool valid{ false };
	string res;
	while (!valid)
	{
		cout << prompt;
		cin >> res;
		if (res.length() > max)
		{
			cout << "Error! Name exceeds character limit." << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		else
		{
			valid = true;
			return res;
		}
	}
	return res;
}

vector<Space*> Utilities::getProperty(Player & player, vector<Space*> spaces)
{
	//iterate through the spaces, check if type is property, then check if the owner name is equal to the player
	//if so, add it to the vector of property they own
	vector<Space*> owned;
	for (auto& space : spaces)
	{
		if (space->getType() == "PROPERTY")
		{
			if (space->getOwner() == player.getName())
			{
				if (!space->isMortgaged())
				{
					owned.push_back(space);
				}
			}
		}
	}
	return owned;
}

vector<Space*> Utilities::getMortgagedProperty(Player & player, vector<Space*> spaces)
{
	//same as above, but just check if it's mortgaged
	vector<Space*> owned;
	for (auto& space : spaces)
	{
		if (space->getType() == "PROPERTY")
		{
			if (space->getOwner() == player.getName())
			{
				if (space->isMortgaged())
				{
					owned.push_back(space);
				}
			}
		}
	}
	return owned;
}

vector<Space*> Utilities::getOwnedRailroads(Player & player, vector<Space*> spaces)
{
	//same as above, but just checks if the property type is railroad
	vector<Space*> owned;
	for (auto& space : spaces)
	{
		if (space->getType() == "PROPERTY")
		{
			if (space->getPropertyType() == "RAILROAD")
			{
				if (space->getOwner() == player.getName())
				{
					owned.push_back(space);
				}
			}
		}
	}
	return owned;
}

std::vector<Space*> Utilities::getOwnedUtilities(Player & player, std::vector<Space*> spaces)
{
	//same as above, but just checks if the property type is a utility
	vector<Space*> owned;
	for (auto& space : spaces)
	{
		if (space->getType() == "PROPERTY")
		{
			if (space->getPropertyType() == "UTILITY")
			{
				if (space->getOwner() == player.getName())
				{
					owned.push_back(space);
				}
			}
		}
	}
	return owned;
}

std::vector<vector<Space*>> Utilities::getOwnedSets(Player & player, std::vector<Space*> spaces, vector<string> colors)
{
	bool ownsSet{ true };
	vector<vector<Space*>> ownedSets; //in basic terms, a collection of sets of property they own by color
	//set to false if player doesn't own every single color, otherwise add to sets player owns
	for (string color : colors)//for each color
	{
		ownsSet = true;//reset to true in case the one before results to false
		vector<Space*> set;
		for (auto& property : spaces)//for each property in the spaces
		{
			if (property->getType() == "PROPERTY")
			{
				if (property->getColor() == color) //check if it's equal to the color we're on
				{
					if (property->getOwner() == player.getName())//check if the player owns it
					{
						if (property->isMortgaged()==false)//make sure not mortgaged
						{
							set.push_back(property);
						}
						else//doesn't own set if mortgaged
						{
							ownsSet = false;
						}
					}//doesn't own set if they don't own 
					else
					{
						ownsSet = false;
					}
				}
			}
		}
		if (ownsSet)//if nothing came out false
		{
			ownedSets.push_back(set);
		}
	}
	return ownedSets;
}

vector<vector<Space*>> Utilities::getHotellableSets(Player & player, vector<Space*> spaces, vector<string> colors)
{
	vector <vector<Space*>> hotellable; //a collection of sets of properties they have every house built to the max of 4 houses
	vector<vector<Space*>> ownedSets = getOwnedSets(player, spaces, colors);
	//similar to above.
	//get all color sets they own, and set canHotel to false if they have < 4 houses on any property
	bool canHotel{ true };
	for (auto& propSet : ownedSets)//for each property set in their color sets
	{
		canHotel = true;//reset to true in case one comes out false before this
		for (auto& prop : propSet)//for each property in each property set
		{
			if (prop->getNumHouses() < 4)//if the number of houses built isn't max, they can't build a hotel on this set
			{
				canHotel = false; 
			}
		}
		if (canHotel)
		{
			hotellable.push_back(propSet);
		}
	}
	return hotellable;
}

void Utilities::resetOwnership(Player & player, vector<Space*> spaces)
{
	vector<Space*> prop = getProperty(player, spaces);
	for (auto& toReset : prop)
	{
		//set the owner to the default, and reset all property numbers to 0, and set the mortgage to false
		toReset->setOwner("None");
		toReset->setNumHouses(0);
		toReset->setNumTurrets(0);
		toReset->setNumHotels(0);
		if (toReset->isMortgaged())
		{
			toReset->setMortgage();
		}
	}
}



#pragma once
#include<vector>
#include<string>
#include<cstdlib>
#include<ctime>
#include"Property.h"
#include <iostream>

//this is an incredibly useful static class i used throughout the game. i'm very proud of it

class Utilities
{
public:
	//gets an integer using a prompt, with validation checking in a range.
	//also makes sure it's an integer being entered
	static int getIntInRange(std::string prompt, int low, int high);

	//gets an integer, and makes sure it's an integer and not a string
	static int getInt(std::string prompt);

	//gets a string, which must be "y" or "n"
	static std::string getStringYesNo(std::string prompt);

	//gets a string with a limit on how many characters the user can enter
	static std::string getStringLimit(std::string prompt, int max);

	//gets all property owned by the player
	static std::vector<Space*> getProperty(Player& player,std::vector<Space*> spaces);

	//gets all property a player has that is currently mortgaged
	static std::vector<Space*> getMortgagedProperty(Player& player, std::vector<Space*> spaces);

	//gets all railroads a player owns
	static std::vector<Space*> getOwnedRailroads(Player& player, std::vector<Space*> spaces);

	//gets all utilities a player owns
	static std::vector<Space*> getOwnedUtilities(Player& player, std::vector<Space*> spaces);

	//gets all property sets the player owns by color
	static std::vector<std::vector<Space*>> getOwnedSets(Player& player, std::vector<Space*> spaces, std::vector<std::string> colors);

	//gets all property sets the players owns and has built the max houses(4) for
	static std::vector<std::vector<Space*>> getHotellableSets(Player& player, std::vector<Space*> spaces, std::vector<std::string> colors);

	//resets ownership of properties after bankruptcy
	static void resetOwnership(Player& player, std::vector<Space*> spaces);

	//a templated function that removes a basic type(string,int,double) from any type of this vector
	template<typename T>
	static void removeByValue(std::vector<T>&, T compare);

	//a templated function that gets the index of a particular pointer member using ->getName() as a comparison
	template<typename T>
	static int getIndexPtrObj(std::vector<T>&, T compare);

	//a templated function that removes an object by value, as long as it has getName() defined
	template<typename T>
	static void removeObjectByValue(std::vector<T>&, T compare);

	//a templated function that removes a pointer object by value, as long as it has ->getName() defined
	template<typename T>
	static void removePtrObjectByValue(std::vector<T>&, T compare);

	//a templated function that removes a random element from a vector of type T
	template<typename T>
	static T removeRandomElement(std::vector<T>&);

	//a templated function that gets, but not removes, a random element from a vector of type T
	template<typename T>
	static T getRandomElement(std::vector<T>&);

private:
};

//i used the "Create Definition/Signature" thing and it automatically made the templates here with the "inline" keyword
//i have no idea why, but i left it

template<typename T>
inline void Utilities::removeByValue(std::vector<T>& vec, T compare)
{
	for (size_t i{ 0 }; i < vec.size(); ++i)
	{
		if (vec[i] == compare)//if comparison equal, return the value at the index we're at
		{
			vec.erase(vec.begin() + i);
		}
	}
}

template<typename T>
inline int Utilities::getIndexPtrObj(std::vector<T>& vec, T compare)
{
	for (size_t i{ 0 }; i < vec.size(); ++i)
	{
		if (vec[i]->getName() == compare->getName()) //if comparison equal, return the index we're at
		{
			return i;
		}
	}
}

template<typename T>
inline void Utilities::removeObjectByValue(std::vector<T>& vec, T compare)
{
	for (size_t i{ 0 }; i < vec.size(); ++i)
	{
		if (vec[i].getName() == compare.getName())//if comparison equal, remove the value at the index we're at
		{
			vec.erase(vec.begin() + i);
		}
	}
}

template<typename T>
inline void Utilities::removePtrObjectByValue(std::vector<T>& vec, T compare)
{
	for (size_t i{ 0 }; i < vec.size(); ++i)
	{
		if (vec[i]->getName() == compare->getName())
		{
			vec.erase(vec.begin() + i);//if comparison equal, remove the value at the index we're at
		}
	}
}

template<typename T>
inline T Utilities::removeRandomElement(std::vector<T>& vec)
{
	//i cant do rand() % 0 here, so i use a ternary operator:
	//if the size of the vector is 1 or less, just grab the 0th element, otherwise:
	//grab a random index from ( 0 ) to ( the size of the vector - 1 )
	//the minus one is to prevent going out of bounds(vector[vector.size()] will be out of range)

	int randIndex = (vec.size() <= 1) ? 0 : rand() % (vec.size());
	T randElement = vec[randIndex]; //set it so we don't lose it after erasing
	vec.erase(vec.begin() + randIndex);
	return randElement;
}

template<typename T>
inline T Utilities::getRandomElement(std::vector<T>& vec)
{
	//i cant do rand() % 0 here, so i use a ternary operator:
	//if the size of the vector is 1 or less, just grab the 0th element, otherwise:
	//grab a random index from ( 0 ) to ( the size of the vector - 1 )
	//the minus one is to prevent going out of bounds(vector[vector.size()] will be out of range)

	int randIndex = (vec.size() <= 1) ? 0 : rand() % (vec.size());
	T randElement = vec[randIndex];
	return randElement;
}


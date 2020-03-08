#pragma once
#include<vector>
#include<string>
#include<cstdlib>
#include<ctime>
#include"Property.h"
#include <iostream>

class Utilities
{
public:
	static int getIntInRange(std::string prompt, int low, int high);
	static int getInt(std::string prompt);
	
	static std::string getStringYesNo(std::string prompt);
	static std::string getStringLimit(std::string prompt, int max);
	
	static std::vector<Space*> getProperty(Player& player,std::vector<Space*> spaces);
	static std::vector<Space*> getMortgagedProperty(Player& player, std::vector<Space*> spaces);
	static std::vector<Space*> getOwnedRailroads(Player& player, std::vector<Space*> spaces);
	static std::vector<Space*> getOwnedUtilities(Player& player, std::vector<Space*> spaces);
	static std::vector<std::vector<Space*>> getOwnedSets(Player& player, std::vector<Space*> spaces, std::vector<std::string> colors);
	static std::vector<std::vector<Space*>> getHotellableSets(Player& player, std::vector<Space*> spaces, std::vector<std::string> colors);
	static void resetOwnership(Player& player, std::vector<Space*> spaces);
	
	template<typename T>
	static void removeByValue(std::vector<T>&, T compare);
	
	template<typename T>
	static int getIndexPtrObj(std::vector<T>&, T compare);
	
	template<typename T>
	static void removeObjectByValue(std::vector<T>&, T compare);
	
	template<typename T>
	static void removePtrObjectByValue(std::vector<T>&, T compare);

	template<typename T>
	static T removeRandomElement(std::vector<T>&);

	template<typename T>
	static T getRandomElement(std::vector<T>&);

private:
};

template<typename T>
inline void Utilities::removeByValue(std::vector<T>& vec, T compare)
{
	for (size_t i{ 0 }; i < vec.size(); ++i)
	{
		if (vec[i] == compare)
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
		if (vec[i]->getName() == compare->getName())
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
		if (vec[i].getName() == compare.getName())
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
			vec.erase(vec.begin() + i);
		}
	}
}

template<typename T>
inline T Utilities::removeRandomElement(std::vector<T>& vec)
{
	int randIndex = (vec.size() <= 1) ? 0 : rand() % (vec.size());
	T randElement = vec[randIndex]; //set it so we don't lose it after erasing
	vec.erase(vec.begin() + randIndex);
	return randElement;
}

template<typename T>
inline T Utilities::getRandomElement(std::vector<T>& vec)
{
	int randIndex = (vec.size() <= 1) ? 0 : rand() % (vec.size());
	T randElement = vec[randIndex];
	return randElement;
}


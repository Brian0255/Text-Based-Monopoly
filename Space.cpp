#include "Space.h"
#include<iostream>

using namespace std;

//nothing very interesting here

Space::Space(std::string n, std::string t)
	:name{ n }, type{ t } {}


std::string Space::getName()
{
	return this->name;
}

std::string Space::getType()
{
	return this->type;
}

Space::~Space()
{
}

std::string Space::toString()
{
	return "";
}

std::string Space::getPropertyType()
{
	return "Not a property.";
}

std::string Space::getOwner()
{
	return "No owner can exist.";
}

void Space::setOwner(std::string newOwner)
{
}

void Space::setNumHouses(int newNumHouses)
{
}

void Space::setNumHotels(int newNumHotels)
{
}

void Space::setNumTurrets(int newNumTurrets)
{
}


int Space::getCost()
{
	return 0;
}

int Space::getNumHouses()
{
	return 0;
}

void Space::addHouse()
{
}

void Space::addHotel()
{
}


int Space::getNumTurrets()
{
	return 0;
}

int Space::getNumHotels()
{
	return 0;
}

int Space::getOneHouseRent()
{
	return 0;
}

int Space::getTwoHouseRent()
{
	return 0;
}

int Space::getThreeHouseRent()
{
	return 0;
}

int Space::getFourHouseRent()
{
	return 0;
}

int Space::getHotelRent()
{
	return 0;
}

int Space::getRent()
{
	return 0;
}

int Space::getRailroadRent(Player & player, std::vector<Space*>& spaces)
{
	return 0;
}

int Space::getUtilRent(Player & player, std::vector<Space*>& spaces, int roll)
{
	return 0;
}

int Space::getHouseCost()
{
	return 0;
}

std::string Space::getColor()
{
	return "NEUTRAL";
}

bool Space::isMortgaged()
{
	return false;
}

void Space::setMortgage()
{
}

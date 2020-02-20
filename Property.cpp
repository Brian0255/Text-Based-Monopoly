#include "Property.h"
#include"Utilities.h"
#include<iostream>

using namespace std;

//i dont think much explanation is needed for this cpp, but i will explain the various rent member functions

Property::Property(std::string n, std::string t, std::string pT, std::string col, int c, int one, int two, int three, int four, int hot, int houCost, int r, std::string o, bool ow, bool mg)
	:Space(n, t), propertyType{ pT }, color{ col }, cost{ c }, rent{ r }, houses{ 0 }, defense{ 0 }, hotels{ 0 }, turrets{ 0 }, 
	oneHouseRent{ one }, twoHouseRent{ two }, threeHouseRent{ three }, fourHouseRent{ four }, 
	hotelRent{ hot }, houseCost{ houCost }, mortgage{ cost / 2 }, owner{ o }, owned{ ow }, mortgaged{ mg } {}

std::string Property::getPropertyType()
{
	return this->propertyType;
}
std::string Property::toString()
{
	string res{ "" };
	res += this->getName() + ", value: " + to_string(this->getCost()) + " dollars," +
		"\n|House/hotel cost: " + to_string(this->houseCost) + "|Turret cost: " + to_string((this->houseCost*2)) + "|";
	return res;
}

std::string Property::getOwner()
{
	return this->owner;
}
void Property::setOwner(std::string newOwner)
{
	this->owner = newOwner;
}

void Property::setNumHouses(int newNumHouses)
{
	this->houses = newNumHouses;
}

void Property::setNumHotels(int newNumHotels)
{
	this->hotels = newNumHotels;
}

void Property::setNumTurrets(int newNumTurrets)
{
	this->turrets = newNumTurrets;
}

int Property::getRent()
{

	//gets the rent based on the number of houses built using a switch case and getters, then returns it. fairly simple
	int rent{ this->rent };
	switch (this->getNumHouses())
	{
	case 1:
		rent = this->getOneHouseRent();
		break;
	case 2:
		rent = this->getTwoHouseRent();
		break;
	case 3:
		rent = this->getThreeHouseRent();
		break;
	case 4:
		rent = this->getFourHouseRent();
		break;
	}
	if (this->getNumHotels())
	{
		rent = this->getHotelRent();
	}
	return rent;
}
int Property::getRailroadRent(Player & owner,vector<Space*>& spaces)
{
	//gets ALL the railroads owned by the owner of the railroad the player landed on
	vector<Space*> rails = Utilities::getOwnedRailroads(owner,spaces);

	//the math here is (2 ^ (numRailroads-1) ) * 25
	//just 1 railroad = 2^0 * 25 = 25
	//2 railroads = 2^1 * 25 = 50
	//3 railroads = 2^2 * 25 = 100
	//it's exponential because the rent doubles for every extra railroads the owner owns besides the one the player landed on
	//i cast it into an int because pow(double,int) returns double. i could have left that but this just makes more sense
	return static_cast<int>(pow(2.0, rails.size()-1) * 25);
}
int Property::getUtilRent(Player & owner, std::vector<Space*>& spaces, int roll)
{
	vector<Space*> utils = Utilities::getOwnedUtilities(owner, spaces);
	return (utils.size() < 2) ? roll * 4 : roll * 10;
	//this first gets all the utilities owned by the owner of the space the player landed on.
	//a ternary operator is then used:
	//the owner has to own at least 1 utilitiy(this space) for this member function to even get called:
	//if the player has one utility, the rent is the roll * 4.
	//otherwise, the player owns both so the rent is roll * 10
}
int Property::getCost()
{
	return this->cost;
}
int Property::getNumHouses()
{
	return this->houses;
}
int Property::getNumTurrets()
{
	return this->turrets;
}
int Property::getNumHotels()
{
	return this->hotels;
}
void Property::addHouse()
{
	++this->houses;
}
void Property::addHotel()
{
	++this->hotels;
}
int Property::getOneHouseRent()
{
	return this->oneHouseRent;
}
int Property::getTwoHouseRent()
{
	return this->twoHouseRent;
}
int Property::getThreeHouseRent()
{
	return this->threeHouseRent;
}
int Property::getFourHouseRent()
{
	return this->fourHouseRent;
}
int Property::getHotelRent()
{
	return this->hotelRent;
}
int Property::getHouseCost()
{
	return this->houseCost;
}
bool Property::isMortgaged()
{
	return this->mortgaged;
}
void Property::setMortgage()
{
	this->mortgaged = !this->mortgaged;
}
std::string Property::getColor()
{
	return this->color;
}
Property::~Property()
{
}
;

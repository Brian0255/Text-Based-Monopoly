#include "Property.h"
#include"Utilities.h"
#include<iostream>

using namespace std;

Property::Property(std::string n, std::string t, std::string pT, std::string col, int c, int one, int two, int three, int four, int hot, int houCost, int r, std::string o, bool ow, bool mg)
	:Space(n, t), propertyType{ pT }, color{ col }, cost{ c }, rent{ r }, houses{ 0 }, defense{ 0 }, hotels{ 0 }, turrets{ 0 },
	oneHouseRent{ one }, twoHouseRent{ two }, threeHouseRent{ three }, fourHouseRent{ four },
	hotelRent{ hot }, houseCost{ houCost }, mortgage{ cost / 2 }, owner{ o }, owned{ ow }, mortgaged{ mg } {}

std::string Property::getPropertyType() {
	return this->propertyType;
}
std::string Property::toString() {
	string res{ "" };
	res += this->getName() + ", value: " + to_string(this->getCost()) + " dollars," +
		"\n|House/hotel cost: " + to_string(this->houseCost) + "|Turret cost: " + to_string((this->houseCost * 2)) + "|";
	return res;
}

std::string Property::getOwner() {
	return this->owner;
}
void Property::setOwner(std::string newOwner) {
	this->owner = newOwner;
}

void Property::setNumHouses(int newNumHouses) {
	this->houses = newNumHouses;
}

void Property::setNumHotels(int newNumHotels) {
	this->hotels = newNumHotels;
}

void Property::setNumTurrets(int newNumTurrets) {
	this->turrets = newNumTurrets;
}

int Property::getRent() {

	int rent{ this->rent };
	switch (this->getNumHouses()) {
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
	if (this->getNumHotels()) {
		rent = this->getHotelRent();
	}
	return rent;
}
int Property::getRailroadRent(Player& owner, vector<Space*>& spaces) {
	vector<Space*> rails = Utilities::getOwnedRailroads(owner, spaces);
	return static_cast<int>(pow(2.0, rails.size() - 1) * 25);
}
int Property::getUtilRent(Player& owner, std::vector<Space*>& spaces, int roll) {
	vector<Space*> utils = Utilities::getOwnedUtilities(owner, spaces);
	return (utils.size() < 2) ? roll * 4 : roll * 10;
}
int Property::getCost() {
	return this->cost;
}
int Property::getNumHouses() {
	return this->houses;
}
int Property::getNumTurrets() {
	return this->turrets;
}
int Property::getNumHotels() {
	return this->hotels;
}
void Property::addHouse() {
	++this->houses;
}
void Property::addHotel() {
	++this->hotels;
}
int Property::getOneHouseRent() {
	return this->oneHouseRent;
}
int Property::getTwoHouseRent() {
	return this->twoHouseRent;
}
int Property::getThreeHouseRent() {
	return this->threeHouseRent;
}
int Property::getFourHouseRent() {
	return this->fourHouseRent;
}
int Property::getHotelRent() {
	return this->hotelRent;
}
int Property::getHouseCost() {
	return this->houseCost;
}
bool Property::isMortgaged() {
	return this->mortgaged;
}
void Property::setMortgage() {
	this->mortgaged = !this->mortgaged;
}
std::string Property::getColor() {
	return this->color;
}
Property::~Property() {
}
;

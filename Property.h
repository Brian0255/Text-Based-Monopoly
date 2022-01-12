#pragma once

#include"Player.h"
#include"Space.h"
#include<string>

class Property : public Space {
public:
	Property(std::string name, std::string type, std::string propertyType, std::string color, int cost, int oneHouseRent, int twoHouseRent, int threeHouseRent,
		int fourHouseRent, int hotelRent, int houseCost, int rent, std::string owner, bool owned, bool mortgaged);

	std::string toString();
	std::string getPropertyType();
	std::string getOwner();
	void setOwner(std::string newOwner);
	int getNumHouses();
	void setNumHouses(int newNumHouses);
	void addHouse();
	int getNumHotels();
	void setNumHotels(int newNumHotels);
	void addHotel();
	int getNumTurrets();
	void setNumTurrets(int newNumTurrets);
	int getRent();
	int getRailroadRent(Player& player, std::vector<Space*>& spaces);
	int getUtilRent(Player& player, std::vector<Space*>& spaces, int roll);
	int getCost();
	int getOneHouseRent();
	int getTwoHouseRent();
	int getThreeHouseRent();
	int getFourHouseRent();
	int getHotelRent();
	int getHouseCost();
	bool isMortgaged();
	void setMortgage();
	std::string getColor();

	//virtual destructor being overrided
	~Property();
private:
	std::string name;
	std::string type;
	std::string propertyType;
	std::string color;
	int cost;
	int rent;
	int turrets;
	int houses;
	int hotels;
	int mortgage;
	int defense;
	int oneHouseRent;
	int twoHouseRent;
	int threeHouseRent;
	int fourHouseRent;
	int hotelRent;
	int houseCost;
	std::string owner;
	bool owned;
	bool mortgaged;
};

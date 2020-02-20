#pragma once

#include"Player.h"
#include"Space.h"
#include<string>

class Property : public Space
{
public:
	//the constructor
	Property(std::string name, std::string type, std::string propertyType, std::string color, int cost, int oneHouseRent, int twoHouseRent, int threeHouseRent,
		int fourHouseRent, int hotelRent, int houseCost, int rent, std::string owner, bool owned, bool mortgaged);

	//formats the property nicely into a string
	std::string toString();

	//getters and setters
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
	//the space's name
	std::string name;

	//the space type
	std::string type;

	//the property type("STANDARD","RAILROAD","UTILITY",etc.)
	std::string propertyType;

	//the color(MAGENTA, BLUE, etc.)
	std::string color;

	//the cost to purchase
	int cost;

	//the base rent
	int rent;

	//the number of turrets built
	int turrets;

	//the number of houses built
	int houses;

	//the number of hotels built
	int hotels;

	//the cost to mortgage
	int mortgage;

	//the property's defense(i don't think i used this)
	int defense;

	//the rent with one house built
	int oneHouseRent;

	//the rent with two houses built
	int twoHouseRent;

	//the rent with three houses built
	int threeHouseRent;

	//the rent with four houses built
	int fourHouseRent;

	//the rent with one hotel built
	int hotelRent;

	//the cost to purchase a house(and a hotel, they are the same)
	int houseCost;

	//the player's name that owns it
	std::string owner;

	//represents if the property is owned
	bool owned;

	//represents if the property is mortgaged
	bool mortgaged;
};

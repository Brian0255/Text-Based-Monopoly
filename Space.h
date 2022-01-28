#pragma once
#include"Player.h"
#include<string>

class Space {
public:
	Space(std::string, std::string);

	std::string getName();
	std::string getType();

	//virtual methods to be overridden in the Property class(including the virtual destructor):
	virtual ~Space();
	virtual std::string toString();
	virtual std::string getPropertyType();
	virtual std::string getOwner();
	virtual void setOwner(std::string newOwner);

	virtual void setNumHouses(int newNumHouses);
	virtual void setNumHotels(int newNumHotels);
	virtual void setNumTurrets(int newNumTurrets);

	virtual int getCost();
	virtual int getNumHouses();

	virtual void addHouse();
	virtual void addHotel();

	virtual int getNumTurrets();
	virtual int getNumHotels();

	virtual int getOneHouseRent();
	virtual int getTwoHouseRent();
	virtual int getThreeHouseRent();
	virtual int getFourHouseRent();
	virtual int getHotelRent();
	virtual int getRent();

	virtual int getRailroadRent(Player& player, std::vector<Space*>& spaces);
	virtual int getUtilRent(Player& player, std::vector<Space*>& spaces, int roll);
	virtual int getHouseCost();

	virtual std::string getColor();

	virtual bool isMortgaged();
	virtual void setMortgage();

private:
	std::string name;
	std::string type;
};

#pragma once
#include<string>

class Card
{
public:
	Card(std::string cardType, std::string effect, int amount, int percentChance, std::string desc);
	
	std::string toString();
	std::string getDesc();
	std::string getEffect();

private:
	std::string cardType;
	std::string effect; 
	int amount;
	int percentChance;
	std::string desc;
	
	friend class CardHandler;
};

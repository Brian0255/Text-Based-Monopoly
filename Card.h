#pragma once
#include<string>

class Card
{
public:
	//the constructor for Card
	Card(std::string cardType, std::string effect, int amount, int percentChance, std::string desc);

	//formats card into a string
	std::string toString();

	//gets description
	std::string getDesc();

	//gets the card effect("pay","get",etc.)
	std::string getEffect();

private:
	//the card type(community,chance,collectable)
	std::string cardType;

	//the effect("pay","get",etc.)
	std::string effect; 

	//the amount the card affects with
	int amount;

	//the chance out of 100 for the card to draw
	int percentChance;

	//a basic description of the card
	std::string desc;

	//this declaration is so CardHandler can directly access these attributes, which I thought was a good idea
	friend class CardHandler;
};

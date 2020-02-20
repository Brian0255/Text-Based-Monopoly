#include "Card.h"

//not much to explain here

Card::Card(std::string cType, std::string eff, int amt, int percChance, std::string d)
	:cardType{ cType }, effect{ eff }, amount{ amt }, percentChance{ percChance }, desc{ d } {}

std::string Card::toString()
{
	return this->cardType + " - " + this->desc;
}

std::string Card::getDesc()
{
	return this->desc;
}

std::string Card::getEffect()
{
	return this->effect;
}
;

#include "Card.h"

Card::Card(std::string cType, std::string eff, int amt, int percChance, std::string d)
	: cardType{ cType },
	effect{ eff },
	amount{ amt },
	percentChance{ percChance },
	desc{ d } {}

Card::Card()
	: cardType{ "None" },
	effect{ "None" },
	amount{ 0 },
	percentChance{ 0 },
	desc{ "" }{};

std::string Card::toString() { return this->cardType + " - " + this->desc; }

std::string Card::getDesc() { return this->desc; }

std::string Card::getEffect() { return this->effect; };

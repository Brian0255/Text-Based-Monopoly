 #include "Player.h"
#include"Utilities.h"

using namespace std;

Player::Player(std::string n, int c, int spot, bool jail, bool railroad, bool computerControlled)
	:name{ n }, cash{ c }, currentSpot{ spot }, defense{ 0 }, inJail{ jail }, 
	onRailroad{ railroad }, hp{ 100 }, bidding{ true }, alwaysOneTwo{ false },
	AI{ computerControlled }, roll{ 0 }, doRoll{ true }, bankrupt{ false }, 
	jailAttempts{ 0 }, doublesRolled{ 0 }, alwaysDoubles{ false } {}

Player::Player()
	: name{ "NONE" }, cash{ 0 }, currentSpot{ 0 }, inJail{ false }, onRailroad{ false }, AI{ false } {}

int Player::getCurrentSpot()
{
	return this->currentSpot;
}
void Player::setCurrentSpot(int newSpot)
{
	this->currentSpot = newSpot;
}
int Player::getRoll()
{
	return this->roll;
}
void Player::setRoll(int newRoll)
{
	this->roll = newRoll;
}
std::string Player::getName()
{
	return this->name;
}
int Player::getCash()
{
	return this->cash;
}
std::vector<Card> Player::getCards()
{
	return this->cards;
}
void Player::setCash(int newCash)
{
	this->cash = newCash;
}
void Player::setCards(std::vector<Card> newCards)
{
	this->cards = newCards;
}
void Player::addCash(int amt)
{
	this->cash += amt;
}
void Player::deductCash(int amt)
{
	this->cash = (this->cash-amt < 0) ? 0 : this->cash-amt;
}
bool Player::canDeduct(int amt)
{
	return (this->cash - amt > 0) ? true : false;
}
void Player::setBankruptcy(bool newBankruptcy)
{
	this->bankrupt = newBankruptcy;
	if (bankrupt)
	{
		this->setCurrentSpot(41);
		//set them out of bounds so they can't end up battling other players even though they're bankrupt
	}
}
bool Player::isBankrupt()
{
	return this->bankrupt;
}
bool Player::isAI()
{
	return this->AI;
}
int Player::getDoublesRolled()
{
	return this->doublesRolled;
}
void Player::setDoublesRolled(int newRoll)
{
	this->doublesRolled = newRoll;
}
int Player::getJailAttempts()
{
	return this->jailAttempts;
}
void Player::addJailAttempt()
{
	++this->jailAttempts;
}
bool Player::canRoll()
{
	return this->doRoll;
}
void Player::setRolling(bool newRolling)
{
	this->doRoll = newRolling;
}
bool Player::isInJail()
{
	return this->inJail;
}
void Player::setJail(bool newJail)
{
	this->inJail = newJail;
}
int Player::getDefense()
{
	return this->defense;
}
void Player::setDefense(int newDefense)
{
	this->defense = newDefense;
}
int Player::getHP()
{
	return this->hp;
}
void Player::setHP(int newHP)
{
	this->hp = (newHP <= 0) ? 0 : newHP;
}
bool Player::isBidding()
{
	return this->bidding;
}
void Player::setBidding(bool newBidding)
{
	this->bidding = newBidding;
}
void Player::setOneTwo(bool newOneTwo)
{
	this->alwaysOneTwo = newOneTwo;
}
void Player::setAlwaysDoubles(bool newDoubles)
{
	this->alwaysDoubles = newDoubles;
}
bool Player::getAlwaysDoubles()
{
	return this->alwaysDoubles;
}
bool Player::getOneTwo()
{
	return this->alwaysOneTwo;
}
bool Player::canDoubleRoll()
{
	return this->doubleRoll;
}
void Player::setDoubleRoll(bool newDoubleRoll)
{
	this->doubleRoll = newDoubleRoll;
}
;


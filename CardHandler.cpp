#include "CardHandler.h"
#include"Utilities.h"
#include<Windows.h>
#include<vector>
#include<string>
#include<iostream>

using namespace std;

vector<Card> CardHandler::commCards;
vector<Card> CardHandler::chanceCards;
vector<Card> CardHandler::collectableCards;

void affectActual(vector<Player>& curPlayers, Player& actual);

void CardHandler::handleCard(vector<Player>& curPlayers, Game& game, Player & player, Card card)
{
	string type = card.effect;
	vector<string> out;
	out.push_back(card.desc);
	game.setGameOutput(out);
	game.displayBoard();
	if (type == "get")
	{
		player.addCash(card.amount);
		game.setInfo(player);
		out.push_back("Cash successfully added.");
	}
	else if (type == "pay")
	{
		player.deductCash(card.amount);
		game.setInfo(player);
		if (player.getCash() <= 0)
		{
			out.push_back("Oh no! You went bankrupt! Better luck next time...");
			player.setBankruptcy(true);
			Utilities::resetOwnership(player, game.getSpaces());
			Sleep(3000);
		}
		else
		{
			out.push_back("Cash successfully deducted.");
			Sleep(3000);
		}
	}
	else if (type == "advanceGo")
	{
		player.setCurrentSpot(0);
		player.addCash(200);
		game.setInfo(player);
		out.push_back("You successfully warped to go and got $200.");
		Sleep(3000);
	}
	else if (type == "goJail")
	{
		player.setCurrentSpot(10);
		game.setInfo(player);
		player.setJail(true);
		player.setRolling(false);
		out.push_back("You're in jail now! Good luck getting out of there...");
	}
	else if (type == "lose")
	{
		out.push_back("Better luck next time...");
		game.setInfo(player);
		player.setBankruptcy(true);
		Utilities::resetOwnership(player, game.getSpaces());
	}
	else if (type == "win")
	{
		for (auto& otherPlayer : curPlayers)
		{
			if (otherPlayer.getName() != player.getName())
			{
				otherPlayer.setBankruptcy(true);
				Utilities::resetOwnership(player, game.getSpaces());
			}
		}
		out.push_back("Not a very skillful victory, but it is still one nonetheless...");
		game.setInfo(player);
	}
	else if (type == "payEach")
	{
		bool keepPaying{ true };
		for (auto& otherPlayer : curPlayers)
		{
			if (otherPlayer.getName() != player.getName())
			{
				if(keepPaying)
				{
					if (player.getCash() <= 0)
					{
						out.push_back("Oh no! " + player.getName() + " went bankrupt! Better luck next time...");
						out.push_back("No one else can get " + player.getName() + "'s cash because " + player.getName() + " went bankrupt.");
						player.setBankruptcy(true);
						game.setInfo(player);
						Utilities::resetOwnership(player, game.getSpaces());
						keepPaying = false;
					}
					else
					{
						int amt = (player.getCash() > card.amount) ? card.amount : player.getCash();
						player.deductCash(amt);
						otherPlayer.addCash(amt);
						game.setInfo(player);
						out.push_back(otherPlayer.getName() + " received " + to_string(amt) + " dollars.");
					}
				}
			}
		}
	}
	else if (type == "goBack")
	{
		player.setCurrentSpot(player.getCurrentSpot() - card.amount);
		game.setInfo(player);
		out.push_back("You were moved back " + to_string(card.amount) + " spaces.");
	}
	else if (type == "doubleRoll")
	{
		player.setDoubleRoll(true);
	}
	else if (type == "getOutJail")
	{
		player.setCurrentSpot(11);
		player.setJail(false);
		game.setInfo(player);
		out.push_back("You were successfully moved a spot in front of jail. Phew!");
	}
	else if (type == "getPlayer")
	{
		vector<Player> availPlayers;
		for (auto& other : curPlayers)
		{
			if (other.getName() != player.getName())
			{
				availPlayers.push_back(other);
			}
		}
		Player randomPlayer = Utilities::getRandomElement(availPlayers);
		
		int amt = (randomPlayer.getCash() > card.amount) ? card.amount : randomPlayer.getCash();
		randomPlayer.deductCash(amt);
		player.addCash(amt);
		game.setInfo(player);
		game.displayBoard();
		out.push_back(player.getName() + " received " + to_string(amt) + " dollars from " + randomPlayer.getName() + ".");
		Sleep(2000);
		if (randomPlayer.getCash()<=0)
		{
			out.push_back("Oh no! " + randomPlayer.getName() + " went bankrupt! Better luck next time...");
			randomPlayer.setBankruptcy(true);
			Utilities::resetOwnership(randomPlayer, game.getSpaces());
			affectActual(curPlayers, randomPlayer);
		}
	}
	game.setGameOutput(out);
	game.displayBoard();
	Sleep(3000);
}

void CardHandler::addCard(Card card)
{
	if (card.cardType == "comm")
	{
		for (int i{ 0 }; i < card.percentChance; ++i)
		{
			commCards.push_back(card);
		}
	}
	else if (card.cardType == "chance")
	{
		for (int i{ 0 }; i < card.percentChance; ++i)
		{
			chanceCards.push_back(card);
		}
	}
	else if (card.cardType == "collect")
	{
		for (int i{ 0 }; i < card.percentChance; ++i)
		{
			collectableCards.push_back(card);
		}
	}
}

Card CardHandler::drawCard(std::string type,Player& player, Game& game)
{
	game.displayBoard();
	int getCollect = rand() % 2;
	vector<Card> collects = player.getCards();

	if (type == "CHANCE")
	{
		cout << "You will now draw a chance card..." << endl;
		Sleep(2000);
		if (getCollect == 0)
		{
			cout << "What luck! You also draw a collectable card." << endl;
			Sleep(1000);
			Card collect = Utilities::getRandomElement(CardHandler::collectableCards);
			collects.push_back(collect);
			cout << "You got the following collectable card: " << endl << collect.getDesc() << endl;
			Sleep(3000);
			player.setCards(collects);
		}
		return Utilities::getRandomElement(CardHandler::chanceCards);
	}
	else if (type == "COMM")
	{
		cout << "You will now draw a community card..." << endl;
		Sleep(2000);
		if (getCollect == 0)
		{
			cout << "What luck! You also draw a collectable card." << endl;
			Sleep(1000);
			Card collect = Utilities::getRandomElement(CardHandler::collectableCards);
			collects.push_back(collect);
			cout << "You got the following collectable card: " << endl << collect.getDesc() << endl;
			Sleep(3000);
			player.setCards(collects);
		}
		return Utilities::getRandomElement(CardHandler::commCards);
	}
}

void affectActual(vector<Player>& curPlayers, Player& toCopy)
{
	for (auto& player : curPlayers)
	{
		if (player.getName() == toCopy.getName())
		{
			player = toCopy;
		}
	}
}

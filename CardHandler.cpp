#include "CardHandler.h"
#include"Utilities.h"
#include<Windows.h>
#include<vector>
#include<string>
#include<iostream>

using namespace std;

//declaring the static members to avoid errors
vector<Card> CardHandler::commCards;
vector<Card> CardHandler::chanceCards;
vector<Card> CardHandler::collectableCards;

//a helper function i used to avoid copies not afffecting the actual player
void affectActual(vector<Player>& curPlayers, Player& actual);

void CardHandler::handleCard(vector<Player>& curPlayers, Game& game, Player & player, Card card)
{
	string type = card.effect;
	vector<string> out; //will be set to gameOutput later
	out.push_back(card.desc);
	game.setGameOutput(out);
	game.displayBoard();
	if (type == "get") //player gets money
	{
		player.addCash(card.amount);
		game.setInfo(player);
		out.push_back("Cash successfully added.");
	}
	else if (type == "pay") //player must pay
	{
		player.deductCash(card.amount);
		game.setInfo(player);
		if (player.getCash() <= 0)//not enough money to pay, bankrupt
		{
			out.push_back("Oh no! You went bankrupt! Better luck next time...");
			player.setBankruptcy(true);
			Utilities::resetOwnership(player, game.getSpaces());
			Sleep(3000);
		}
		else//they had enough
		{
			out.push_back("Cash successfully deducted.");
			Sleep(3000);
		}
	}
	else if (type == "advanceGo")//they warp to GO
	{
		player.setCurrentSpot(0);//0 is the GO space in the spaces vector
		player.addCash(200);
		game.setInfo(player);
		out.push_back("You successfully warped to go and got $200.");
		Sleep(3000);
	}
	else if (type == "goJail")
	{
		player.setCurrentSpot(10);//10 is the jail spot in the spaces vector
		game.setInfo(player);
		player.setJail(true);
		player.setRolling(false);
		//this is used for one specific scenario, which is when
		//the player rolls doubles and gets this card, they can't roll again
		out.push_back("You're in jail now! Good luck getting out of there...");
	}
	else if (type == "lose")
	{
		//oof
		out.push_back("Better luck next time...");
		game.setInfo(player);
		player.setBankruptcy(true);
		Utilities::resetOwnership(player, game.getSpaces());
	}
	else if (type == "win")
	{
		//make everyone else bankrupt except the player that drew this card
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
		//this is used to prevent the bankrupt dialogue to keep printing
		//which would happen if they had to pay 3 players and went bankrupt after the firtst one
		for (auto& otherPlayer : curPlayers)
		{
			if (otherPlayer.getName() != player.getName())
			{
				if(keepPaying)
				{
					//make sure player isn't bankrupt before paying
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
						//remove as much as the player has
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
		//pretty simple
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
		//moves them a spot in front of jail, which is space 11
		player.setCurrentSpot(11);
		player.setJail(false);
		game.setInfo(player);
		out.push_back("You were successfully moved a spot in front of jail. Phew!");
	}
	else if (type == "getPlayer")
	{
		//the players they can grab cash from cannot include themselves, so I do this
		vector<Player> availPlayers;
		for (auto& other : curPlayers)
		{
			if (other.getName() != player.getName())
			{
				availPlayers.push_back(other);
			}
		}
		Player randomPlayer = Utilities::getRandomElement(availPlayers);

		//a ternary operator:
		//if they have the card amount, deduct that
		//if they dont, give em everything they got
		int amt = (randomPlayer.getCash() > card.amount) ? card.amount : randomPlayer.getCash();
		randomPlayer.deductCash(amt);
		player.addCash(amt);
		game.setInfo(player);
		game.displayBoard();
		out.push_back(player.getName() + " received " + to_string(amt) + " dollars from " + randomPlayer.getName() + ".");
		Sleep(2000);
		if (randomPlayer.getCash()<=0)
		{
			//player went bankrupt
			out.push_back("Oh no! " + randomPlayer.getName() + " went bankrupt! Better luck next time...");
			randomPlayer.setBankruptcy(true);
			Utilities::resetOwnership(randomPlayer, game.getSpaces());
			//set the actual player to randomPlayer to reflect changes made to the copy,
			//which was grabbed from getRandomElement at line 152
			affectActual(curPlayers, randomPlayer);
		}
	}
	game.setGameOutput(out);
	game.displayBoard();
	Sleep(3000);
}

void CardHandler::addCard(Card card)
{
	//adds cards based on the type

	//the way I did the randomness is a pretty weird way to do it
	//it pushes back into the vector based on the percent chance
	//i made sure all the percents added to 100 for each one so it's actually accurate

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
	int getCollect = rand() % 2; // 50% chance to grab a collectable when you draw a chance or community card
	vector<Card> collects = player.getCards(); //grab the collectables the player has

	//both of these if statements are basically the same, just different based on the type
	if (type == "CHANCE")
	{
		cout << "You will now draw a chance card..." << endl;
		Sleep(2000);
		if (getCollect == 0) //again, just doing a coin flip here
		{
			cout << "What luck! You also draw a collectable card." << endl;
			Sleep(1000);
			Card collect = Utilities::getRandomElement(CardHandler::collectableCards);//get a random collectable card
			collects.push_back(collect); //add card to player's collectables
			cout << "You got the following collectable card: " << endl << collect.getDesc() << endl;
			Sleep(3000);
			player.setCards(collects);
		}
		return Utilities::getRandomElement(CardHandler::chanceCards); //return a random selection from the chance cards
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
	//a copy is passed into this function, which is then set to the actual player in curPlayers
	//this was used to make sure changes made to a copy were actually reflected
	for (auto& player : curPlayers)
	{
		if (player.getName() == toCopy.getName())
		{
			player = toCopy;
		}
	}
}

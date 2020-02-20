#pragma once
#include"Player.h"
#include"Card.h"
#include"Game.h"
#include<string>
#include<vector>
#include"Utilities.h"

class CardHandler
{
public:
	//does all the card effects correctly
	static void handleCard(std::vector<Player>& curPlayers, Game& game, Player& player, Card card);

	//adds a card to the correct deck(commCards,chanceCards,collectableCards) depending on the type
	static void addCard(Card card);

	//a vector of community cards
	static std::vector<Card> commCards;

	//a vector of chance cards
	static std::vector<Card> chanceCards;

	//a vector of collectable cards
	static std::vector<Card> collectableCards;

	//draws a card from the correct deck using the card type
	static Card drawCard(std::string type, Player& player, Game& game);
private:
};

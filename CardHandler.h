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
	static void handleCard(std::vector<Player>& curPlayers, Game& game, Player& player, Card card);

	static void addCard(Card card);

	static std::vector<Card> commCards;
	static std::vector<Card> chanceCards;
	static std::vector<Card> collectableCards;

	static Card drawCard(std::string type, Player& player, Game& game);
private:
};

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

	static void handleGetOutJail(Player& player, Game& game, std::vector<std::string>& out);
	static void handleGoBack(Player& player, Card& card, Game& game, std::vector<std::string>& out);
	static void handleGetPlayerCash(std::vector<Player>& curPlayers, Player& player, Card& card, Game& game, std::vector<std::string>& out);
	static void handlePayEach(std::vector<Player>& curPlayers, Player& player, std::vector<std::string>& out, Game& game, Card& card);
	static void handleWinCard(std::vector<Player>& curPlayers, Player& player, Game& game, std::vector<std::string>& out);
	static void handleLose(std::vector<std::string>& out, Game& game, Player& player);
	static void handleGoToJail(Player& player, Game& game, std::vector<std::string>& out);
	static void handleAdvanceGo(Player& player, Game& game, std::vector<std::string>& out);
	static void handlePayCard(Player& player, Card& card, Game& game, std::vector<std::string>& out);
	static void handleGetCard(Player& player, Card& card, Game& game, std::vector<std::string>& out);

	static void addCard(Card card);
    static Card drawCard(std::string type, Player& player, Game& game);
    static void tryForCollectableCard(Player&);

	static std::vector<Card> commCards;
	static std::vector<Card> chanceCards;
	static std::vector<Card> collectableCards;

	static void setCards();
private:
};

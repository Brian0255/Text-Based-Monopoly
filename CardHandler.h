#pragma once
#include"Player.h"
#include"Card.h"
#include"Game.h"
#include<string>
#include<vector>
#include"Utilities.h"

class CardHandler {
public:
	static std::vector<Card> commCards;
	static std::vector<Card> chanceCards;
	static std::vector<Card> collectableCards;

	CardHandler(std::vector<Player>&, Game&, Player&, Card);

	void handle();

	void handleGetOutJail();
	void handleGoBack();
	void handleGetPlayerCash();
	void handlePayEach();
	void handleWinCard();
	void handleLose();
	void handleGoToJail();
	void handleAdvanceGo();
	void handlePayCard();
	void handleGetCard();

	static void addCard(Card card);
	void drawCard(std::string type);
	void tryForCollectableCard();

	static void setCards();
private:
	std::vector<Player>& curPlayers;
	Game& game;
	Player& player;
	Card card;
	std::vector<std::string> out;
};

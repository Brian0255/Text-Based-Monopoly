#include "CardHandler.h"

#include <Windows.h>

#include <iostream>
#include <string>
#include <vector>

#include "Utilities.h"

using namespace std;

std::vector<Card> CardHandler::commCards = std::vector<Card>();
std::vector<Card> CardHandler::chanceCards = std::vector<Card>();
std::vector<Card> CardHandler::collectableCards = std::vector<Card>();

void CardHandler::handle() {
	string type = card.effect;
	out.push_back(card.desc);
	game.setGameOutput(out);
	game.displayBoard();
	if (type == "get") {
		handleGetCard();
	}
	else if (type == "pay") {
		handlePayCard();
	}
	else if (type == "advanceGo") {
		handleAdvanceGo();
	}
	else if (type == "goJail") {
		handleGoToJail();
	}
	else if (type == "lose") {
		handleLose();
	}
	else if (type == "win") {
		handleWinCard();
	}
	else if (type == "payEach") {
		handlePayEach();
	}
	else if (type == "goBack") {
		handleGoBack();
	}
	else if (type == "doubleRoll") {
		player.setDoubleRoll(true);
	}
	else if (type == "getOutJail") {
		handleGetOutJail();
	}
	else if (type == "getPlayer") {
		handleGetPlayerCash();
	}
	game.setGameOutput(out);
	game.displayBoard();
	Sleep(3000);
}

CardHandler::CardHandler(std::vector<Player>& curPlrs, Game& g, Player& plr, Card c)
	: curPlayers{ curPlrs }, game{ g }, player{ plr }, card{ c } {
	out = std::vector<string>();
};

void CardHandler::handleGetOutJail() {
	player.setCurrentSpot(11);
	player.setJail(false);
	game.setInfo(player);
	out.push_back("You were successfully moved a spot in front of jail. Phew!");
}

void CardHandler::handleGoBack() {
	player.setCurrentSpot(player.getCurrentSpot() - card.amount);
	game.setInfo(player);
	out.push_back("You were moved back " + to_string(card.amount) + " spaces.");
}

void CardHandler::handleGetPlayerCash() {
	vector<Player> availPlayers;
	for (auto& other : curPlayers) {
		if (other.getName() != player.getName()) {
			availPlayers.push_back(other);
		}
	}
	Player& randomPlayer = Utilities::getRandomElement(availPlayers);

	int amt = (randomPlayer.getCash() > card.amount) ? card.amount
		: randomPlayer.getCash();
	randomPlayer.deductCash(amt);
	player.addCash(amt);
	game.setInfo(player);
	game.displayBoard();
	out.push_back(player.getName() + " received " + to_string(amt) + " dollars from " + randomPlayer.getName() + ".");
	Sleep(2000);
	if (randomPlayer.getCash() <= 0) {
		out.push_back("Oh no! " + randomPlayer.getName() +
			" went bankrupt! Better luck next time...");
		randomPlayer.setBankruptcy(true);
		Utilities::resetOwnership(randomPlayer, game.getSpaces());
	}
}

void CardHandler::handlePayEach() {
	bool keepPaying{ true };
	for (auto& otherPlayer : curPlayers) {
		if (otherPlayer.getName() != player.getName()) {
			if (keepPaying) {
				if (player.getCash() <= 0) {
					out.push_back("Oh no! " + player.getName() +
						" went bankrupt! Better luck next time...");
					out.push_back("No one else can get " + player.getName() +
						"'s cash because " + player.getName() +
						" went bankrupt.");
					player.setBankruptcy(true);
					game.setInfo(player);
					Utilities::resetOwnership(player, game.getSpaces());
					keepPaying = false;
				}
				else {
					int amt = (player.getCash() > card.amount) ? card.amount
						: player.getCash();
					player.deductCash(amt);
					otherPlayer.addCash(amt);
					game.setInfo(player);
					out.push_back(otherPlayer.getName() + " received " +
						to_string(amt) + " dollars.");
				}
			}
		}
	}
}

void CardHandler::handleWinCard() {
	for (auto& otherPlayer : curPlayers) {
		if (otherPlayer.getName() != player.getName()) {
			otherPlayer.setBankruptcy(true);
			Utilities::resetOwnership(player, game.getSpaces());
		}
	}
	out.push_back("Not a very skillful victory, but it is still one nonetheless...");
	game.setInfo(player);
}

void CardHandler::handleLose() {
	out.push_back("Better luck next time...");
	game.setInfo(player);
	player.setBankruptcy(true);
	Utilities::resetOwnership(player, game.getSpaces());
}

void CardHandler::handleGoToJail() {
	player.setCurrentSpot(10);
	game.setInfo(player);
	player.setJail(true);
	player.setRolling(false);
	out.push_back("You're in jail now! Good luck getting out of there...");
}

void CardHandler::handleAdvanceGo() {
	player.setCurrentSpot(0);
	player.addCash(200);
	game.setInfo(player);
	out.push_back("You successfully warped to go and got $200.");
	Sleep(3000);
}

void CardHandler::handlePayCard() {
	player.deductCash(card.amount);
	game.setInfo(player);
	if (player.getCash() <= 0) {
		out.push_back("Oh no! You went bankrupt! Better luck next time...");
		player.setBankruptcy(true);
		Utilities::resetOwnership(player, game.getSpaces());
		Sleep(3000);
	}
	else {
		out.push_back("Cash successfully deducted.");
		Sleep(3000);
	}
}

void CardHandler::handleGetCard() {
	player.addCash(card.amount);
	game.setInfo(player);
	out.push_back("Cash successfully added.");
}

void CardHandler::addCard(Card card) {
	if (card.cardType == "comm") {
		for (int i{ 0 }; i < card.percentChance; ++i) {
			commCards.push_back(card);
		}
	}
	else if (card.cardType == "chance") {
		for (int i{ 0 }; i < card.percentChance; ++i) {
			chanceCards.push_back(card);
		}
	}
	else if (card.cardType == "collect") {
		for (int i{ 0 }; i < card.percentChance; ++i) {
			collectableCards.push_back(card);
		}
	}
}

void CardHandler::drawCard(std::string type) {
	game.displayBoard();

	if (type == "CHANCE") {
		cout << "You will now draw a chance card..." << endl;
		Sleep(2000);
		tryForCollectableCard();
		card = Utilities::getRandomElement(CardHandler::chanceCards);
	}
	else if (type == "COMM") {
		cout << "You will now draw a community card..." << endl;
		Sleep(2000);
		tryForCollectableCard();
		card = Utilities::getRandomElement(CardHandler::commCards);
	}
}

void CardHandler::tryForCollectableCard() {
	int getCollect = rand() % 2;
	vector<Card> collectables = player.getCards();

	if (getCollect == 0) {
		cout << "What luck! You also draw a collectable card." << endl;
		Sleep(1000);
		Card collect = Utilities::getRandomElement(CardHandler::collectableCards);
		collectables.push_back(collect);
		cout << "You got the following collectable card: " << endl
			<< collect.getDesc() << endl;
		Sleep(3000);
		player.setCards(collectables);
	}
}

void CardHandler::setCards() {
	addCard(Card{ "comm","get",10,5,"You win a contest for the world's ugliest person - you get $10" });
	addCard(Card{ "comm","pay",50,7,"Your toilet breaks. You must pay the plumber $50." });
	addCard(Card{ "comm","get",100,2,"You get elected as mayor and get $100." });
	addCard(Card{ "comm","pay",300,2,"Your dog breaks out and gets attacked by a coyote. You must pay the vet $300." });
	addCard(Card{ "comm","pay",100,3,"Your grandma dies. You must pay $100 for funeral expenses." });
	addCard(Card{ "comm","pay",30,10,"Your car breaks down. You must pay $30." });
	addCard(Card{ "comm","advanceGo",0,15,"You advance to go and collect $200." });
	addCard(Card{ "comm","goJail",0,10,"Oh no! You must go to jail!" });
	addCard(Card{ "comm","pay",50,10,"Your cat scratches the mayor. You must pay $50." });
	addCard(Card{ "comm","get",300,1,"Your dog wins a beauty pageant. You get $300." });
	addCard(Card{ "comm","get",50,10, "The town cuts taxes and you get a break. You get $50." });
	addCard(Card{ "comm","get",10,15,"You win $10 off of a scratch ticket." });
	addCard(Card{ "comm","get",30,5,"You win $30 off of a scratch ticket." });
	addCard(Card{ "comm","pay",50,5,"You lose $50 wasting money on scratch tickets." });

	addCard(Card{ "chance","lose",0,2,"You waste all your money on casino slots! You go bankrupt!" });
	addCard(Card{ "chance","win",50,1,"You hide in a cave while everyone else gets robbed and goes bankrupt. You win!" });
	addCard(Card{ "chance","pay",200,5,"You must pay the banker $200." });
	addCard(Card{ "chance","pay",20,15,"You must pay the banker $20." });
	addCard(Card{ "chance","pay",50,10,"You must pay the banker $50." });
	addCard(Card{ "chance","get",1000,1,"You find the Mona Lisa painting in your basement. An art curator gives you $1000 for it.." });
	addCard(Card{ "chance","get",50,10,"The banker cuts you a deal and gives you $50." });
	addCard(Card{ "chance","get",50,15,"You play guitar on the street and end up collecting $50." });
	addCard(Card{ "chance","get",100,5,"You find $100 on the ground and decide to pocket it." });
	addCard(Card{ "chance","payEach",50,3,"You lose a bet attempting to gamble with the other players. You must pay everyone $50." });
	addCard(Card{ "chance","advanceGo",0,10, "You advance to go and collect $200." });
	addCard(Card{ "chance","goJail",0,5,"Oh no! You must go to jail!" });
	addCard(Card{ "chance","goBack",3,5,"You slip on a banana peel and fall backwards 3 spaces." });
	addCard(Card{ "chance","goBack",5,3,"You see a dog 5 spaces back and run towards it." });
	addCard(Card{ "chance","goBack",2,10,"You left your wallet 2 spaces back and have to go back for it." });

	addCard(Card{ "collect","get",25,20,"This card will grant you $25 from the bank." });
	addCard(Card{ "collect","get",50,10,"This card will grant you $50 from the bank." });
	addCard(Card{ "collect","get",100,5,"This card will grant you $100 from the bank." });
	addCard(Card{ "collect","getPlayer",25,20, "This card will give you $25 from a random player." });
	addCard(Card{ "collect","getPlayer",50,10,"This card will give you $50 from a random player." });
	addCard(Card{ "collect","getPlayer",100,5,"This card will give you $100 from a random player." });
	addCard(Card{ "collect","doubleRoll",0,15,"This card will double your next roll." });
	addCard(Card{ "collect","getOutJail",0,15,"This card will get you out of jail." });
}

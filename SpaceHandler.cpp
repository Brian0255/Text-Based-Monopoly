#include "SpaceHandler.h"
#include"Utilities.h"
#include<vector>
#include<string>
#include<iostream>
#include<Windows.h>
#include"CardHandler.h"

using namespace std;

int getBidders(vector<Player>& bidders);

void SpaceHandler::handle() {
	game.displayBoard();

	string type = curSpace->getType();
	int cost = curSpace->getCost();

	checkForABattle();

	if (type == "PROPERTY") {
		game.displayBoard();
		handlePropertySpace(cost);
	}
	else if (type == "TAX_SPACE") {
		handleTaxSpace();
	}
	else if (type == "GOTO_JAIL") {
		handleJailSpace();
	}
	else if (type == "COMM" || type == "CHANCE") {
		CardHandler handler = CardHandler(curPlayers, game, curPlayer, Card());
		handler.drawCard(type);
		handler.handle();
	}
	else if (type == "JAIL" || type == "FREE") {
		cout << "The space you landed on does nothing to you." << endl;
		Sleep(3000);
	}
}

void SpaceHandler::handleJailSpace() {
	game.displayBoard();
	cout << "You will now be sent to jail. OOF!" << endl;
	Sleep(3000);
	curPlayer.setJail(true);
	curPlayer.setCurrentSpot(10);
}

void SpaceHandler::handleTaxSpace() {
	if (curSpace->getName() == "Income Tax") {
		handleIncomeTax();
	}
	else if (curSpace->getName() == "Luxury Tax") {
		handleLuxuryTax();
	}
}

void SpaceHandler::handleLuxuryTax() {
	game.displayBoard();
	cout << "You landed on the luxury tax space.\nYou will now be deducted $100. Bankruptcy is possible." << endl;
	Sleep(3000);
	curPlayer.deductCash(100);
	game.setInfo(curPlayer);
	game.displayBoard();
	if (!checkPlayerBankrupt(curPlayer)) {
		cout << "Cash successfully deducted." << endl;
		Sleep(3000);
	}
}

void SpaceHandler::handleIncomeTax() {
	int assets = game.calculateAssets(curPlayer);
	game.displayBoard();
	if (!curPlayer.isAI()) {
		handleIncomeTaxPlayer(assets);
	}
	else {
		handleIncomeTaxAI();
	}
}

void SpaceHandler::handleIncomeTaxAI() {
	cout << curPlayer.getName() << " landed on income tax. They are now making a decision..." << endl;
	Sleep(4000);
	int payAssets = game.calculateAssets(curPlayer);
	if (payAssets < 200) {
		curPlayer.deductCash(payAssets);
		game.setInfo(curPlayer);
		game.displayBoard();
		if (!checkPlayerBankrupt(curPlayer)) {
			cout << curPlayer.getName() << " decided to pay on their assets for " << payAssets << " dollars." << endl;
			Sleep(4000);
		}
	}
	else {
		curPlayer.deductCash(200);
		game.setInfo(curPlayer);
		if (!checkPlayerBankrupt(curPlayer)) {
			cout << curPlayer.getName() << " decided to just pay 200 dollars." << endl;
			Sleep(3000);
		}
	}
}


void SpaceHandler::handleIncomeTaxPlayer(int assets) {
	cout << "You landed on income tax. Here are your options: " << endl << endl;
	vector<string> choices = { "1 - Pay 10% of your assets(this will cost you " + to_string(assets) + " dollars.",
		"2 - Pay 200 dollars." };
	for (size_t i{ 0 }; i < choices.size(); ++i) {
		cout << choices[i] << endl;
	}
	int choice = Utilities::getIntInRange("Please enter an option: ", 1, 2);
	curPlayer.deductCash((choice == 1) ? assets : 200);
	game.setInfo(curPlayer);
	if (!checkPlayerBankrupt(curPlayer)) {
		cout << "Cash was deducted." << endl;
		Sleep(2000);
	}
}

bool SpaceHandler::checkPlayerBankrupt(Player& player) {
	string bankrupt = "You went bankrupt. Better luck next time...";
	if (player.isAI()) {
		bankrupt = player.getName() + " went bankrupt. Better luck next time...";
	}
	if (player.getCash() <= 0) {
		cout << bankrupt << endl;
		Sleep(3000);
		player.setBankruptcy(true);
		Utilities::resetOwnership(player, game.getSpaces());
		return true;
	}
	return false;
}

void SpaceHandler::handlePropertySpace(int cost) {
	cout << "You have landed on a property." << endl;
	if (curSpace->getOwner() != "None") {
		handleOwnedProperty(cost);
	}
	else {
		handleUnownedProperty(cost);
	}
}

void SpaceHandler::handleUnownedProperty(int cost) {
	bool biddable{ false };
	if (!curPlayer.isAI()) {
		askPlayerToPurchase(cost,biddable);
	}
	else {
		askAIToPurchase(cost, biddable);
	}

	if (biddable) {
		doBid(cost);
	}
}

void SpaceHandler::doBid(int cost) {
	cout << "The property will now be put up for auction, since " << curPlayer.getName() << " did not want it." << endl;
	Sleep(5000);
	int currentBid{ cost };
	vector<Player> bidders;
	int AILimit = cost * 2;

	for (auto& other : curPlayers) {
		if (other.getName() != curPlayer.getName()) {
			if (!other.isAI()) {
				askPlayerParticipateBid(other, currentBid, bidders);
			}
			else {
				askAIParticipateBid(other, currentBid, bidders);
			}
		}
	}

	bool doneBidding{ false };
	while (!doneBidding) {
		if (bidders.empty()) {
			cout << "No one wanted the property. What a shame..." << endl;
			doneBidding = true;
			Sleep(3000);
		}
		else {
			runBidCycle(bidders,currentBid,doneBidding, cost);
		}
	}
}

void SpaceHandler::runBidCycle(std::vector<Player>& bidders, int& currentBid,  bool& doneBidding, int cost) {
	for (auto& bidder : bidders) {
		game.displayBoard();
		if (getBidders(bidders) == 1 && bidder.isBidding()) {
			setBidWinner(bidder, currentBid, doneBidding);
			break;
		}
		else if (getBidders(bidders) > 1) {
			if (bidder.isBidding()) {
				if (bidder.getCash() >= currentBid + 1) {
					if (!bidder.isAI()) {
						askPlayerKeepBidding(currentBid, bidder);
					}
					else {
						askAIKeepBidding(cost, currentBid, bidder);
					}
				}
				else {
					cout << bidder.getName() << " does not have enough money to stay in the bid." << endl;
					bidder.setBidding(false);
					Sleep(3000);
				}
			}
		}
	}
}

void SpaceHandler::askAIKeepBidding(int cost, int& currentBid, Player& bidder) {
	int AILimit = cost * 1.5;
	if (currentBid <= AILimit) {
		int nextPossibleBid = currentBid * 1.1;
		if (bidder.getCash() >= nextPossibleBid) {
			cout << "AI " << bidder.getName() << " is deciding what to raise the bid to..." << endl;
			Sleep(3000);
			currentBid = nextPossibleBid;
			cout << bidder.getName() << " has raised the bid to " << currentBid << " dollars." << endl;
			Sleep(4000);
		}
		else {
			cout << bidder.getName() << " has backed out of the bid..." << endl;
			bidder.setBidding(false);
			Sleep(3000);
		}
	}
	else {
		cout << "The bid got too high for " << bidder.getName() << ", so they backed out." << endl;
		bidder.setBidding(false);
		Sleep(4000);
	}
}

void SpaceHandler::askPlayerKeepBidding(int& currentBid, Player& bidder) {
	cout << "The current bid is " << currentBid << " dollars, " << bidder.getName() << endl;
	cout << "You must bid higher than this value to keep bidding." << endl;
	string keepGoing = Utilities::getStringYesNo("Do you want to keep bidding or back out?(y/n): ");
	if (keepGoing == "Y" || keepGoing == "y") {
		int bid = Utilities::getIntInRange("What would you like to bid?: ", currentBid + 1, bidder.getCash() - 1);
		currentBid = bid;
		cout << bidder.getName() << " has raised the bid to " << currentBid << " dollars." << endl;
		Sleep(3000);
	}
	else if (keepGoing == "N" || keepGoing == "n") {
		bidder.setBidding(false);
		cout << "You successfully chickened out on the bid." << endl;
		Sleep(3000);
	}
}

void SpaceHandler::setBidWinner(Player& bidder, int& currentBid, bool& doneBidding) {
	cout << bidder.getName() << " won the bid and got the property for " << currentBid << " dollars." << endl;
	bidder.deductCash(currentBid);
	curSpace->setOwner(bidder.getName());
	Sleep(3000);
	doneBidding = true;
}

void SpaceHandler::askAIParticipateBid(Player& other, int currentBid, std::vector<Player>& bidders) {
	cout << "AI " << other.getName() << " is deciding if they want to bid..." << endl;
	Sleep(3000);
	if (other.getCash() >= (currentBid * 2)) {
		cout << "AI " << other.getName() << " has decided to bid." << endl;
		Sleep(1500);
		bidders.push_back(other);
	}
	else {
		cout << "AI " << other.getName() << " has decided not to bid." << endl;
		Sleep(1500);
		other.setBidding(false);
	}
}

void SpaceHandler::askPlayerParticipateBid(Player& other, int currentBid, std::vector<Player>& bidders) {
	string ans = Utilities::getStringYesNo(other.getName() + ", would you like to participate in the bidding?(y/n): ");
	if (ans == "Y" || ans == "y") {
		if (other.getCash() <= currentBid + 1) {
			cout << "You don't have enough money to participate in the bidding..." << endl;
			other.setBidding(false);
			Sleep(3000);
		}
		else {
			bidders.push_back(other);
		}
	}
}

void SpaceHandler::askAIToPurchase(int cost, bool& biddable) {
	cout << curPlayer.getName() << " is deciding if they want to purchase the property..." << endl;
	Sleep(3000);

	//AI only purchases if they have at least 2.5 * the cost of the property
	if (curPlayer.getCash() > 2.5 * cost) {
		curPlayer.deductCash(cost);
		curSpace->setOwner(curPlayer.getName());
		game.setInfo(curPlayer);
		game.displayBoard();
		cout << curPlayer.getName() << " bought " << curSpace->getName() << ".\n";
		Sleep(3000);
		biddable = false;
	}
	else {
		cout << curPlayer.getName() << " did not want the property." << endl;
		Sleep(3000);
		biddable = true;
	}
}

void SpaceHandler::askPlayerToPurchase(int cost, bool& biddable) {
	string ans = Utilities::getStringYesNo("Did you want to purchase this property for " + to_string(cost) + " dollars?(y/n):");
	if (ans == "Y" || ans == "y") {
		if (curPlayer.canDeduct(cost)) {
			curPlayer.deductCash(cost);
			curSpace->setOwner(curPlayer.getName());
			game.setInfo(curPlayer);
			game.displayBoard();
			cout << "Property succesfully bought." << endl;
			Sleep(3000);
		}
		else {
			cout << "You do not have enough money..." << endl;
			biddable = true;
			Sleep(3000);
		}
	}
	else if (ans == "N" || ans == "n") {
		biddable = true;
	}
}

void SpaceHandler::handleOwnedProperty(int cost) {
	if (curSpace->getOwner() != curPlayer.getName()) {
		if (!curSpace->isMortgaged()) {
			handleOwnedByAnother(cost);
		}
		else {
			cout << "This property is mortgaged by a player.\nYou cannot attack it, but you also don't have to pay rent." << endl;
			Sleep(4000);
		}
	}
	else {
		cout << "You own this property, so nothing happens..." << endl;
		Sleep(3000);
	}
}

void SpaceHandler::handleOwnedByAnother(int cost) {
	int rent{ 0 };
	Player* owner{ NULL };
	for (int i{ 0 }; i < curPlayers.size(); ++i) {
		if (curPlayers[i].getName() == curSpace->getOwner()) {
			owner = &curPlayers[i];
		}
	}
	vector<Space*> spaces = game.getSpaces();
	rent = getRent(owner, spaces);
	if (!curPlayer.isAI()) {
		ownedByAnotherPlrChoice(cost, rent, owner);
	}
	else {
		ownedByAnotherAIChoice(rent);
	}
}

void SpaceHandler::ownedByAnotherAIChoice(int rent) {
	bool attack{ false };
	cout << curPlayer.getName() << " is making a decision..." << endl;
	Sleep(4000);
	for (auto& owner : curPlayers) {
		bool differentOwner{ owner.getName() != curPlayer.getName() };
		bool correctOwner{ owner.getName() == curSpace->getOwner() };
		if (differentOwner && correctOwner) {

			int AIdef = game.calculateAssets(curPlayer) - curPlayer.getCash() / 10;
			int ownerDef = game.calculateAssets(owner) - owner.getCash() / 10;

			bool higherDefense{ static_cast<double>(AIdef / ownerDef) >= 1.25 };
			bool hasTurrets{ curSpace->getNumTurrets() > 0 };
			bool cantPayRent{ rent > curPlayer.getCash() };

			attack = (cantPayRent || (higherDefense && !hasTurrets));
				if (attack) {
					game.attackProp(curPlayer, owner);
				}
				else {
					curPlayer.deductCash(rent);
					owner.addCash(rent);
					game.setInfo(curPlayer);
					game.displayBoard();
					cout << curPlayer.getName() << " has decided to just pay the rent." << endl;
					Sleep(2000);
				}
		}
	}
}

void SpaceHandler::ownedByAnotherPlrChoice(int cost, int rent, Player* owner) {
	vector<string> choices{ "1 - Pay rent, which will cost you " + to_string(rent) + " dollars."
	"If you cannot afford this, you will go bankrupt).",
	"2 - Attack the property. You must pay twice the cost of the property if you win, which will be " + to_string(cost * 2) + " dollars."
	"\nIf you cannot afford this, you will go bankrupt. If you lose, you will lose 30% of your cash." };

	cout << "Someone owns this property. Here are your options: " << endl;
	for (size_t i{ 0 }; i < choices.size(); ++i) {
		cout << choices[i] << endl;
	}
	int ans = Utilities::getIntInRange("What would you like to do?: ", 1, 2);
	switch (ans) {
	case 1:
		payRent(rent, owner);
		break;
	case 2: 
		attackProperty();
		break;
	}
}

void SpaceHandler::attackProperty() {
	for (auto& owner : curPlayers) {
		bool correctOwner{ owner.getName() == curSpace->getOwner() };
		bool differentOwner{ owner.getName() != curPlayer.getName() };

		if (correctOwner && differentOwner) {
			game.attackProp(curPlayer, owner);
		}
	}
}

void SpaceHandler::payRent(int rent, Player* owner) {
	curPlayer.deductCash(rent);
	owner->addCash(rent);
	game.setInfo(curPlayer);
	game.displayBoard();
	if (!checkPlayerBankrupt(curPlayer)) {
		cout << "Cash was subtracted." << endl;
		Sleep(2000);
	}
}

int SpaceHandler::getRent(Player* owner, std::vector<Space*> spaces) {
	int rent{ 0 };
	if (curSpace->getPropertyType() == "STANDARD") {
		rent = curSpace->getRent();
	}
	else if (curSpace->getPropertyType() == "RAILROAD") {
		rent = curSpace->getRailroadRent(*owner, spaces);
	}
	else if (curSpace->getPropertyType() == "UTILITY") {
		rent = curSpace->getUtilRent(*owner, spaces, curPlayer.getRoll());
	}
	return rent;
}

void SpaceHandler::checkForABattle() {
	vector<Player*> toBattle;
	for (int i{ 0 }; i < curPlayers.size(); ++i) {
		bool notTheSame{ (curPlayers[i].getName() != curPlayer.getName()) };
		bool sameSpot{ (curPlayers[i].getCurrentSpot() == curPlayer.getCurrentSpot()) };
		if (notTheSame && sameSpot) {
			toBattle.push_back(&curPlayers[i]);
		}
	}
	if (toBattle.empty()) {
		cout << "No other players are on this spot. Phew!" << endl;
		Sleep(3000);
	}
	else {
		cout << "Oh no! 1 or more players is on the spot you landed on! Let the battle commence!" << endl;
		cout << "A random player on this spot will be selected to battle with you. Good luck!" << endl;
		Sleep(6000);
		int randInt = (toBattle.size() <= 1) ? 0 : rand() % toBattle.size();
		game.battle(curPlayer, *(toBattle[randInt]));
	}
}

int getBidders(vector<Player>& bidders) {
	int tot{ 0 };
	for (auto& bidder : bidders) {
		if (bidder.isBidding()) {
			++tot;
		}
	}
	return tot;
}

SpaceHandler::SpaceHandler(Game& g, Player& plr, std::vector<Player>& curPlrs, Space* space) :
	game{ g }, curPlayer{ plr }, curPlayers{ curPlrs }, curSpace{ space } {};


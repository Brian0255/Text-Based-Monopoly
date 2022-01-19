#include "Game.h"
#include"Utilities.h"
#include"TaxSpace.h"
#include"Property.h"
#include"CardHandler.h"
#include<iostream>
#include<iomanip>
#include<vector>
#include<array>
#include"Windows.h"
#include<stdlib.h>
#include"SpaceHandler.h"
#include"TurnHandler.h"

using namespace std;

vector<string> Game::battleDialogChoices =
{
	" throws their money at the other player! They deal ",
	" throws the board at the other player! They deal ",
	" hits the other player with a baseball bat! They deal ",
	" body slams the other player! It's a smackdown! They deal ",
	" throws a bomb at the other player! They deal ",
	" smashes the board over the other player's head! OOF! They deal ",
	" throws a miniature house at the other player! Ouch! They deal ",
	" trips over a banana peel right into the other player! They deal ",
	" takes the banker's briefcase and hits the other player with it! They deal ",
	" tells the other player how worthless they are! They deal ",
	" takes their shoe off and throws it at the other player! They deal "
};

vector<string> Game::playerMobChoices =
{
	" throws their money at the mob of people! They deal ",
	" throws the board at the mob of people! They deal ",
	" tells a horribly boring story! They deal ",
	" body slams the mob of people! It's a smackdown! They deal ",
	" throws a water balloon at the mob of people! They deal ",
	" smashes the board over the mob of people! OOF! They deal ",
	" throws several miniature houses at the mob of people! Ouch! They deal ",
	" trips over a banana peel right into the mob of people! They deal ",
	" takes the banker's briefcase and hits the mob of people with it! They deal ",
	" tells the mob of people how worthless they are! They deal ",
	" takes their shoe off and throws it at the mob of people! They deal "
};
vector<string> Game::mobChoices =
{
	" damages the attacker with pitch forks! They deal ",
	" drops a bucket of water on the attacker! They deal ",
	" shoots flaming arrows at the attacker! They deal ",
	" sends a pack of angry dogs at the attacker! They deal ",
	" throws rocks at the attacker! They deal ",
	" shouts angrily at the attacker! They deal ",
	" throws spears at the attacker! They deal ",
	" catches the attacker in a trap! They deal ",
	" throws their two cents at the attacker! They deal ",
	" jumps at the same time and causes an earthquake. OOF! They deal "
};

Game::Game() {
	initializeSpaces();
	initializeBoard();

	curPlayers = vector<Player>();

	colorSets = { "MAGENTA","BLUE","PINK","ORANGE","RED","YELLOW","GREEN","DARK_BLUE" };

	playerInfo = {
		"Player Information",
	};

	gameOutput = {
		"Nothing is currently happening."
	};
}

void Game::initializeBoard() {
	board = "21       22   23   24   25   26   27   28   29   30       31\n"
		"  +------------------------------------------------------+\n"
		"  |FREE|KENT|CHNC|INDI|ILLI|B&O |ATLN|VENT|WATR|MRVN|GOTO|\n"
		"  |PARK|AVE |????|AVE |AVE |RAIL|AVE |AVE |WRKS|GARD|JAIL|\n"
		"  +------------------------------------------------------+\n"
		"  |NEWY|                                            |PACI|\n"
		"20|AVE |                                            |AVE |32\n"
		"  +----+                                            +---+-\n"
		"  |TENN|                                            |NCAR|\n"
		"19|AVE |                                            |AVE |33\n"
		"  +----+                                            +----+\n"
		"  |COMM|                                            |COMM|\n"
		"18|CHST|                                            |CHST|34\n"
		"  +----+                                            +----+\n"
		"  |STJA|                                            |PENN|\n"
		"17|PLCE|                                            |AVE |35\n"
		"  +----+                                            +----+\n"
		"  |PENN|                                            |SHRT|\n"
		"16|RAIL|                                            |LINE|36\n"
		"  +----+                                            +----+\n"
		"  |VIRG|                                            |CHNC|\n"
		"15|AVE |                                            |????|37\n"
		"  +----+                                            +----+\n"
		"  |STAT|                                            |PARK|\n"
		"14|AVE |                                            |PLCE|38\n"
		"  +----+                                            +----+\n"
		"  |ELEC|                                            |LUXR|\n"
		"13|COMP|                                            |TAX |39\n"
		"  +----+                                            +----+\n"
		"  |STCH|                                            |BRD |\n"
		"12|PLCE|                                            |WALK|40\n"
		"  +------------------------------------------------------+\n"
		"  | IN |CONN|VERM|CHNC|ORNT|READ|INCM|BLTC|COMM|MDTN|PASS|\n"
		"  |JAIL|AVE |AVE |????|AVE |RAIL|TAX |AVE |CHST|AVE | GO |\n"
		"  +-------------------------------------------------+----+\n"
		"11       10   9    8    7    6    5    4    3    2        1\n";


	boardInfo =
	{
		"Board Information",
	};
}

void Game::initializeSpaces() {
	spaces.push_back(new Space("Go Space", "GO_SPACE"));
	spaces.push_back(new Property{ "Mediterranean Avenue","PROPERTY","STANDARD","MAGENTA",60,10,30,90,160,250,50,2,"None",false,false });
	spaces.push_back(new Space{ "Community Chest","COMM" });
	spaces.push_back(new Property{ "Baltic Avenue","PROPERTY","STANDARD","MAGENTA",60,20,60,180,320,450,50,4,"None",false,false });
	spaces.push_back(new TaxSpace{ "Income Tax","TAX_SPACE",200 });
	spaces.push_back(new Property{ "Reading Railroad","PROPERTY","RAILROAD","WHITE",200,0,0,0,0,0,50,25,"None",false,false });
	spaces.push_back(new Property{ "Oriental Avenue","PROPERTY","STANDARD","BLUE",100,30,90,270,400,550,50,6,"None",false,false });
	spaces.push_back(new Space{ "Chance Chest","CHANCE" });
	spaces.push_back(new Property{ "Vermont Avenue","PROPERTY","STANDARD","BLUE",100,30,90,270,400,550,50,6,"None",false,false });
	spaces.push_back(new Property{ "Connecticut Avenue","PROPERTY","STANDARD","BLUE",120,40,100,300,450,600,50,8,"None",false,false });
	spaces.push_back(new Space{ "In Jail","JAIL" });
	spaces.push_back(new Property{ "St. Charles Place","PROPERTY","STANDARD","PINK",140,50,150,450,625,750,100,10,"None",false,false });
	spaces.push_back(new Property{ "Electric Company","PROPERTY","UTILITY","NEUTRAL",150,0,0,0,0,0,50,0,"None",false,false });
	spaces.push_back(new Property{ "States Avenue","PROPERTY","STANDARD","PINK",140,50,150,450,625,750,100,10,"None",false,false });
	spaces.push_back(new Property{ "Virginia Avenue","PROPERTY","STANDARD","PINK",160,60,180,500,700,900,100,12,"None",false,false });
	spaces.push_back(new Property{ "Pennsylvania Railroad","PROPERTY","RAILROAD","WHITE",200,0,0,0,0,0,50,25,"None",false,false });
	spaces.push_back(new Property{ "St. James Place","PROPERTY","STANDARD","ORANGE",180,70,200,550,750,950,100,14,"None",false,false });
	spaces.push_back(new Space{ "Community Chest","COMM" });
	spaces.push_back(new Property{ "Tennessee Avenue","PROPERTY","STANDARD","ORANGE",180,70,200,550,750,950,100,14,"None",false,false });
	spaces.push_back(new Property{ "New York Avenue","PROPERTY","STANDARD","ORANGE",180,80,220,600,800,1000,100,16,"None",false,false });
	spaces.push_back(new Space{ "Free Parking","FREE" });
	spaces.push_back(new Property{ "Kentucky Avenue","PROPERTY","STANDARD","RED",220,90,250,700,875,1050,150,18,"None",false,false });
	spaces.push_back(new Space{ "Chance Chest","CHANCE" });
	spaces.push_back(new Property{ "Indiana Avenue","PROPERTY","STANDARD","RED",220,90,250,700,875,1050,150,18,"None",false,false });
	spaces.push_back(new Property{ "Illinois Avenue","PROPERTY","STANDARD","RED",240,100,300,750,925,1100,150,20,"None",false,false });
	spaces.push_back(new Property{ "B&O Railroad","PROPERTY","RAILROAD","WHITE",200,0,0,0,0,0,50,25,"None",false,false });
	spaces.push_back(new Property{ "Atlantic Avenue","PROPERTY","STANDARD","YELLOW",260,110,330,800,975,1150,150,22,"None",false,false });
	spaces.push_back(new Property{ "Ventnor Avenuie","PROPERTY","STANDARD","YELLOW",260,110,330,800,975,1150,150,22,"None",false,false });
	spaces.push_back(new Property{ "Water Works","PROPERTY","UTILITY","NEUTRAL",150,0,0,0,0,0,50,0,"None",false,false });
	spaces.push_back(new Property{ "Marvin Gardens","PROPERTY","STANDARD","YELLOW",280,120,360,850,1025,1200,150,24,"None",false,false });
	spaces.push_back(new Space{ "Go to Jail","GOTO_JAIL" });
	spaces.push_back(new Property{ "Pacific Avenue","PROPERTY","STANDARD","GREEN",300,130,390,900,1100,1275,200,26,"None",false,false });
	spaces.push_back(new Property{ "North Carolina Avenue","PROPERTY","STANDARD","GREEN",300,130,390,900,1100,1275,200,26,"None",false,false });
	spaces.push_back(new Space{ "Community Chest","COMM" });
	spaces.push_back(new Property{ "Pennsylvania Avenue","PROPERTY","STANDARD","GREEN",320,150,450,1000,1200,1400,200,28,"None",false,false });
	spaces.push_back(new Property{ "Short Line Railroad","PROPERTY","RAILROAD","WHITE",200,0,0,0,0,0,50,25,"None",false,false });
	spaces.push_back(new Space{ "Chance Chest","CHANCE" });
	spaces.push_back(new Property{ "Park Place","PROPERTY","STANDARD","DARK_BLUE",350,175,500,1100,1300,1500,200,35,"None",false,false });
	spaces.push_back(new TaxSpace{ "Luxury Tax","TAX_SPACE",100 });
	spaces.push_back(new Property{ "Boardwalk","PROPERTY","STANDARD","DARK_BLUE",400,200,600,1400,1700,2000,200,50,"None",false,false });
}

void Game::displayBoard() {
	system("CLS");
	cout << board;
	cout << "-----------------------------------------------------------------------" << endl;
	for (size_t i{ 0 }; i < boardInfo.size(); ++i) {
		cout << "|" << boardInfo[i] << setfill(' ') << setw(35 - boardInfo[i].length()) << right;
		cout << "|" << playerInfo[i] << setfill(' ') << setw(35 - playerInfo[i].length()) << right << "|" << endl;
	}
	cout << "-----------------------------------------------------------------------" << endl;
	for (auto& str : gameOutput) {
		cout << str << endl;
	}
}

void Game::displayRules() {
	system("CLS");
	cout << "Please refer to the text file located within the game folder \"RULES.TXT\" to see how to play." << endl;
}

void Game::setInfo(Player plr) {
	boardInfo.clear();
	playerInfo.clear();
	int spot = plr.getCurrentSpot();
	Space* curSpace = spaces[spot];
	boardInfo.push_back("Space information");
	boardInfo.push_back("Space name: " + curSpace->getName());
	boardInfo.push_back("Space number: " + to_string(spot + 1));
	playerInfo.push_back("Player Information");
	playerInfo.push_back("Player name: " + plr.getName());
	playerInfo.push_back("Cash: " + to_string(plr.getCash()));
}

void Game::doStuffBeforeRoll(Player& player) {
	TurnHandler turnHandler = TurnHandler(*this, player, curPlayers, spaces, gameOutput, colorSets);
	turnHandler.handle();
}

vector<Player> Game::setup() {
	system("CLS");
	int numPlayers = Utilities::getIntInRange("How many players will be playing?(0-6):", 0, 6);
	int possibleAI = 6 - numPlayers;
	int numAI = 0;
	if (possibleAI > 0) {
		numAI = setupAI(possibleAI);
	}

	askForPlayerNames(numPlayers);
	if (numAI > 0) {
		generateAI(numAI);
	}
	bool infCash = setupCheats();
	int toLoan = (infCash == true) ? 1'000'000 : 1500;
	cout << "The banker will now loan every player $" + to_string(toLoan) + " to start the game." << endl;
	for (auto& player : curPlayers) {
		player.setCash(toLoan);
	}
	Sleep(3000);
	cout << "The board will now be generated in a few seconds." << endl;
	Sleep(3000);
	system("CLS");
	return curPlayers;
}

int Game::setupAI(int possibleAI) {
	int numAI{ 0 };
	string choice = Utilities::getStringYesNo("Would you like to play against AI?(y/n): ");
	if (choice == "y") {
		if (possibleAI > 1) {
			string prompt = "How many AI would you like to play against?(1-" + to_string(possibleAI) + "):";
			numAI = Utilities::getIntInRange(prompt, 0, possibleAI);
		}
		else {
			cout << "You have 5 players, so the game will put you against 1 AI.";
			numAI = 1;
		}
	}
	return numAI;
}

bool Game::setupCheats() {
	bool doneCheating{ false };
	bool infCash{ false };
	vector<string> cheats{
		"1 - Everyone gets 1 million(for house/hotel/turret purchase testing)",
		"2 - Every roll is doubles(for three doubles testing) - rolling to get out of jail is ignored",
		"3 - Everybody rolls a 1 and a 2(for battle testing) - this overrides option 2, and rolling to get out of jail is ignored",
		"4 - All property is randomly assigned ownership throughout players(for trade testing)",
		"5 - All property is assigned ownership to player 1",
	};
	while (!doneCheating) {
		system("CLS");
		cout << "Here are the following cheats you can enable: " << endl << endl;
		for (size_t i{ 0 }; i < cheats.size(); ++i) {
			cout << cheats[i] << endl;
		}
		cout << endl;
		int ans = Utilities::getIntInRange("Which cheats would you like to enable? If you are done, hit 0: ", 0, 6);

		switch (ans) {
		case 0:
			doneCheating = true;
			break;
		case 1:
			infCash = true;
			cout << "Infinite cash was enabled." << endl;
			Sleep(2000);
			break;
		case 2:
			enableAlwaysRollDoubles();
			break;
		case 3:
			enableRollOneTwo();
			break;
		case 4:
			assignPropRandomly();
			break;
		case 5:
			assignPropFirstPlayer();
			break;
		}
	}
	return infCash;
}


void Game::enableAlwaysRollDoubles() {
	for (auto& player : curPlayers) {
		player.setAlwaysDoubles(true);
	}
	cout << "Always roll doubles was enabled." << endl;
	Sleep(2000);
}

void Game::enableRollOneTwo() {
	for (auto& player : curPlayers) {
		player.setOneTwo(true);
	}
	cout << "Always roll a 1 and a 2 was enabled." << endl;
	Sleep(2000);
}

void Game::assignPropRandomly() {
	for (auto& prop : spaces) {
		if (prop->getType() == "PROPERTY") {
			prop->setOwner(Utilities::getRandomElement(curPlayers).getName());
		}
	}
	cout << "All property was randomly assigned." << endl;
	Sleep(2000);
}

void Game::assignPropFirstPlayer() {
	for (auto& prop : spaces) {
		if (prop->getType() == "PROPERTY") {
			prop->setOwner(curPlayers[0].getName());
		}
	}
	cout << "All property was given ownership to " << curPlayers[0].getName() << ".\n";
	Sleep(2000);
}

void Game::generateAI(int numAI) {
	vector<string> possibleNames{ "Carl the Camel","Decius the Dog","Robert the Rabbit","Bob the Bear",
	"Fred the Fish","Willie the Weasel","Harold the Hamster","David the Dragon",
	"Frank the Frog","Steve the Snake" };

	cout << "The AI will now be generated..." << endl;
	for (int i{ 0 }; i < numAI; ++i) {
		string name = Utilities::removeRandomElement(possibleNames);
		Player p{ name,0,0,false,false,true };
		curPlayers.push_back(p);
		cout << "AI " << name << " has been created." << endl;
		Sleep(1500);
	}
}

void Game::askForPlayerNames(int numPlayers) {
	for (int i{ 1 }; i <= numPlayers; ++i) {
		cout << "Player " << to_string(i) << ", it's time to enter your name." << endl;
		string name = Utilities::getStringLimit("Please enter a name(1-10 characters): ", 10);
		cout << "Name fits limit." << endl;
		Player p{ name,0,0,false,false,false };
		curPlayers.push_back(p);
	}
}

void Game::setCards() {
	CardHandler::setCards();
}

void Game::setGameOutput(std::vector<std::string> newOutput) {
	gameOutput.clear();
	for (auto& str : newOutput) {
		gameOutput.push_back(str);
	}
}

int Game::getNumPlayers() {
	int count{ 0 };
	for (auto& player : curPlayers) {
		if (player.isBankrupt() == false) {
			++count;
		}
	}
	return count;
}

int Game::rollDie() {
	return (rand() % 6) + 1;
}

Player Game::play() {
	int inGame = getNumPlayers();
	while (inGame >= 2) {
		for (auto& player : curPlayers) {
			//have to check how many are in game again, in case other players go bankrupt from a turn
			inGame = getNumPlayers();
			if (inGame > 1) {
				setInfo(player);
				displayBoard();
				if (!player.isBankrupt()) {
					runPlayerTurn(player);
					inGame = getNumPlayers();
				}
			}
		}
	}
	return curPlayers[0];
}

void Game::runPlayerTurn(Player& player) {
	int jail = 10;
	setInfo(player);
	displayBoard();
	doStuffBeforeRoll(player);
	gameOutput.clear();
	displayBoard();
	if (player.isInJail() == true) {
		runPlayerTurnJail(player);
	}
	if (player.canRoll()) {
		letPlayerRoll(player);
	}
}

void Game::letPlayerRoll(Player& player) {
	int jail{ 10 };
	int doublesCount{ 0 };
	bool inJail{ false };
	bool keepRolling{ true };
	while (keepRolling) {
		gameOutput.clear();
		displayBoard();
		cout << player.getName() << ", you will now roll." << endl;
		Sleep(3000);
		int roll1 = rollDie();
		int roll2 = (player.getAlwaysDoubles()) ? roll1 : rollDie();
		if (player.getOneTwo()) {
			roll1 = 1;
			roll2 = 2;
		}
		player.setRoll(roll1 + roll2);
		if (player.canDoubleRoll()) {
			player.setRoll(player.getRoll() * 2);
			cout << "Since you used a collectable to double your roll, your roll was doubled to " << player.getRoll() << ".\n";
		}
		cout << "You roll a " << to_string(roll1) << " and a " << to_string(roll2) << ".\n";
		Sleep(2000);
		keepRolling = (roll1 == roll2) ? runDoublesCase(player, jail) : false;
		if (!player.isInJail()) {
			movePlayer(player);
			SpaceHandler handler = SpaceHandler(*this, player, curPlayers, spaces[player.getCurrentSpot()]);
			handler.handle();
		}
	}
}

void Game::movePlayer(Player& player) {
	displayBoard();
	int start = player.getCurrentSpot();
	int toMove = start + player.getRoll();
	for (int i{ start + 1 }; i <= toMove; ++i) {
		int actual = i % 40;
		player.setCurrentSpot(actual);
		setInfo(player);
		displayBoard();
		cout << player.getName() << ", you are now moving." << endl;
		if (spaces[actual]->getType() == "GO_SPACE") {
			player.addCash(200);
			setInfo(player);
			displayBoard();
			cout << "You land on GO! Take this $200!" << endl;
			Sleep(3000);
		}
		Sleep(500);
	}
}

bool Game::runDoublesCase(Player& player, int jail) {
	cout << "You rolled doubles!" << endl;
	Sleep(3000);
	player.setDoublesRolled(player.getDoublesRolled() + 1);
	bool keepRolling{ true };
	if (player.getDoublesRolled() == 3) {
		keepRolling = false;
		player.setCurrentSpot(jail);
		setInfo(player);
		displayBoard();
		cout << "Oh no! You rolled 3 doubles and are now in jail!\nAt least you got 2 turns before that..." << endl;
		player.setJail(true);
		Sleep(5000);
	}
	return keepRolling;
}

void Game::runPlayerTurnJail(Player& player) {
	vector<string> jailChoices{ "1 - Attempt to roll a double",
						"2 - Pay the $50(this will bankrupt you if you cannot pay it)" };

	player.setRolling(false);
	cout << "Since you are in jail, you must pay a $50 fine or attempt to roll doubles.\nAfter 2 failed attempts to roll doubles, you must pay up." << endl;
	Sleep(4000);
	if (player.getJailAttempts() < 2) {
		if (!player.isAI()) {
			runPlayerJailDecision(player, jailChoices);
		}
		else {
			runAIJailDecision(player);
		}
	}
	else {
		punishPlayerForFailingJail(player);
	}
}

void Game::runPlayerJailDecision(Player& player, std::vector<std::string>& jailChoices) {
	cout << "You have not yet failed 2 attempts, and are at " << to_string(player.getJailAttempts()) << " attempts." << endl;
	cout << "Here are your choices: " << endl;
	for (size_t i{ 0 }; i < jailChoices.size(); ++i) {
		cout << jailChoices[i] << endl;
	}
	cout << endl;
	int choice = Utilities::getIntInRange("What would you like to do?: ", 1, jailChoices.size());
	switch (choice) {
	case 1: {
		attemptToRollDoublesPlayer(player);
	}
	break;
	case 2:{
		pay50InJail(player);
	}
	break;
	}
}

void Game::pay50InJail(Player& player) {
	player.deductCash(50);
	setInfo(player);
	displayBoard();

	player.deductCash(50);
	if (player.getCash() <= 0) {
		player.setBankruptcy(true);
		Utilities::resetOwnership(player, spaces);
		cout << "You went bankrupt. Better luck next time..." << endl;
		Sleep(3000);
		player.setRolling(false);
	}
	else {
		string message = (player.isAI()) ? (player.getName() + " decided to just pay the 50 dollars.")
			: "$50 dollars was subtracted, and you are now out of jail.";
		cout << message << endl;
		Sleep(3000);
		player.setJail(false);
		player.setRolling(true);
	}
}

void Game::attemptToRollDoublesPlayer(Player& player) {
	displayBoard();
	cout << "You roll the dice..." << endl;
	Sleep(3000);
	int roll1 = rollDie();
	int roll2 = rollDie();
	player.setRoll(roll1 + roll2);
	cout << "You roll a " << to_string(roll1) << " and a " << to_string(roll2) << ".\n";
	Sleep(2000);
	if (roll1 == roll2) {
		cout << "You rolled doubles! Congratulations!" << endl;
		Sleep(3000);
		player.setJail(false);
		player.setRolling(true);
	}
	else {
		cout << "You didn't roll doubles..." << endl;
		Sleep(1500);
		cout << "Don't do the crime if you can't do the time..." << endl;
		player.addJailAttempt();
		Sleep(3000);
		player.setRolling(false);
	}
}

void Game::runAIJailDecision(Player& player) {
	cout << player.getName() << " is making a decision..." << endl;
	Sleep(3000);
	//the AI will always just pay the fine, unless they actually cant
	if (player.getCash() > 50) {
		pay50InJail(player);
	}
	else {
		attemptToRollDoublesAI(player);
	}
}

void Game::attemptToRollDoublesAI(Player& player) {
	displayBoard();
	cout << player.getName() << " is going to attempt to roll doubles." << endl;
	Sleep(3000);
	int roll1 = rollDie();
	int roll2 = rollDie();
	player.setRoll(roll1 + roll2);
	cout << player.getName() << " rolled a " << to_string(roll1) << " and a " << to_string(roll2) << ".\n";
	Sleep(2000);
	if (roll1 == roll2) {
		cout << player.getName() << " rolled doubles! Wowee!" << endl;
		Sleep(3000);
		player.setJail(false);
		player.setRolling(true);
	}
	else {
		cout << player.getName() << " didn't roll doubles. Nothing happens for the rest of their turn..." << endl;
		player.addJailAttempt();
		Sleep(3000);
		player.setRolling(false);
	}
}

void Game::punishPlayerForFailingJail(Player& player) {
	displayBoard();
	cout << "Since you have 2 failed attempts to rolled doubles, you will now be charged $50. Bankruptcy is possible." << endl;
	Sleep(4000);
	player.deductCash(50);
	if (player.getCash() <= 0) {
		player.setBankruptcy(true);
		Utilities::resetOwnership(player, spaces);
		cout << "You went bankrupt. Better luck next time..." << endl;
		Sleep(3000);
		player.setRolling(false);
	}
	else {
		cout << "$50 dollars was subtracted, and you are now out of jail." << endl;
		Sleep(3000);
		player.setRolling(false);
	}
}

int Game::calculateAssets(Player& player) {
	int total{ 0 };
	total += player.getCash();
	vector<Space*> properties = Utilities::getProperty(player, spaces);
	for (auto& prop : properties) {
		for (int i{ 0 }; i < prop->getNumHouses(); ++i) {
			total += prop->getHouseCost();
		}
		for (int i{ 0 }; i < prop->getNumHotels(); ++i) {
			total += prop->getHouseCost();
		}
		for (int i{ 0 }; i < prop->getNumTurrets(); ++i) {
			total += prop->getHouseCost() * 2;
		}
		total += prop->getCost();
	}
	vector<Space*> mort = Utilities::getMortgagedProperty(player, spaces);
	for (auto& prop : mort) {
		total += prop->getCost();
	}
	return total / 10;
}

vector<Space*> Game::getSpaces() {
	return this->spaces;
}

void Game::battle(Player& player1, Player& player2) {

	setupHPDefense(player1, player2);
	preBattleDialog(player1, player2);

	bool doneBattling{ false };
	bool player1Turn{ true };
	while (!doneBattling) {
		displayBoard();
		if (!player1Turn) {
			doneBattling = runPlayerBattleTurn(player2, player1, player1Turn);
		}
		doneBattling = runPlayerBattleTurn(player1, player2, player1Turn);
		player1Turn = !player1Turn;
	}
}

bool Game::runPlayerBattleTurn(Player& player2, Player& player1, bool player1Turn) {
	int damage = (rand() % 11) + 30;
	int toSubtract = player2.getDefense() / 5;
	damage -= toSubtract;
	player2.setHP(player2.getHP() - damage);

	//this is done to make sure the order of HP displayed is always the same despite whose turn it is(easier to keep track of)
	Player first = (player1Turn) ? player1 : player2;
	Player second = (player1Turn) ? player2 : player1;
	cout << first.getName() << "'s HP: " << first.getHP() << endl;
	cout << second.getName() << "'s HP: " << second.getHP() << endl << endl;
	cout << player1.getName() + Utilities::getRandomElement(battleDialogChoices) + to_string(damage) + " damage to " + player2.getName() + "!!!";
	Sleep(5000);
	if (player2.getHP() <= 0) {
		rewardBattleWinner(player2, player1);
		return true;
	}
	return false;
}

void Game::rewardBattleWinner(Player& player2, Player& player1) {
	int toReceive = player2.getCash() / 5;
	player2.deductCash(toReceive);
	player1.addCash(toReceive);
	setInfo(player1);
	displayBoard();
	cout << player1.getName() << " has won! They get 20% of " << player2.getName() << "'s money and receive " << to_string(toReceive) << " dollars!" << endl;
	Sleep(4000);
}

void Game::preBattleDialog(Player& player1, Player& player2, bool mobAttack) {
	displayBoard();
	cout << player1.getName() << ", you will face off against..." << endl;
	Sleep(3000);
	string secondName = (mobAttack) ? "the mob" : player2.getName();
	cout << secondName << "!!!" << endl;
	Sleep(2000);
	cout << "3..."; Sleep(1000);
	cout << "2..."; Sleep(1000);
	cout << "1..."; Sleep(1000);
	cout << "FIGHT!!!"; Sleep(2000);
}

void Game::setupHPDefense(Player& player1, Player& player2) {
	player1.setHP(100 + calculateAssets(player1) - (player1.getCash() / 10));
	player2.setHP(100 + calculateAssets(player2) - (player2.getCash() / 10));

	vector<Space*> properties = Utilities::getProperty(player1, spaces);
	for (auto& prop : properties) {
		player1.setDefense(player1.getDefense() + prop->getNumTurrets() * 10);
	}
	properties = Utilities::getProperty(player2, spaces);
	for (auto& prop : properties) {
		player2.setDefense(player2.getDefense() + prop->getNumTurrets() * 10);
	}
}

void Game::attackProp(Player& player, Player& mob) {
	setupHPDefensePropAttack(player, mob);
	preBattleDialog(player, mob, true);

	bool doneBattling{ false };
	bool playerTurn{ true };
	Space* prop = spaces[player.getCurrentSpot()];
	while (!doneBattling) {
		displayBoard();
		doneBattling = runMobBattleTurn(playerTurn, mob, player, prop);
		playerTurn = !playerTurn;
	}
}

bool Game::runMobBattleTurn(bool& playerTurn, Player& mob, Player& player, Space* prop) {
	bool doneBattling{ false };
	if (playerTurn) {
		damageMob(mob, player);
		if (mob.getHP() <= 0) {
			awardPlayerMobProperty(player, prop);
			doneBattling = true;
		}
	}
	else {
		attackPlayerAsMob(player, mob, prop);
		if (player.getHP() <= 0) {
			awardMobDefending(player);
			doneBattling = true;
		}
	}
	return doneBattling;
}

void Game::awardMobDefending(Player& player) {
	player.deductCash(player.getCash() / 3);
	setInfo(player);
	displayBoard();
	cout << "The mob has defended the attack! Huzzah! The mob robs the attacker of 30% of their money." << endl;
	Sleep(4000);
}

void Game::attackPlayerAsMob(Player& player, Player& mob, Space* prop) {
	int damage = (rand() % 20) + 30;
	int turretDamage = damage;
	int toSubtract = player.getDefense() / 5;
	damage -= toSubtract;
	player.setHP(player.getHP() - damage);
	displayBoard();
	cout << player.getName() << "'s HP: " << player.getHP() << endl;
	cout << "The mob's HP: " << mob.getHP() << endl << endl;
	cout << "The mob" + Utilities::getRandomElement(mobChoices) + to_string(damage) + " damage to " + player.getName() + "!!!";
	if (prop->getNumTurrets() > 0) {
		player.setHP(player.getHP() - turretDamage);
		cout << "The turret on the property also fires for " << turretDamage << " damage to the attacker." << endl;
	}
	Sleep(5000);
}

void Game::awardPlayerMobProperty(Player& player, Space* prop) {
	displayBoard();
	cout << "The player successfully attacked the property!" << endl;
	cout << "Since you were so daring, you must pay twice the cost of the property, or go bankrupt." << endl;
	Sleep(3000);
	player.deductCash(prop->getCost() * 2);
	setInfo(player);
	displayBoard();
	if (player.getCash() <= 0) {
		cout << "You went bankrupt! Maybe you should have left them alone..." << endl;
		player.setBankruptcy(true);
		Utilities::resetOwnership(player, spaces);
		Sleep(3000);
	}
	else {
		prop->setOwner(player.getName());
		cout << "The property now belongs to you, " << player.getName() << ".\n";
		Sleep(3000);
	}
}

void Game::damageMob(Player& mob, Player& player) {
	int damage = (rand() % 20) + 30;
	int toSubtract = mob.getDefense() / 5;
	damage -= toSubtract;
	displayBoard();
	mob.setHP(mob.getHP() - damage);
	cout << player.getName() << "'s HP: " << player.getHP() << endl;
	cout << "The mob's HP: " << mob.getHP() << endl << endl;
	cout << player.getName() + Utilities::getRandomElement(playerMobChoices) + to_string(damage) + " damage to the mob!!!";
	Sleep(5000);
}

void Game::setupHPDefensePropAttack(Player& player, Player& mob) {
	player.setHP(100);
	mob.setHP(100);

	player.setHP(player.getHP() + calculateAssets(player) - (player.getCash() / 10));
	mob.setHP(mob.getHP() + calculateAssets(mob) - (mob.getCash() / 10));

	vector<Space*> properties = Utilities::getProperty(player, spaces);
	for (auto& prop : properties) {
		player.setDefense(player.getDefense() + prop->getNumTurrets() * 10);
		cout << player.getName() << "'s defense:" << player.getDefense() << endl;
	}
	properties = Utilities::getProperty(mob, spaces);
	for (auto& prop : properties) {
		mob.setDefense(mob.getDefense() + prop->getNumTurrets() * 10);
		cout << mob.getName() << "'s defense:" << mob.getDefense() << endl;
	}
}

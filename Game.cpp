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

using namespace std;

Game::Game() {
	initializeSpaces();
	initializeBoard();

	curPlayers = vector<Player>();

	colorSets = { "MAGENTA","BLUE","PINK","ORANGE","RED","YELLOW","GREEN","DARK_BLUE" };

	playerInfo ={
		"Player Information",
	};

	gameOutput ={
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
	bool done{ false };
	player.setRolling(true);
	while (!done) {
		if (getNumPlayers() == 1) {
			cout << player.getName() << " has won the game! Congratulations!" << endl;
			Sleep(5000);
			done = true;
		}
		else {
			//TurnHandler turnHandler = TurnHandler();
			//turnHandler.handle();
			gameOutput.clear();
			setInfo(player);
			if (!player.isAI()) {
				gameOutput.push_back("Here are your options before you roll: ");
				gameOutput.push_back("1 - Mortgage owned property");
				gameOutput.push_back("2 - Lift mortgages");
				gameOutput.push_back("3 - Trade with another player");
				gameOutput.push_back("4 - Build houses/hotels/turrets");
				gameOutput.push_back("5 - Warp via railroad(you must be on one and own a different one)");
				gameOutput.push_back("6 - Use Collectable Card");
				displayBoard();

				bool doneUsingCollectables{ false };
				bool doneTrading{ false };
				bool doneHotelling{ false };
				bool doneBuildingHotels{ false };
				bool doneBuilding{ false };
				bool doneTurreting{ false };
				bool exitTrade{ false };
				bool doneEditing{ false };
				bool doneHousing{ false };

				int ans = Utilities::getIntInRange("Please enter an option. If you wish to roll, type 0: ", 0, 6);

				Space* currentSpace = spaces[player.getCurrentSpot()];
				vector<Space*> prop = Utilities::getProperty(player, spaces);
				vector<Space*> mortProp = Utilities::getMortgagedProperty(player, spaces);
				vector<Space*> railroads = Utilities::getOwnedRailroads(player, spaces);
				vector<vector<Space*>> sets;
				vector<Player>tradeable = curPlayers;
				vector<Card> collectables = player.getCards();
				Utilities::removeObjectByValue(tradeable, player); //avoid player trading with themselves
				switch (ans) {
				case 0: //they want to exit
					done = true;
					break;
				case 1: //property mortgaging
					if (prop.empty()) {
						cout << "You do not own any property to mortgage..." << endl;
						Sleep(3000);
						break;
					}
					else {
						system("CLS");
						cout << "Here are your owned properties: " << endl;

						for (size_t i{ 0 }; i < prop.size(); ++i) {
							cout << to_string(i + 1) << " - " << prop[i]->toString() << endl << endl;
						}
						int choice = Utilities::getIntInRange("Please type the number for which property you want to mortgage.\nIf you want to exit, type 0: ", 0, prop.size());
						if (choice != 0) {
							int mortValue = prop[choice - 1]->getCost() / 2;
							int numHouses = prop[choice - 1]->getNumHouses();
							int numHotels = prop[choice - 1]->getNumHotels();
							int numTurrets = prop[choice - 1]->getNumTurrets();
							for (int i{ 0 }; i < numHouses; ++i) {
								mortValue += prop[choice - 1]->getHouseCost() / 2;
							}
							for (int i{ 0 }; i < numHotels; ++i) {
								mortValue += prop[choice - 1]->getHouseCost() / 2;
							}
							for (int i{ 0 }; i < numTurrets; ++i) {
								mortValue += prop[choice - 1]->getHouseCost();
							}
							cout << "Mortgaging this property will give you " << to_string(mortValue) << " dollars." << endl;
							cout << "This value includes half the cost back for any houses, hotels, and turrets you bought, but they will be removed." << endl;
							string answer = Utilities::getStringYesNo("Are you sure ?(y/n): ");
							if (answer == "y" || answer == "Y") {
								prop[choice - 1]->setNumHouses(0);
								prop[choice - 1]->setNumHotels(0);
								prop[choice - 1]->setNumTurrets(0);
								player.addCash(mortValue);
								prop[choice - 1]->setMortgage();
								cout << "Property successfully mortgaged." << endl;
								Sleep(3000);
							}
						}
					}
					break;
				case 2://lifting mortgages
					if (mortProp.empty()) {
						cout << "You do not have any mortgages..." << endl;
						Sleep(3000);
						break;
					}
					else {
						system("CLS");
						cout << "Here are your mortgaged properties: " << endl;
						for (size_t i{ 0 }; i < mortProp.size(); ++i) {
							cout << to_string(i + 1) << " - " << mortProp[i]->toString() << endl;
						}
						int choice = Utilities::getIntInRange("Please type the number for the mortgage you wish to lift.\nIf you want to exit, type 0: ", 0, mortProp.size());
						if (choice != 0) {
							int cost = (mortProp[choice - 1]->getCost() / 2) + (mortProp[choice - 1]->getCost() / 10);
							cout << "Lifting this mortgage will cost " << to_string(cost) << " dollars.";
							string answer = Utilities::getStringYesNo("Are you sure ?(y/n): ");
							if (answer == "y" || answer == "Y") {
								if (player.canDeduct(cost)) {
									player.deductCash(cost);
									mortProp[choice - 1]->setMortgage();//set the mortgage value to false
									cout << "Property successfully bought back." << endl;
									Sleep(3000);
								}
								else {
									cout << "You do not have enough money..." << endl;
									Sleep(3000);
								}
							}
						}
					}
					break;
				case 3://trading section
					while (!doneTrading) {
						if (prop.empty()) {
							cout << "You do not have any property to trade with..." << endl;
							Sleep(3000);
							doneTrading = true;
						}
						else {
							system("CLS");
							cout << "Here are the players you can trade with: " << endl;
							for (size_t i{ 0 }; i < tradeable.size(); ++i) {
								cout << to_string(i + 1) << " - " << tradeable[i].getName() << endl;
							}
							int choice = Utilities::getIntInRange("Please type the number for the player you wish to trade with.\nIf you want to exit, type 0: ", 0, tradeable.size());
							if (choice != 0) {
								Player toTrade = tradeable[choice - 1];
								vector<Space*> prop2 = Utilities::getProperty(toTrade, spaces);
								if (prop2.empty()) {
									cout << toTrade.getName() << " has no property..." << endl;
									Sleep(3000);
								}
								else {
									bool doneSelecting{ false };
									vector<Space*> availOptions = prop;
									vector<Space*> playerGive;
									vector<Space*> playerGet;
									cout << "\nHere are " << toTrade.getName() << "'s" << " properties: " << endl;
									for (auto& property : prop2) {
										cout << property->toString() << endl;
									}
									while (!doneSelecting) {
										if (availOptions.empty()) {
											cout << "No more cards exist to select..." << endl;
											Sleep(3000);
											doneSelecting = true;
										}
										else {
											system("CLS");
											cout << "Here are your properties: " << endl;
											for (size_t i{ 0 }; i < availOptions.size(); ++i) {
												cout << to_string(i + 1) << " - " << availOptions[i]->toString() << endl;
											}
											int toRemove = Utilities::getIntInRange("Enter the corresponding number for the properties you wish to offer."
												"When you are done, hit 0.\n If you want to exit the entire trade, enter -1: ", -1, availOptions.size());
											if (toRemove == -1) {
												exitTrade = true;
												doneSelecting = true;
												doneTrading = true;
											}
											else if (toRemove == 0) {
												if (playerGive.empty()) {
													cout << "\nYou did not select any cards! Please select at least 1 card to offer." << endl;
													Sleep(3000);
												}
												else {
													doneSelecting = true;
												}
											}
											else {
												playerGive.push_back(availOptions[toRemove - 1]);
												availOptions.erase(availOptions.begin() + (toRemove - 1));
												cout << "Card was successfully selected for trade." << endl;
												Sleep(3000);
											}
										}
									}
									if (!exitTrade) {
										doneSelecting = false;
										availOptions = prop2;
									}
									while (!doneSelecting) {
										if (availOptions.empty()) {
											cout << "No more cards exist to select..." << endl;
											Sleep(3000);
											doneSelecting = true;
										}
										else {
											system("CLS");
											cout << "Here are " << toTrade.getName() << "'s" << " properties: " << endl;
											for (size_t i{ 0 }; i < availOptions.size(); ++i) {
												cout << to_string(i + 1) << " - " << availOptions[i]->toString() << endl;
											}
											int toRemove = Utilities::getIntInRange("Enter the corresponding number for the properties you want."
												"When you are done, hit 0.\n If you want to exit the entire trade, enter -1: ", -1, availOptions.size());
											if (toRemove == -1) {
												doneSelecting = true;
												doneTrading = true;
											}
											else if (toRemove == 0) {
												if (playerGet.empty()) {
													cout << "You did not select any cards! Please select at least 1 card to take." << endl;
												}
												else {
													doneSelecting = true;
												}
											}
											else {
												playerGet.push_back(availOptions[toRemove - 1]);
												availOptions.erase(availOptions.begin() + (toRemove - 1));
												cout << "Card was successfully selected for trade." << endl;
												Sleep(3000);
											}
										}
									}
									if (!doneTrading) {
										system("CLS");
										cout << player.getName() << " will give the following cards:" << endl;
										for (auto& property : playerGive) {
											cout << property->toString() << endl;
										}
										cout << endl << toTrade.getName() << ", you will give the following cards:" << endl;
										for (auto& property : playerGet) {
											cout << property->toString() << endl;
										}
										cout << endl;
										if (!toTrade.isAI()) {
											string doTheTrade = Utilities::getStringYesNo(toTrade.getName() + ", do you accept this offer by " + player.getName() + "?(y/n)");
											if (doTheTrade == "y" || doTheTrade == "Y") {
												for (auto& property : playerGive) {
													property->setOwner(toTrade.getName());
												}
												for (auto& property : playerGet) {
													property->setOwner(player.getName());
												}
												cout << "Trade was successful. Now returning to main menu..." << endl;
												Sleep(3000);
												doneTrading = true;
											}
											else if (doTheTrade == "n" || doTheTrade == "N") {
												cout << "Trade was rejected! Nothing will happen between both players." << endl;
												Sleep(1000);
												cout << "Returning to main menu..." << endl;
												Sleep(3000);
												doneTrading = true;
											}
										}
										else {
											cout << "\nThe AI is making a decision based on your offer..." << endl;
											Sleep(4000);
											if (playerGive.size() > playerGet.size()) {
												cout << "AI " << toTrade.getName() << " agreed to your trade." << endl;
												for (auto& property : playerGive) {
													property->setOwner(toTrade.getName());
												}
												for (auto& property : playerGet) {
													property->setOwner(player.getName());
												}
												Sleep(2000);
												cout << "Trade was successful. Now returning to main menu..." << endl;
												Sleep(4000);
												doneTrading = true;
											}
											else {
												cout << "The AI " << toTrade.getName() << " has rejected your offer." << endl;
												Sleep(1000);
												cout << "Now returning to main menu..." << endl;
												Sleep(3000);
												doneTrading = true;
											}
										}
									}
								}
							}
							else {
								doneTrading = true;
							}
						}
					}
					break;
				case 4://house,hotel, and turret editing case
				{
					while (!doneEditing) {
						system("CLS");
						cout << "Here are your options:" << endl;
						cout << "1 - Build house" << endl;
						cout << "2 - Build hotel" << endl;
						cout << "3 - Build turret" << endl;
						int choice = Utilities::getIntInRange("Please choose an option. If you want to exit, type 0: ", 0, 3);
						switch (choice) {
						case 0:
							doneEditing = true;
							break;
						case 1://house building case
							sets = Utilities::getOwnedSets(player, spaces, colorSets);
							if (sets.empty()) {
								cout << "You do not own any sets of properties..." << endl;
								Sleep(3000);
								doneEditing = true;
							}
							else {
								while (!doneBuilding) {
									system("CLS");
									cout << "Here are the sets you own: " << endl;
									for (size_t i{ 0 }; i < sets.size(); ++i) {
										cout << to_string(i + 1) << " - " << sets[i][0]->getColor() << ":" << endl;
									}
									doneHousing = false;
									int ans = Utilities::getIntInRange("Please select which color of property you want to build houses on.\nIf you wish to exit, type 0: ", 0, sets.size());
									if (ans == 0) //player wants to exit
									{
										doneBuilding = true;
										doneEditing = true;
									}
									else {
										while (!doneHousing) {
											system("CLS");
											vector<Space*>propSet = sets[ans - 1];
											cout << "Here are the properties in that set you can build houses for: " << endl << endl;;
											for (size_t i{ 0 }; i < propSet.size(); ++i) {
												cout << to_string(i + 1) << " - " << propSet[i]->toString() << "Number of houses: " << propSet[i]->getNumHouses()
													<< "|Number of hotels: " << propSet[i]->getNumHotels() << "|" << endl << endl;
											}
											int ans = Utilities::getIntInRange("Please select which property you wish to build houses for.\nIf you wish to exit, type 0: ", 0, propSet.size());
											if (ans == 0) {
												doneHousing = true;
											}
											else {
												bool canBuild{ true };
												Space* toBuild = propSet[ans - 1];
												if (toBuild->getNumHouses() < 4) {
													for (auto& prop : propSet) {
														if (prop->getName() != toBuild->getName()) {
															if (prop->getNumHouses() < toBuild->getNumHouses()) {
																canBuild = false;
															}
														}
													}
													if (toBuild->getNumHotels() > 0) {
														cout << "A hotel exists on that property. You may not build houses while a hotel is there.\nPlease select another." << endl;
														Sleep(4000);
													}
													else {
														if (canBuild) {
															int costToBuild = toBuild->getHouseCost();
															if (player.canDeduct(costToBuild))//if they have enough
															{
																player.deductCash(costToBuild);
																toBuild->addHouse();
																cout << "\nHouse was successfully built." << endl;
																Sleep(2000);
															}
															else {
																cout << "\nYou lack sufficient funds to build a house. Please select another property." << endl;
																Sleep(3000);
															}
														}
														else {
															cout << "\nYou are attempting to build unevenly. Please select another property." << endl;
															Sleep(3000);
														}
													}
												}
												else {
													cout << "\nNumber of houses on that property is already at max.\nPlease select another. " << endl;
													Sleep(3000);
												}
											}
										}
									}
								}
							}
							break;
						case 2://hotel building switch case
							sets = Utilities::getHotellableSets(player, spaces, colorSets);
							if (sets.empty()) {
								cout << "You do not own any sets of properties that have the max number of houses built on every property..." << endl;
								Sleep(6000);
								doneEditing = true;
							}
							else {
								while (!doneHotelling) {
									system("CLS");
									doneBuildingHotels = false;
									cout << "Here are the sets you own which you can build hotels: " << endl;
									for (size_t i{ 0 }; i < sets.size(); ++i) {
										cout << to_string(i + 1) << " - " << sets[i][0]->getColor() << ":" << endl;
									}
									int ans = Utilities::getIntInRange("Please select which color of property you want to build a hotel on.\nIf you wish to exit, type 0: ", 0, sets.size());
									if (ans == 0) {
										doneHotelling = true;
										doneBuildingHotels = true;
									}
									else {
										while (!doneBuildingHotels) {
											system("CLS");
											vector<Space*> propSet = sets[ans - 1];
											cout << "Here are the properties in that set you can build hotels for: " << endl;
											for (size_t i{ 0 }; i < propSet.size(); ++i) {
												cout << to_string(i + 1) << " - " << propSet[i]->toString() << "Number of hotels: " << propSet[i]->getNumHotels() << "|" << endl << endl;
											}
											int ans = Utilities::getIntInRange("Please select which property you wish to build hotels for.\nIf you wish to exit, type 0: ", 0, propSet.size());
											if (ans == 0) {
												doneBuildingHotels = true;
											}
											else {
												bool canBuild{ true };
												Space* toBuild = propSet[ans - 1];
												if (toBuild->getNumHotels() >= 1) {
													canBuild = false;
												}
												if (canBuild) {
													int costToBuild = toBuild->getHouseCost();
													if (player.canDeduct(costToBuild)) {
														player.deductCash(costToBuild);
														toBuild->addHotel();
														toBuild->setNumHouses(0);
														cout << "\nHotel was successfully built." << endl;
														Sleep(2000);
													}
													else {
														cout << "\nYou lack sufficient funds to build a hotel. Please select another property." << endl;
														Sleep(3000);
													}
												}
												else {
													cout << "\nHotel already built on that property.\nPlease select another." << endl;
													Sleep(3000);
												}
											}
										}
									}
								}
							}
							break;
						case 3://turret switch case starts
							if (prop.empty()) {
								cout << "You do not have any property to build turrets on..." << endl;
								Sleep(6000);
								doneEditing = true;
							}
							else {
								doneTurreting = false;
								while (!doneTurreting) {
									system("CLS");
									cout << "Here are the properties you can build turrets on:" << endl;
									for (size_t i{ 0 }; i < prop.size(); ++i) {
										//list choices
										cout << to_string(i + 1) << " - " << prop[i]->toString() << "Number of turrets: " << prop[i]->getNumTurrets() << "|" << endl << endl;
									}
									int ans = Utilities::getIntInRange("Please select which property you want to build a turret on.\nIf you wish to exit, type 0: ", 0, prop.size());
									if (ans == 0) {
										doneTurreting = true;
									}
									else {
										bool canBuild{ true };
										Space* toBuild = prop[ans - 1];
										if (toBuild->getNumTurrets() == 1) {
											canBuild = false;
										}
										if (canBuild) {
											int costToBuild = toBuild->getHouseCost() * 2;
											if (player.canDeduct(costToBuild)) {
												player.deductCash(costToBuild);
												toBuild->setNumTurrets(1);
												cout << "\nTurret was successfully built." << endl;
												Sleep(2000);
											}
											else {
												cout << "\nYou lack sufficient funds to build a turret. Please select another property." << endl;
												Sleep(3000);
											}
										}
										else {
											cout << "\nTurret already built on that property.\nPlease select another." << endl;
											Sleep(3000);
										}
									}
								}
							}
						}
					}
				}
				break;
				case 5://railroad warp switch case
					if (currentSpace->getPropertyType() == "RAILROAD") {
						vector<Space*> availRailroads;
						for (auto& rail : railroads) {
							if (rail->getName() != spaces[player.getCurrentSpot()]->getName()) {
								availRailroads.push_back(rail);
							}
						}
						if (availRailroads.empty()) {
							cout << "You do not own any other railroads." << endl;
							Sleep(3000);
						}
						else {
							system("CLS");
							cout << "Here are the railroads you can warp to: \n\n";
							for (size_t i{ 0 }; i < availRailroads.size(); ++i) {
								cout << to_string(i + 1) << " - " << availRailroads[i]->toString() << endl;
							}
							int ans = Utilities::getIntInRange("Please select a railroad. If you would like to exit, type 0:", 0, railroads.size());
							if (ans != 0) {
								Space* toWarp = availRailroads[ans - 1];
								player.setCurrentSpot(Utilities::getIndexPtrObj(spaces, toWarp));
								setInfo(player);
								displayBoard();
								cout << "You have successfully warped to " << toWarp->getName() << "." << endl;
								player.setRolling(false);
								Sleep(3000);
							}
						}
					}
					else {
						cout << "You are not currently on a railroad. Please select another option." << endl;
						Sleep(3000);
					}
					break;
				case 6://start collectable using switch case
					if (collectables.empty()) {
						cout << "You do not have any collectable cards. Please select another option." << endl;
						Sleep(3000);
					}
					else {
						system("CLS");
						cout << "Here are your collectable cards: " << endl << endl;
						for (size_t i{ 0 }; i < collectables.size(); ++i) {
							cout << to_string(i + 1) << " - " << collectables[i].getDesc() << endl;
						}
						int ans = Utilities::getIntInRange("Please select a card to use. If you would like to exit, type 0:", 0, collectables.size());
						if (ans != 0) {
							Card toUse = collectables[ans - 1];
							if (toUse.getEffect() == "getOutJail") {
								if (player.getCurrentSpot() == 10) {
									CardHandler handler = CardHandler(curPlayers, *this, player, toUse);
									handler.handle();
									collectables.erase(collectables.begin() + (ans - 1));
									player.setCards(collectables);
								}
								else {
									cout << "You are not currently in jail!" << endl;
									Sleep(3000);
								}
							}
							else {
								CardHandler handler = CardHandler(curPlayers, *this, player, toUse);
								handler.handle();
								collectables.erase(collectables.begin() + (ans - 1));
								player.setCards(collectables);
							}
						}
					}
					break;
				}
			}
			else
				//AI section of code
			{
				displayBoard();
				cout << "AI " << player.getName() << " is deciding what to do before they roll..." << endl;
				Sleep(3000);
				bool doneMortgaging{ false };
				bool doneHousing{ false };
				bool doneHotelling{ false };
				bool doneLiftingMortgages{ false };
				bool doneBuildingHouses{ false };
				bool doneBuildingHotels{ false };
				bool doneBuildingTurrets{ false };
				bool doneUsingCollectables{ false };

				vector<Space*> AIhotSets = Utilities::getProperty(player, spaces);
				while (!doneMortgaging) {
					vector<Space*> AIprop = Utilities::getProperty(player, spaces);
					if (!AIprop.empty()) {
						displayBoard();
						if (player.getCash() < 100)//mortgaging should only be done when the AI is nearly bankrupt and is running out of options
						{
							cout << player.getName() << " is going to mortgage a property." << endl;
							Sleep(2000);
							int AImortValue{ 0 };
							int randIndex = (AIprop.size() > 1) ? rand() % (AIprop.size() - 1) : 0;

							AImortValue = AIprop[randIndex]->getCost() / 2;
							int numHouses = AIprop[randIndex]->getNumHouses();
							int numHotels = AIprop[randIndex]->getNumHotels();
							int numTurrets = AIprop[randIndex]->getNumTurrets();
							for (int i{ 0 }; i < numHouses; ++i) {
								AImortValue += AIprop[randIndex]->getHouseCost() / 2;
							}
							for (int i{ 0 }; i < numHotels; ++i) {
								AImortValue += AIprop[randIndex]->getHouseCost() / 2;
							}
							for (int i{ 0 }; i < numTurrets; ++i) {
								AImortValue += AIprop[randIndex]->getHouseCost();
							}
							AIprop[randIndex]->setMortgage();
							player.addCash(AImortValue);
							AIprop[randIndex]->setNumHouses(0);
							AIprop[randIndex]->setNumHotels(0);
							AIprop[randIndex]->setNumTurrets(0);
							setInfo(player);
							displayBoard();
							cout << player.getName() << " received " << AImortValue << " dollars for mortgaging " << AIprop[randIndex]->getName() << ".\n";
							Sleep(3000);
						}
						else {
							doneMortgaging = true;
						}
					}
					else {
						doneMortgaging = true;
					}
				}

				//start mortgage lifting loop
				while (!doneLiftingMortgages) {
					vector<Space*> AImortProp = Utilities::getMortgagedProperty(player, spaces);
					if (!AImortProp.empty()) {
						//AI only lifts mortgage if they have 5* the cost to lift it
						for (auto& prop : AImortProp) {
							int cost = (prop->getCost() / 2) + (prop->getCost() / 10);
							if (player.getCash() > (cost * 5)) {
								cout << player.getName() << " is going to lift a mortgage." << endl;
								Sleep(2000);
								player.deductCash(cost);
								prop->setMortgage();
								setInfo(player);
								displayBoard();
								cout << player.getName() << " lifted their mortgage on " << prop->getName() << ".\n";
								Sleep(3000);
							}
							else {
								doneLiftingMortgages = true;
							}
						}
					}
					else {
						doneLiftingMortgages = true;
					}
				}

				while (!doneBuildingHouses)//start house building loop
				{
					//this whole loop is pretty neat, the AI will just automatically add 1 house to everything and build evenly
					//and keep doing it until they don't have a reasonable amount of cash
					displayBoard();
					vector<vector<Space*>> AIsets = Utilities::getOwnedSets(player, spaces, colorSets);
					if (!AIsets.empty()) {
						for (auto& propSet : AIsets) {
							doneHousing = true;
							for (auto& prop : propSet) {
								if (prop->getNumHouses() < 4) {
									doneHousing = false;
								}
							}
							while (!doneHousing) {
								for (auto& prop : propSet) {
									if (prop->getNumHouses() < 4) {
										bool canBuild{ true };
										if (player.getCash() > prop->getHouseCost() * 3) {
											for (auto& otherProp : propSet) {
												if (otherProp->getName() != prop->getName()) {
													if (otherProp->getNumHouses() < prop->getNumHouses()) {
														canBuild = false;
													}
												}
											}
											if (canBuild) {
												prop->addHouse();
												player.deductCash(prop->getHouseCost());
												setInfo(player);
												displayBoard();
												cout << player.getName() << " built a house on " << prop->getName() << ".\n";
												Sleep(2000);
											}
										}
										else {
											doneHousing = true;
											doneBuildingHouses = true;
										}
									}
									else {
										doneHousing = true;
									}
								}
							}
						}
						doneBuildingHouses = true;
					}
					else {
						doneBuildingHouses = true;
					}
				}
				while (!doneBuildingHotels)//AI automatic hotel building loop
				{
					displayBoard();
					vector<vector<Space*>> AIhotSets = Utilities::getHotellableSets(player, spaces, colorSets);
					if (!AIhotSets.empty()) {
						//AI only builds a house if they have at least 3* the cost of the house
						for (auto& propSet : AIhotSets) {
							for (auto& prop : propSet) {
								if (prop->getNumHotels() < 1) {
									bool canBuild{ true };
									if (player.getCash() > prop->getHouseCost() * 3) {
										for (auto& otherProp : propSet) {
											if (otherProp->getName() != prop->getName()) {
												if (otherProp->getNumHotels() < prop->getNumHotels()) {
													canBuild = false;
												}
											}
										}
										if (canBuild) {
											prop->addHotel();
											player.deductCash(prop->getHouseCost());
											setInfo(player);
											displayBoard();
											cout << player.getName() << " built a hotel on " << prop->getName() << ".\n";
											Sleep(2000);
										}
									}
									else {
										doneBuildingHotels = true;
									}
								}
								else {
									doneBuildingHotels = true;
								}
							}
						}
					}
					else {
						doneBuildingHotels = true;
					}
				}
				while (!doneBuildingTurrets) {
					displayBoard();
					vector<Space*> properties = Utilities::getProperty(player, spaces);
					if (!properties.empty()) {
						//AI only builds a turret if they have at least 3* the cost of a turret
						for (auto& prop : properties) {
							if (prop->getNumTurrets() < 1) {
								bool canBuild{ true };
								//3 * the turret cost is the same as 6 * the house cost
								if (player.getCash() > prop->getHouseCost() * 6) {
									for (auto& otherProp : properties) {
										if (otherProp->getName() != prop->getName()) {
											if (otherProp->getNumTurrets() < prop->getNumTurrets()) {
												canBuild = false;
											}
										}
									}
									if (canBuild) {
										prop->setNumTurrets(1);
										player.deductCash(prop->getHouseCost() * 2);
										setInfo(player);
										displayBoard();
										cout << player.getName() << " built a turret on " << prop->getName() << ".\n";
										Sleep(2000);
									}
								}
								else {
									doneBuildingTurrets = true;
								}
							}
							else {
								doneBuildingTurrets = true;
							}
						}
					}
					else {
						doneBuildingTurrets = true;
					}
				}
				while (!doneUsingCollectables)//automatic collectable usage
				{
					vector<Card> AIcards = player.getCards();
					if (!AIcards.empty()) {
						for (auto& card : AIcards) {
							if (card.getEffect() != "getOutJail" || card.getEffect() != "doubleRoll") {
								cout << player.getName() << " is going to use a collectable." << endl;
								Sleep(2000);
								CardHandler handler = CardHandler(curPlayers, *this, player, card);
								handler.handle();
								player.setCards(AIcards);
							}
							else if (card.getEffect() == "getOutJail") {
								if (player.isInJail()) {
									cout << player.getName() << " is going to use a collectable." << endl;
									Sleep(3000);
									CardHandler handler = CardHandler(curPlayers, *this, player, card);
									handler.handle();
									player.setCards(AIcards);
								}
							}
							else if (card.getEffect() == "doubleRoll") {
								if (!player.isInJail()) {
									cout << player.getName() << " is going to use a collectable." << endl;
									Sleep(3000);
									CardHandler handler = CardHandler(curPlayers, *this, player, card);
									handler.handle();
									player.setCards(AIcards);
								}
							}
							AIcards.clear();
							player.setCards(AIcards);
						}
						doneUsingCollectables = true;
					}
					else {
						doneUsingCollectables = true;
					}
				}
				done = true;
			}
		}
	}
}

vector<Player> Game::setup() {
	vector<Player> players;
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
	for (auto& player : players) {
		player.setCash(toLoan);
	}
	Sleep(3000);
	cout << "The board will now be generated in a few seconds." << endl;
	Sleep(3000);
	system("CLS");
	return players;
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
		//key difference here is that AI is set to true on the last parameter here
		//thus, they are nearly identical to a regular player, which makes things easy
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
			cout << "You have not yet failed 2 attempts, and are at " << to_string(player.getJailAttempts()) << " attempts." << endl;
			cout << "Here are your choices: " << endl;
			for (size_t i{ 0 }; i < jailChoices.size(); ++i) {
				cout << jailChoices[i] << endl;
			}
			cout << endl;
			int choice = Utilities::getIntInRange("What would you like to do?: ", 1, jailChoices.size());
			switch (choice) {
			case 1://attempt to roll doubles
			{
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
			break;
			case 2://just pay 50 case
			{
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
					cout << "$50 dollars was subtracted, and you are now out of jail." << endl;
					Sleep(3000);
					player.setJail(false);
					player.setRolling(true);
				}
			}
			break;
			}
		}
		else//AI makes decision
		{
			cout << player.getName() << " is making a decision..." << endl;
			Sleep(3000);
			//the AI will always just pay the fine, unless they actually cant
			if (player.getCash() > 50) {
				player.deductCash(50);
				setInfo(player);
				displayBoard();
				cout << player.getName() << " decided to just pay the 50 dollars." << endl;
				player.setJail(false);
				player.setRolling(true);
				Sleep(3000);
			}
			else {
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
		}
	}
	else {
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
	vector<string> battleDialogChoices
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
	player1.setHP(100);
	player2.setHP(100);

	player1.setHP(player1.getHP() + calculateAssets(player1) - (player1.getCash() / 10));
	player2.setHP(player1.getHP() + calculateAssets(player2) - (player2.getCash() / 10));

	vector<Space*> properties = Utilities::getProperty(player1, spaces);
	for (auto& prop : properties) {
		player1.setDefense(player1.getDefense() + prop->getNumTurrets() * 10);
	}
	properties = Utilities::getProperty(player2, spaces);
	for (auto& prop : properties) {
		player2.setDefense(player2.getDefense() + prop->getNumTurrets() * 10);
	}

	displayBoard();
	cout << player1.getName() << ", you will face off against..." << endl;
	Sleep(3000);
	cout << player2.getName() << "!!!" << endl;
	Sleep(2000);
	cout << "3..."; Sleep(1000);
	cout << "2..."; Sleep(1000);
	cout << "1..."; Sleep(1000);
	cout << "FIGHT!!!"; Sleep(2000);
	bool doneBattling{ false };
	bool player1Turn{ true };
	while (!doneBattling) {
		displayBoard();
		int damage = (rand() % 11) + 30;
		if (player1Turn) {
			int toSubtract = player2.getDefense() / 5;
			damage -= toSubtract;
			displayBoard();
			player2.setHP(player2.getHP() - damage);
			cout << player1.getName() << "'s HP: " << player1.getHP() << endl;
			cout << player2.getName() << "'s HP: " << player2.getHP() << endl << endl;
			cout << player1.getName() + Utilities::getRandomElement(battleDialogChoices) + to_string(damage) + " damage to " + player2.getName() + "!!!";
			Sleep(5000);
			if (player2.getHP() <= 0) {
				doneBattling = true;
				int toReceive = player2.getCash() / 5;
				player2.deductCash(toReceive);
				player1.addCash(toReceive);
				setInfo(player1);
				displayBoard();
				cout << player1.getName() << " has won! They get 20% of " << player2.getName() << "'s money and receive " << to_string(toReceive) << " dollars!" << endl;
				Sleep(4000);
			}
			else {
				player1Turn = false;
			}
		}
		else {
			int toSubtract = player1.getDefense() / 5;
			damage -= toSubtract;
			player1.setHP(player1.getHP() - damage);
			displayBoard();
			cout << player1.getName() << "'s HP: " << player1.getHP() << endl;
			cout << player2.getName() << "'s HP: " << player2.getHP() << endl << endl;
			cout << player2.getName() + Utilities::getRandomElement(battleDialogChoices) + to_string(damage) + " damage to " + player1.getName() + "!!!";
			Sleep(5000);

			if (player1.getHP() <= 0) {
				doneBattling = true;
				int toReceive = player1.getCash() / 5;
				player1.deductCash(toReceive);
				player2.addCash(toReceive);
				setInfo(player1);
				displayBoard();
				cout << player2.getName() << " has won! They get 20% of " << player1.getName() << "'s money and receive " << to_string(toReceive) << " dollars!" << endl;
				Sleep(4000);
			}
			else {
				player1Turn = true;
			}
		}
	}
}

void Game::attackProp(Player& player, Player& mob) {
	vector<string> playerChoices
	{
		" throws their money at the mob of people! They deal ",
		" throws the board at the mob of people! They deal ",
		" hits each person in the mob of people with a baseball bat! They deal ",
		" body slams the mob of people! It's a smackdown! They deal ",
		" throws a bomb at the mob of people! They deal ",
		" smashes the board over the mob of people! OOF! They deal ",
		" throws several miniature houses at the mob of people! Ouch! They deal ",
		" trips over a banana peel right into the mob of people! They deal ",
		" takes the banker's briefcase and hits the mob of people with it! They deal ",
		" tells the mob of people how worthless they are! They deal ",
		" takes their shoe off and throws it at the mob of people! They deal "
	};
	vector<string> mobChoices
	{
		" stabs the attacker with pitch forks! They deal ",
		" lights the attacker on fire! They deal ",
		" shoots flaming arrows at the attacker! They deal ",
		" sends a pack of angry dogs at the attacker! They deal ",
		" throws rocks at the attacker! They deal ",
		" tries to drown the attacker! They deal ",
		" throws spears at the attacker! They deal ",
		" catches the attacker in a trap! They deal ",
		" throws their two cents at the attacker! They deal ",
		" jumps at the same time and causes an earthquake. OOF! They deal "
	};
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

	displayBoard();
	cout << player.getName() << ", you will now face off against the mob!!!" << endl;
	Sleep(1000);
	cout << "3..."; Sleep(1000);
	cout << "2..."; Sleep(1000);
	cout << "1..."; Sleep(1000);
	cout << "FIGHT!!!"; Sleep(2000);
	bool doneBattling{ false };
	bool playerTurn{ true };
	Space* prop = spaces[player.getCurrentSpot()];
	while (!doneBattling) {
		displayBoard();
		int damage = (rand() % 20) + 30;
		int turretDamage = damage;

		if (playerTurn) {
			int toSubtract = mob.getDefense() / 5;
			damage -= toSubtract;
			displayBoard();
			mob.setHP(mob.getHP() - damage);
			cout << player.getName() << "'s HP: " << player.getHP() << endl;
			cout << "The mob's HP: " << mob.getHP() << endl << endl;
			cout << player.getName() + Utilities::getRandomElement(playerChoices) + to_string(damage) + " damage to the mob!!!";
			Sleep(5000);

			if (mob.getHP() <= 0) {
				doneBattling = true;
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
			else {
				playerTurn = false;
			}
		}
		else {
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

			if (player.getHP() <= 0) {
				doneBattling = true;
				player.deductCash(player.getCash() / 3);
				setInfo(player);
				displayBoard();
				cout << "The mob has defended the attack! Huzzah! The mob robs the attacker of 30% of their money." << endl;
				Sleep(4000);
			}
			else {
				playerTurn = true;
			}
		}
	}
}

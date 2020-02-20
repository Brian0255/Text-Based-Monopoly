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

Game::Game()
{
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

	colorSets = { "MAGENTA","BLUE","PINK","ORANGE","RED","YELLOW","GREEN","DARK_BLUE" };

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

	playerInfo =
	{
		"Player Information",
	};

	gameOutput =
	{
		"Nothing is currently happening."
	};
}

void Game::displayBoard()
{
	//some iomanip headers being used here for formatting

	//flush everything
	system("CLS");
	cout << board;
	cout << "-----------------------------------------------------------------------" << endl;
	for (size_t i{ 0 }; i < boardInfo.size(); ++i)
	{
		cout << "|" << boardInfo[i] << setfill(' ') << setw(35 - boardInfo[i].length()) << right;
		cout << "|" << playerInfo[i] << setfill(' ') << setw(35 - playerInfo[i].length()) << right << "|" << endl;
	}
	cout << "-----------------------------------------------------------------------" << endl;

	//I actually didn't use this gameOutput very much at all
	//I mostly just flushed the output and then displayed the board and used cout
	//which was much easier
	for (auto& str : gameOutput)
	{
		cout << str << endl;
	}
}

void Game::displayRules()
{
	system("CLS");
	cout << "Please refer to the text file located within the game folder \"RULES.TXT\" to see how to play." << endl;
}

void Game::setInfo(Player plr)
{
	//very simple, just sets up the output with the space and player information correctly
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

void Game::doStuffBeforeRoll(Player & player, vector<Player>& players)
{

	bool done{ false };
	player.setRolling(true); // reset in case they warped last turn
	while (!done)//not done menu selecting
	{
		if (getNumPlayers(players) == 1)//if a menu choice made everyone else go bankrupt, such as using a collectable that steals money
		{
			cout << player.getName() << " has won the game! Congratulations!" << endl;
			Sleep(5000);
			done = true;
		}
		else
		{
			gameOutput.clear();
			setInfo(player);
			if (!player.isAI())
			{
				gameOutput.push_back("Here are your options before you roll: ");
				gameOutput.push_back("1 - Mortgage owned property");
				gameOutput.push_back("2 - Lift mortgages");
				gameOutput.push_back("3 - Trade with another player");
				gameOutput.push_back("4 - Build houses/hotels/turrets");
				gameOutput.push_back("5 - Warp via railroad(you must be on one and own a different one)");
				gameOutput.push_back("6 - Use Collectable Card");
				displayBoard();

				//boolean declarations
				bool doneUsingCollectables{ false };
				bool doneTrading{ false };
				bool doneHotelling{ false };
				bool doneBuildingHotels{ false };
				bool doneBuilding{ false };
				bool doneTurreting{ false };
				bool exitTrade{ false };
				bool doneEditing{ false };
				bool doneHousing{ false };

				//option selecting
				int ans = Utilities::getIntInRange("Please enter an option. If you wish to roll, type 0: ", 0, 6);

				//vector declarations for properties and such
				Space* currentSpace = spaces[player.getCurrentSpot()];
				vector<Space*> prop = Utilities::getProperty(player, spaces);
				vector<Space*> mortProp = Utilities::getMortgagedProperty(player, spaces);
				vector<Space*> railroads = Utilities::getOwnedRailroads(player, spaces);
				vector<vector<Space*>> sets;
				vector<Player>tradable = players;
				vector<Card> collectables = player.getCards();
				Utilities::removeObjectByValue(tradable, player); //avoid player trading with themselves
				switch (ans)
				{
				case 0: //they want to exit
					//set roll to true
					done = true;
					break;
				case 1: //property mortgaging
					if (prop.empty()) //if they don't have any property
					{
						cout << "You do not own any property to mortgage..." << endl;
						Sleep(3000);
						break;
					}
					else
					{
						system("CLS");
						cout << "Here are your owned properties: " << endl;

						//display their properties they can mortgage
						for (size_t i{ 0 }; i < prop.size(); ++i)
						{
							cout << to_string(i + 1) << " - " << prop[i]->toString() << endl << endl;
						}
						int choice = Utilities::getIntInRange("Please type the number for which property you want to mortgage.\nIf you want to exit, type 0: ", 0, prop.size());
						if (choice != 0)//if they don't want to exit
						{
							//[choice-1] because of indexing starting at 0 and choices starting at 1 for user convenience
							int mortValue = prop[choice - 1]->getCost() / 2;
							int numHouses = prop[choice - 1]->getNumHouses();
							int numHotels = prop[choice - 1]->getNumHotels();
							int numTurrets = prop[choice - 1]->getNumTurrets();

							//adding houses turrets and hotels to the mortgage value
							for (int i{ 0 }; i < numHouses; ++i)
							{
								mortValue += prop[choice - 1]->getHouseCost() / 2;
							}
							for (int i{ 0 }; i < numHotels; ++i)
							{
								mortValue += prop[choice - 1]->getHouseCost() / 2;
							}
							for (int i{ 0 }; i < numTurrets; ++i)
							{
								mortValue += prop[choice - 1]->getHouseCost(); //turret costs twice as much as house, so dividing by 2 after multiplying 2 is redundant
							}
							cout << "Mortgaging this property will give you " << to_string(mortValue) << " dollars." << endl;
							cout << "This value includes half the cost back for any houses, hotels, and turrets you bought, but they will be removed." << endl;
							string answer = Utilities::getStringYesNo("Are you sure ?(y/n): ");
							if (answer == "y" || answer == "Y")
							{
								//set everything to 0 since they mortgaged it
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
					if (mortProp.empty())//they don't have anything mortgaged
					{
						cout << "You do not have any mortgages..." << endl;
						Sleep(3000);
						break;
					}
					else
					{
						system("CLS");
						cout << "Here are your mortgaged properties: " << endl; 
						//display all mortgages that they have
						for (size_t i{ 0 }; i < mortProp.size(); ++i)
						{
							cout << to_string(i + 1) << " - " << mortProp[i]->toString() << endl;
						}
						int choice = Utilities::getIntInRange("Please type the number for the mortgage you wish to lift.\nIf you want to exit, type 0: ", 0, mortProp.size());
						if (choice != 0)//if they don't want to exit
						{
							//the cost is their choice's cost/2 + 10% interest
							int cost = (mortProp[choice - 1]->getCost() / 2) + (mortProp[choice - 1]->getCost() / 10);

							//make them choose yes again just to be totally sure
							cout << "Lifting this mortgage will cost " << to_string(cost) << " dollars.";
							string answer = Utilities::getStringYesNo("Are you sure ?(y/n): ");
							if (answer == "y" || answer == "Y")//if they said yes
							{
								if (player.canDeduct(cost))//only lift mortgage if they have it
								{
									player.deductCash(cost);
									mortProp[choice - 1]->setMortgage();//set the mortgage value to false
									cout << "Property successfully bought back." << endl;
									Sleep(3000);
								}
								else//dont have enough money to lift it
								{
									cout << "You do not have enough money..." << endl;
									Sleep(3000);
								}
							}
						}
					}
					break;
				case 3://trading section
					while (!doneTrading)//while player isn't done trading
					{
						if (prop.empty())//only let them trade if they have property
						{
							cout << "You do not have any property to trade with..." << endl;
							Sleep(3000);
							doneTrading = true;
						}
						else
						{
							system("CLS");
							cout << "Here are the players you can trade with: " << endl;
							for (size_t i{ 0 }; i < tradable.size(); ++i)
							{
								cout << to_string(i + 1) << " - " << tradable[i].getName() << endl;
							}
							int choice = Utilities::getIntInRange("Please type the number for the player you wish to trade with.\nIf you want to exit, type 0: ", 0, tradable.size());
							if (choice != 0)
							{
								Player toTrade = tradable[choice - 1];
								vector<Space*> prop2 = Utilities::getProperty(toTrade, spaces);//the player they are trading's properties
								if (prop2.empty())//make sure the player they are trading has property as well
								{
									cout << toTrade.getName() << " has no property..." << endl;
									Sleep(3000);
								}
								else
								{
									bool doneSelecting{ false };//let them keep selecting properties to offer
									vector<Space*> availOptions = prop;//the options to choose
									vector<Space*> playerGive;//what the player gives
									vector<Space*> playerGet;//what the player gets from the player they're trading with
									cout << "\nHere are " << toTrade.getName() << "'s" << " properties: " << endl;
									for (auto& property : prop2)
									{
										cout << property->toString() << endl;//list choices
									}
									while (!doneSelecting)//while they're not done selecting stuff to offer
									{
										if (availOptions.empty())//they don't have anything left to select
										{
											cout << "No more cards exist to select..." << endl;
											Sleep(3000);
											doneSelecting = true;//exit loop
										}
										else//they still have options to select
										{
											system("CLS");
											cout << "Here are your properties: " << endl;
											for (size_t i{ 0 }; i < availOptions.size(); ++i)
											{
												cout << to_string(i + 1) << " - " << availOptions[i]->toString() << endl;//list available options
											}
											int toRemove = Utilities::getIntInRange("Enter the corresponding number for the properties you wish to offer."
												"When you are done, hit 0.\n If you want to exit the entire trade, enter -1: ", -1, availOptions.size());
											if (toRemove == -1)//this ain't it chief, back out
											{
												exitTrade = true;
												doneSelecting = true;
												doneTrading = true;
											}
											else if (toRemove == 0)//done selecting
											{
												//make sure they actually selected cards
												if (playerGive.empty())
												{
													cout << "\nYou did not select any cards! Please select at least 1 card to offer." << endl;
													Sleep(3000);
												}
												else
												{
													doneSelecting = true;//exit loop
												}
											}
											else
											{
												playerGive.push_back(availOptions[toRemove - 1]);//add their selection to what they're giving
												availOptions.erase(availOptions.begin() + (toRemove - 1));
												//this is to prevent duplicating, i.e. offering multiples of the same exact card
												cout << "Card was successfully selected for trade." << endl;
												Sleep(3000);
											}
										}
									}
									if (!exitTrade)//they didn't back out
									{
										doneSelecting = false;//reset the bool so we can use it for the next section
										availOptions = prop2; //set what's available to the properties the player being traded with has
									}
									while (!doneSelecting)
									{
										if (availOptions.empty())//if they've selected all possible options
										{
											cout << "No more cards exist to select..." << endl;
											Sleep(3000);
											doneSelecting = true;//exit loop
										}
										else
										{
											system("CLS");
											cout << "Here are " << toTrade.getName() << "'s" << " properties: " << endl;
											for (size_t i{ 0 }; i < availOptions.size(); ++i)
											{
												cout << to_string(i + 1) << " - " << availOptions[i]->toString() << endl;
												//list properties available to grab from other player
											}
											int toRemove = Utilities::getIntInRange("Enter the corresponding number for the properties you want."
												"When you are done, hit 0.\n If you want to exit the entire trade, enter -1: ", -1, availOptions.size());
											if (toRemove == -1)
											{
												//they changed their mind, so exit every loop
												doneSelecting = true;
												doneTrading = true;
											}
											else if (toRemove == 0)
											{
												//make sure they actually selected cards
												if (playerGet.empty())
												{
													cout << "You did not select any cards! Please select at least 1 card to take." << endl;
												}
												else
												{
													doneSelecting = true;
													//we're all good here
												}
											}
											else
											{
												playerGet.push_back(availOptions[toRemove - 1]);
												availOptions.erase(availOptions.begin() + (toRemove - 1));
												//same as above to prevent duplicate trading
												cout << "Card was successfully selected for trade." << endl;
												Sleep(3000);
											}
										}
									}
									//ready to set up player being traded with to confirm the offer:
									if (!doneTrading)//bool was never set to true, which means we keep going here
									{
										system("CLS");
										cout << player.getName() << " will give the following cards:" << endl;
										for (auto& property : playerGive)
										{
											cout << property->toString() << endl;//list what they give
										}
										cout << endl << toTrade.getName() << ", you will give the following cards:" << endl;
										for (auto& property : playerGet)
										{
											cout << property->toString() << endl;//list what they get
										}
										cout << endl;
										if (!toTrade.isAI())//player decision
										{
											//let the player being traded with make a decision
											string doTheTrade = Utilities::getStringYesNo(toTrade.getName() + ", do you accept this offer by " + player.getName() + "?(y/n)");
											if (doTheTrade == "y" || doTheTrade == "Y")//they said yes
											{
												//swap cards ownership
												for (auto& property : playerGive)
												{
													property->setOwner(toTrade.getName());
												}
												for (auto& property : playerGet)
												{
													property->setOwner(player.getName());
												}
												cout << "Trade was successful. Now returning to main menu..." << endl;
												Sleep(3000);
												doneTrading = true;//exit entire loop
											}
											else if (doTheTrade == "n" || doTheTrade == "N")//they rejected
											{
												cout << "Trade was rejected! Nothing will happen between both players." << endl;
												Sleep(1000);
												cout << "Returning to main menu..." << endl;
												Sleep(3000);
												doneTrading = true;//exit entire loop
											}
										}
										else
										{
											//AI only says yes if they are getting more in return for the trade(literally, more cards).
											//equal to or less, and the AI will say no
											cout << "\nThe AI is making a decision based on your offer..." << endl;
											Sleep(4000);
											if (playerGive.size() > playerGet.size())//if ai is getting at least 1 more
											{
												cout << "The AI " << toTrade.getName() << " agreed to your trade." << endl;
												//swap cards ownership
												for (auto& property : playerGive)
												{
													property->setOwner(toTrade.getName());
												}
												for (auto& property : playerGet)
												{
													property->setOwner(player.getName());
												}
												Sleep(2000);
												cout << "Trade was successful. Now returning to main menu..." << endl;
												Sleep(4000);
												doneTrading = true;
											}
											else
											{
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
							else //they wanted to exit on the player trading selection screen
							{
								doneTrading = true;
							}
						}
					}
					break;
				case 4://house,hotel, and turret editing case
				{
					while (!doneEditing)//keep letting player build stuff while in loop
					{
						system("CLS");
						cout << "Here are your options:" << endl;
						cout << "1 - Build house" << endl;
						cout << "2 - Build hotel" << endl;
						cout << "3 - Build turret" << endl;
						int choice = Utilities::getIntInRange("Please choose an option. If you want to exit, type 0: ", 0, 3);
						switch (choice)
						{
						case 0://player decided to exit
							doneEditing = true;//back to main menu
							break;
						case 1://house building case
							sets = Utilities::getOwnedSets(player, spaces, colorSets);
							if (sets.empty())//make sure they own color sets before letting them build a house
							{
								cout << "You do not own any sets of properties..." << endl;
								Sleep(3000);
								doneEditing = true;
							}
							else
							{
								while (!doneBuilding)//keep letting them select property color sets
								{
									system("CLS");
									cout << "Here are the sets you own: " << endl;
									for (size_t i{ 0 }; i < sets.size(); ++i)
									{
										//list the color sets they own
										cout << to_string(i + 1) << " - " << sets[i][0]->getColor() << ":" << endl;
									}
									doneHousing = false;//reset to false in case they build houses then exit to this loop
									int ans = Utilities::getIntInRange("Please select which color of property you want to build houses on.\nIf you wish to exit, type 0: ", 0, sets.size());
									if (ans == 0) //player wants to exit
									{
										//exit all loops
										doneBuilding = true;
										doneEditing = true;
									}
									else
									{
										while (!doneHousing)//keep letting them pick houses to build on the color set they're on
										{
											system("CLS");
											vector<Space*>propSet = sets[ans - 1]; //the vector of properties in the set they chose
											cout << "Here are the properties in that set you can build houses for: " << endl << endl;;
											for (size_t i{ 0 }; i < propSet.size(); ++i)
											{
												//list all the stuff
												cout << to_string(i + 1) << " - " << propSet[i]->toString() << "Number of houses: " << propSet[i]->getNumHouses()
													<< "|Number of hotels: " << propSet[i]->getNumHotels() << "|" << endl << endl;
											}
											int ans = Utilities::getIntInRange("Please select which property you wish to build houses for.\nIf you wish to exit, type 0: ", 0, propSet.size());
											if (ans == 0)//exit just this loop, and return to color selection
											{
												doneHousing = true;
											}
											else
											{
												//assume they can build unless we test conditions and they can't
												bool canBuild{ true };
												Space* toBuild = propSet[ans - 1]; //the space they will build on
												if (toBuild->getNumHouses() < 4)
												{
													//can only build if every other property in set has the same amount of houses or greater
													//that's how the uneven building math works out
													for (auto& prop : propSet)
													{
														if (prop->getName() != toBuild->getName())
														{
															if (prop->getNumHouses() < toBuild->getNumHouses())
															{
																canBuild = false;
															}
														}
													}
													if (toBuild->getNumHotels() > 0)//can't build a house if there's a hotel there
													{
														cout << "A hotel exists on that property. You may not build houses while a hotel is there.\nPlease select another." << endl;
														Sleep(4000);
													}
													else//if there isn't a hotel there
													{
														if (canBuild)//if the above conditions didn't make this false
														{
															int costToBuild = toBuild->getHouseCost();
															if (player.canDeduct(costToBuild))//if they have enough
															{
																player.deductCash(costToBuild);
																toBuild->addHouse();//add a house to the property
																cout << "\nHouse was successfully built." << endl;
																Sleep(2000);
															}
															else//didn't have enough money
															{
																cout << "\nYou lack sufficient funds to build a house. Please select another property." << endl;
																Sleep(3000);
															}
														}
														else//uneven build condition tested to true
														{
															cout << "\nYou are attempting to build unevenly. Please select another property." << endl;
															Sleep(3000);
														}
													}
												}
												else//number of houses was greater than or equal to 4
												{
													cout << "\nNumber of houses on that property is already at max.\nPlease select another. " << endl;
													Sleep(3000);
												}
											}
										}
									}
								}
							}
							break;//end house building switch case
						case 2://hotel building switch case starts
							sets = Utilities::getHotellableSets(player, spaces, colorSets);
							if (sets.empty())//they don't have any color sets with the max houses built
							{
								cout << "You do not own any sets of properties that have the max number of houses built on every property..." << endl;
								Sleep(6000);
								doneEditing = true; //back to main menu
							}
							else//they have at least one color set with all 4 houses built on every property
							{
								while (!doneHotelling)//while they want to keep selecting sets
								{
									system("CLS");
									doneBuildingHotels = false;//reset to false in case they build a hotel then back out to this menu and want to keep going
									cout << "Here are the sets you own which you can build hotels: " << endl;
									for (size_t i{ 0 }; i < sets.size(); ++i)
									{
										//list color sets with 4 houses built everywhere
										cout << to_string(i + 1) << " - " << sets[i][0]->getColor() << ":" << endl;
									}
									int ans = Utilities::getIntInRange("Please select which color of property you want to build a hotel on.\nIf you wish to exit, type 0: ", 0, sets.size());
									if (ans == 0)//back to color sets
									{
										doneHotelling = true;
										doneBuildingHotels = true;
									}
									else//they want to build
									{
										while (!doneBuildingHotels)//keep letting them select properties in the color set they chose
										{
											system("CLS");
											vector<Space*> propSet = sets[ans - 1];//the color set they chose
											cout << "Here are the properties in that set you can build hotels for: " << endl;
											for (size_t i{ 0 }; i < propSet.size(); ++i)
											{
												//list properties in that set
												cout << to_string(i + 1) << " - " << propSet[i]->toString() << "Number of hotels: " << propSet[i]->getNumHotels() << "|" << endl << endl;
											}
											int ans = Utilities::getIntInRange("Please select which property you wish to build hotels for.\nIf you wish to exit, type 0: ", 0, propSet.size());
											if (ans == 0)//exit back to color selection
											{
												doneBuildingHotels = true;
											}
											else//they want to build hotel
											{
												bool canBuild{ true };
												Space* toBuild = propSet[ans - 1]; //the property to build a hotel on
												if (toBuild->getNumHotels() >= 1)//hotel already exists
												{
													canBuild = false;
												}
												if (canBuild)//if above didn't test to false
												{
													int costToBuild = toBuild->getHouseCost();//hotel cost same as house
													if (player.canDeduct(costToBuild))//if they have enough
													{
														player.deductCash(costToBuild);
														toBuild->addHotel();//add a hotel
														toBuild->setNumHouses(0);//hotel negates all houses and sets them to 0
														cout << "\nHotel was successfully built." << endl;
														Sleep(2000);
													}
													else//didn't have enough money
													{
														cout << "\nYou lack sufficient funds to build a hotel. Please select another property." << endl;
														Sleep(3000);
													}
												}
												else//they already built a hotel
												{
													cout << "\nHotel already built on that property.\nPlease select another." << endl;
													Sleep(3000);
												}
											}
										}
									}
								}
							}
							break;//end hotel switch case
						case 3://turret switch case starts
							if (prop.empty())//player didn't have any property owned
							{
								cout << "You do not have any property to build turrets on..." << endl;
								Sleep(6000);
								doneEditing = true;
							}
							else//they have property
							{
								doneTurreting = false;
								while (!doneTurreting)//keep letting them select properties to build turrets on
								{
									system("CLS");
									cout << "Here are the properties you can build turrets on:" << endl;
									for (size_t i{ 0 }; i < prop.size(); ++i)
									{
										//list choices
										cout << to_string(i + 1) << " - " << prop[i]->toString() << "Number of turrets: " << prop[i]->getNumTurrets() << "|" << endl << endl;
									}
									int ans = Utilities::getIntInRange("Please select which property you want to build a turret on.\nIf you wish to exit, type 0: ", 0, prop.size());
									if (ans == 0)//back to editing selection screen
									{
										doneTurreting = true;
									}
									else//they wanna build a turret
									{
										bool canBuild{ true };
										Space* toBuild = prop[ans - 1]; //property to build turret on
										if (toBuild->getNumTurrets() == 1)//turret already exists, they can only build one
										{
											canBuild = false;
										}
										if (canBuild)//if above did not test false
										{
											int costToBuild = toBuild->getHouseCost() * 2;//turret cost is double the house cost
											if (player.canDeduct(costToBuild))//if they got enough
											{
												player.deductCash(costToBuild);
												toBuild->setNumTurrets(1);//add a turret basically(i was too lazy to make an addTurret() method in property)
												cout << "\nTurret was successfully built." << endl;
												Sleep(2000);
											}
											else//not enough money
											{
												cout << "\nYou lack sufficient funds to build a turret. Please select another property." << endl;
												Sleep(3000);
											}
										}
										else//already built a turret
										{
											cout << "\nTurret already built on that property.\nPlease select another." << endl;
											Sleep(3000);
										}
									}
								}
							}
						}
					}
				}
				break;//end turret switch case
				case 5://railroad warp switch case starts
					if (currentSpace->getPropertyType() == "RAILROAD")//make sure they're actually on a railroad
					{
						vector<Space*> availRailroads;//can't warp to the one that they're on
						for (auto& rail : railroads)
						{
							if (rail->getName() != spaces[player.getCurrentSpot()]->getName())
							{
								availRailroads.push_back(rail);
							}
						}
						if (availRailroads.empty())//they don't own any besides the one they're on
						{
							cout << "You do not own any other railroads." << endl;
							Sleep(3000);
						}
						else//they own at least one
						{
							system("CLS");
							cout << "Here are the railroads you can warp to: \n\n";
							for (size_t i{ 0 }; i < availRailroads.size(); ++i)
							{
								//list choices
								cout << to_string(i + 1) << " - " << availRailroads[i]->toString() << endl;
							}
							int ans = Utilities::getIntInRange("Please select a railroad. If you would like to exit, type 0:", 0, railroads.size());
							if (ans != 0)//if they decided to warp
							{
								Space* toWarp = availRailroads[ans - 1]; //the railroad to warp to
								player.setCurrentSpot(Utilities::getIndexPtrObj(spaces, toWarp));
								//getIndexPtrObj is called to get the spot where the railroad they selected resides
								//i then warp them, which ignores collecting $200 at GO anyway
								setInfo(player);
								displayBoard();
								cout << "You have successfully warped to " << toWarp->getName() << "." << endl;
								player.setRolling(false); //skip roll since they warped
								Sleep(3000);
							}
						}
					}
					else//weren't on a railroad
					{
						cout << "You are not currently on a railroad. Please select another option." << endl;
						Sleep(3000);
					}
					break;//end railroad switch case
				case 6://start collectable using switch case
					if (collectables.empty())//they don't have any collectables
					{
						cout << "You do not have any collectable cards. Please select another option." << endl;
						Sleep(3000);
					}
					else//they do have collectables
					{
						system("CLS");
						cout << "Here are your collectable cards: " << endl << endl;
						for (size_t i{ 0 }; i < collectables.size(); ++i)
						{
							//list choices
							cout << to_string(i + 1) << " - " << collectables[i].getDesc() << endl;
						}
						int ans = Utilities::getIntInRange("Please select a card to use. If you would like to exit, type 0:", 0, collectables.size());
						if (ans != 0)//if they still wanna use a card
						{
							Card toUse = collectables[ans - 1];
							//special case for using a get out of jail card
							//we have to make sure that they're actually in jail when using it
							if (toUse.getEffect() == "getOutJail")//if they're trying to get out of jail
							{
								if (player.getCurrentSpot() == 10)//make sure they're on the jail space
								{
									CardHandler::handleCard(players, *this, player, toUse);
									collectables.erase(collectables.begin() + (ans - 1));
									player.setCards(collectables);
								}
								else//they're not in jail, so ignore them
								{
									cout << "You are not currently in jail!" << endl;
									Sleep(3000);
								}
							}
							else//they're not using a get out of jail card, so just call handleCard and that's it
							{
								CardHandler::handleCard(players, *this, player, toUse);
								collectables.erase(collectables.begin() + (ans - 1));
								player.setCards(collectables);
							}
						}
					}
					break;//end collectables switch case
				}
			}
			else
			//another huge section of code for the AI to automatically do stuff before their turn, with somewhat intelligent choices
			{
				displayBoard();
				cout << "AI " << player.getName() << " is deciding what to do before they roll..." << endl;
				Sleep(3000);

				//boolean declarations
				bool doneMortgaging{ false };
				bool doneHousing{ false };
				bool doneHotelling{ false };
				bool doneLiftingMortgages{ false };
				bool doneBuildingHouses{ false };
				bool doneBuildingHotels{ false };
				bool doneBuildingTurrets{ false };
				bool doneUsingCollectables{ false };

				//vector declarations for stuff the AI has
				vector<Space*> AIhotSets = Utilities::getProperty(player, spaces);
				while (!doneMortgaging)//AI will keep mortgaging while their money is low
				{
					vector<Space*> AIprop = Utilities::getProperty(player, spaces);
					if (!AIprop.empty())
					{
						displayBoard();
						if (player.getCash() < 100)//mortgaging should only be done when the AI is nearly bankrupt and is running out of options
						{
							cout << player.getName() << " is going to mortgage a property." << endl;
							Sleep(2000);
							int AImortValue{ 0 };

							//I cant do rand() % 0 here, so i use a ternary operator:
							//if the size of the vector is 1 or less, just grab the 0th element, otherwise:
							//grab a random index from ( 0 ) to ( the size of the vector - 1 )
							//the minus one is to prevent going out of bounds(vector[vector.size()] will be out of range)
							int randIndex = (AIprop.size() > 1) ? rand() % (AIprop.size() - 1) : 0;

							//stuff below is similar to above, just adds whatever the AI has built to the mortgage value
							AImortValue = AIprop[randIndex]->getCost() / 2;
							int numHouses = AIprop[randIndex]->getNumHouses();
							int numHotels = AIprop[randIndex]->getNumHotels();
							int numTurrets = AIprop[randIndex]->getNumTurrets();
							for (int i{ 0 }; i < numHouses; ++i)
							{
								AImortValue += AIprop[randIndex]->getHouseCost() / 2;
							}
							for (int i{ 0 }; i < numHotels; ++i)
							{
								AImortValue += AIprop[randIndex]->getHouseCost() / 2;
							}
							for (int i{ 0 }; i < numTurrets; ++i)
							{
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
						else//AI exits loop since they now have enough cash
						{
							doneMortgaging = true;
						}
					}
					else//AI had no property to mortgage so just exit the loop anyway
					{
						doneMortgaging = true;
					}
				}//end mortgaging loop

				//start mortgage lifting loop
				while (!doneLiftingMortgages)
				{
					vector<Space*> AImortProp = Utilities::getMortgagedProperty(player, spaces);
					if (!AImortProp.empty())//AI checks if it has and proprety to mortgage
					{
						//AI only lifts mortgage if they have 5* the cost to lift it
						for (auto& prop : AImortProp)
						{
							int cost = (prop->getCost() / 2) + (prop->getCost() / 10);
							if (player.getCash() > (cost * 5))//has at least 5 times the cost of lifting
							{
								cout << player.getName() << " is going to lift a mortgage." << endl;
								Sleep(2000);
								player.deductCash(cost);
								prop->setMortgage();
								setInfo(player);
								displayBoard();
								cout << player.getName() << " lifted their mortgage on " << prop->getName() << ".\n";
								Sleep(3000);
							}
							else//doesn't have enough, so just exit the loop
							{
								doneLiftingMortgages = true;
							}
						}
					}
					else//doesn't have anything to mortgage, so just exit the loop
					{
						doneLiftingMortgages = true;
					}
				}//end mortgage lifting loop

				while (!doneBuildingHouses)//start house building loop
				{
					//this whole loop is pretty neat, the AI will just automatically add 1 house to everything and build evenly
					//and keep doing it until they don't have a reasonable amount of cash
					displayBoard();
					vector<vector<Space*>> AIsets = Utilities::getOwnedSets(player, spaces, colorSets);
					if (!AIsets.empty())//doesn't have any color sets
					{
						//AI only builds a house if they have at least 3* the cost of the house
						for (auto& propSet : AIsets)//for each color set they got
						{
							doneHousing = true;
							for (auto& prop : propSet)
							{
								if (prop->getNumHouses() < 4)
									//if at least one house isn't at max the AI can keep building on the set
								{
									doneHousing = false;
								}
							}
							while (!doneHousing)//AI keeps building on the set as long as it can
							{
								for (auto& prop : propSet)//for each prop in each color set
								{
									if (prop->getNumHouses() < 4)//if the number of houses is not at the max
									{
										bool canBuild{ true };//assume they can build
										if (player.getCash() > prop->getHouseCost() * 3)//AI makes sure it has sufficient cash
										{
											for (auto& otherProp : propSet)//make sure we aren't building unevenly
											{
												if (otherProp->getName() != prop->getName())
												{
													if (otherProp->getNumHouses() < prop->getNumHouses())
													{
														//building unevenly, so we can't build
														canBuild = false;
													}
												}
											}
											if (canBuild)
											{
												//we can build and have cash, so AI builds a house
												prop->addHouse();
												player.deductCash(prop->getHouseCost());
												setInfo(player);
												displayBoard();
												cout << player.getName() << " built a house on " << prop->getName() << ".\n";
												Sleep(2000);
											}
										}
										else//AI doesn't have sufficient cash, so exit the entire loop
										{
											doneHousing = true;
											doneBuildingHouses = true;
										}
									}
									else//number of houses is at max, so exit the inner loop
									{
										doneHousing = true;
									}
								}
							}
						}
						doneBuildingHouses = true;
					}
					else//AI has no sets, so exit the loop
					{
						doneBuildingHouses = true;
					}
				}
				while (!doneBuildingHotels)//AI automatic hotel building loop
				{
					displayBoard();
					vector<vector<Space*>> AIhotSets = Utilities::getHotellableSets(player, spaces, colorSets);
					if (!AIhotSets.empty())//check if AI has any sets they can build on
					{
						//AI only builds a house if they have at least 3* the cost of the house
						for (auto& propSet : AIhotSets)
						{
							//let AI build hotels on each property in each set if the num is not already 1, and builds evenly
							for (auto& prop : propSet)
							{
								if (prop->getNumHotels() < 1)
								{
									bool canBuild{ true };
									//again, AI only builds if they have 3* the cost
									if (player.getCash() > prop->getHouseCost() * 3)
									{
										//uneven build checking
										for (auto& otherProp : propSet)
										{
											if (otherProp->getName() != prop->getName())
											{
												if (otherProp->getNumHotels() < prop->getNumHotels())
												{
													canBuild = false;
												}
											}
										}
										if (canBuild)
										{
											prop->addHotel();
											player.deductCash(prop->getHouseCost());
											setInfo(player);
											displayBoard();
											cout << player.getName() << " built a hotel on " << prop->getName() << ".\n";
											Sleep(2000);
										}
									}
									else//not enough
									{
										doneBuildingHotels = true;
									}
								}
								else//number of hotels already at max
								{
									doneBuildingHotels = true;
								}
							}
						}
					}
					else//no sets to build on
					{
						doneBuildingHotels = true;
					}
				}
				while (!doneBuildingTurrets)//automatic turret building loop, basically the same as above but with turrets
				{
					displayBoard();
					vector<Space*> properties = Utilities::getProperty(player, spaces);
					if (!properties.empty())
					{
						//AI only builds a turret if they have at least 3* the cost of a turret
						for (auto& prop : properties)
						{
							if (prop->getNumTurrets() < 1)
							{
								bool canBuild{ true };
								//3 * the turret cost is the same as 6 * the house cost(turret costs twice as much as a house)
								if (player.getCash() > prop->getHouseCost() * 6)
								{
									//uneven build checking
									for (auto& otherProp : properties)
									{
										if (otherProp->getName() != prop->getName())
										{
											if (otherProp->getNumTurrets() < prop->getNumTurrets())
											{
												canBuild = false;
											}
										}
									}
									if (canBuild)
									{
										prop->setNumTurrets(1);
										player.deductCash(prop->getHouseCost()*2);
										setInfo(player);
										displayBoard();
										cout << player.getName() << " built a turret on " << prop->getName() << ".\n";
										Sleep(2000);
									}
								}
								else//not enough
								{
									doneBuildingTurrets = true;
								}
							}
							else//number of turrets already at max
							{
								doneBuildingTurrets = true;
							}
						}
					}
					else//no property to build turrets on
					{
						doneBuildingTurrets = true;
					}
				}
				while (!doneUsingCollectables)//automatic collectable usage
				{
					vector<Card> AIcards = player.getCards();
					if (!AIcards.empty())//check if AI has any
					{
						for (auto& card : AIcards)//automatically uses them
						{
							//exceptions exist for these two types of collectable cards
							//if the card effect isn't an exception, AI just uses it
							if (card.getEffect() != "getOutJail" || card.getEffect() != "doubleRoll")
							{
								cout << player.getName() << " is going to use a collectable." << endl;
								Sleep(2000);
								CardHandler::handleCard(players, *this, player, card);
								player.setCards(AIcards);
							}
							else if (card.getEffect() == "getOutJail")
							{
								//gotta check if the AI is actually in jail, if so they will use it
								if (player.isInJail())
								{
									cout << player.getName() << " is going to use a collectable." << endl;
									Sleep(3000);
									CardHandler::handleCard(players, *this, player, card);
									player.setCards(AIcards);
								}
							}
							else if (card.getEffect() == "doubleRoll")
							{
								//doubling roll does nothing in jail, so AI doesn't use this if they're in jail
								if (!player.isInJail())
								{
									cout << player.getName() << " is going to use a collectable." << endl;
									Sleep(3000);
									CardHandler::handleCard(players, *this, player, card);
									player.setCards(AIcards);
								}
							}
							AIcards.clear();
							player.setCards(AIcards);
						}
						doneUsingCollectables = true;
					}
					else//no collectable cards to use
					{
						doneUsingCollectables = true;
					}
				}
				done = true;//entire loop finished
			}
		}
	}
}

	vector<Player> Game::setup()
	{
		vector<Player> players;
		system("CLS");
		int numPlayers = Utilities::getIntInRange("How many players will be playing?(0-6):", 0, 6);
		int possibleAI = 6 - numPlayers;
		int numAI = 0;

		if (possibleAI > 0)//changes range based on number of players picked above
		{
			string choice = Utilities::getStringYesNo("Would you like to play against AI?(y/n): ");
			if (choice == "y")
			{
				if (possibleAI > 1)
				{
					string prompt = "How many AI would you like to play against?(1-" + to_string(possibleAI) + "):";
					numAI = Utilities::getIntInRange(prompt, 0, possibleAI);
				}
				else//special exception
				{
					cout << "You have 5 players, so the game will put you against 1 AI.";
					numAI = 1;
				}
			}
		}

		for (int i{ 1 }; i <= numPlayers; ++i)
			//prompt each player for a name, and make sure it fits limit, then make a Player object for each of them
		{
			cout << "Player " << to_string(i) << ", it's time to enter your name." << endl;
			string name = Utilities::getStringLimit("Please enter a name(1-10 characters): ", 10);
			cout << "Name fits limit." << endl;
			Player p{ name,0,0,false,false,false };
			players.push_back(p);//add them to the players
		}

		vector<string> possibleNames{ "Carl the Camel","Decius the Dog","Robert the Rabbit","Bob the Bear",
			"Fred the Fish","Willie the Weasel","Harold the Hamster","David the Dragon",
			"Pepe the Frog","Steve the Snake" };

		if (numAI > 0)
		{
			cout << "The AI will now be generated..." << endl;
			for (int i{ 0 }; i < numAI; ++i)
			{
				//gets random name from the vector of possibleNames
				string name = Utilities::removeRandomElement(possibleNames);
				Player p{ name,0,0,false,false,true };
				//key difference here is that AI is set to true on the last parameter here
				//thus, they are nearly identical to a regular player, which makes things easy
				players.push_back(p);
				cout << "AI " << name << " has been created." << endl;
				Sleep(1500);
			}
		}

		bool infCash{ false };
		bool doneCheating{ false };
		vector<string> cheats{
							  "1 - Everyone gets 1 million(for house/hotel/turret purchase testing)",
							  "2 - Every roll is doubles(for three doubles testing) - rolling to get out of jail is ignored",
							  "3 - Everybody rolls a 1 and a 2(for battle testing) - this overrides option 2, and rolling to get out of jail is ignored",
							  "4 - All property is randomly assigned ownership throughout players(for trade testing)",
							  "5 - All property is assigned ownership to player 1",
							//  "6 - All spaces are assigned to be community/chance chests(for various card testing)"
							 };
		while (!doneCheating)
		{
			system("CLS");
			cout << "Here are the following cheats you can enable: " << endl << endl;
			for (size_t i{ 0 }; i < cheats.size(); ++i)
			{
				//list cheats they can use
				cout << cheats[i] << endl;
			}
			cout << endl;
			int ans = Utilities::getIntInRange("Which cheats would you like to enable? If you are done, hit 0: ", 0, 6);
			switch (ans)
			{
			case 0://doesn't wanna cheat or finished
				doneCheating = true;
				break;
			case 1://$1,000,000 cash cheat
				infCash = true;
				cout << "Infinite cash was enabled." << endl;
				Sleep(2000);
				break;
			case 2://always roll doubles
				for (auto& player : players)
				{
					player.setAlwaysDoubles(true);
				}
				cout << "Always roll doubles was enabled." << endl;
				Sleep(2000);
				break;
			case 3://always roll 1 and 2
				for (auto& player : players)
				{
					player.setOneTwo(true);
				}
				cout << "Always roll a 1 and a 2 was enabled." << endl;
				Sleep(2000);
				break;
			case 4://randomly assign property
				for (auto& prop : spaces)
				{
					if (prop->getType() == "PROPERTY")
					{
						prop->setOwner(Utilities::getRandomElement(players).getName());
					}
				}
				cout << "All property was randomly assigned." << endl;
				Sleep(2000);
				break;
			case 5:
				//the 0th player element gets all proeprty
				for (auto& prop : spaces)
				{
					if (prop->getType() == "PROPERTY")
					{
						prop->setOwner(players[0].getName());
					}
				}
				cout << "All property was given ownership to " << players[0].getName() << ".\n";
				Sleep(2000);
				break;
			}
		}
		//ternary operator:
		//if infinite cash is enabled, set it to 1,000,000, otherwise set it to the standard, which is 1500
		int toLoan = (infCash == true) ? 1'000'000 : 1500;
		cout << "The banker will now loan every player $" + to_string(toLoan) + " to start the game." << endl;
		for (auto& player : players)
		{
			player.setCash(toLoan);
		}
		Sleep(3000);
		cout << "The board will now be generated in a few seconds." << endl;
		Sleep(3000);
		system("CLS");
		return players;
	}

	void Game::setCards()
	{
		//just a bunch of card adding, not much to explain here

		//community cards
		CardHandler::addCard(Card{ "comm","get",10,5,"You win a contest for the world's ugliest person - you get $10" });
		CardHandler::addCard(Card{ "comm","pay",50,7,"Your toilet breaks. You must pay the plumber $50."});
		CardHandler::addCard(Card{ "comm","get",100,2,"You get elected as mayor and get $100." });
		CardHandler::addCard(Card{ "comm","pay",300,2,"Your dog breaks out and gets attacked by a coyote. You must pay the vet $300." });
		CardHandler::addCard(Card{ "comm","pay",100,3,"Your grandma dies. You must pay $100 for funeral expenses." });
		CardHandler::addCard(Card{ "comm","pay",30,10,"Your car breaks down. You must pay $30." });
		CardHandler::addCard(Card{ "comm","advanceGo",0,15,"You advance to go and collect $200." });
		CardHandler::addCard(Card{ "comm","goJail",0,10,"Oh no! You must go to jail!" });
		CardHandler::addCard(Card{ "comm","pay",50,10,"Your cat scratches the mayor. You must pay $50." });
		CardHandler::addCard(Card{ "comm","get",300,1,"Your dog wins a beauty pageant. You get $300." });
		CardHandler::addCard(Card{ "comm","get",50,10, "The town cuts taxes and you get a break. You get $50." });
		CardHandler::addCard(Card{ "comm","get",10,15,"You win $10 off of a scratch ticket." });
		CardHandler::addCard(Card{ "comm","get",30,5,"You win $30 off of a scratch ticket." });
		CardHandler::addCard(Card{ "comm","pay",50,5,"You lose $50 wasting money on scratch tickets." });

		//chance cards
		CardHandler::addCard(Card{ "chance","lose",0,2,"You waste all your money on casino slots! You go bankrupt!" });
		CardHandler::addCard(Card{ "chance","win",50,1,"You hide in a cave while everyone else gets robbed and goes bankrupt. You win!" });
		CardHandler::addCard(Card{ "chance","pay",200,5,"You must pay the banker $200." });
		CardHandler::addCard(Card{ "chance","pay",20,15,"You must pay the banker $20." });
		CardHandler::addCard(Card{ "chance","pay",50,10,"You must pay the banker $50." });
		CardHandler::addCard(Card{ "chance","get",1000,1,"You find the Mona Lisa painting in your basement. An art curator gives you $1000 for it.." });
		CardHandler::addCard(Card{ "chance","get",50,10,"The banker cuts you a deal and gives you $50." });
		CardHandler::addCard(Card{ "chance","get",50,15,"You play guitar on the street and end up collecting $50."});
		CardHandler::addCard(Card{ "chance","get",100,5,"You find $100 on the ground and decide to pocket it."});
		CardHandler::addCard(Card{ "chance","payEach",50,3,"You lose a bet attempting to gamble with the other players. You must pay everyone $50."});
		CardHandler::addCard(Card{ "chance","advanceGo",0,10, "You advance to go and collect $200." });
		CardHandler::addCard(Card{ "chance","goJail",0,5,"Oh no! You must go to jail!" });
		CardHandler::addCard(Card{ "chance","goBack",3,5,"You slip on a banana peel and fall backwards 3 spaces." });
		CardHandler::addCard(Card{ "chance","goBack",5,3,"You see a dog 5 spaces back and run towards it." });
		CardHandler::addCard(Card{ "chance","goBack",2,10,"You left your wallet 2 spaces back and have to go back for it." });

		//collectables
		CardHandler::addCard(Card{ "collect","get",25,20,"This card will grant you $25 from the bank." });
		CardHandler::addCard(Card{ "collect","get",50,10,"This card will grant you $50 from the bank." });
		CardHandler::addCard(Card{ "collect","get",100,5,"This card will grant you $100 from the bank." });
		CardHandler::addCard(Card{ "collect","getPlayer",25,20, "This card will give you $25 from a random player." });
		CardHandler::addCard(Card{ "collect","getPlayer",50,10,"This card will give you $50 from a random player." });
		CardHandler::addCard(Card{ "collect","getPlayer",100,5,"This card will give you $100 from a random player." });
		CardHandler::addCard(Card{ "collect","doubleRoll",0,15,"This card will double your next roll." });
		CardHandler::addCard(Card{ "collect","getOutJail",0,15,"This card will get you out of jail." });
	}

	void Game::setGameOutput(std::vector<std::string> newOutput)
	{
		gameOutput.clear();
		for (auto&str : newOutput)
		{
			gameOutput.push_back(str);
		}
	}

	int Game::getNumPlayers(vector<Player>& curPlayers)
	{
		//gets the players who aren't bankrupt
		int count{ 0 };
		for (auto& player : curPlayers)
		{
			if (player.isBankrupt() == false)
			{
				++count;
			}
		}
		return count;
	}

	int Game::rollDie()
	{
		//simple math to get 1-6 roll
		return (rand() % 6) + 1;
	}

	Player Game::play(vector<Player>& curPlayers)
	{
		int jail = 10;
		int inGame = getNumPlayers(curPlayers);
		vector<string> jailChoices{ "1 - Attempt to roll a double",
									"2 - Pay the $50(this will bankrupt you if you cannot pay it)" };
		while (inGame >= 2)//while at least 2 people aren't bankrupt
		{
			//check special conditions first before letting them roll 
			for (auto& player : curPlayers)
			{
				inGame = getNumPlayers(curPlayers);//redeclared here in case someone goes bankrupt before their turn starts
				if (inGame > 1)
				{
					setInfo(player);
					displayBoard();
					if (player.isBankrupt() == false)
					{
						setInfo(player);
						displayBoard();
						doStuffBeforeRoll(player, curPlayers);//calls the member function inside of this class to do menu stuff before turn
						gameOutput.clear();
						displayBoard();
						if (player.isInJail() == true)
						{
							player.setRolling(false);//don't let them roll initially
							cout << "Since you are in jail, you must pay a $50 fine or attempt to roll doubles.\nAfter 2 failed attempts to roll doubles, you must pay up." << endl;
							Sleep(4000);
							if (player.getJailAttempts() < 2)//if they haven't already tried to get out of jail rolling doubles twice
							{
								if (!player.isAI())//player makes decision
								{
									cout << "You have not yet failed 2 attempts, and are at " << to_string(player.getJailAttempts()) << " attempts." << endl;
									cout << "Here are your choices: " << endl;
									for (size_t i{ 0 }; i < jailChoices.size(); ++i)
									{
										cout << jailChoices[i] << endl;
										//list choices
									}
									cout << endl;
									int choice = Utilities::getIntInRange("What would you like to do?: ", 1, jailChoices.size());
									switch (choice)
									{
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
											if (roll1 == roll2)
											{
												cout << "You rolled doubles! Congratulations!" << endl;
												Sleep(3000);
												player.setJail(false);
												player.setRolling(true);
												//i decided to let them do their turn if they roll doubles, but they roll again
											}
											else
											{
												cout << "You didn't roll doubles..." << endl;
												Sleep(1500);
												cout << "Don't do the crime if you can't do the time..." << endl;
												player.addJailAttempt();
												Sleep(3000);
												player.setRolling(false);
											}
										}
										break;//end double rolling case
										case 2://just pay 50 case
										{
											displayBoard();
											player.deductCash(50);
											if (player.getCash() <= 0)//went bankrupt paying the 50 dollars
											{
												player.setBankruptcy(true);
												Utilities::resetOwnership(player, spaces);
												cout << "You went bankrupt. Better luck next time..." << endl;
												Sleep(3000);
												player.setRolling(false);
											}
											else//player had enough
											{
												cout << "$50 dollars was subtracted, and you are now out of jail." << endl;
												Sleep(3000);
												player.setJail(false);
												player.setRolling(true);
												//they paid so might as well let them roll
											}
										}
										break;//end pay 50 case
									}
								}
								else//AI makes decision
								{
									cout << player.getName() << " is making a decision..." << endl;
									Sleep(3000);
									//the AI will always just pay the fine, unless they actually cant
									if (player.getCash() > 50)
									{
										player.deductCash(50);
										setInfo(player);
										displayBoard();
										cout << player.getName() << " decided to just pay the 50 dollars." << endl;
										player.setJail(false);
										player.setRolling(true);
										Sleep(3000);
									}
									else
									{
										displayBoard();
										cout << player.getName() << " is going to attempt to roll doubles." << endl;
										Sleep(3000);
										int roll1 = rollDie();
										int roll2 = rollDie();
										player.setRoll(roll1 + roll2);
										cout << player.getName() << " rolled a " << to_string(roll1) << " and a " << to_string(roll2) << ".\n";
										Sleep(2000);
										if (roll1 == roll2)//AI rolled doubles
										{
											cout << player.getName() << " rolled doubles! Wowee!" << endl;
											Sleep(3000);
											player.setJail(false);
											player.setRolling(true);
										}
										else
										{
											cout << player.getName() << " didn't roll doubles. Nothing happens for the rest of their turn..." << endl;
											player.addJailAttempt();
											Sleep(3000);
											player.setRolling(false);
										}
									}
								}
							}
							else//they're already at 2 jail attempts now
							{
								displayBoard();
								cout << "Since you have 2 failed attempts to rolled doubles, you will now be charged $50. Bankruptcy is possible." << endl;
								Sleep(4000);
								player.deductCash(50);
								if (player.getCash() <= 0)
								{
									player.setBankruptcy(true);
									Utilities::resetOwnership(player, spaces);
									cout << "You went bankrupt. Better luck next time..." << endl;
									Sleep(3000);
									player.setRolling(false);
								}
								else
								{
									cout << "$50 dollars was subtracted, and you are now out of jail." << endl;
									Sleep(3000);
									player.setRolling(false);
								}
							}
						}
						if (player.canRoll())//check if the playe can roll based on the above
						{
							int doublesCount{ 0 };
							bool inJail{ false };
							bool keepRolling{ true }; //used for doubles module
							while (keepRolling)//player keeps rolling doubles then keep going
							{
								gameOutput.clear();
								displayBoard();
								cout << player.getName() << ", you will now roll." << endl;
								Sleep(3000);
								int roll1 = rollDie();
								int roll2 = rollDie();
								if (player.getAlwaysDoubles())//doubles cheat
								{
									roll2 = roll1;
								}
								else if (player.getOneTwo())//1 and 2 cheat
								{
									roll1 = 1;
									roll2 = 2;
								}
								player.setRoll(roll1 + roll2);
								if (player.canDoubleRoll())//used the double collectable which doubles their roll
								{
									player.setRoll(player.getRoll() * 2);
									cout << "Since you used a collectable to double your roll, your roll was doubled to " << player.getRoll() << ".\n";
								}
								cout << "You roll a " << to_string(roll1) << " and a " << to_string(roll2) << ".\n";
								Sleep(2000);
								if (roll1 == roll2)//if they rolled doubles
								{
									cout << "You rolled doubles!" << endl;
									Sleep(3000);
									player.setDoublesRolled(player.getDoublesRolled() + 1);//add 1 to the amount of times they've rolled doubles
									keepRolling = true;//keep going since they rolled doubles
									if (player.getDoublesRolled() == 3)//check if it's the 3rd time they have
									{
										keepRolling = false;//can't keep rolling
										player.setCurrentSpot(jail);//put them in jail
										setInfo(player);
										displayBoard();
										cout << "Oh no! You rolled 3 doubles and are now in jail!\nAt least you got 2 turns before that..." << endl;
										player.setJail(true);
										Sleep(5000);
									}
								}
								else//they didn't roll doubles, so exit the loop
								{
									keepRolling = false;
								}
								if (!player.isInJail())
									//make sure they're not in jail as a result of rolling(such as landing on GO TO JAIL)
								{
									displayBoard(); //flush the output besides board
									int start = player.getCurrentSpot();
									int toMove = start + player.getRoll();
									for (int i{ start + 1 }; i <= toMove; ++i)
									{
										int actual = i % 40; //range checking
										player.setCurrentSpot(actual);
										setInfo(player);
										displayBoard();
										cout << player.getName() << ", you are now moving." << endl;
										if (spaces[actual]->getType() == "GO_SPACE")//check if they passed GO
										{
											player.addCash(200);
											setInfo(player);
											displayBoard();
											cout << "You land on GO! Take this $200!" << endl;
											Sleep(3000);
										}
										Sleep(500);//to create a sort of space walking effect
									}
									//call the handle method of SpaceHandler depending on where they landed
									SpaceHandler::handle(*this, player, spaces[player.getCurrentSpot()], curPlayers);
								}
							}
						}
						inGame = getNumPlayers(curPlayers);
						//redeclare again so if handling the space results in bankruptcy,
						//the game loop adjusts correctly
					}
				}
			}
		}
		return curPlayers[0];
		//the game exited the big outer loop, which means one person is left
		//so i return the only element in the vector of players as the winner
	}

	int Game::calculateAssets(Player & player)
	{
		//pretty self-explanatory
		//total just keeps getting incremented based on what the player has
		int total{ 0 };
		total += player.getCash();
		vector<Space*> properties = Utilities::getProperty(player, spaces);
		for (auto& prop : properties)
		{
			for (int i{ 0 }; i < prop->getNumHouses(); ++i)
			{
				total += prop->getHouseCost();
			}
			for (int i{ 0 }; i < prop->getNumHotels(); ++i)
			{
				total += prop->getHouseCost();
			}
			for (int i{ 0 }; i < prop->getNumTurrets(); ++i)
			{
				total += prop->getHouseCost()*2;
			}
			total += prop->getCost();
		}
		vector<Space*> mort = Utilities::getMortgagedProperty(player, spaces);
		for (auto& prop : mort)
		{
			total += prop->getCost();
		}
		//add everything up then divide by 10, since income tax is 10%
		return total / 10;
	}

	vector<Space*> Game::getSpaces()
	{
		return this->spaces;
	}

	void Game::battle(Player & player1, Player & player2)
	{
		//set of dialogue battle can use
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
		//HP is reset so if a player wins one fight and gets in another they aren't at a disadvantage HP-wise
		player1.setHP(100);
		player2.setHP(100);
		//give each player a boost to getHP() equal to 10% on assets owned, but ignore cash
		player1.setHP(player1.getHP()+calculateAssets(player1)-(player1.getCash()/10));
		player2.setHP(player1.getHP()+calculateAssets(player2)-(player2.getCash()/10));
		//give each player a slight boost to defense based on turrets they have
		vector<Space*> properties = Utilities::getProperty(player1, spaces);
		for (auto& prop : properties)
		{
			player1.setDefense(player1.getDefense() + prop->getNumTurrets() * 10);
		}
		properties = Utilities::getProperty(player2, spaces);
		for (auto& prop : properties)
		{
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
		while (!doneBattling)//while no one has died
		{
			displayBoard();
			int damage = (rand() % 11) + 30;//random number from 40-50
			//modify damage based on defense
			if (player1Turn)//if attacker turn
			{
				//some simple math to adjust for defense
				int toSubtract = player2.getDefense() / 5;
				damage -= toSubtract;
				displayBoard();
				player2.setHP(player2.getHP() - damage);
				cout << player1.getName() << "'s HP: " << player1.getHP() << endl;
				cout << player2.getName() << "'s HP: " << player2.getHP() << endl << endl;
				cout << player1.getName() + Utilities::getRandomElement(battleDialogChoices) + to_string(damage) + " damage to " + player2.getName() + "!!!";
				Sleep(5000);
				//check if they died
				if (player2.getHP() <= 0)
				{
					doneBattling = true;
					int toReceive = player2.getCash() / 5;
					player2.deductCash(toReceive);
					player1.addCash(toReceive);
					setInfo(player1);
					displayBoard();
					cout << player1.getName() << " has won! They get 20% of " << player2.getName() << "'s money and receive " << to_string(toReceive) << " dollars!" << endl;
					Sleep(4000);
				}
				else
				{
					player1Turn = false;
				}
			}
			else
			{
				int toSubtract = player1.getDefense() / 5;
				damage -= toSubtract;
				player1.setHP(player1.getHP() - damage);
				displayBoard();
				cout << player1.getName() << "'s HP: " << player1.getHP() << endl;
				cout << player2.getName() << "'s HP: " << player2.getHP() << endl << endl;
				cout << player2.getName() + Utilities::getRandomElement(battleDialogChoices) + to_string(damage) + " damage to " + player1.getName() + "!!!";
				Sleep(5000);
				//check if they died
				if (player1.getHP() <= 0)
				{
					doneBattling = true;
					int toReceive = player1.getCash() / 5;
					player1.deductCash(toReceive);
					player2.addCash(toReceive);
					setInfo(player1);
					displayBoard();
					cout << player2.getName() << " has won! They get 20% of " << player1.getName() << "'s money and receive " << to_string(toReceive) << " dollars!" << endl;
					Sleep(4000);
				}
				else
				{
					player1Turn = true;
				}
			}
		}
	}

	void Game::attackProp(Player & player, Player & mob)
	{
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
		//give each player a boost to getHP() equal to 10% on assets owned(minus cash)
		player.setHP(player.getHP() + calculateAssets(player) - (player.getCash() / 10));
		mob.setHP(mob.getHP() + calculateAssets(mob) - (mob.getCash() / 10));
		//give each player a slight boost to defense based on turrets they have
		vector<Space*> properties = Utilities::getProperty(player, spaces);
		for (auto& prop : properties)
		{
			player.setDefense(player.getDefense() + prop->getNumTurrets() * 10);
			cout << player.getName() << "'s defense:" << player.getDefense() << endl;
		}
		properties = Utilities::getProperty(mob, spaces);
		for (auto& prop : properties)
		{
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
		while (!doneBattling)
		{
			displayBoard();
			int damage = (rand() % 20) + 30;
			int turretDamage = damage;
			//modify damage based on defense, prevent division by 0 as well
			if (playerTurn)
			{
				int toSubtract = mob.getDefense() / 5;
				damage -= toSubtract;
				displayBoard();
				mob.setHP(mob.getHP() - damage);
				cout << player.getName() << "'s HP: " << player.getHP() << endl;
				cout << "The mob's HP: " << mob.getHP() << endl << endl;
				cout << player.getName() + Utilities::getRandomElement(playerChoices) + to_string(damage) + " damage to the mob!!!";
				Sleep(5000);
				//check if they died
				if (mob.getHP() <= 0)
				{
					doneBattling = true;//battle is over
					displayBoard();
					cout << "The player successfully attacked the property!" << endl;
					cout << "Since you were so daring, you must pay twice the cost of the property, or go bankrupt." << endl;
					Sleep(3000);
					player.deductCash(prop->getCost()*2);//deduct twice the cost
					setInfo(player);
					displayBoard();
					if (player.getCash() <= 0)//check if it bankrupts them
					{
						cout << "You went bankrupt! Maybe you should have left them alone..." << endl;
						player.setBankruptcy(true);
						Utilities::resetOwnership(player, spaces);
						Sleep(3000);
					}
					else
					{
						prop->setOwner(player.getName());
						cout << "The property now belongs to you, " << player.getName() << ".\n";
						Sleep(3000);
					}
				}
				else
				{
					playerTurn = false;//set turn false so other player can attack
				}
			}
			else//not player turn, let other player attack
			{
				int toSubtract = player.getDefense() / 5;
				damage -= toSubtract;
				player.setHP(player.getHP() - damage);
				displayBoard();
				cout << player.getName() << "'s HP: " << player.getHP() << endl;
				cout << "The mob's HP: " << mob.getHP() << endl << endl;
				cout << "The mob" + Utilities::getRandomElement(mobChoices) + to_string(damage) + " damage to " + player.getName() + "!!!";
				if (prop->getNumTurrets() > 0)//check if there's a turret
				{
					player.setHP(player.getHP() - turretDamage);//turret attacks
					cout << "The turret on the property also fires for " << turretDamage << " damage to the attacker." << endl;
				}
				Sleep(5000);
				//check if they died
				if (player.getHP() <= 0)
				{
					doneBattling = true;
					player.deductCash(player.getCash() / 3);
					setInfo(player);
					displayBoard();
					cout << "The mob has defended the attack! Huzzah! The mob robs the attacker of 30% of their money." << endl;
					Sleep(4000);
				}
				else
				{
					playerTurn = true;
				}
			}
		}
	}

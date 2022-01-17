
#include "TurnHandler.h"
#include "CardHandler.h"
#include"Windows.h"

using namespace std;

void TurnHandler::handle() {
	bool done{ false };
	player.setRolling(true);
	while (!done) {
		if (game.getNumPlayers() == 1) {
			cout << player.getName() << " has won the game! Congratulations!" << endl;
			Sleep(5000);
			done = true;
		}
		else {
			gameOutput.clear();
			game.setInfo(player);
			if (!player.isAI()) {
				gameOutput.push_back("Here are your options before you roll: ");
				gameOutput.push_back("1 - Mortgage owned property");
				gameOutput.push_back("2 - Lift mortgages");
				gameOutput.push_back("3 - Trade with another player");
				gameOutput.push_back("4 - Build houses/hotels/turrets");
				gameOutput.push_back("5 - Warp via railroad(you must be on one and own a different one)");
				gameOutput.push_back("6 - Use Collectable Card");
				game.displayBoard();

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
								game.setInfo(player);
								game.displayBoard();
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
									CardHandler handler = CardHandler(curPlayers, game, player, toUse);
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
								CardHandler handler = CardHandler(curPlayers, game, player, toUse);
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
				game.displayBoard();
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
						game.displayBoard();
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
							game.setInfo(player);
							game.displayBoard();
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
								game.setInfo(player);
								game.displayBoard();
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
					game.displayBoard();
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
												game.setInfo(player);
												game.displayBoard();
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
					game.displayBoard();
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
											game.setInfo(player);
											game.displayBoard();
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
					game.displayBoard();
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
										game.setInfo(player);
										game.displayBoard();
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
								CardHandler handler = CardHandler(curPlayers, game, player, card);
								handler.handle();
								player.setCards(AIcards);
							}
							else if (card.getEffect() == "getOutJail") {
								if (player.isInJail()) {
									cout << player.getName() << " is going to use a collectable." << endl;
									Sleep(3000);
									CardHandler handler = CardHandler(curPlayers, game, player, card);
									handler.handle();
									player.setCards(AIcards);
								}
							}
							else if (card.getEffect() == "doubleRoll") {
								if (!player.isInJail()) {
									cout << player.getName() << " is going to use a collectable." << endl;
									Sleep(3000);
									CardHandler handler = CardHandler(curPlayers, game, player, card);
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

TurnHandler::TurnHandler(Game& g, Player& p, std::vector<Player>& curPlrs, std::vector<Space*>& s,
	std::vector<std::string>& gameOut, std::vector<std::string>& cSets)
	: game( g ), player( p ), curPlayers( curPlrs ), spaces( s ), gameOutput( gameOut ), colorSets( cSets ) {};
	

#include "SpaceHandler.h"
#include"Utilities.h"
#include<vector>
#include<string>
#include<iostream>
#include<Windows.h>
#include"CardHandler.h"

using namespace std;

int getBidders(vector<Player>& bidders);

void SpaceHandler::handle(Game& game, Player& player, Space* space, vector<Player>& curPlayers)
{
	game.displayBoard();

	string type = space->getType();
	vector<Player> toBattle;
	int cost = space->getCost();
	
	for (auto& other : curPlayers)
	{
		if (other.getName() != player.getName())
		{
			if (other.getCurrentSpot() == player.getCurrentSpot())
			{
				toBattle.push_back(other);
			}
		}
	}
	if (toBattle.empty())
	{
		cout << "No other players are on this spot. Phew!" << endl;
		Sleep(3000);
	}
	else
	{
		cout << "Oh no! 1 or more players is on the spot you landed on! Let the battle commence!" << endl;
		cout << "A random player on this spot will be selected to battle with you. Good luck!" << endl;
		Sleep(6000);
		int randInt = (toBattle.size() <= 1) ? 0 : rand() % (toBattle.size() - 1);
		game.battle(player, toBattle[randInt]);
	}
	if (type == "PROPERTY")
	{
		game.displayBoard();
		cout << "You have landed on a property." << endl;
		if (space->getOwner() != "None")
		{
			if (space->getOwner() != player.getName())
			{
				if (!space->isMortgaged())
				{
					int rent{ 0 };
					Player owner;
					for (auto& other : curPlayers)
					{
						if (other.getName() == space->getOwner())
						{
							owner = other;
						}
					}

					if (space->getPropertyType() == "STANDARD")
					{
						rent = space->getRent();
					}
					else if (space->getPropertyType() == "RAILROAD")
					{
						vector<Space*> spaces = game.getSpaces();
						rent = space->getRailroadRent(owner, spaces);
					}
					else if (space->getPropertyType() == "UTILITY")
					{
						vector<Space*> spaces = game.getSpaces();
						rent = space->getUtilRent(owner, spaces,player.getRoll());
					}
					vector<string> choices{ "1 - Pay rent, which will cost you " + to_string(rent) + " dollars."
											"If you cannot afford this, you will go bankrupt).",
										   "2 - Attack the property. You must pay twice the cost of the property if you win, which will be " + to_string(cost * 2) + " dollars."
											"\nIf you cannot afford this, you will go bankrupt. If you lose, you will lose 30% of your cash." };
					if (!player.isAI())
					{
						cout << "Someone owns this property. Here are your options: " << endl;
						for (size_t i{ 0 }; i < choices.size(); ++i)
						{
							cout << choices[i] << endl;
						}
						int ans = Utilities::getIntInRange("What would you like to do?: ", 1, 2);
						switch (ans)
						{
						case 1: 
							player.deductCash(rent);
							owner.addCash(rent);
							game.setInfo(player);
							game.displayBoard();
							if (player.getCash() <= 0)
							{
								cout << "OOF! You went bankrupt! Better luck next time..." << endl;
								player.setBankruptcy(true);
								Utilities::resetOwnership(player, game.getSpaces());
								Sleep(3000);
							}
							else
							{
								cout << "Cash was subtracted." << endl;
								Sleep(2000);
							}
							break;
						case 2: //the case for attacking
							for (auto& owner : curPlayers)
							{
								if (owner.getName() != player.getName())
								{
									if (owner.getName() == space->getOwner())
									{
										game.attackProp(player, owner);
									}
								}
							}
							break;
						}
					}

					else
					{
						bool attack{ false };
						cout << player.getName() << " is making a decision..." << endl;
						Sleep(4000);
						for (auto& owner : curPlayers)
						{
							if (owner.getName() != player.getName())
							{
								if (owner.getName() == space->getOwner())
								{
									//The AI will attack if they have at least 25% more of prop-cash assets
									int AIdef = game.calculateAssets(player) - player.getCash() / 10;
									int ownerDef = game.calculateAssets(owner) - owner.getCash() / 10;
									if (static_cast<double>(AIdef / ownerDef) >= 1.25)
									{
										attack = true;
									}
									else
									{
										attack = false;
									}
									if (space->getNumTurrets() > 0)
									{
										attack = false;
									}
									if (rent > player.getCash())
									{
										attack = true;
									}
									if (attack)
									{
										game.attackProp(player, owner);
									}
									else
									{
										player.deductCash(rent);
										owner.addCash(rent);
										game.setInfo(player);
										game.displayBoard();
										cout << player.getName() << " has decided to just pay the rent." << endl;
										Sleep(2000);
									}
								}
							}
						}
					}
				}
				else
				{
					cout << "This property is mortgaged by a player.\nYou cannot attack it, but you also don't have to pay rent." << endl;
					Sleep(4000);
				}
			}
			else
			{
			cout << "You own this property, so nothing happens..." << endl;
			Sleep(3000);
			}
		}
		else
		{
			bool biddable{ false };
			if (!player.isAI())
			{
				string ans = Utilities::getStringYesNo("Did you want to purchase this property for " + to_string(cost) + " dollars?(y/n):");
				if (ans == "Y" || ans == "y")
				{
					if (player.canDeduct(cost))
					{
						player.deductCash(cost);
						space->setOwner(player.getName());
						game.setInfo(player);
						game.displayBoard();
						cout << "Property succesfully bought." << endl;
						Sleep(3000);
					}
					else
					{
						cout << "You do not have enough money..." << endl;
						biddable = true;
						Sleep(3000);
					}
				}
				else if (ans == "N" || ans == "n")
				{
					biddable = true;
				}
			}
			else //if the player is AI controlled:
			{
				cout << player.getName() << " is deciding if they want to purchase the property..." << endl;
				Sleep(3000);

				//AI only purchases if they have at least 2.5 * the cost of the property
				if (player.getCash() > 2.5 * cost)
				{
					player.deductCash(cost);
					space->setOwner(player.getName());
					game.setInfo(player);
					game.displayBoard();
					cout << player.getName() << " bought " << space->getName() << ".\n";
					Sleep(3000);
					biddable = false;
				}
				else
				{
					cout << player.getName() << " did not want the property." << endl;
					Sleep(3000);
					biddable = true;
				}
			}

			if (biddable)
			{
				cout << "The property will now be put up for auction, since " << player.getName() << " did not want it." << endl;
				Sleep(5000);
				int currentBid{ cost };
				bool doneBidding{ false };
				vector<Player> bidders;
				int AILimit = cost * 2;
				//AI will stop if the cost skyrockets
				for (auto& other : curPlayers)
				{
					if (other.getName() != player.getName())
					{
						if (!other.isAI())
						{
							string ans = Utilities::getStringYesNo(other.getName() + ", would you like to participate in the bidding?(y/n): ");
							if (ans == "Y" || ans == "y")
							{
								if (other.getCash() <= currentBid + 1)
								{
									cout << "You don't have enough money to participate in the bidding..." << endl;
									other.setBidding(false);
									Sleep(3000);
								}
								else
								{
									bidders.push_back(other);
								}
							}
						}
						else
						{
							cout << "AI " << other.getName() << " is deciding if they want to bid..." << endl;
							Sleep(3000); 
							if (other.getCash() >= (currentBid * 2))
							{
								cout << "AI " << other.getName() << " has decided to bid." << endl;
								Sleep(1500);
								bidders.push_back(other);
							}
							else
							{
								cout << "AI " << other.getName() << " has decided not to bid." << endl;
								Sleep(1500);
								other.setBidding(false);
							}
						}
					}
				}
				while (!doneBidding)
				{
					if (bidders.empty())
					{
						cout << "No one wanted the property. What a shame..." << endl;
						doneBidding = true;
						Sleep(3000);
					}
					else
					{
						for (auto& bidder : bidders)
						{
							game.displayBoard();
							if (getBidders(bidders) == 1)
							{
								if (bidder.isBidding())
								{
									cout << bidder.getName() << " won the bid and got the property for " << currentBid << " dollars." << endl;
									bidder.deductCash(currentBid);
									space->setOwner(bidder.getName());
									Sleep(3000);
									doneBidding = true;
								}
							}
							
							else if (getBidders(bidders)>1)
							{
								if (bidder.isBidding())
								{
									if (bidder.getCash() >= currentBid + 1)
									{
										if (!bidder.isAI())
										{
											cout << "The current bid is " << currentBid << " dollars, " << bidder.getName() << endl;
											cout << "You must bid higher than this value to keep bidding." << endl;
											string keepGoing = Utilities::getStringYesNo("Do you want to keep bidding or back out?(y/n): ");
											if (keepGoing == "Y" || keepGoing == "y")
											{
												int bid = Utilities::getIntInRange("What would you like to bid?: ", currentBid + 1, bidder.getCash() - 1);
												currentBid = bid;
												cout << bidder.getName() << " has raised the bid to " << currentBid << " dollars." << endl;
												Sleep(3000);
											}
											else if (keepGoing == "N" || keepGoing == "n")
											{
												bidder.setBidding(false);
												cout << "You successfully chickened out on the bid." << endl;
												Sleep(3000);
											}
										}
										else//AI decision
										{
											//AI only keeps bidding if the current bid is less than 1.5 * the property value
											if (currentBid <= cost * 1.5)
											{
												//AI always raises bid by 10%. If the AI cannot(due to lack of money), they will back out
												if (bidder.getCash() >= (currentBid + currentBid / 10))
												{
													cout << "AI " << bidder.getName() << " is deciding what to raise the bid to..." << endl;
													Sleep(3000);
													currentBid = currentBid + currentBid / 10;
													cout << bidder.getName() << " has raised the bid to " << currentBid << " dollars." << endl;
													Sleep(4000);
												}
												else
												{
													cout << bidder.getName() << " has backed out of the bid..." << endl;
													bidder.setBidding(false);
													Sleep(3000);
												}
											}
											else
											{
												cout << "The bid got too high for " << bidder.getName() << ", so they backed out." << endl;
												bidder.setBidding(false); 
												Sleep(4000);
											}
										}
									}
									else
									{
										cout << bidder.getName() << " does not have enough money to stay in the bid." << endl;
										bidder.setBidding(false);
										Sleep(3000);
									}
								}
							}
						}
					}
				}
			}
		}
	}
	else if (type == "TAX_SPACE")
	{
		if (space->getName() == "Income Tax")
		{
			int assets = game.calculateAssets(player);
			game.displayBoard();
			if (!player.isAI())
			{
				cout << "You landed on income tax. Here are your options: " << endl << endl;
				vector<string> choices = { "1 - Pay 10% of your assets(this will cost you " + to_string(assets) + " dollars.",
										  "2 - Pay 200 dollars." };
				for (size_t i{ 0 }; i < choices.size(); ++i)
				{
					cout << choices[i] << endl;
				}
				int choice = Utilities::getIntInRange("Please enter an option: ", 1, 2);
				player.deductCash((choice == 1) ? assets : 200);
				game.setInfo(player);
				game.displayBoard();
				if (player.getCash() <= 0)
				{
					cout << "You went bankrupt. Better luck next time..." << endl;
					Sleep(3000);
					player.setBankruptcy(true);
					Utilities::resetOwnership(player, game.getSpaces());
				}
				else
				{
					cout << "Cash was deducted." << endl;
					Sleep(2000);
				}
			}
			else//AI decision
			{
				cout << player.getName() << " landed on income tax. They are now making a decision..." << endl;
				Sleep(4000);
				int payAssets = game.calculateAssets(player);
				if (payAssets < 200)
				{
					player.deductCash(payAssets);
					game.setInfo(player);
					game.displayBoard();
					if (player.getCash() <= 0)
					{
						cout << player.getName() << " went bankrupt. Better luck next time..." << endl;
						Sleep(3000);
						player.setBankruptcy(true);
						Utilities::resetOwnership(player, game.getSpaces());
					}
					else//they had enough
					{
						cout << player.getName() << " decided to pay on their assets for " << payAssets << " dollars." << endl;
						Sleep(4000);
					}
				}
				else
				{
					player.deductCash(200);
					game.setInfo(player);
					game.displayBoard();
					if (player.getCash() <= 0)
					{
						cout << player.getName() << " went bankrupt. Better luck next time..." << endl;
						Sleep(3000);
						player.setBankruptcy(true);
						Utilities::resetOwnership(player, game.getSpaces());
					}
					else
					{
						cout << player.getName() << " decided to just pay 200 dollars." << endl;
						Sleep(3000);
					}
				}
			}
		}
		else if (space->getName() == "Luxury Tax")
		{
			game.displayBoard();
			cout << "You landed on the luxury tax space.\nYou will now be deducted $100. Bankruptcy is possible." << endl;
			Sleep(3000);
			player.deductCash(100);
			if (player.getCash() <= 0)
			{
				cout << "You went bankrupt. Better luck next time..." << endl;
				Sleep(3000);
				game.setInfo(player);
				game.displayBoard();
				player.setBankruptcy(true);
				Utilities::resetOwnership(player, game.getSpaces());
			}
			else
			{
				cout << "Cash successfully deducted." << endl;
				game.setInfo(player);
				game.displayBoard();
				Sleep(3000);
			}
		}
	}
	else if (type == "GOTO_JAIL")
	{
		game.displayBoard();
		cout << "You will now be sent to jail. OOF!" << endl;
		Sleep(3000);
		player.setJail(true);
		player.setCurrentSpot(10);
	}
	else if (type == "COMM" || type == "CHANCE")
	{
		Card card = CardHandler::drawCard(type, player, game);
		cout << card.getDesc() << endl;
		CardHandler::handleCard(curPlayers,game,player,card);
	}
	else if (type == "JAIL" || type == "FREE")
	{
		cout << "The space you landed on does nothing to you." << endl;
		Sleep(3000);
	}
}

int getBidders(vector<Player>& bidders)
{
	int tot{ 0 };
	for (auto& bidder : bidders)
	{
		if (bidder.isBidding())
		{
			++tot;
		}
	}
	return tot;
}

#include "SpaceHandler.h"
#include"Utilities.h"
#include<vector>
#include<string>
#include<iostream>
#include<Windows.h>
#include"CardHandler.h"

using namespace std;

//returns the players bidding
int getBidders(vector<Player>& bidders);

//this cpp is pretty big, but i will do my best to explain it

void SpaceHandler::handle(Game& game, Player& player, Space* space, vector<Player>& curPlayers)
{
	//here, i check if other player(s) are on the space first and do battle
	//if more than 1 player is on the space, they battle a random player on that space
	//after battling is set, other stuff is checked

	//flush the output first...
	game.displayBoard();

	string type = space->getType();
	vector<Player> toBattle;
	int cost = space->getCost();

	//all this does here is get all other players on the spot they landed on.
	//the extra check here is to avoid making the player battle themselves.
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

		//i cant do rand() % 0 here, so i use a ternary operator:
		//if the size of the vector is 1 or less, just grab the 0th element, otherwise:
		//grab a random index from ( 0 ) to ( the size of the vector - 1 )
		//the minus one is to prevent going out of bounds(vector[vector.size()] will be out of range)

		int randInt = (toBattle.size() <= 1) ? 0 : rand() % (toBattle.size() - 1);
		game.battle(player, toBattle[randInt]);
	}
	if (type == "PROPERTY")
	{
		game.displayBoard();
		cout << "You have landed on a property." << endl;
		if (space->getOwner() != "None")
		{
			//someone owns it, but make sure it isn't the person who stepped on it
			if (space->getOwner() != player.getName())
			{
				if (!space->isMortgaged()) //everything below can only occur if the property isn't mortgaged
				{
					int rent{ 0 };
					Player owner;
					//get the player that owns the property
					for (auto& other : curPlayers)
					{
						if (other.getName() == space->getOwner())
						{
							owner = other;
						}
					}

					//set the rent based on the property type
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

					//choices for landing on an owned property
					vector<string> choices{ "1 - Pay rent, which will cost you " + to_string(rent) + " dollars."
											"If you cannot afford this, you will go bankrupt).",
										   "2 - Attack the property. You must pay twice the cost of the property if you win, which will be " + to_string(cost * 2) + " dollars."
											"\nIf you cannot afford this, you will go bankrupt. If you lose, you will lose 30% of your cash." };

					//big check here: do a bunch of stuff differently if the player isn't AI controlled:
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
						case 1: //the case for paying rent
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

							//this will get funky if i dont check against the player.
							//if they attack property and become the owner, then this will let the player attack their own property,
							//because ownership was changed. so i add an extra check here as well
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

					//if the player is AI controlled:
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
									//the AI will attack if they have at least 25% more of prop-cash assets
									//i don't include cash because i think that could get unfair
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
									//if there is a turret, however, the AI will not attack
									if (space->getNumTurrets() > 0)
									{
										attack = false;
									}
									//if AI cannot pay rent, attack anyways and maybe just lose the 30% cash...
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
				else //if the property is mortgaged:
				{
					cout << "This property is mortgaged by a player.\nYou cannot attack it, but you also don't have to pay rent." << endl;
					Sleep(4000);
				}
			}
			else //if you stepped on a property you own:
			{
			cout << "You own this property, so nothing happens..." << endl;
			Sleep(3000);
			}
		}
		else //if the property is not owned:
		{
			bool biddable{ false };

			//ask player if they want it, if they aren't AI:
			if (!player.isAI())
			{
				string ans = Utilities::getStringYesNo("Did you want to purchase this property for " + to_string(cost) + " dollars?(y/n):");
				if (ans == "Y" || ans == "y")
				{
					if (player.canDeduct(cost)) //make sure they have enough money first
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
					//property can be put up for auction
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

			//if the above did not want the property:
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
					if (other.getName() != player.getName()) //don't let the player that didn't want it bid
					{
						//ask player if they want to bid
						if (!other.isAI())
						{
							string ans = Utilities::getStringYesNo(other.getName() + ", would you like to participate in the bidding?(y/n): ");
							if (ans == "Y" || ans == "y")
							{
								if (other.getCash() <= currentBid + 1)//make sure they got enough money
								{
									cout << "You don't have enough money to participate in the bidding..." << endl;
									other.setBidding(false);
									Sleep(3000);
								}
								else
								{
									//add to bidder vector
									bidders.push_back(other);
								}
							}
						}
						//AI deciding if they want to bid
						else
						{
							cout << "AI " << other.getName() << " is deciding if they want to bid..." << endl;
							Sleep(3000); 
							//AI only bids if they have at least twice the property value:
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

				//keep running bid cycles while we're not done
				while (!doneBidding)
				{
					//keep asking players if they want it
					if (bidders.empty()) //if no one said yes to bid on it
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
							//check if they're the only one in the vector, if so the bidding is done
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
							
							else if (getBidders(bidders)>1)//if at least 2 are bidding
							{
								if (bidder.isBidding())//check if they are actually still bidding
								{
									if (bidder.getCash() >= currentBid + 1)
									{
										if (!bidder.isAI())//player choice
										{
											cout << "The current bid is " << currentBid << " dollars, " << bidder.getName() << endl;
											cout << "You must bid higher than this value to keep bidding." << endl;
											string keepGoing = Utilities::getStringYesNo("Do you want to keep bidding or back out?(y/n): ");
											if (keepGoing == "Y" || keepGoing == "y")
											{
												int bid = Utilities::getIntInRange("What would you like to bid?: ", currentBid + 1, bidder.getCash() - 1); //can't go bankrupt technically
												currentBid = bid;
												cout << bidder.getName() << " has raised the bid to " << currentBid << " dollars." << endl;
												Sleep(3000);
											}
											else if (keepGoing == "N" || keepGoing == "n")
											{
												bidder.setBidding(false);//take em out of the bidders
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
									else//bidder doesn't have enough money to keep up
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
			if (!player.isAI())//player decision
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
				//another ternary operator here(i really like these):
				//deduct assets if they choose 1, deduct the 200 if they choose the other option, which is 2
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
				if (payAssets < 200)//if their assets cost less than the 200
				{
					player.deductCash(payAssets);
					game.setInfo(player);
					game.displayBoard();
					if (player.getCash() <= 0)//they can go bankrupt, so i have to check it here
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
				else//if they choose to just pay 200, because it was less expensive than their assets
				{
					player.deductCash(200);
					game.setInfo(player);
					game.displayBoard();
					if (player.getCash() <= 0)//still gotta check bankruptcy
					{
						cout << player.getName() << " went bankrupt. Better luck next time..." << endl;
						Sleep(3000);
						player.setBankruptcy(true);
						Utilities::resetOwnership(player, game.getSpaces());
					}
					else//they got the 200, so it's fine
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
			//no decision-making here, so AI check unnecessary
			cout << "You landed on the luxury tax space.\nYou will now be deducted $100. Bankruptcy is possible." << endl;
			Sleep(3000);
			player.deductCash(100);
			if (player.getCash() <= 0)//oof, they went bankrupt from the $100 deduction
			{
				cout << "You went bankrupt. Better luck next time..." << endl;
				Sleep(3000);
				game.setInfo(player);
				game.displayBoard();
				player.setBankruptcy(true);
				Utilities::resetOwnership(player, game.getSpaces());
			}
			else//everything's fine, they have at least $101
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
		//not much to explain here
		game.displayBoard();
		cout << "You will now be sent to jail. OOF!" << endl;
		Sleep(3000);
		player.setJail(true);
		player.setCurrentSpot(10); //the jail spot in the vector of board spaces is spaces[10]
	}
	else if (type == "COMM" || type == "CHANCE")
	{
		//draw the card from the correct deck, then do the stuff with the card's attributes using handleCard
		Card card = CardHandler::drawCard(type, player, game);
		cout << card.getDesc() << endl;
		CardHandler::handleCard(curPlayers,game,player,card);
	}
	else if (type == "JAIL" || type == "FREE")
	{
		//very simple
		cout << "The space you landed on does nothing to you." << endl;
		Sleep(3000);
	}
}

int getBidders(vector<Player>& bidders)
{
	//gets the bidders still bidding(helper function basically)
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

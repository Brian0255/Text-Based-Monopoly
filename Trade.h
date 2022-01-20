#pragma once
#include<vector>
#include"Player.h"
#include"Space.h"
struct Trade {
	Player& player1;
	Player& player2;
	std::vector<Space*> prop1;
	std::vector<Space*> prop2;
	std::vector<Space*> player1Offer;
	std::vector<Space*> player1Get;
	bool exitTrade;
};
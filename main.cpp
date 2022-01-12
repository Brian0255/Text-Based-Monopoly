#include "Game.h"
#include<ctime>
#include<iostream>
#include<Windows.h>
using namespace std;

int main() {
	std::srand(static_cast<unsigned int>(time(0)));
	Game game;
	game.setCards();
	vector<Player> curPlayers;
	cout << "Welcome to Monopoly!" << endl;
	Sleep(5000);
	curPlayers = game.setup();
	Player winner = game.play(curPlayers);
	cout << winner.getName() << " has won the game!" << endl;
	system("pause");
}

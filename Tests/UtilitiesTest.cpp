#include "pch.h"
#include "CppUnitTest.h"
#include"Utilities.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests {
	TEST_CLASS(Tests) {
public:
	TEST_METHOD(testRemoveByValue) {
		std::vector<int> numbers{ 1,2,3 };
		Utilities::removeByValue(numbers, 1);
		Assert::AreEqual(size_t{ 2 }, numbers.size());
	}
	TEST_METHOD(TestGetIndexPtrObj) {
		Player* p1 = new Player("player1", 0, 0, false, false, false);
		Player* p2 = new Player("player2", 0, 0, false, false, false);
		Player* p3 = new Player("player3", 0, 0, false, false, false);
		std::vector<Player*> players{ p1,p2,p3 };
		Assert::AreEqual(0, Utilities::getIndexPtrObj(players, p1));
	}
	TEST_METHOD(testRemoveObjectByValue) {
		Player p1 = Player("player1", 0, 0, false, false, false);
		Player p2 = Player("player2", 0, 0, false, false, false);
		Player p3 = Player("player3", 0, 0, false, false, false);
		std::vector<Player> players{ p1,p2,p3 };
		Utilities::removeObjectByValue(players, p1);
		Assert::AreEqual(size_t{ 2 }, players.size());
	}
	TEST_METHOD(testRemovePtrObjectByValue) {
		Player* p1 = new Player("player1", 0, 0, false, false, false);
		Player* p2 = new Player("player2", 0, 0, false, false, false);
		Player* p3 = new Player("player3", 0, 0, false, false, false);
		std::vector<Player*> players{ p1,p2,p3 };
		Utilities::removePtrObjectByValue(players, p1);
		Assert::AreEqual(size_t{ 2 }, players.size());
	}
	TEST_METHOD(testRemoveRandomElement) {
		Player p1 = Player("player1", 0, 0, false, false, false);
		Player p2 = Player("player2", 0, 0, false, false, false);
		Player p3 = Player("player3", 0, 0, false, false, false);
		std::vector<Player> players{ p1,p2,p3 };
		Utilities::removeRandomElement(players);
		Assert::AreEqual(size_t{ 2 }, players.size());
		Utilities::removeRandomElement(players);
		Utilities::removeRandomElement(players);
		Assert::AreEqual(size_t{ 0 }, players.size());
	}
	TEST_METHOD(testGetRandomElement) {
		Player p1 = Player("player1", 0, 0, false, false, false);
		Player p2 = Player("player2", 0, 0, false, false, false);
		std::vector<Player> players{ p1,p2 };
		Player got = Utilities::getRandomElement(players);
		Assert::IsTrue(got.getName() == p1.getName() || got.getName() == p2.getName());
	}
	};
}

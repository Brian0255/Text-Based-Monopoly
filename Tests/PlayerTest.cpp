#include "pch.h"
#include "CppUnitTest.h"
#include"Player.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(Tests)
	{
	public:
		TEST_METHOD(TestInit)
		{
			Player player = Player();
			std::string name = "NONE";
			Assert::AreEqual(name, player.getName());
			Assert::AreEqual(0, player.getCash());
			Assert::AreEqual(0, player.getCurrentSpot());
		}
		TEST_METHOD(TestCashDeduction) {
			Player player = Player();
			player.setCash(1500);
			player.deductCash(1100);
			Assert::AreEqual(400, player.getCash());
		}
		TEST_METHOD(TestNegativeCash) {
			Player player = Player();
			player.setCash(500);
			player.deductCash(600);
			Assert::AreEqual(0, player.getCash());
		}
		TEST_METHOD(TestBankruptcy) {
			Player player = Player();
			player.setBankruptcy(true);
			Assert::IsTrue(player.isBankrupt());
		}
		TEST_METHOD(TestJailAttempts) {
			Player player = Player();
			for (int i = 0; i < 4; ++i) {
				player.addJailAttempt();
			}
			Assert::AreEqual(player.getJailAttempts(), 4);
		}
		TEST_METHOD(TestCanRoll) {
			Player player = Player();
			player.setRolling(false);
			Assert::IsFalse(player.canRoll());
			player.setRolling(true);
			Assert::IsTrue(player.canRoll());
		}
	};
}

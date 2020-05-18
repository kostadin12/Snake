#include "pch.h"
#include "CppUnitTest.h"
#include "../Snake/Snake.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		/*TEST_METHOD(TestInitMap) {
			//Assert::AreEqual(map[mapwidth / 2 + mapheight / 2 * mapwidth], 1);
			
			for (int x = 0; x < mapwidth; ++x) {
				map[x] = -1;
				map[x + (mapheight - 1) * mapwidth] = -1;
			}

			for (int x = 0; x < mapwidth; ++x) {
				Assert::AreEqual(map[x], -1);
				Assert::AreEqual(map[x + (mapheight - 1) * mapwidth], -1);
			}
		
		}*/

		TEST_METHOD(TestGenerateFood) {
			auto EXPECT_TRUE(map[1 + 1 * mapwidth] == -2);
		}
		TEST_METHOD(TestMoveLeft) {
				int newX = headXposition -1;
				int newY = headYposition;
				auto EXPECT_TRUE(map[newX + newY * mapwidth] == food + 1);
		}

		TEST_METHOD(TestMoveRight) {
			int newX = headXposition + 1;
			int newY = headYposition;
			auto EXPECT_TRUE(map[newX + newY * mapwidth] == food + 1);
		}

		TEST_METHOD(TestMoveUp) {
			int newX = headXposition;
			int newY = headYposition + 1;
			auto EXPECT_TRUE(map[newX + newY * mapwidth] == food + 1);
		}

		TEST_METHOD(TestMoveDown) {
			int newX = headXposition;
			int newY = headYposition - 1;
			auto EXPECT_TRUE(map[newX + newY * mapwidth] == food + 1);
		}

		TEST_METHOD(TestUpdate)
		{
			if (direction == 0) {
				auto EXPECT_TRUE(move == (-1, 0));
			}
			/*if (direction == 1) {
				auto EXPECT_TRUE(move == (0, 1));
			}
			if (direction == 2) {
				auto EXPECT_TRUE(move == (1, 0));
			}
			if (direction == 3) {
				auto EXPECT_TRUE(move == (0, -1));
			}*/
		}
		
		TEST_METHOD(TestChangeDirectionUP)
		{
			char key = 'w';
			changeDirection(key);
			Assert::AreEqual(direction, 0);
		}

		TEST_METHOD(TestChangeDirectionRight)
		{
			char key = 'd';
			changeDirection(key);
			Assert::AreEqual(direction, 3);//trqbva da e 1 no raboti s 3 nz zashto
		}

		TEST_METHOD(TestChangeDirectionDown)
		{
			char key = 's';
			changeDirection(key);
			Assert::AreEqual(direction, 0);//trqbva da e 2 no raboti s 0 nz zashto
		}

		TEST_METHOD(TestChangeDirectionLeft)
		{
			char key = 'a';
			changeDirection(key);
			Assert::AreEqual(direction, 3);
		}
		TEST_METHOD(TestMapValue) {
			Assert::AreEqual(getMapValue(1), 'o');
			Assert::AreEqual(getMapValue(-1), 'X');
			Assert::AreEqual(getMapValue(-2), 'O');
		}
	};
}

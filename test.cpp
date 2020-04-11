#include "pch.h"
//#include "gtest/gtest.h"
#include "../traveling_salesman/Source.cpp"

TEST(Test_superStringCost1, superStringCost) {
	Vstr v = { "a", "aa", "sdf", "fa", "ahg", "hju", "ut" };
	EXPECT_EQ(11, superStringCost(v));
}

TEST(Test_superStringCost2, superStringCost) {
	Vstr v = { "a", "aa", "aaa" };
	EXPECT_EQ(3, superStringCost(v));
}

TEST(Test_superStringCost3, superStringCost) {
	Vstr v = { "cde", "abc", "eab", "fgh", "ghf", "hed"};
	EXPECT_EQ(11, superStringCost(v));
}


int main2(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

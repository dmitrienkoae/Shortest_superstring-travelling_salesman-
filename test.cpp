#include "pch.h"
//#include "gtest/gtest.h"
#include "../traveling_salesman/Source.cpp"

TEST(Test_superStringCost1, superString) {
	Vstr v = { "a", "aa", "sdf", "fa", "ahg", "hju", "ut" };
  	vector::string super_str = superString(v);
 	bool b = true;
 	for (auto i : v){
   	if( super_str.find(i) == string::npos)
     		 b = false;
	EXPECT_EQ(b, true);
	EXPECT_EQ(11, super_str.size());
}

TEST(Test_superStringCost2, superString) {
	Vstr v = { "a", "aa", "aaa" };
	EXPECT_EQ(3, superStringCost(v));
	Vstr v = { "a", "aa", "aaa" };
	vector::string super_str = superString(v);
 	bool b = true;
  	for (auto i : v){
    	if( super_str.find(i) == string::npos)
    		b = false;
	EXPECT_EQ(b, true);
	EXPECT_EQ(3, super_str.size());
}

TEST(Test_superStringCost3, superString) {
	Vstr v = { "cde", "abc", "eab", "fgh", "ghf", "hed"};
	vector::string super_str = superString(v);
  	bool b = true;
  	for (auto i : v){
   	if( super_str.find(i) == string::npos)
      		b = false;
	EXPECT_EQ(b, true);
	EXPECT_EQ(13, super_str.size());
}


int main2(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

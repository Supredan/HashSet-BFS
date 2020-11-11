#include "gtest/gtest.h"
#include "Wordset.hpp"
#include "proj3.hpp"
#include <string>
#include <fstream>

namespace{


// NOTE:  these are not intended as exhaustive tests.
// This should get you started testing.


TEST(HashFunctionTest, Hf1)
{
	int hv = hashFunction("dbc", 41, 100000);
	int shouldBe = 3*41*41 + 1*41 + 2;
	EXPECT_TRUE(hv == shouldBe);
}


TEST(TableTest, Tab1)
{
	WordSet ws;
	ws.insert("dbc");
	EXPECT_TRUE(ws.contains("dbc"));
}

TEST(ResizeTest, Tab2)
{
	WordSet ws;
	ws.insert("sleepy");
	ws.insert("happy");
	EXPECT_TRUE(ws.getCapacity() == 13);
	ws.insert("dopey");
	ws.insert("sneezy");
	EXPECT_TRUE(ws.getCapacity() == 29);
	ws.insert("datalink");
	ws.insert("australia");
	ws.insert("guacamole");
	ws.insert("phylum");
	EXPECT_TRUE(ws.contains("happy"));
	EXPECT_TRUE(ws.contains("dopey"));
}


TEST(ResizeTest, Tab3)
{
	WordSet ws;
	ws.insert("sleepy");
	ws.insert("happy");
	EXPECT_TRUE(ws.getCapacity() == 13);
	ws.insert("dopey");
	ws.insert("sneezy");
	EXPECT_TRUE(ws.getCapacity() == 29);
	ws.insert("datalink");
	ws.insert("australia");
	ws.insert("guacamole");
	ws.insert("phylum");
	EXPECT_TRUE(ws.contains("happy"));
	EXPECT_TRUE(ws.contains("dopey"));
	ws.insert("one");
	ws.insert("two");
	EXPECT_TRUE(ws.getCapacity() == 59);
}

TEST(SampleTest, Abandoning)
{
	WordSet words;
	words.insert("abandoning");
	EXPECT_TRUE(words.contains("abandoning"));
}


TEST(ConvertWords, AntToArt)
{
	WordSet words;
	std::ifstream in("E:\\OneDrive - Microsoft 365\\CODE\\clion\\hw3\\cmake-build-debug\\words.txt");
	loadWordsIntoTable(words, in);
    EXPECT_TRUE(words.contains("abandoned"));

 	std::string r = convert("ant", "art", words);
 	EXPECT_TRUE(r == "ant --> art");
}



TEST(ConvertWords, AntToEat)
{
	WordSet words;
	std::ifstream in("E:\\OneDrive - Microsoft 365\\CODE\\clion\\hw3\\cmake-build-debug\\words.txt");
	loadWordsIntoTable(words, in);

 	std::string r = convert("ant", "eat", words);
 	EXPECT_TRUE(r == "ant --> aft --> oft --> oat --> eat");
 	// of course, if yours outputs a way to do this with exactly 5 words, it is also correct.
 	// So maybe confirm if yours is right or not if this test appears to be failing.
 	// I will be verifying it differently when I grade this assignment.
}






}
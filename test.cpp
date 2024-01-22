#include "../headers/countWordsClass.h"
#include "gtest/gtest.h"
using namespace std;

TEST(task1, countWords) {
    //arrange
    fstream fileIn, fileOut;
    fileIn.open("in.txt", fstream::in | fstream::out);
    fileOut.open("out.txt", fstream::out | fstream::in);
    ASSERT_EQ((fileIn.is_open() && fileOut.is_open()), true);
    countWordsClass classObj;
    
    //act
    fileIn << "one two three pragme one two one one";
    classObj.callMainFunctions(fileIn, fileOut);
    
    string line;
    stringstream fileContent;
    while(getline(fileOut, line)) {
        fileContent << line << "\n";
    }

    //assert
    EXPECT_EQ(fileContent.str(), "one;4;50\ntwo;2;25\npragme;1;12.5\nthree;1;12.5\n");

    //act
    fileIn << "stratocaster telecaster lesPaul stratocaster superstrat explorer stratocaster,, stratocaster";
    classObj.callMainFunctions(fileIn, fileOut);
    while(getline(fileOut, line)) {
        fileContent << line << "\n";
    }

    //assert
    EXPECT_EQ(fileContent.str(), "one;4;50\ntwo;2;25\npragme;1;12.5\nthree;1;12.5\n");

    fileIn.close();
    fileOut.close();
}

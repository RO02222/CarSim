//============================================================================
// Name        : Car_SimDomainTest.cpp
// Date        : 19/03/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 1
//============================================================================


#include <iostream>
#include <fstream>
#include "gtest/gtest.h"
#include "../Simulation/GenerateIni.h"
#include "../Functions.h"


class Car_SimOutputTest: public ::testing::Test {
protected:
    // You should make the members protected s.t. they can be
    // accessed from sub-classes.

    // virtual void SetUp() will be called before each test is run.  You
    // should define it if you need to initialize the variables.
    // Otherwise, this can be skipped.
    virtual void SetUp() {
    }

    // virtual void TearDown() will be called after each test is run.
    // You should define it if there is cleanup work to do.  Otherwise,
    // you don't have to provide it.
    virtual void TearDown() {
    }

    // Declares the variables your tests want to use.
    friend class World;
    friend class Road;
    friend class Car;
    friend class CarGen;
    friend class Light;
    friend class Clock;
    friend class BusStop;
    friend class Junction;
    friend class CarData;
    // You should make the members protected s.t. they can be
    // accessed from sub-classes.
};

void Test_Simulation(const char* inputfile, std::string compareFile, bool graphic, std::string errorFile = "../testOutput/emptyFile.txt") {
    srand(123);
    World *w = input::loadWorldXML(inputfile);
    std::ofstream myFile;
    if(!graphic){
        myFile.open("../outputFile/Car_sim.txt");
    }
    else{
        myFile.open("../outputFile/Car_sim2.txt");
    }
    if (graphic){
        w->graficImpSimulateWorld(myFile);
    }
    else{
        w->simpleSimulateWorld(myFile);
    }
    for (unsigned int i =0; i < 200; i++) {
        for (unsigned int _ = 0; _ < 50; _++) {
            w->updateWorld(0.01);
        }
        if(graphic){
            w->graficImpSimulateWorld(myFile);
        }
        else{
            w->simpleSimulateWorld(myFile);
        }
    }
    myFile.close();
    delete w;
    if(!graphic){
        EXPECT_TRUE(FileCompare("../outputFile/Car_sim.txt", compareFile));
    }
    else{
        EXPECT_TRUE(FileCompare("../outputFile/Car_sim2.txt", compareFile));
    }
    EXPECT_TRUE(FileCompare("../outputFile/error.txt", errorFile));
}


void Test_SimulationEngine(const char* inputfile, std::string compareFile) {
    srand(123);
    World* w = input::loadWorldXML(inputfile);
    GenerateIni g(w, "sim");
    for (unsigned int i = 0; i<5; i++) {
        g.generate();
        for (unsigned int _ = 0; _<10; _++) {
            w->updateWorld(0.1);
        }
    }
    std::ofstream myFile;
    myFile.close();
    delete w;
    for(unsigned int i = 1; i<6; i++){
        EXPECT_TRUE(FileCompare("../outputFile/Ini/sim000" + std::itos(i) + ".ini", compareFile + "/sim000" + std::itos(i) + ".ini"));
    }
}


// Tests the compare files
TEST_F(Car_SimOutputTest, FileCompare) {
    ASSERT_TRUE(DirectoryExists("../testOutput"));

    ofstream myfile;
    myfile.open("../testOutput/file1.txt");
    myfile.close();
    myfile.open("../testOutput/file2.txt");
    myfile.close();

    EXPECT_TRUE(FileExists("../testOutput/file1.txt"));
    EXPECT_TRUE(FileExists("../testOutput/file2.txt"));
    EXPECT_TRUE(FileIsEmpty("../testOutput/file1.txt"));
    EXPECT_TRUE(FileIsEmpty("../testOutput/file2.txt"));


    //compare 2 empty files
// *** Beware: the following does not work with older versions of libstdc++
// *** It doesn't work with gcc version 4.0.1 (Apple Inc. build 5465)
// *** It does work with gcc version 4.2.1
//    EXPECT_TRUE(FileCompare("../testOutput/file1.txt", "../testOutput/file2.txt"));
//    EXPECT_TRUE(FileCompare("../testOutput/file2.txt", "../testOutput/file1.txt"));

    //compare an empty and a non-empty files
    myfile.open("../testOutput/file1.txt");
    myfile << "xxx" << endl << "yyy";
    myfile.close();
    EXPECT_TRUE(FileExists("../testOutput/file1.txt"));
    EXPECT_FALSE(FileIsEmpty("../testOutput/file1.txt"));
    EXPECT_FALSE(FileCompare("../testOutput/file1.txt", "../testOutput/file2.txt"));
    EXPECT_FALSE(FileCompare("../testOutput/file2.txt", "../testOutput/file1.txt"));

    //compare two equal files
    myfile.open("../testOutput/file2.txt");
    myfile << "xxx" << endl << "yyy";
    myfile.close();
    EXPECT_TRUE(FileExists("../testOutput/file2.txt"));
    EXPECT_FALSE(FileIsEmpty("../testOutput/file2.txt"));
    EXPECT_TRUE(FileCompare("../testOutput/file1.txt", "../testOutput/file2.txt"));
    EXPECT_TRUE(FileCompare("../testOutput/file2.txt", "../testOutput/file1.txt"));

    //compare 2 non-empty files which are off by a character in the middle
    myfile.open("../testOutput/file2.txt");
    myfile << "xxx" << endl << "xyy";
    myfile.close();
    EXPECT_FALSE(FileCompare("../testOutput/file1.txt", "../testOutput/file2.txt"));
    EXPECT_FALSE(FileCompare("../testOutput/file2.txt", "../testOutput/file1.txt"));

    //compare 2 non-empty files where one is one character shorter than the other
    myfile.open("../testOutput/file2.txt");
    myfile << "xxx" << endl << "yy";
    myfile.close();
    EXPECT_FALSE(FileCompare("../testOutput/file1.txt", "../testOutput/file2.txt"));
    EXPECT_FALSE(FileCompare("../testOutput/file2.txt", "../testOutput/file1.txt"));

    //compare existing against non existing file
    EXPECT_FALSE(
            FileCompare("../testOutput/file1.txt", "../testOutput/nonexisting.txt"));
    EXPECT_FALSE(
            FileCompare("../testOutput/nonexisting.txt", "../testOutput/file1.txt"));
}

/**
Tests FileOutput: test if the output is right for a simple impression.
*/
TEST_F(Car_SimOutputTest, SimpleFileOutput) {
    Test_Simulation("../testInput/testCase1.xml",  "../testOutput/testOutput1.txt", false);
    Test_Simulation("../testInput/testCase2.xml",  "../testOutput/testOutput2.txt", false);
}

/**
Tests GraphicFileOutput: test if the output is right for the graphical impression.
*/
TEST_F(Car_SimOutputTest, GraphicFileOutput) {
    Test_Simulation("../testInput/testCase1.xml",  "../testOutput/testOutput1.0.txt", true);
    Test_Simulation("../testInput/testCase2.xml",  "../testOutput/testOutput2.0.txt", true);
}

/**
Tests GraphicEngineOutput: test if the output is right for the impression with the engine.
*/
TEST_F(Car_SimOutputTest, GraphicEngineFileOutput) {
    Test_SimulationEngine("../testInput/testCase7.xml",  "../testOutput/Ini1");
    Test_SimulationEngine("../testInput/testCase8.xml",  "../testOutput/Ini2");
}




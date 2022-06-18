//============================================================================
// Name        : Car_SimDomainTest.cpp
// Date        : 19/03/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 1
//============================================================================

#include <iostream>
#include <fstream>
#include "../Input.h"
#include "gtest/gtest.h"
#include "../Classes/World.h"
#include "../Car_SimUtils.h"
#include "../Classes/Light.h"
#include "../Classes/Junction.h"



using namespace std;


class Car_SimInputTest: public ::testing::Test {
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

void Test_error(const char* inputfile, std::string compareFile){
    World* w = input::loadWorldXML(inputfile);
    delete w;
    if (!FileCompare("../outputFile/error.txt", compareFile)){
        std::cout<<inputfile<<std::cout;
    }
    EXPECT_TRUE(FileCompare("../outputFile/error.txt", compareFile));
}

/**
Tests InputHappyDay
*/
TEST_F(Car_SimInputTest, InputHappyDayAll) {
    World* w = input::loadWorldXML("../testInput/testCase1.xml");

    EXPECT_EQ(w->getRoads()[0]->getName(), "Middelheimlaan");
    EXPECT_EQ(w->getRoads()[0]->getLength(), 400);

    EXPECT_EQ(w->getRoads()[0]->getLights()[0]->getRoad()->getName(), "Middelheimlaan");
    EXPECT_EQ(w->getRoads()[0]->getLights()[0]->getPosition(), 400);
    EXPECT_EQ(w->getRoads()[0]->getLights()[0]->getCycle(), 20);

    EXPECT_EQ(w->getRoads()[0]->getCars()[0]->getRoad()->getName(), "Middelheimlaan");
    EXPECT_EQ(w->getRoads()[0]->getCars()[0]->getDistance(), 40);
    EXPECT_EQ(w->getRoads()[0]->getCars()[1]->getRoad()->getName(), "Middelheimlaan");
    EXPECT_EQ(w->getRoads()[0]->getCars()[1]->getDistance(), 20);

    EXPECT_EQ(w->getRoads()[0]->getCarGen()[0]->getRoad()->getName(), "Middelheimlaan");
    EXPECT_EQ(w->getRoads()[0]->getCarGen()[0]->getFrequency(), 5);

    EXPECT_EQ(w->getJunctions()[0]->getRoad(0)->getName(), "Middelheimlaan");
    EXPECT_EQ(w->getJunctions()[0]->getPosition("Middelheimlaan"), 300);
    EXPECT_EQ(w->getJunctions()[0]->getRoad(1)->getName(), "Groenenborgerlaan");
    EXPECT_EQ(w->getJunctions()[0]->getPosition("Groenenborgerlaan"), 100);

    EXPECT_EQ(w->getRoads()[0]->getBusStops()[0]->getRoad()->getName(), "Middelheimlaan");
    EXPECT_EQ(w->getRoads()[0]->getBusStops()[0]->getPosition(), 35);
    EXPECT_EQ(w->getRoads()[0]->getBusStops()[0]->getStopTime(), 4);
    delete w;
}

TEST_F(Car_SimInputTest, InputHappyDayBasic) {
    World *w = input::loadWorldXML("../testInput/testCase4.xml");

    EXPECT_EQ(w->getRoads()[0]->getName(), "Kerkstraat");
    EXPECT_EQ(w->getRoads()[0]->getLength(), 500);

    EXPECT_EQ(w->getRoads()[0]->getLights()[0]->getRoad()->getName(), "Kerkstraat");
    EXPECT_EQ(w->getRoads()[0]->getLights()[0]->getPosition(), 250);
    EXPECT_EQ(w->getRoads()[0]->getLights()[0]->getCycle(), 9);
    EXPECT_EQ(w->getRoads()[0]->getLights()[1]->getRoad()->getName(), "Kerkstraat");
    EXPECT_EQ(w->getRoads()[0]->getLights()[1]->getPosition(), 100);
    EXPECT_EQ(w->getRoads()[0]->getLights()[1]->getCycle(), 4);

    EXPECT_EQ(w->getRoads()[0]->getCars()[0]->getRoad()->getName(), "Kerkstraat");
    EXPECT_EQ(w->getRoads()[0]->getCars()[0]->getDistance(), 100);
    EXPECT_EQ(w->getRoads()[0]->getCars()[0]->getData()->getType(), car);
    EXPECT_EQ(w->getRoads()[0]->getCars()[1]->getRoad()->getName(), "Kerkstraat");
    EXPECT_EQ(w->getRoads()[0]->getCars()[1]->getDistance(), 20);
    EXPECT_EQ(w->getRoads()[0]->getCars()[1]->getData()->getType(), ambulance);

    EXPECT_EQ(w->getRoads()[0]->getCarGen()[0]->getRoad()->getName(), "Kerkstraat");
    EXPECT_EQ(w->getRoads()[0]->getCarGen()[0]->getFrequency(), 3);
    delete w;
}

/**
Tests InputMixed: test if xml read in different order of Classes also works.
*/
TEST_F(Car_SimInputTest, InputMixed) {
    World* w = input::loadWorldXML("../testInput/testCase2.xml");

    EXPECT_EQ(w->getRoads()[0]->getName(), "Molenstraat");
    EXPECT_EQ(w->getRoads()[0]->getLength(), 700);
    EXPECT_EQ(w->getRoads()[1]->getName(), "Middelheimlaan");
    EXPECT_EQ(w->getRoads()[1]->getLength(), 400);

    EXPECT_EQ(w->getRoads()[1]->getLights()[0]->getRoad()->getName(), "Middelheimlaan");
    EXPECT_EQ(w->getRoads()[1]->getLights()[0]->getPosition(), 400);
    EXPECT_EQ(w->getRoads()[1]->getLights()[0]->getCycle(), 20);

    EXPECT_EQ(w->getRoads()[0]->getCars()[0]->getRoad()->getName(), "Molenstraat");
    EXPECT_EQ(w->getRoads()[0]->getCars()[0]->getDistance(), 20);
    EXPECT_EQ(w->getRoads()[1]->getCars()[0]->getRoad()->getName(), "Middelheimlaan");
    EXPECT_EQ(w->getRoads()[1]->getCars()[0]->getDistance(), 40);

    EXPECT_EQ(w->getRoads()[1]->getCarGen()[0]->getRoad()->getName(), "Middelheimlaan");
    EXPECT_EQ(w->getRoads()[1]->getCarGen()[0]->getFrequency(), 5);

    EXPECT_EQ(w->getJunctions()[0]->getRoad(0)->getName(), "Molenstraat");
    EXPECT_EQ(w->getJunctions()[0]->getPosition("Molenstraat"), 500);
    EXPECT_EQ(w->getJunctions()[0]->getRoad(1)->getName(), "Middelheimlaan");
    EXPECT_EQ(w->getJunctions()[0]->getPosition("Middelheimlaan"), 200);

    EXPECT_EQ(w->getRoads()[1]->getBusStops()[0]->getRoad()->getName(), "Middelheimlaan");
    EXPECT_EQ(w->getRoads()[1]->getBusStops()[0]->getPosition(), 35);
    EXPECT_EQ(w->getRoads()[1]->getBusStops()[0]->getStopTime(), 4);
    delete w;
}

TEST_F(Car_SimInputTest, LightsOnJunction) {
    World* w = input::loadWorldXML("../testInput/testCase6.xml");

    EXPECT_EQ(w->getRoads()[0]->getName(), "Middelheimlaan");
    EXPECT_EQ(w->getRoads()[0]->getLength(), 400);
    EXPECT_EQ(w->getRoads()[1]->getName(), "Groenenborgerlaan");
    EXPECT_EQ(w->getRoads()[1]->getLength(), 400);
    EXPECT_EQ(w->getRoads()[2]->getName(), "Kerkstraat");
    EXPECT_EQ(w->getRoads()[2]->getLength(), 500);
    EXPECT_EQ(w->getRoads()[3]->getName(), "Molendreef");
    EXPECT_EQ(w->getRoads()[3]->getLength(), 600);

    EXPECT_EQ(w->getRoads()[0]->getLights()[0]->getRoad()->getName(), "Middelheimlaan");
    EXPECT_EQ(w->getRoads()[0]->getLights()[0]->getPosition(), 300);
    EXPECT_EQ(w->getRoads()[0]->getLights()[0]->getCycle(), 5);

    EXPECT_EQ(w->getRoads()[1]->getLights()[0]->getRoad()->getName(), "Groenenborgerlaan");
    EXPECT_EQ(w->getRoads()[1]->getLights()[0]->getPosition(), 100);
    EXPECT_EQ(w->getRoads()[1]->getLights()[0]->getCycle(), 8);

    EXPECT_EQ(w->getRoads()[2]->getLights()[0]->getRoad()->getName(), "Kerkstraat");
    EXPECT_EQ(w->getRoads()[2]->getLights()[0]->getPosition(), 250);
    EXPECT_EQ(w->getRoads()[2]->getLights()[0]->getCycle(), 6);

    EXPECT_EQ(w->getRoads()[3]->getLights()[0]->getRoad()->getName(), "Molendreef");
    EXPECT_EQ(w->getRoads()[3]->getLights()[0]->getPosition(), 130);
    EXPECT_EQ(w->getRoads()[3]->getLights()[0]->getCycle(), 6);

    EXPECT_EQ(w->getJunctions()[0]->getRoad(0)->getName(), "Middelheimlaan");
    EXPECT_EQ(w->getJunctions()[0]->getPosition("Middelheimlaan"), 300);
    EXPECT_EQ(w->getJunctions()[0]->getRoad(1)->getName(), "Groenenborgerlaan");
    EXPECT_EQ(w->getJunctions()[0]->getPosition("Groenenborgerlaan"), 100);
    EXPECT_EQ(w->getJunctions()[0]->getRoad(2)->getName(), "Kerkstraat");
    EXPECT_EQ(w->getJunctions()[0]->getPosition("Kerkstraat"), 250);
    EXPECT_EQ(w->getJunctions()[0]->getRoad(3)->getName(), "Molendreef");
    EXPECT_EQ(w->getJunctions()[0]->getPosition("Molendreef"), 130);
    delete w;
}

/**
Tests InputSyntaxFails
*/
TEST_F(Car_SimInputTest, InputSyntaxFail) {
    //InputNoWorld: test if xml read without a world part works.
    Test_error("../testInput/testFail1.xml","../testOutput/testFail1.txt");
    //InputNoRootTest if xml read without a root works.
    Test_error("../testInput/testFail2.xml","../testOutput/testFail2.txt");
    //InputNoLength: test if xml read without a length in baan works.
    Test_error("../testInput/testFail3.xml","../testOutput/testFail3.txt");
    //InputNoPosition: test if xml read works when there is no position given for the light.
    Test_error("../testInput/testFail6.xml", "../testOutput/testFail6.txt");
    //InputNoBaan: test if xml read works when there is no baan given for the CarGenerator.
    Test_error("../testInput/testFail7.xml", "../testOutput/testFail7.txt");
    //InputNoRoadBus: test if xml read works when busstop without road.
    Test_error("../testInput/testFail12.xml", "../testOutput/testFail12.txt");
    //InputJunction1road: test if xml read works when junction has only 1 road.
    Test_error("../testInput/testFail13.xml", "../testOutput/testFail13.txt");

}
/**
Tests InputValueFail
*/
TEST_F(Car_SimInputTest, InputValueFail) {
    //InputLightToFar: test if xml read works when the position of the light is not on the road.
    Test_error("../testInput/testFail4.xml", "../testOutput/testFail4.txt");
    //InputAlreadyExist: test if xml read works when the name of the road already exists.
    Test_error("../testInput/testFail5.xml", "../testOutput/testFail5.txt");
    //InputCarToFar: test if xml read works when the position of the car is not on the road.
    Test_error("../testInput/testFail8.xml", "../testOutput/testFail8.txt");
    //InputNotExType: test if xml read works for a non-coded type of vehicle.
    Test_error("../testInput/testFail9.xml", "../testOutput/testFail9.txt");
    //InputNotExRoad: test if xml read works when put cargen on not-defined road.
    Test_error("../testInput/testFail10.xml", "../testOutput/testFail10.txt");
    //InputNothingExonRoad: test if xml read works when not-defined road.
    Test_error("../testInput/testFail11.xml", "../testOutput/testFail11.txt");
    }
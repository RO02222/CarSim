//============================================================================
// Name        : BusStopDomainTest.cpp
// Date        : 18/06/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 4
//============================================================================

#include <iostream>
#include "gtest/gtest.h"
#include "../Classes/Car.h"
#include "../Classes/CarGen.h"
#include "../Classes/Road.h"
using namespace std;

class BusStopDomainTest: public ::testing::Test {
protected:
    // You should make the members protected s.t. they can be
    // accessed from sub-classes.

    // virtual void SetUp() will be called before each test is run.  You
    // should define it if you need to initialize the variables.
    // Otherwise, this can be skipped.
    virtual void SetUp() {
        World();
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
/**
Tests Initialiser: test if every object is initialised right.
*/
TEST_F(BusStopDomainTest, Initialiser) {
    srand(123);
    World* w = new World();
    w->addRoad("Middelheimlaan", 500);
    w->getRoads()[0]->addBusStop(150, 1546941451651);
    w->getRoads()[0]->addBusStop(15,5);
    w->getRoads()[0]->addBusStop(500, 1);
    EXPECT_EQ(w->getRoads()[0]->getBusStops()[0]->getRoad()->getName(), "Middelheimlaan");
    EXPECT_EQ(w->getRoads()[0]->getBusStops()[0]->getPosition(), 150);
    EXPECT_EQ(w->getRoads()[0]->getBusStops()[0]->getStopTime(), 1546941451651);
    EXPECT_EQ(w->getRoads()[0]->getBusStops()[1]->getRoad()->getName(), "Middelheimlaan");
    EXPECT_EQ(w->getRoads()[0]->getBusStops()[1]->getPosition(), 15);
    EXPECT_EQ(w->getRoads()[0]->getBusStops()[1]->getStopTime(), 5);
    EXPECT_EQ(w->getRoads()[0]->getBusStops()[2]->getRoad()->getName(), "Middelheimlaan");
    EXPECT_EQ(w->getRoads()[0]->getBusStops()[2]->getPosition(), 500);
    EXPECT_EQ(w->getRoads()[0]->getBusStops()[2]->getStopTime(), 1);
    delete w;
}

TEST_F(BusStopDomainTest, readySetGo) {
    srand(123);
    World *w = new World();
    w->addRoad("Middelheimlaan", 10000);
    w->getRoads()[0]->addBusStop(100, 5);
    w->getRoads()[0]->addCar(15, w->getCarData(bus));
    EXPECT_EQ(w->getRoads()[0]->getCars()[0]->getData()->getType(), bus);
    for(unsigned int _=0; _<40; _++){
        w->updateWorld(0.1);
    }
    EXPECT_EQ(w->getRoads()[0]->getCars()[0]->getAction(), slow);
    EXPECT_EQ(w->getRoads()[0]->getBusStops()[0]->getbussy(), false);
    for(unsigned int _=0; _<130; _++){
        w->updateWorld(0.1);
    }
    EXPECT_EQ(w->getRoads()[0]->getCars()[0]->getAction(), stop);
    EXPECT_LT(w->getRoads()[0]->getCars()[0]->getSpeed(), 0.01);
    EXPECT_EQ(w->getRoads()[0]->getBusStops()[0]->getbussy(), true);
    for(unsigned int _=0; _<5; _++){
        w->updateWorld(1);
    }
    EXPECT_EQ(w->getRoads()[0]->getCars()[0]->getAction(), fast);
    EXPECT_TRUE(w->getRoads()[0]->getBusStops()[0]->getStopTime() < w->getRoads()[0]->getBusStops()[0]->getTimeStopped());
    for(unsigned int _=0; _<5; _++){
        w->updateWorld(1);
    }
    EXPECT_EQ(w->getRoads()[0]->getBusStops()[0]->getbussy(), false);
    delete w;
}

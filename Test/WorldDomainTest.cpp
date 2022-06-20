//============================================================================
// Name        : WorldDomainTest.cpp
// Date        : 18/06/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 4
//============================================================================

#include <iostream>
#include "gtest/gtest.h"

using namespace std;


class WorldDomainTest: public ::testing::Test {
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
TEST_F(WorldDomainTest, Initialiser) {
    World* w = new World();

    EXPECT_EQ(w->getTime(), 0);
    delete w;
}

TEST_F(WorldDomainTest, EverythingInWorld) {
    ofstream error;
    World* w = new World();
    Road* r1 = new Road("Middelheimlaan", 100, &error);
    Road* r2 = new Road("Groenenborgerlaan", 101, &error);
    w->addRoad(r1);
    w->addRoad(r2);
    EXPECT_EQ(w->getRoads()[0]->getName(), "Middelheimlaan");
    EXPECT_EQ(w->getRoads()[0]->getLength(), 100);
    EXPECT_EQ(w->getRoads()[1]->getName(), "Groenenborgerlaan");
    EXPECT_EQ(w->getRoads()[1]->getLength(), 101);
    std::vector<std::pair<Road *, double> > roads;
    roads.push_back(std::pair<Road*,double>(r1,50));
    roads.push_back(std::pair<Road*,double>(r2,51));
    w->addJunction(roads);
    EXPECT_EQ(w->getJunctions()[0]->getRoad(0)->getName(), "Middelheimlaan");
    EXPECT_EQ(w->getJunctions()[0]->getRoad(1)->getName(), "Groenenborgerlaan");
    EXPECT_EQ(w->getJunctions()[0]->getPosition(0), 50);
    EXPECT_EQ(w->getJunctions()[0]->getPosition(1), 51);

    EXPECT_EQ(w->getTime(), 0);
    delete w;
}
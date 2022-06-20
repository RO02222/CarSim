//============================================================================
// Name        : RoadDomainTest.cpp
// Date        : 18/06/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 4
//============================================================================

#include <iostream>
#include "gtest/gtest.h"
#include <bits/stdc++.h>
#include <vector>
#include "../Classes/Junction.h"
#include "../Classes/BusStop.h"

using namespace std;

class RoadDomainTest: public ::testing::Test {
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
TEST_F(RoadDomainTest, Initialiser) {
    std::ofstream error;
    Road r1 = Road("Middelheimlaan", 100, &error);

    EXPECT_EQ(r1.getName(), "Middelheimlaan");
    EXPECT_EQ(r1.getLength(), 100);
}


/**
Tests InitialiserEdge: test if every object is initialised right with some edge cases or extreme numbers.
*/
TEST_F(RoadDomainTest, InitialiserEdge) {
    std::ofstream error;
    Road r1 = Road("Middelheimlaan", 1000000000000, &error);
    Road r2 = Road("Groenenborgerlaan", 15, &error);


    EXPECT_EQ(r1.getLength(), 1000000000000);
    EXPECT_EQ(r2.getLength(), 15);
}

/**
Tests addLight: test if function addLight works properly.
*/
TEST_F(RoadDomainTest, addEverythingPossible){
    ofstream error;
    srand(123);
    World* w = new World();
    Road* r1 = new Road("Middelheimlaan", 100, &error);
    Road* r2 = new Road("Groenenborgerlaan", 100, &error);
    w->addRoad(r1);
    w->addRoad(r2);
    w->getRoads()[0]->addLight(50,2);
    EXPECT_EQ(w->getRoads()[0]->getLights()[0]->getPosition(), 50);
    EXPECT_EQ(w->getRoads()[0]->getLights()[0]->getCycle(), 2);
    w->getRoads()[0]->addCar(5, w->getCarData(car));
    EXPECT_EQ(w->getRoads()[0]->getCars()[0]->getDistance(), 5);
    EXPECT_EQ(w->getRoads()[0]->getCars()[0]->getData()->getType(), car);
    w->getRoads()[0]->addCarGen(3, w->getCarData(police));
    EXPECT_EQ(w->getRoads()[0]->getCarGen()[0]->getFrequency(), 3);
    EXPECT_EQ(w->getRoads()[0]->getCarGen()[0]->getData()->getType(), police);
    std::vector<std::pair<Road *, double> > roads;
    roads.push_back(std::pair<Road*,double>(r1,50));
    roads.push_back(std::pair<Road*,double>(r2,51));
    w->addJunction(roads);
    EXPECT_EQ(w->getJunctions()[0]->getRoad(0)->getName(), "Middelheimlaan");
    EXPECT_EQ(w->getJunctions()[0]->getRoad(1)->getName(), "Groenenborgerlaan");
    EXPECT_EQ(w->getJunctions()[0]->getPosition(0), 50);
    EXPECT_EQ(w->getJunctions()[0]->getPosition(1), 51);
    w->getRoads()[0]->addBusStop(90, 5);
    EXPECT_EQ(w->getRoads()[0]->getBusStops()[0]->getPosition(), 90);
    EXPECT_EQ(w->getRoads()[0]->getBusStops()[0]->getStopTime(), 5);

    delete w;
}

TEST_F(RoadDomainTest, roadUpdate){
    ofstream error;
    srand(123);
    World* w = new World();
    Road* r1 = new Road("Middelheimlaan", 100, &error);
    Road* r2 = new Road("Groenenborgerlaan", 100, &error);
    w->addRoad(r1);
    w->addRoad(r2);
    w->getRoads()[0]->addLight(50,2);
    //int lastCycleL = int(w->getRoads()[0]->getLights()[0]->getLastCycle());
    w->getRoads()[0]->addCar(5, w->getCarData(car));
    double distance = w->getRoads()[0]->getCars()[0]->getDistance();
    w->getRoads()[0]->addCarGen(3, w->getCarData(police));
    int lastCycleC = int(w->getRoads()[0]->getCarGen()[0]->getCycle());

    std::vector<std::pair<Road *, double> > roads;
    roads.push_back(std::pair<Road*,double>(r1,50));
    roads.push_back(std::pair<Road*,double>(r2,51));
    w->addJunction(roads);
    w->getRoads()[0]->addBusStop(90, 5);

    w->getRoads()[0]->updateRoad(1);
    EXPECT_EQ(w->getRoads()[0]->getLights()[0]->getLastCycle(), 0);
    EXPECT_TRUE(w->getRoads()[0]->getCars()[0]->getDistance() > distance);
    EXPECT_EQ(w->getRoads()[0]->getCarGen()[0]->getCycle(), (lastCycleC+1)%3);

    delete w;
}


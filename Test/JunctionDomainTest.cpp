//============================================================================
// Name        : Car_SimDomainTest.cpp
// Date        : 19/03/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 1
//============================================================================

#include <iostream>
#include "gtest/gtest.h"
#include "../Classes/Car.h"
#include "../Classes/CarGen.h"
#include "../Classes/Road.h"
using namespace std;

class JunctionDomainTest: public ::testing::Test {
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
TEST_F(JunctionDomainTest, BasicInitialiser) {
    srand(123);
    ofstream error;
    World* w = new World();
    Road* r1 = new Road("Middelheimlaan", 100, &error);
    Road* r2 = new Road("Groenenborgerlaan", 100, &error);
    w->addRoad(r1);
    w->addRoad(r2);
    std::vector<std::pair<Road *, double> > roads;
    roads.push_back(std::pair<Road*,double>(r1,83));
    roads.push_back(std::pair<Road*,double>(r2,70));
    w->addJunction(roads);
    EXPECT_EQ(w->getJunctions()[0]->getRoad(0)->getName(), "Middelheimlaan");
    EXPECT_EQ(w->getJunctions()[0]->getRoad(1)->getName(), "Groenenborgerlaan");
    EXPECT_EQ(w->getJunctions()[0]->getPosition(0), 83);
    EXPECT_EQ(w->getJunctions()[0]->getPosition(1), 70);
    delete w;
}

TEST_F(JunctionDomainTest, moreRoads) {
    srand(123);
    ofstream error;
    World* w = new World();
    Road* r1 = new Road("Middelheimlaan", 100, &error);
    Road* r2 = new Road("Groenenborgerlaan", 100, &error);
    Road* r3 = new Road("Kerkstraat", 100, &error);
    Road* r4 = new Road("Molendreef", 100, &error);
    Road* r5 = new Road("Zonderhaatstraat", 100, &error);
    w->addRoad(r1);
    w->addRoad(r2);
    w->addRoad(r3);
    w->addRoad(r4);
    w->addRoad(r5);
    std::vector<std::pair<Road *, double> > roads;
    roads.push_back(std::pair<Road*,double>(r1,83));
    roads.push_back(std::pair<Road*,double>(r2,70));
    roads.push_back(std::pair<Road*,double>(r3,20));
    roads.push_back(std::pair<Road*,double>(r4,50));
    roads.push_back(std::pair<Road*,double>(r5,76));

    w->addJunction(roads);
    EXPECT_EQ(w->getJunctions()[0]->getRoad(0)->getName(), "Middelheimlaan");
    EXPECT_EQ(w->getJunctions()[0]->getRoad(1)->getName(), "Groenenborgerlaan");
    EXPECT_EQ(w->getJunctions()[0]->getRoad(2)->getName(), "Kerkstraat");
    EXPECT_EQ(w->getJunctions()[0]->getRoad(3)->getName(), "Molendreef");
    EXPECT_EQ(w->getJunctions()[0]->getRoad(4)->getName(), "Zonderhaatstraat");
    EXPECT_EQ(w->getJunctions()[0]->getPosition(0), 83);
    EXPECT_EQ(w->getJunctions()[0]->getPosition(1), 70);
    EXPECT_EQ(w->getJunctions()[0]->getPosition(2), 20);
    EXPECT_EQ(w->getJunctions()[0]->getPosition(3), 50);
    EXPECT_EQ(w->getJunctions()[0]->getPosition(4), 76);
    delete w;
}

TEST_F(JunctionDomainTest, readySetGo) {
    srand(123);
    ofstream error;
    World* w = new World();
    Road* r1 = new Road("Middelheimlaan", 100, &error);
    Road* r2 = new Road("Groenenborgerlaan", 100, &error);
    w->addRoad(r1);
    w->addRoad(r2);
    std::vector<std::pair<Road *, double> > roads;
    roads.push_back(std::pair<Road*,double>(r1,50));
    roads.push_back(std::pair<Road*,double>(r2,70));
    w->addJunction(roads);
    w->getRoads()[0]->addCar(0, w->getCarData(car));
    for(unsigned int _=0; _<25; _++){
        w->updateWorld(0.1);
    }
    EXPECT_EQ(w->getRoads()[0]->getCars().size(),(unsigned int)1);
    double distance = w->getRoads()[0]->getCars()[0]->getDistance();//43.16
    EXPECT_EQ(w->getJunctions()[0]->getCars().size(), (unsigned int) 0);
    w->getRoads()[0]->updateRoad(1);
    EXPECT_EQ(w->getRoads()[0]->getCars()[0]->getDistance(), distance);//43.16
    EXPECT_EQ(w->getJunctions()[0]->getCars().size(), (unsigned int) 1);
    w->getJunctions()[0]->updateJunction(1);
    EXPECT_TRUE(w->getRoads()[0]->getCars()[0]->getDistance() > distance);
    delete w;
}

TEST_F(JunctionDomainTest, startOnEdge) {
    srand(123);
    ofstream error;
    World* w = new World();
    Road* r1 = new Road("Middelheimlaan", 100, &error);
    Road* r2 = new Road("Groenenborgerlaan", 100, &error);
    w->addRoad(r1);
    w->addRoad(r2);
    std::vector<std::pair<Road *, double> > roads;
    roads.push_back(std::pair<Road*,double>(r1,50));
    roads.push_back(std::pair<Road*,double>(r2,70));
    w->addJunction(roads);
    w->getRoads()[0]->addCar(35, w->getCarData(car));
    EXPECT_EQ(w->getRoads()[0]->getCars().size(), (unsigned int)1);
    double distance = w->getRoads()[0]->getCars()[0]->getDistance();
    w->getRoads()[0]->updateRoad(1);
    EXPECT_EQ(w->getRoads()[0]->getCars()[0]->getDistance(), distance);
    w->getJunctions()[0]->updateJunction(1);
    EXPECT_EQ(w->getRoads()[0]->getCars().size(), (unsigned int) 0);//change road
    EXPECT_TRUE(w->getRoads()[1]->getCars()[0]->getDistance() > distance);
    delete w;
}

TEST_F(JunctionDomainTest, endOfRoad) {
    srand(123);
    ofstream error;
    World* w = new World();
    Road* r1 = new Road("Middelheimlaan", 100, &error);
    Road* r2 = new Road("Groenenborgerlaan", 100, &error);
    w->addRoad(r1);
    w->addRoad(r2);
    std::vector<std::pair<Road *, double> > roads;
    roads.push_back(std::pair<Road*,double>(r1,100));
    roads.push_back(std::pair<Road*,double>(r2,0));
    w->addJunction(roads);
    w->getRoads()[0]->addCar(85, w->getCarData(car));
    for(unsigned int _=0; _<15; _++){
        w->updateWorld(0.1);
    }//change road
    EXPECT_EQ(w->getRoads()[0]->getCars().size(),(unsigned int) 0);
    EXPECT_EQ(w->getRoads()[1]->getCars().size(),(unsigned int) 1);
    double distance = w->getRoads()[1]->getCars()[0]->getDistance();
    EXPECT_TRUE(distance<100);
    EXPECT_TRUE(distance>0);
    w->getRoads()[1]->updateRoad(1);
    EXPECT_EQ(w->getRoads()[1]->getCars()[0]->getDistance(), distance);
    EXPECT_EQ(w->getJunctions()[0]->getCars().size(),(unsigned int) 1);
    w->getJunctions()[0]->updateJunction(1);
    EXPECT_FALSE(w->getRoads()[1]->getCars()[0]->getDistance() == distance);
    delete w;
}

TEST_F(JunctionDomainTest, GoSmaller) {
    srand(123);
    ofstream error;
    World* w = new World();
    Road* r1 = new Road("Middelheimlaan", 100, &error);
    Road* r2 = new Road("Groenenborgerlaan", 100, &error);
    w->addRoad(r1);
    w->addRoad(r2);
    std::vector<std::pair<Road *, double> > roads;
    roads.push_back(std::pair<Road*,double>(r1,88));
    roads.push_back(std::pair<Road*,double>(r2,62));
    w->addJunction(roads);
    w->getRoads()[0]->addCar(70, w->getCarData(car));
    for(unsigned int _=0; _<15; _++){
        w->updateWorld(0.1);
    }//change road
    EXPECT_EQ(w->getRoads()[0]->getCars().size(),(unsigned int) 0);
    EXPECT_EQ(w->getRoads()[1]->getCars().size(),(unsigned int) 1);
    double distance = w->getRoads()[1]->getCars()[0]->getDistance();
    EXPECT_TRUE(distance<88);
    EXPECT_TRUE(distance>62);
    w->getRoads()[1]->updateRoad(1);
    EXPECT_EQ(w->getRoads()[1]->getCars()[0]->getDistance(), distance);
    EXPECT_EQ(w->getJunctions()[0]->getCars().size(),(unsigned int) 1);
    w->getJunctions()[0]->updateJunction(1);
    EXPECT_FALSE(w->getRoads()[1]->getCars()[0]->getDistance() == distance);
    delete w;
}
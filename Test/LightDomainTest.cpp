//============================================================================
// Name        : Car_SimDomainTest.cpp
// Date        : 19/03/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 1
//============================================================================

#include <iostream>
#include "gtest/gtest.h"
#include "../Car_SimUtils.h"
#include "../Basic_Values.h"
#include "../Classes/Light.h"

using namespace std;


class LightDomainTest: public ::testing::Test {
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
TEST_F(LightDomainTest, Initialiser) {
    std::ofstream error;
    Road r1 = Road("Middelheimlaan", 300, &error);
    r1.addLight(50,3);
    r1.addLight(150,4);
    r1.addLight(250, 5);
    r1.getLights()[0]->setState(red);
    r1.getLights()[1]->setState(orange);
    r1.getLights()[2]->setState(green);

    EXPECT_EQ(r1.getLights()[0]->getPosition(), 50);
    EXPECT_EQ(r1.getLights()[0]->getCycle(), 3);
    EXPECT_EQ(r1.getLights()[0]->getState(), red);

    EXPECT_EQ(r1.getLights()[1]->getPosition(), 150);
    EXPECT_EQ(r1.getLights()[1]->getCycle(), 4);
    EXPECT_EQ(r1.getLights()[1]->getState(), orange);

    EXPECT_EQ(r1.getLights()[2]->getPosition(), 250);
    EXPECT_EQ(r1.getLights()[2]->getCycle(), 5);
    EXPECT_EQ(r1.getLights()[2]->getState(), green);
}


/**
Tests InitialiserEdge: test if every object is initialised right when edge case.
*/

TEST_F(LightDomainTest, InitialiserEdge) {
    std::ofstream error;
    error.open("../outputFile/error.txt");

    Road r1 = Road("Middelheimlaan", 1000, &error);
    r1.addLight(50, 1.0000001);
    r1.addLight(70,1);
    r1.addLight(900,16000);
    r1.addLight(1000,2);
    r1.addLight(15, 4);

    EXPECT_EQ(r1.getLights()[0]->getCycle(), 1.0000001);
    EXPECT_EQ(r1.getLights()[1]->getCycle(), (unsigned int) 1);
    EXPECT_EQ(r1.getLights()[2]->getCycle(), (unsigned int)16000);
    EXPECT_EQ(r1.getLights().size(), (unsigned int) 5);
    error.close();
}

TEST_F(LightDomainTest, LightChange) {
    srand(123);
    World* w = new World();
    w->addRoad("Middelheimlaan", 10000);
    w->getRoads()[0]->addLight(50, 20);
    w->getRoads()[0]->addCar(0, w->getCarData(car));
    w->getRoads()[0]->addCar(20, w->getCarData(fire));
    w->getRoads()[0]->getLights()[0]->setLastCycle(0);
    w->getRoads()[0]->getLights()[0]->setState(red);
    EXPECT_EQ(w->getRoads()[0]->getCars()[0]->getAction(), fast);
    int lastcycle = w->getRoads()[0]->getLights()[0]->getLastCycle();
    for (unsigned int _ = 0; _<40;_++) {
        w->updateWorld(0.1);
    }//na 1 keer update vertraagt de auto
    lastcycle = (lastcycle+4)%20;
    EXPECT_TRUE(w->getRoads()[0]->getLights()[0]->getLastCycle()-lastcycle<0.0000001);
    EXPECT_EQ(w->getRoads()[0]->getCars()[0]->getAction(), slow);
    EXPECT_EQ(w->getRoads()[0]->getCars()[1]->getAction(), fast);

    for (unsigned int _ = 0; _<10;_++) {
        w->updateWorld(1);
    } //kleiner interval, meerdere keren werkt wel!!!
    lastcycle = (lastcycle+10)%20;
    EXPECT_TRUE(w->getRoads()[0]->getLights()[0]->getLastCycle()-lastcycle< 0.0000001);
    EXPECT_EQ(w->getRoads()[0]->getCars()[0]->getAction(), stop);
    EXPECT_EQ(w->getRoads()[0]->getCars()[1]->getAction(), fast);

    for (unsigned int _ = 0; _<10;_++) {
        w->updateWorld(1);
    }
    lastcycle = (lastcycle+10)%20;
    EXPECT_EQ(w->getRoads()[0]->getLights()[0]->getLastCycle(), lastcycle);
    EXPECT_EQ(w->getRoads()[0]->getCars()[0]->getAction(), fast);
    EXPECT_EQ(w->getRoads()[0]->getCars()[1]->getAction(), fast);
    delete w;
}

TEST_F(LightDomainTest, CheckColors) {
    srand(123);
    World* w = new World();
    w->addRoad("Middelheimlaan", 10000);
    w->getRoads()[0]->addLight(50, 20);
    w->getRoads()[0]->addLight(500, 5);
    w->getRoads()[0]->getLights()[0]->setLastCycle(0);
    w->getRoads()[0]->getLights()[0]->setState(red);
    w->getRoads()[0]->getLights()[1]->setLastCycle(0);
    w->getRoads()[0]->getLights()[1]->setState(green);
    double lastcycle = w->getRoads()[0]->getLights()[0]->getLastCycle();
    for (unsigned int _ = 0; _<40;_++) {
        w->updateWorld(0.1);
    }//na 1 keer update vertraagt de auto
    lastcycle = std::fmod(lastcycle+4, 20);
    EXPECT_TRUE(w->getRoads()[0]->getLights()[0]->getLastCycle() - lastcycle<0.0000001);
    EXPECT_EQ(w->getRoads()[0]->getLights()[0]->getState(), red);
    EXPECT_EQ(w->getRoads()[0]->getLights()[1]->getState(), green);

    for (unsigned int _ = 0; _<11;_++) {
        w->updateWorld(0.1);
    } //kleiner interval, meerdere keren werkt wel!!!
    lastcycle = std::fmod(lastcycle+1.1, 20.0);
    EXPECT_TRUE(w->getRoads()[0]->getLights()[0]->getLastCycle()-lastcycle<0.000000001);
    EXPECT_EQ(w->getRoads()[0]->getLights()[0]->getState(), red);
    EXPECT_EQ(w->getRoads()[0]->getLights()[1]->getState(), orange);

    for (unsigned int _ = 0; _<4;_++) {
        w->updateWorld(0.1);
    }

    lastcycle = std::fmod(lastcycle+0.4, 20.0);
    EXPECT_TRUE(w->getRoads()[0]->getLights()[0]->getLastCycle()- lastcycle<0.00000001);
    EXPECT_EQ(w->getRoads()[0]->getLights()[0]->getState(), red);
    EXPECT_EQ(w->getRoads()[0]->getLights()[1]->getState(), orange);

    for (unsigned int _ = 0; _<1;_++) {
        w->updateWorld(0.1);
    }

    lastcycle = std::fmod(lastcycle+0.1,20);
    EXPECT_TRUE(w->getRoads()[0]->getLights()[0]->getLastCycle()- lastcycle<0.00000001);
    EXPECT_EQ(w->getRoads()[0]->getLights()[0]->getState(), red);
    EXPECT_EQ(w->getRoads()[0]->getLights()[1]->getState(), red);
    for (unsigned int _ = 0; _<146;_++) {
        w->updateWorld(0.1);
    }

    lastcycle = std::fmod(lastcycle+14.6,20);
    EXPECT_TRUE(w->getRoads()[0]->getLights()[0]->getLastCycle()- lastcycle<0.00000001);
    EXPECT_EQ(w->getRoads()[0]->getLights()[0]->getState(), green);
    EXPECT_EQ(w->getRoads()[0]->getLights()[1]->getState(), red);
    delete w;
}

TEST_F(LightDomainTest, LightOnJunction) {
    ofstream error;
    srand(123);
    World* w = new World();
    Road* r1 = new Road("Middelheimlaan", 10000, &error);
    Road* r2 = new Road("Groenenborgerlaan", 10000, &error);
    Road* r3 = new Road("Kerkstraat", 10000, &error);
    Road* r4 = new Road("Molendreef", 10000, &error);
    w->addRoad(r1);
    w->addRoad(r2);
    w->addRoad(r3);
    w->addRoad(r4);
    vector<std::pair<Road*, double> > roads;
    roads.push_back(pair<Road*, double> (r1, 100));
    roads.push_back(pair<Road*, double> (r2, 150));
    roads.push_back(pair<Road*, double> (r3, 600));
    roads.push_back(pair<Road*, double> (r4, 574));
    w->addJunction(roads);
    w->getRoads()[0]->addLight(100, 4);
    w->getRoads()[1]->addLight(150, 7);
    w->getRoads()[2]->addLight(600, 3);
    w->getRoads()[3]->addLight(574, 9);
    w->getJunctions()[0]->checkJunctionLights();
    w->getJunctions()[0]->getClock()->setLastCycle(0);

    EXPECT_EQ(w->getRoads()[0]->getLights()[0]->getClock(), false);
    EXPECT_EQ(w->getRoads()[1]->getLights()[0]->getClock(), false);
    EXPECT_EQ(w->getRoads()[2]->getLights()[0]->getClock(), false);
    EXPECT_EQ(w->getRoads()[3]->getLights()[0]->getClock(), false);

    EXPECT_EQ(w->getRoads()[0]->getLights()[0]->getPosition(), 100);
    EXPECT_EQ(w->getRoads()[1]->getLights()[0]->getPosition(), 150);
    EXPECT_EQ(w->getRoads()[2]->getLights()[0]->getPosition(), 600);
    EXPECT_EQ(w->getRoads()[3]->getLights()[0]->getPosition(), 574);

    EXPECT_EQ(w->getJunctions()[0]->getRoad(0)->getName(), "Middelheimlaan");
    EXPECT_EQ(w->getJunctions()[0]->getRoad(1)->getName(), "Groenenborgerlaan");
    EXPECT_EQ(w->getJunctions()[0]->getRoad(2)->getName(), "Kerkstraat");
    EXPECT_EQ(w->getJunctions()[0]->getRoad(3)->getName(), "Molendreef");

    EXPECT_EQ(w->getJunctions()[0]->getRoad(0)->getLights()[0]->getState(), green);
    EXPECT_EQ(w->getJunctions()[0]->getRoad(1)->getLights()[0]->getState(), red);
    EXPECT_EQ(w->getJunctions()[0]->getRoad(2)->getLights()[0]->getState(), red);
    EXPECT_EQ(w->getJunctions()[0]->getRoad(3)->getLights()[0]->getState(), red);

    for(unsigned int _=0; _<41; _++){
        w->updateWorld(0.1);
    }
    EXPECT_EQ(w->getJunctions()[0]->getRoad(0)->getLights()[0]->getState(), orange);
    EXPECT_EQ(w->getJunctions()[0]->getRoad(1)->getLights()[0]->getState(), red);
    EXPECT_EQ(w->getJunctions()[0]->getRoad(2)->getLights()[0]->getState(), red);
    EXPECT_EQ(w->getJunctions()[0]->getRoad(3)->getLights()[0]->getState(), red);

    for(unsigned int _=0; _<5; _++){
        w->updateWorld(0.1);
    }
    EXPECT_EQ(w->getJunctions()[0]->getRoad(0)->getLights()[0]->getState(), red);
    EXPECT_EQ(w->getJunctions()[0]->getRoad(1)->getLights()[0]->getState(), green);
    EXPECT_EQ(w->getJunctions()[0]->getRoad(2)->getLights()[0]->getState(), red);
    EXPECT_EQ(w->getJunctions()[0]->getRoad(3)->getLights()[0]->getState(), red);

    for(unsigned int _=0; _<39; _++){
        w->updateWorld(0.1);
    }
    EXPECT_EQ(w->getJunctions()[0]->getRoad(0)->getLights()[0]->getState(), red);
    EXPECT_EQ(w->getJunctions()[0]->getRoad(1)->getLights()[0]->getState(), orange);
    EXPECT_EQ(w->getJunctions()[0]->getRoad(2)->getLights()[0]->getState(), red);
    EXPECT_EQ(w->getJunctions()[0]->getRoad(3)->getLights()[0]->getState(), red);

    for(unsigned int _=0; _<4; _++){
        w->updateWorld(0.1);
    }

    EXPECT_EQ(w->getJunctions()[0]->getRoad(0)->getLights()[0]->getState(), red);
    EXPECT_EQ(w->getJunctions()[0]->getRoad(1)->getLights()[0]->getState(), red);
    EXPECT_EQ(w->getJunctions()[0]->getRoad(2)->getLights()[0]->getState(), green);
    EXPECT_EQ(w->getJunctions()[0]->getRoad(3)->getLights()[0]->getState(), red);

    delete w;
}

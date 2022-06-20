//============================================================================
// Name        : Car_SimDomainTest.cpp
// Date        : 18/06/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 4
//============================================================================


#include <iostream>
#include "gtest/gtest.h"
#include "../Classes/World.h"
#include "../Classes/Light.h"
#include "../Classes/Car.h"
#include "../Classes/CarGen.h"
#include "../Classes/BusStop.h"
#include "../Classes/Junction.h"
#include "../Classes/CarData.h"
using namespace std;

class Car_SimDomainTest: public ::testing::Test {
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

//source: https://www.codegrepper.com/code-examples/cpp/c%2B%2B+round+number+to+2+decimal+places
float roundoff(float value, unsigned char prec)
{
    float pow_10 = pow(10.0f, (float)prec);
    return round(value * pow_10) / pow_10;
}

/**
Tests if every object is initialised right.
*/
TEST_F(Car_SimDomainTest, Initialiserbasic) {
    srand(123);
    World* w = new World();
    Road* r1 = new Road("Middelheimlaan", 200, &w->error);
    Road* r2 = new Road("Groenenborgerlaan", 200, &w->error);
    w->addRoad(r1);
    w->addRoad(r2);
    r1->addCar(25, w->getCarData(car));
    r1->addCar(60, w->getCarData(bus));
    r1->addCar(90,w->getCarData(ambulance));
    r2->addCar(90, w->getCarData(fire));
    r1->addLight(33, 5);
    r1->addLight( 20, 5);
    r2->addLight(150,5);
    r1->addCarGen(5, w->getCarData(car));
    r2->addCarGen(5, w->getCarData(bus));
    std::vector<std::pair<Road *, double> > roads;
    roads.push_back(pair<Road*,double>(r1,83));
    roads.push_back(pair<Road*,double>(r2,70));
    w->addJunction(roads);
    w->getRoads()[0]->addBusStop(200, 7);
    color l1 = r1->getLights()[0]->getState();
    color l2 = r1->getLights()[1]->getState();
    color l3 = r2->getLights()[0]->getState();

    EXPECT_EQ(r1->getName(), "Middelheimlaan");
    EXPECT_EQ(r1->getLength(), 200);
    EXPECT_EQ(r2->getName(), "Groenenborgerlaan");
    EXPECT_EQ(r2->getLength(), 200);

    EXPECT_EQ(r1->getCars()[0]->getDistance(),25);
    EXPECT_EQ(r1->getCars()[1]->getDistance(),60);
    EXPECT_EQ(r1->getCars()[2]->getDistance(), 90);
    EXPECT_EQ(r2->getCars()[0]->getDistance(),90);

    EXPECT_EQ(r1->getLights()[0]->getPosition(), 33);
    EXPECT_EQ(r1->getLights()[1]->getPosition(), 20);
    EXPECT_EQ(r2->getLights()[0]->getPosition(), 150);
    EXPECT_EQ(r1->getLights()[0]->getCycle(), 5);
    EXPECT_EQ(r1->getLights()[1]->getCycle(), 5);
    EXPECT_EQ(r2->getLights()[0]->getCycle(), 5);

    EXPECT_EQ(r1->getCarGen()[0]->getFrequency(), 5);
    EXPECT_EQ(r2->getCarGen()[0]->getFrequency(), 5);

    EXPECT_EQ(w->getJunctions()[0]->getRoad(0)->getName(), "Middelheimlaan");
    EXPECT_EQ(w->getJunctions()[0]->getRoad(1)->getName(), "Groenenborgerlaan");
    EXPECT_EQ(w->getJunctions()[0]->getPosition(0), 83);
    EXPECT_EQ(w->getJunctions()[0]->getPosition(1), 70);

    EXPECT_EQ(w->getRoads()[0]->getBusStops()[0]->getRoad()->getName(), "Middelheimlaan");
    EXPECT_EQ(w->getRoads()[0]->getBusStops()[0]->getPosition(), 200);
    EXPECT_EQ(w->getRoads()[0]->getBusStops()[0]->getStopTime(), 7);

    EXPECT_EQ(r1->getLights()[0]->getState(), l1);
    EXPECT_EQ(r1->getLights()[1]->getState(), l2);
    EXPECT_EQ(r2->getLights()[0]->getState(), l3);
    delete w;
}
/**
Tests update simulated world and see if the new situation is right (here just the lights).
*/

TEST_F(Car_SimDomainTest, UpdateWorld) {
    srand(123);
    World* w = new World();
    Road* r1 = new Road("Middelheimlaan", 200, &w->error);
    Road* r2 = new Road("Groenenborgerlaan", 200, &w->error);
    w->addRoad(r1);
    w->addRoad(r2);
    r1->addCar(0, w->getCarData(car));
    r1->addCar(60, w->getCarData(bus));
    r1->addCar(90,w->getCarData(ambulance));
    r2->addCar(90, w->getCarData(fire));
    r1->addLight(33, 5);
    r1->addLight( 130, 5);
    r2->addLight(150,5);
    w->getRoads()[0]->getLights()[0]->setLastCycle(0);
    w->getRoads()[0]->getLights()[1]->setLastCycle(0);
    w->getRoads()[1]->getLights()[0]->setLastCycle(0);
    w->getRoads()[0]->getLights()[0]->setState(green);
    w->getRoads()[0]->getLights()[1]->setState(red);
    w->getRoads()[1]->getLights()[0]->setState(red);
    r1->addCarGen(5, w->getCarData(car));
    r2->addCarGen(5, w->getCarData(bus));
    w->getRoads()[0]->getCarGen()[0]->setCycle(0);
    w->getRoads()[1]->getCarGen()[0]->setCycle(0);
    std::vector<std::pair<Road *, double> > roads;
    roads.push_back(pair<Road*,double>(r1,83));
    roads.push_back(pair<Road*,double>(r2,70));
    w->addJunction(roads);
    w->getRoads()[1]->addBusStop(200, 7);
    double distance1 = w->getRoads()[0]->getCars()[0]->getDistance();
    double distance2 = w->getRoads()[0]->getCars()[1]->getDistance();
    double distance3 = w->getRoads()[0]->getCars()[2]->getDistance();
    double distance4 = w->getRoads()[1]->getCars()[0]->getDistance();
    for(unsigned int i=0; i<20; i++){
        w->updateWorld(0.1);
    }

    double lastcycle = std::fmod(2.0,5.0);
    EXPECT_EQ(w->getRoads()[0]->getCars()[0]->getAction(), fast);
    EXPECT_NE(w->getRoads()[0]->getCars()[0]->getDistance(), distance1);
    distance1 = w->getRoads()[0]->getCars()[0]->getDistance();

    EXPECT_EQ(w->getRoads()[0]->getCars()[1]->getAction(), slow);
    EXPECT_NE(w->getRoads()[0]->getCars()[1]->getDistance(), distance2);
    distance2 = w->getRoads()[0]->getCars()[1]->getDistance();

    EXPECT_EQ(w->getRoads()[0]->getCars()[2]->getAction(), fast);
    EXPECT_NE(w->getRoads()[0]->getCars()[2]->getDistance(), distance3);
    distance3 = w->getRoads()[0]->getCars()[2]->getDistance();

    EXPECT_EQ(w->getRoads()[1]->getCars()[0]->getAction(), fast);
    EXPECT_NE(w->getRoads()[1]->getCars()[0]->getDistance(), distance4);
    distance4 = w->getRoads()[1]->getCars()[0]->getDistance();

    EXPECT_EQ(w->getRoads()[0]->getLights()[0]->getState(), green);
    EXPECT_TRUE(abs(fmod(roundoff(w->getRoads()[0]->getLights()[0]->getLastCycle(),10),5) - lastcycle)<0.0001);

    EXPECT_EQ(w->getRoads()[0]->getLights()[1]->getState(), red);
    EXPECT_TRUE(abs(fmod(roundoff(w->getRoads()[0]->getLights()[1]->getLastCycle(),10),5) - lastcycle)<0.0001);

    EXPECT_EQ(w->getRoads()[1]->getLights()[0]->getState(), red);
    EXPECT_TRUE(abs(fmod(roundoff(w->getRoads()[1]->getLights()[0]->getLastCycle(),10),5) - lastcycle)<0.0001);

    EXPECT_TRUE(abs(fmod(roundoff(w->getRoads()[0]->getCarGen()[0]->getCycle(),10),5) - lastcycle)<0.0001);
    EXPECT_TRUE(abs(fmod(roundoff(w->getRoads()[1]->getCarGen()[0]->getCycle(),10),5) - lastcycle)<0.0001);

    EXPECT_EQ(w->getRoads()[1]->getBusStops()[0]->getTimeStopped(), 0);
    EXPECT_EQ(w->getRoads()[1]->getBusStops()[0]->getbussy(), false);

    for(unsigned int i=0; i<30; i++){
        w->updateWorld(0.1);
    }
    lastcycle = std::fmod(lastcycle+3.0,5.0);
    EXPECT_EQ(w->getRoads()[0]->getCars()[0]->getAction(), fast);
    EXPECT_NE(w->getRoads()[0]->getCars()[0]->getDistance(), distance1);
    distance1 = w->getRoads()[0]->getCars()[0]->getDistance();

    EXPECT_EQ(w->getRoads()[0]->getCars()[1]->getAction(), slow);
    EXPECT_NE(w->getRoads()[0]->getCars()[1]->getDistance(), distance2);
    distance2 = w->getRoads()[0]->getCars()[1]->getDistance();

    EXPECT_EQ(w->getRoads()[0]->getCars()[2]->getAction(), fast);
    EXPECT_NE(w->getRoads()[0]->getCars()[2]->getDistance(), distance3);
    distance3 = w->getRoads()[0]->getCars()[2]->getDistance();

    EXPECT_EQ(w->getRoads()[1]->getCars()[0]->getAction(), fast);
    EXPECT_NE(w->getRoads()[1]->getCars()[0]->getDistance(), distance4);
    distance4 = w->getRoads()[1]->getCars()[0]->getDistance();

    EXPECT_EQ(w->getRoads()[0]->getLights()[0]->getState(), green);
    EXPECT_TRUE(abs(fmod(roundoff(w->getRoads()[0]->getLights()[0]->getLastCycle(),10), 5)-lastcycle)<0.0001);

    EXPECT_EQ(w->getRoads()[0]->getLights()[1]->getState(), red);
    EXPECT_TRUE(abs(fmod(roundoff(w->getRoads()[0]->getLights()[1]->getLastCycle(),10), 5))-lastcycle<0.0001);

    EXPECT_EQ(w->getRoads()[1]->getLights()[0]->getState(), red);
    EXPECT_TRUE(abs(fmod(roundoff(w->getRoads()[1]->getLights()[0]->getLastCycle(),10),5)-lastcycle)<0.0001);

    EXPECT_TRUE(abs(fmod(roundoff(w->getRoads()[0]->getCarGen()[0]->getCycle(),10), 5)-lastcycle)<0.0001);
    EXPECT_TRUE(abs(fmod(roundoff(w->getRoads()[1]->getCarGen()[0]->getCycle(),10),5)-lastcycle)<0.0001);

    EXPECT_EQ(w->getRoads()[1]->getBusStops()[0]->getTimeStopped(), 0);
    EXPECT_EQ(w->getRoads()[1]->getBusStops()[0]->getbussy(), false);

    for(unsigned int i=0; i<2; i++){
        w->updateWorld(0.1);
    }
    lastcycle = std::fmod(lastcycle+0.2,5);
    EXPECT_EQ(w->getRoads()[0]->getCars()[0]->getAction(), fast);
    EXPECT_NE(w->getRoads()[0]->getCars()[0]->getDistance(), distance1);
    distance1 = w->getRoads()[0]->getCars()[0]->getDistance();

    EXPECT_EQ(w->getRoads()[0]->getCars()[1]->getAction(), fast);
    EXPECT_NE(w->getRoads()[0]->getCars()[1]->getDistance(), distance2);
    distance2 = w->getRoads()[0]->getCars()[1]->getDistance();

    EXPECT_EQ(w->getRoads()[0]->getCars()[2]->getAction(), fast);
    EXPECT_NE(w->getRoads()[0]->getCars()[2]->getDistance(), distance3);
    distance3 = w->getRoads()[0]->getCars()[2]->getDistance();

    EXPECT_EQ(w->getRoads()[1]->getCars()[0]->getAction(), fast);
    EXPECT_NE(w->getRoads()[1]->getCars()[0]->getDistance(), distance4);
    distance4 = w->getRoads()[1]->getCars()[0]->getDistance();

    EXPECT_EQ(w->getRoads()[0]->getLights()[0]->getState(), orange);
    EXPECT_TRUE(abs(fmod(roundoff(w->getRoads()[0]->getLights()[0]->getLastCycle(),10),5)-lastcycle)<0.0001);

    EXPECT_EQ(w->getRoads()[0]->getLights()[1]->getState(), green);
    EXPECT_TRUE(abs(fmod(roundoff(w->getRoads()[0]->getLights()[1]->getLastCycle(),10),5)-lastcycle)<0.0001);

    EXPECT_EQ(w->getRoads()[1]->getLights()[0]->getState(), green);
    EXPECT_TRUE(abs(fmod(roundoff(w->getRoads()[1]->getLights()[0]->getLastCycle(),10),5)-lastcycle)<0.0001);

    EXPECT_TRUE(abs(fmod(roundoff(w->getRoads()[0]->getCarGen()[0]->getCycle(),10),5)-lastcycle)<0.0001);
    EXPECT_TRUE(abs(fmod(roundoff(w->getRoads()[1]->getCarGen()[0]->getCycle(),10),5)-lastcycle)<0.0001);

    EXPECT_EQ(w->getRoads()[1]->getBusStops()[0]->getTimeStopped(), 0);
    EXPECT_EQ(w->getRoads()[1]->getBusStops()[0]->getbussy(), false);


    for(unsigned int i=0; i<10; i++){
        w->updateWorld(0.1);
    }
    double lastcycle2 = w->getRoads()[0]->getLights()[0]->getLastCycle();

    lastcycle = std::fmod(lastcycle+1,5);
    EXPECT_EQ(w->getRoads()[0]->getCars()[0]->getAction(), fast);
    EXPECT_NE(w->getRoads()[0]->getCars()[0]->getDistance(), distance1);
    distance1 = w->getRoads()[0]->getCars()[0]->getDistance();

    EXPECT_EQ(w->getRoads()[0]->getCars()[1]->getAction(), fast);
    EXPECT_NE(w->getRoads()[0]->getCars()[1]->getDistance(), distance2);
    distance2 = w->getRoads()[0]->getCars()[1]->getDistance();

    EXPECT_EQ(w->getRoads()[0]->getCars()[2]->getAction(), fast);
    EXPECT_NE(w->getRoads()[0]->getCars()[2]->getDistance(), distance3);
    distance3 = w->getRoads()[0]->getCars()[2]->getDistance();

    EXPECT_EQ(w->getRoads()[1]->getCars()[0]->getAction(), fast);
    EXPECT_NE(w->getRoads()[1]->getCars()[0]->getDistance(), distance4);
    distance4 = w->getRoads()[1]->getCars()[0]->getDistance();

    EXPECT_EQ(w->getRoads()[0]->getLights()[0]->getState(), red);
    EXPECT_TRUE(abs(fmod(roundoff(w->getRoads()[0]->getLights()[0]->getLastCycle(),10),5)-lastcycle2)<0.0001);

    EXPECT_EQ(w->getRoads()[0]->getLights()[1]->getState(), green);
    EXPECT_TRUE(abs(fmod(roundoff(w->getRoads()[0]->getLights()[1]->getLastCycle(),10),5)-lastcycle)<0.0001);
    EXPECT_TRUE(abs(fmod(roundoff(w->getRoads()[0]->getLights()[1]->getLastCycle(),10),5)-lastcycle)<0.00001);

    EXPECT_EQ(w->getRoads()[1]->getLights()[0]->getState(), green);
    EXPECT_TRUE(abs(fmod(roundoff(w->getRoads()[1]->getLights()[0]->getLastCycle(),10),5)-lastcycle)<0.0001);
    EXPECT_TRUE(abs(fmod(roundoff(w->getRoads()[1]->getLights()[0]->getLastCycle(),10),5)-lastcycle)<0.00001);

    for (unsigned int i=0; i<60; i++){
        w->updateWorld(0.1);
    }
    EXPECT_EQ(w->getRoads()[1]->getCars()[0]->getAction(), slow);
    EXPECT_EQ(w->getRoads()[1]->getCars()[0]->getData()->getType(), car);
    EXPECT_NE(w->getRoads()[1]->getCars()[0]->getDistance(), distance2);
    distance1 = w->getRoads()[1]->getCars()[0]->getDistance();

    EXPECT_EQ(w->getRoads()[1]->getBusStops()[0]->getTimeStopped(), 0);
    EXPECT_EQ(w->getRoads()[1]->getBusStops()[0]->getbussy(), false);

    for (unsigned int i=0; i<90; i++){
        w->updateWorld(0.1);
    }
    EXPECT_EQ(w->getRoads()[1]->getCars()[0]->getAction(), fast);
    EXPECT_NE(w->getRoads()[1]->getCars()[0]->getDistance(), distance1);
    distance1 = w->getRoads()[1]->getCars()[0]->getDistance();

    EXPECT_EQ(w->getRoads()[1]->getBusStops()[0]->getTimeStopped(), 0);
    EXPECT_EQ(w->getRoads()[1]->getBusStops()[0]->getbussy(), false);
    for (unsigned int i=0; i<50; i++){
        w->updateWorld(0.1);
    }
    EXPECT_EQ(w->getRoads()[1]->getCars()[0]->getAction(), fast);
    EXPECT_NE(w->getRoads()[1]->getCars()[0]->getDistance(), distance1);
    distance1 = w->getRoads()[1]->getCars()[0]->getDistance();

    EXPECT_TRUE(w->getRoads()[1]->getBusStops()[0]->getTimeStopped() == 0);
    EXPECT_EQ(w->getRoads()[1]->getBusStops()[0]->getbussy(), false);

    for (unsigned int i=0; i<70; i++){
        w->updateWorld(0.1);
    }
    EXPECT_EQ(w->getRoads()[1]->getCars()[0]->getAction(), slow);
    EXPECT_NE(w->getRoads()[1]->getCars()[0]->getDistance(), distance1);
    distance1 = w->getRoads()[1]->getCars()[0]->getDistance();
    EXPECT_EQ(w->getRoads()[1]->getBusStops()[0]->getbussy(), false);

   for (unsigned int i=0; i<30; i++){
        w->updateWorld(0.1);
    }
    for (unsigned int i=0; i<5; i++){
        w->updateWorld(0.1);
    }
    EXPECT_EQ(w->getRoads()[1]->getBusStops()[0]->getbussy(), false);
    delete w;
}
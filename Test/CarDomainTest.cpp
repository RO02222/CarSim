//============================================================================
// Name        : CarDomainTest.cpp
// Date        : 18/06/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 4
//============================================================================

#include <iostream>
#include "gtest/gtest.h"
#include "../Classes/World.h"
#include "../Classes/Car.h"
#include "../Classes/Light.h"

using namespace std;



class CarDomainTest: public ::testing::Test {
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
TEST_F(CarDomainTest, Initialiser) {
    World* w = new World();
    Road r1 = Road("Middelheimlaan", 100, &w->error);

    r1.addCar(3, w->getCarData(car));
    EXPECT_EQ(r1.getCars()[0]->getDistance(), 3);
    EXPECT_EQ(r1.getCars()[0]->getData(), w->getCarData(car));

    r1.addCar(29, w->getCarData(ambulance));
    EXPECT_EQ(r1.getCars()[1]->getDistance(), 29);
    EXPECT_EQ(r1.getCars()[1]->getData(), w->getCarData(ambulance));

    r1.addCar(35, w->getCarData(fire));
    EXPECT_EQ(r1.getCars()[2]->getDistance(), 35);
    EXPECT_EQ(r1.getCars()[2]->getData(), w->getCarData(fire));

    r1.addCar(60, w->getCarData(bus));
    EXPECT_EQ(r1.getCars()[3]->getDistance(), 60);
    EXPECT_EQ(r1.getCars()[3]->getData(), w->getCarData(bus));

    r1.addCar(70, w->getCarData(police));
    EXPECT_EQ(r1.getCars()[4]->getDistance(), 70);
    EXPECT_EQ(r1.getCars()[4]->getData(), w->getCarData(police));

    r1.addCar(70, w->getCarData(police));
    EXPECT_EQ(r1.getCars()[5]->getDistance(), 70);
    EXPECT_EQ(r1.getCars()[5]->getData(), w->getCarData(police));

    r1.addCar(90, w->getCarData(bugatti));
    EXPECT_EQ(r1.getCars()[6]->getDistance(), 90);
    EXPECT_EQ(r1.getCars()[6]->getData(), w->getCarData(bugatti));

}


/**
Tests InitialiserEdge: test if every object is initialised right with some edge cases.
*/
TEST_F(CarDomainTest, InitialiserEdge) {
    World* w = new World();
    Road r1 = Road("Middelheimlaan", 100, &w->error);

    r1.addCar(0, w->getCarData(car));
    EXPECT_EQ(r1.getCars()[0]->getDistance(), 0);
    EXPECT_EQ(r1.getCars()[0]->getData(), w->getCarData(car));

    r1.addCar(100, w->getCarData(ambulance));
    EXPECT_EQ(r1.getCars()[1]->getDistance(), 100);
    EXPECT_EQ(r1.getCars()[1]->getData(), w->getCarData(ambulance));

    r1.addCar(-1, w->getCarData(fire));
    EXPECT_EQ(r1.getCars().size(), (long unsigned) 2);

    r1.addCar(101, w->getCarData(bus));
    EXPECT_EQ(r1.getCars().size(), (long unsigned) 2);

}

TEST_F(CarDomainTest, updatetest) {
    World* w = new World();
    Road r1 = Road("Middelheimlaan", 200, &w->error);
    vector<double> speed;
    vector<double> accelaration;
    vector<double> distance;

    r1.addCar(3, w->getCarData(car));
    EXPECT_EQ(r1.getCars()[0]->getDistance(), 3);
    EXPECT_EQ(r1.getCars()[0]->getData(), w->getCarData(car));
    speed.push_back(r1.getCars()[0]->getSpeed());
    accelaration.push_back(r1.getCars()[0]->getAcceleration());
    distance.push_back(r1.getCars()[0]->getDistance());

    r1.addCar(29, w->getCarData(ambulance));
    EXPECT_EQ(r1.getCars()[1]->getDistance(), 29);
    EXPECT_EQ(r1.getCars()[1]->getData(), w->getCarData(ambulance));
    speed.push_back(r1.getCars()[1]->getSpeed());
    accelaration.push_back(r1.getCars()[1]->getAcceleration());
    distance.push_back(r1.getCars()[1]->getDistance());

    r1.addCar(35, w->getCarData(fire));
    EXPECT_EQ(r1.getCars()[2]->getDistance(), 35);
    EXPECT_EQ(r1.getCars()[2]->getData(), w->getCarData(fire));
    speed.push_back(r1.getCars()[2]->getSpeed());
    accelaration.push_back(r1.getCars()[2]->getAcceleration());
    distance.push_back(r1.getCars()[2]->getDistance());

    r1.addCar(60, w->getCarData(bus));
    EXPECT_EQ(r1.getCars()[3]->getDistance(), 60);
    EXPECT_EQ(r1.getCars()[3]->getData(), w->getCarData(bus));
    speed.push_back(r1.getCars()[3]->getSpeed());
    accelaration.push_back(r1.getCars()[3]->getAcceleration());
    distance.push_back(r1.getCars()[3]->getDistance());

    r1.addCar(70, w->getCarData(police));
    EXPECT_EQ(r1.getCars()[4]->getDistance(), 70);
    EXPECT_EQ(r1.getCars()[4]->getData(), w->getCarData(police));
    speed.push_back(r1.getCars()[4]->getSpeed());
    accelaration.push_back(r1.getCars()[4]->getAcceleration());
    distance.push_back(r1.getCars()[4]->getDistance());

    r1.addCar(80, w->getCarData(bugatti));
    EXPECT_EQ(r1.getCars()[5]->getDistance(), 80);
    EXPECT_EQ(r1.getCars()[5]->getData(), w->getCarData(bugatti));
    speed.push_back(r1.getCars()[5]->getSpeed());
    accelaration.push_back(r1.getCars()[5]->getAcceleration());
    distance.push_back(r1.getCars()[5]->getDistance());

    r1.updateRoad(2);
    if(r1.getCars()[0]->getSpeed()!= 0){
        EXPECT_NE(r1.getCars()[0]->getAcceleration(), accelaration[0]);
        EXPECT_NE(r1.getCars()[0]->getDistance(), distance[0]);
        EXPECT_NE(r1.getCars()[0]->getSpeed(), speed[0]);
    }
    if(r1.getCars()[1]->getSpeed()!= 0){
        EXPECT_NE(r1.getCars()[1]->getAcceleration(), accelaration[1]);
        EXPECT_NE(r1.getCars()[1]->getDistance(), distance[1]);
        EXPECT_NE(r1.getCars()[1]->getSpeed(), speed[1]);
    }
    if(r1.getCars()[2]->getSpeed()!= 0){
        EXPECT_NE(r1.getCars()[2]->getAcceleration(), accelaration[2]);
        EXPECT_NE(r1.getCars()[2]->getDistance(), distance[2]);
        EXPECT_NE(r1.getCars()[2]->getSpeed(), speed[2]);
    }
    if(r1.getCars()[3]->getSpeed()!= 0){
        EXPECT_NE(r1.getCars()[3]->getAcceleration(), accelaration[3]);
        EXPECT_NE(r1.getCars()[3]->getDistance(), distance[3]);
        EXPECT_NE(r1.getCars()[3]->getSpeed(), speed[3]);
    }

    if(r1.getCars()[4]->getSpeed()!= 0){
        EXPECT_NE(r1.getCars()[4]->getAcceleration(), accelaration[4]);
        EXPECT_NE(r1.getCars()[4]->getDistance(), distance[4]);
        EXPECT_NE(r1.getCars()[4]->getSpeed(), speed[4]);
    }

    if(r1.getCars()[5]->getSpeed()!= 0){
        EXPECT_NE(r1.getCars()[5]->getAcceleration(), accelaration[5]);
        EXPECT_NE(r1.getCars()[5]->getDistance(), distance[5]);
        EXPECT_NE(r1.getCars()[5]->getSpeed(), speed[5]);
    }

    speed.clear();
    speed.push_back(r1.getCars()[0]->getSpeed());
    speed.push_back(r1.getCars()[1]->getSpeed());
    speed.push_back(r1.getCars()[2]->getSpeed());
    speed.push_back(r1.getCars()[3]->getSpeed());
    speed.push_back(r1.getCars()[4]->getSpeed());
    speed.push_back(r1.getCars()[5]->getSpeed());
    distance.push_back(r1.getCars()[0]->getDistance());
    distance.push_back(r1.getCars()[1]->getDistance());
    distance.push_back(r1.getCars()[2]->getDistance());
    distance.push_back(r1.getCars()[3]->getDistance());
    distance.push_back(r1.getCars()[4]->getDistance());
    distance.push_back(r1.getCars()[5]->getDistance());
    accelaration.push_back(r1.getCars()[0]->getAcceleration());
    accelaration.push_back(r1.getCars()[1]->getAcceleration());
    accelaration.push_back(r1.getCars()[2]->getAcceleration());
    accelaration.push_back(r1.getCars()[3]->getAcceleration());
    accelaration.push_back(r1.getCars()[4]->getAcceleration());
    accelaration.push_back(r1.getCars()[5]->getAcceleration());

    r1.updateRoad(20);
    if(r1.getCars()[0]->getSpeed()!= 0){
        EXPECT_NE(r1.getCars()[0]->getAcceleration(), accelaration[0]);
        EXPECT_NE(r1.getCars()[0]->getDistance(), distance[0]);
        EXPECT_NE(r1.getCars()[0]->getSpeed(), speed[0]);
    }
    if(r1.getCars()[1]->getSpeed()!= 0){
        EXPECT_NE(r1.getCars()[1]->getAcceleration(), accelaration[1]);
        EXPECT_NE(r1.getCars()[1]->getDistance(), distance[1]);
        EXPECT_NE(r1.getCars()[1]->getSpeed(), speed[1]);
    }
    if(r1.getCars()[2]->getSpeed()!= 0){
        EXPECT_NE(r1.getCars()[2]->getAcceleration(), accelaration[2]);
        EXPECT_NE(r1.getCars()[2]->getDistance(), distance[2]);
        EXPECT_NE(r1.getCars()[2]->getSpeed(), speed[2]);
    }
    if(r1.getCars()[3]->getSpeed()!= 0){
        EXPECT_NE(r1.getCars()[3]->getAcceleration(), accelaration[3]);
        EXPECT_NE(r1.getCars()[3]->getDistance(), distance[3]);
        EXPECT_NE(r1.getCars()[3]->getSpeed(), speed[3]);
    }

    EXPECT_EQ(r1.getCars().size(), (long unsigned) 4);
}


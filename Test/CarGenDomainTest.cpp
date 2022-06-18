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
#include "../Classes/World.h"
using namespace std;

class CarGenDomainTest: public ::testing::Test {
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
void test_CarGen(Type type){
    // normal working
    srand(123);
    World* w = new World();
    w->addRoad("Middelheimlaan", 10000);
    w->getRoads()[0]->addCarGen(8, w->getCarData(type));
    double time = w->getRoads()[0]->getCarGen()[0]->getCycle();
    double numCars = w->getRoads()[0]->getCars().size();
    EXPECT_EQ(int (w->getRoads()[0]->getCars().size()), 0);
    for (unsigned int _ = 0; _ < 20; _++){
        w->getRoads()[0]->getCarGen()[0]->updateCarGen(2);
        for (unsigned int i = 0 ; i<w->getRoads()[0]->getCars().size();i++){
            w->getRoads()[0]->getCars()[i]->updateCar(2);
        }
        time += 2;
        if (time >= 8){
            time = time -8;
            numCars += 1;
            EXPECT_EQ(w->getRoads()[0]->getCars()[w->getRoads()[0]->getCars().size()-1]->getData()->getType(), type);
        }
        EXPECT_EQ(w->getRoads()[0]->getCars().size(), numCars);
        EXPECT_EQ(double (w->getRoads()[0]->getCarGen()[0]->getCycle()), time);
    }
    delete w;
    //road opstructed
    World* u = new World();
    u->addRoad("Middelheimlaan", 100);
    u->getRoads()[0]->addCarGen(1, u->getCarData(type));
    EXPECT_EQ(int(u->getRoads()[0]->getCars().size()), 0);
    u->getRoads()[0]->getCarGen()[0]->updateCarGen(2);
    EXPECT_EQ(int(u->getRoads()[0]->getCars().size()), 1);
    u->getRoads()[0]->getCarGen()[0]->updateCarGen(2);
    EXPECT_EQ(int(u->getRoads()[0]->getCars().size()), 1);
    delete u;
}

/**
Tests Initialiser: test if every object is initialised right.
*/
TEST_F(CarGenDomainTest, Initialiser) {
//CargenCar: test if CarGen works for cars.
    test_CarGen(car);
//CargenCar: test if CarGen works for ambulances.
    test_CarGen(ambulance);
//CargenCar: test if CarGen works for firetrucks.
    test_CarGen(fire);
//CargenCar: test if CarGen works for busses.
    test_CarGen(bus);
//CargenCar: test if CarGen works for bugatti's.
    test_CarGen(bugatti);
//CargenCar: test if CarGen works for policecars.
    test_CarGen(police);
}

TEST_F(CarGenDomainTest, Initialiser2) {
    // normal working
    srand(123);
    World* w = new World();
    w->addRoad("Middelheimlaan", 10000);
    w->getRoads()[0]->addCarGen(8, w->getAllData());
    double time = w->getRoads()[0]->getCarGen()[0]->getCycle();
    double numCars = w->getRoads()[0]->getCars().size();
    EXPECT_EQ(int (w->getRoads()[0]->getCars().size()), 0);
    for (unsigned int _ = 0; _ < 20; _++){
        w->getRoads()[0]->getCarGen()[0]->updateCarGen(2);
        for (unsigned int i = 0 ; i<w->getRoads()[0]->getCars().size();i++){
            w->getRoads()[0]->getCars()[i]->updateCar(2);
        }
        time += 2;
        if (time >= 8){
            time = time -8;
            numCars += 1;
            EXPECT_EQ(w->getRoads()[0]->getCars()[w->getRoads()[0]->getCars().size()-1]->getData(), w->getRoads()[0]->getCarGen()[0]->getData());
        }
        EXPECT_EQ(w->getRoads()[0]->getCars().size(), numCars);
        EXPECT_EQ(double (w->getRoads()[0]->getCarGen()[0]->getCycle()), time);
    }
    delete w;
    //road opstructed
    World* u = new World();
    u->addRoad("Middelheimlaan", 100);
    u->getRoads()[0]->addCarGen(1, u->getAllData());
    EXPECT_EQ(int(u->getRoads()[0]->getCars().size()), 0);
    u->getRoads()[0]->getCarGen()[0]->updateCarGen(2);
    EXPECT_EQ(int(u->getRoads()[0]->getCars().size()), 1);
    u->getRoads()[0]->getCarGen()[0]->updateCarGen(2);
    EXPECT_EQ(int(u->getRoads()[0]->getCars().size()), 1);
    delete u;
}
TEST_F(CarGenDomainTest, WeWantMore) {
    srand(123);
    World *w = new World();
    w->addRoad("Middelheimlaan", 10000);
    w->getRoads()[0]->addCarGen(8, w->getCarData(car));
    w->getRoads()[0]->addCarGen(3, w->getCarData(police));
    w->getRoads()[0]->addCarGen(10, w->getCarData(bus));
    w->getRoads()[0]->addCarGen(3, w->getCarData(police));
    w->getRoads()[0]->getCarGen()[0]->setCycle(0);
    w->getRoads()[0]->getCarGen()[1]->setCycle(0);
    w->getRoads()[0]->getCarGen()[2]->setCycle(0);
    for(unsigned int _=0; _<3; _++){
        w->updateWorld(1);
    }
    EXPECT_EQ(w->getRoads()[0]->getCars()[0]->getData()->getType(), police);
    EXPECT_EQ(w->getRoads()[0]->getCars().size(), (unsigned int) 1);
    for(unsigned int _=0; _<3; _++){
        w->updateWorld(1);
    }
    EXPECT_EQ(w->getRoads()[0]->getCars()[1]->getData()->getType(), police);
    EXPECT_EQ(w->getRoads()[0]->getCars().size(), (unsigned int) 2);
    for(unsigned int _=0; _<2; _++){
        w->updateWorld(1);
    }
    EXPECT_EQ(w->getRoads()[0]->getCars()[2]->getData()->getType(), car);
    for(unsigned int _=0; _<2; _++){
        w->updateWorld(1);
    }
    EXPECT_EQ(w->getRoads()[0]->getCars()[3]->getData()->getType(), police);
    EXPECT_EQ(w->getRoads()[0]->getCars()[4]->getData()->getType(), bus);
    delete w;
}

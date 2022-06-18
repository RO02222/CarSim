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


class ClockDomaimTest: public ::testing::Test {
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
TEST_F(ClockDomaimTest, Initialiser) {
    Clock c = Clock(4);
    c.setLastCycle(0);
    c.setState(green);

    EXPECT_EQ(c.getCycle(), 4);
    EXPECT_EQ(c.getLastCycle(), 0);
    EXPECT_EQ(c.getState(), green);
}

/**
Tests Update: test if every object is updated right.
*/
TEST_F(ClockDomaimTest, updateClock) {
    Clock c = Clock(4);
    c.setLastCycle(0);
    c.setState(green);

    c.updateClock(2);
    EXPECT_EQ(c.getLastCycle(), 2);
    EXPECT_EQ(c.getState(),green);

    c.updateClock(2);
    EXPECT_EQ(c.getLastCycle(), 0);
    EXPECT_EQ(c.getState(),orange);

    c.updateClock(0.4);
    EXPECT_EQ(c.getLastCycle(), 0);
    EXPECT_EQ(c.getState(),red);

    c.updateClock(2);
    EXPECT_EQ(c.getLastCycle(), 2);
    EXPECT_EQ(c.getState(),red);

    c.updateClock(2);
    EXPECT_EQ(c.getLastCycle(), 0);
    EXPECT_EQ(c.getState(),green);
}
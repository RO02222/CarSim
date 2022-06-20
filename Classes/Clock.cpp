//============================================================================
// Name        : Clock.cpp
// Date        : 18/06/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 4
//============================================================================


#include "Clock.h"
#include "World.h"
#include "../DesignByContract.h"


Clock::Clock(double c): state(color(rand() % 2)) {
    REQUIRE(c>=1, "Cycle is not valid");
    cycle = c;
    lastCycle = rand() % lround(cycle);
    _initCheck = this;
    ENSURE(this->properlyInitialized(), "constructor must end in properlyInitialized state");
}

Clock::~Clock() {}


void Clock::updateClock(double t) {
    REQUIRE(t>0, "Time cannot be negative");
    REQUIRE(isvalid(), "Clock is not valid");
    double ensureLastCycle = lastCycle + t;
    lastCycle += t;
    if (state == green and lastCycle >= cycle) {
        lastCycle -= cycle;
        ensureLastCycle -= cycle;
        setState(orange);
    }
    else if (state == orange and lastCycle >= cycle / 10.0) {
        lastCycle -= cycle / 10.0;
        ensureLastCycle -= cycle / 10.0;
        setState(red);
    }
    else if (state == red and lastCycle >= cycle) {
        lastCycle -= cycle;
        ensureLastCycle -= cycle;
        setState(green);
    }
    ENSURE(ensureLastCycle == lastCycle, "lastCycle is not right");
}







double Clock::getCycle() {
    REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling getCycle");
    ENSURE(cycle>0, "Cycle cannot be negative or zero");
    return cycle;
}


void Clock::setCycle(double c) {
    REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling setCycle");
    REQUIRE(c>0, "Cycle cannot be negative or zero");
    cycle = c;
    ENSURE(cycle == c,"Cycle hasn't changed");
}


double Clock::getLastCycle() {
    REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling getLastCycle");
    ENSURE(lastCycle>=0, "LastCycle cannot be negative");
    return lastCycle;
}


void Clock::setLastCycle(double c) {
    REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling setLastCycle");
    REQUIRE(c>=0, "LastCycle cannot be negative");
    lastCycle = c;
    ENSURE(lastCycle == c,"Lastcycle hasn't changed");
}


color Clock::getState() {
    REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling getState");
    ENSURE(state==green or state==red or state==orange, "Color does not exist ");
    return state;
}


void Clock::setState(color s) {
    REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling setState");
    REQUIRE(s==green or s==red or s==orange, "Color does not exist ");
    state = s;
    ENSURE(state == s,"State hasn't changed");
}




bool Clock::properlyInitialized () const{
    return _initCheck == this;
}

bool Clock::isvalid() const {
    if (!properlyInitialized()) {
        return false;
    }
    if (!(state == green or state == red or state == orange)) {
        return false;
    }
    if (lastCycle > cycle or lastCycle < 0) {
        return false;
    }
    return true;
}
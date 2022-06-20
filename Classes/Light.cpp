//============================================================================
// Name        : Light.cpp
// Date        : 18/06/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 4
//============================================================================

#include <cmath>
#include "Light.h"
#include "Car.h"
#include "Road.h"
#include "CarData.h"
#include "Clock.h"
#include "../Basic_Values.h"
#include "../DesignByContract.h"

Light::Light(double p, double c, Road* r, std::ofstream* error): Clock(c), error(error) {
    REQUIRE(r->isValidToAdd(p), "Light cannot be added");
    REQUIRE(c>=1, "Cycle is not valid");
    position = p;
    road = r;
    _initCheck = this;
    clock = true;
    ENSURE(this->properlyInitialized(), "constructor must end in properlyInitialized state");
}

Light::~Light() {}


void Light::updateLight(double t) {
    REQUIRE(isvalid(road), "Light wasn't initialized when calling updateLight");
    REQUIRE(t >= 0, "Time cannot be negative");
    if (clock) {
        updateClock(t);
    }
    std::vector<Car *> carsOnRoad = getRoad()->getCars();
    Car *firstCar = NULL;
    for (std::vector<Car *>::iterator itC = carsOnRoad.begin(); itC != carsOnRoad.end(); itC++) {
        if (!(*itC)->getData()->getpriority()) {//geen prioriteitsvoertuigen
            if ((*itC)->getDistance() < getPosition() - gStopDistance or (*itC)->getAction() != fast){
                if (firstCar == NULL or (*itC)->getDistance() > firstCar->getDistance()) {
                    firstCar = (*itC);
                }
            }
        }
    }
    if (firstCar != NULL) {
        if (getState() == green) {
            firstCar->setAction(fast);
        } else if (getState() == red or getState() == orange) {
            if ((firstCar->getDistance() + gStopDistance) > getPosition()) {
                if (getState() == red) {
                    firstCar->setAction(stop);
                }
            } else if ((firstCar->getDistance() + gBreakDistance) > getPosition()) {
                firstCar->setAction(slow);
            }
        }
    }
    ENSURE(isvalid(road), "Light wasn't initialized when calling updateLight");
}







/////////////

Road* Light::getRoad() {
    REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling getRoad");
    ENSURE(road->properlyInitialized(), "Road is not properly initialised");
    return road;
}


void Light::setRoad(Road *r) {
    REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling setRoad");
    REQUIRE(r->properlyInitialized(), "Road is not properly initialised");
    REQUIRE(r->isValid(), "Road is not valid");
    Light::road = r;
    ENSURE(road == r,"Road hasn't changed");
}


double Light::getPosition() {
    REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling getPosition");
    ENSURE(onRoad(), "Light is not on road");
    return position;
}


void Light::setPosition(double p) {
    REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling setPosition");
    REQUIRE(onRoad(p), "Light not on road");
    Light::position = p;
    ENSURE(position == p,"Position hasn't changed");
}


bool Light::getClock() {
    REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling getClock");
    ENSURE(clock >= 0.0, "Clock cannot be negative");
    return clock;
}


void Light::setClock(bool s) {
    REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling setState");
    REQUIRE(s >= 0.0, "Clock cannot be negative");
    clock = s;
    ENSURE(clock == s,"clock hasn't changed");
}
/////////////



//////////////

bool Light::properlyInitialized () const{
    return _initCheck == this;
}

bool Light::onRoad() const{
    if (position<0 or position>road->getLength()){
        return false;
    }
    return true;
}

bool Light::onRoad(int p) const{
    if (p<0 or p>road->getLength()){
        return false;
    }
    return true;
}

bool Light::isvalid(Road* r) const {
    if(!properlyInitialized()){
        return false;
    }
    if(!r->properlyInitialized()){
        return false;
    }
    if(road != r){
        return false;
    }
    if(!onRoad()){
        return false;
    }
    if (!Clock::isvalid()){
        return false;
    }
    return true;
}
//////////////
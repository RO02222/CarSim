//============================================================================
// Name        : Car_SimDomainTest.cpp
// Date        : 19/03/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 1
//============================================================================


#include "BusStop.h"
#include "Light.h"
#include "Car.h"
#include "Road.h"
#include "CarData.h"
#include "../Basic_Values.h"
#include "../DesignByContract.h"

BusStop::BusStop(double p, double s, Road *r) : timestopped(0), currentBus(NULL), bussy(false)  {
    REQUIRE(s>=1, "Time is not valid");
    REQUIRE(r->isValidToAdd(p), "Busstop cannot be added to the road");
    road = r;
    stoptime = s;
    position = p;
    _initCheck = this;
    ENSURE(this->properlyInitialized(), "constructor must end in properlyInitialized state");

}



void BusStop::updateBusStop(double t) {
    REQUIRE(isValid(road), "Busstop wasn't initialized when calling updateBusStop");
    REQUIRE(t > 0, "Time cannot be negative");
    REQUIRE(road->isvalidSimulation(), "part of the Simulation wasn't valid when calling updateBusStop");
    Action expectAction;
    bool expectBussy;
    Car* expectCurrentBus;
    double expectTimeStopped = timestopped;
    std::vector<Car *> carsOnRoad = getRoad()->getCars();
    Car *firstBus = NULL;
    for (std::vector<Car *>::iterator itC = carsOnRoad.begin(); itC != carsOnRoad.end(); itC++) {
        if ((*itC)->getData()->getType() == bus) {
            if ((*itC)->getDistance() < getPosition() - gStopDistance or (*itC)->getAction() != fast){
                if (firstBus == NULL or (*itC)->getDistance() > firstBus->getDistance()) {
                    firstBus = (*itC);
                }
            }
        }
    }
    if (firstBus == NULL) {
        bussy = false;
        return;
    }
    else {
        expectBussy = false;
        if (firstBus != currentBus) {
            bussy = false;
        }
        currentBus = firstBus;
        expectCurrentBus = firstBus;
        if (bussy) {
            timestopped += t;
            expectTimeStopped = timestopped;
            if (timestopped > stoptime) {
                currentBus->setAction(fast);
                expectAction = fast;
            }
            return;
        }
        if (currentBus->getDistance() + gBreakDistance < getPosition()) {
            expectAction = currentBus->getAction();
        } else if (currentBus->getDistance() + gStopDistance < getPosition()) {
            currentBus->setAction(slow);
            expectAction = slow;
        } else {
            currentBus->setAction(stop);
            expectAction = stop;
            if (currentBus->getSpeed() < 0.01) {
                bussy = true;
                expectBussy = true;
                timestopped = 0;
                expectTimeStopped = 0;
            }
        }
    }
    ENSURE(expectTimeStopped == timestopped, "time hasn't changed");
    ENSURE(expectBussy == bussy, "Bussy is not right");
    ENSURE(isValid(road), "Busstop isn't valid after calling updateBusStop");
    ENSURE(currentBus->getAction() == expectAction, "Action of current bus is not right");
    ENSURE(expectCurrentBus = currentBus, "CurrentBus is not valid");
}



/////////////

Road* BusStop::getRoad() {
    REQUIRE(this->properlyInitialized(), "BusStop wasn't initialized when calling getRoad");
    ENSURE(road->properlyInitialized(), "Road is not properly initialised");
    return road;
}


void BusStop::setRoad(Road *r) {
    REQUIRE(this->properlyInitialized(), "BusStop wasn't initialized when calling setRoad");
    REQUIRE(r->properlyInitialized(), "Road is not properly initialised");
    REQUIRE(r->isValid(),"Road isn't valid");
    BusStop::road = r;
    ENSURE(road == r,"Road hasn't changed");
}


double BusStop::getPosition() {
    REQUIRE(this->properlyInitialized(), "BusStop wasn't initialized when calling getPosition");
    ENSURE(onRoad(), "Busstop is not on road");
    return position;
}


void BusStop::setPosition(double p) {
    REQUIRE(this->properlyInitialized(), "BusStop wasn't initialized when calling setPosition");
    REQUIRE(onRoad(road, p), "Busstop is not on road");
    BusStop::position = p;
    ENSURE(position == p,"Position hasn't changed");
}


double BusStop::getStopTime() {
    REQUIRE(this->properlyInitialized(), "BusStop wasn't initialized when calling getStopTime");
    ENSURE(stoptime>=0, "stoptime cannot be negative");
    return stoptime;
}


double BusStop::getTimeStopped() {
    REQUIRE(this->properlyInitialized(), "BusStop wasn't initialized when calling getTimeStopped");
    ENSURE(timestopped>=0, "Timestopped cannot be negative");
    return timestopped;
}


bool BusStop::getbussy() {
    REQUIRE(this->properlyInitialized(), "BusStop wasn't initialized when calling getbussy");
    return bussy;
}


void BusStop::setbussy(bool b) {
    REQUIRE(this->properlyInitialized(), "BusStop wasn't initialized when calling setbussy");
    bussy = b;
    ENSURE(bussy==b, "Bussy hasn't changed");
}

/////////////



//////////////

bool BusStop::properlyInitialized () const{
    return _initCheck == this;
}

bool BusStop::onRoad() const {
    REQUIRE(road->properlyInitialized(), "Road wasn't initialized when calling onRoad");
    if (position < 0 or position > road->getLength()) {
        return false;
    }
    return true;
}

bool BusStop::onRoad(Road* r, int p) const{
    if (p<0 or p>r->getLength()){
        return false;
    }
    return true;
}


bool BusStop::isValid(Road* r) {
    if(!properlyInitialized()){
        return false;
    }
    if(!r->properlyInitialized()){
        return false;
    }
    if(road != r){
        return false;
    }
    if(position < gStopDistance){
        return false;
    }
    if(!onRoad()){
        return false;
    }
    if(stoptime < 1){
        return false;
    }
    if(timestopped < 0){
        return false;
    }
    return true;
}
//////////////
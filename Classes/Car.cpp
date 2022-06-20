//============================================================================
// Name        : Car.cpp
// Date        : 18/06/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 4
//============================================================================


#include "Car.h"
#include "CarData.h"
#include "../Basic_Values.h"
#include "../DesignByContract.h"
#include "Road.h"
#include "Junction.h"
#include <cmath>

Car::Car(double d, CarData* da, Road* r) : acceleration(0), action(fast){
    REQUIRE(da->properlyInitialized(), "Data is not valid");
    REQUIRE(onRoad(d,r), "Car is not on road");
    REQUIRE(r->isValid(), "Road is not valid");
    road = r;
    distance = d;
    _initCheck = this;
    data = da;
    speed = data->getvMax();
    maxSpeed = data->getvMax();
    ENSURE(properlyInitialized(),"constructor must end in properlyInitialized state");
}


bool Car::updateCar(double t, bool onJunction) {
    REQUIRE(isValid(road), "Car is not valid");
    REQUIRE(t >= 0, "Time cannot be negative");
    REQUIRE(road->isvalidSimulation(), "Road of the simulation is not valid");
    bool returnValue = true;
    double ensurePos;
    double ensureSpeed;
    double ensureMaxSpeed = maxSpeed;
    double ensureAcceleration;
    if (getAction() == fast) {
        maxSpeed = data->getvMax();
        ensureMaxSpeed = maxSpeed;
    } else if (getAction() == slow) {
        maxSpeed = gSlowFactor * data->getvMax();
        ensureMaxSpeed = maxSpeed;
        if (maxSpeed > 15) {
            maxSpeed = 15;
            ensureMaxSpeed = 15;
        }
    }
    double v0 = getSpeed();

    double a;
    if (getAction() != stop) {
        std::vector<Car *> carsOnRoad = getRoad()->getCars();
        Car *nextCar = NULL;
        for (std::vector<Car *>::iterator itC = carsOnRoad.begin(); itC != carsOnRoad.end(); itC++) {
            if ((*itC)->getDistance() > this->getDistance()) {
                if (nextCar == NULL or (*itC)->getDistance() < nextCar->getDistance()) {
                    nextCar = (*itC);
                }
            }
        }
        double delta = 0.0;
        if (nextCar == NULL) {
            delta = 0.0;
        } else {
            double dx = nextCar->getDistance() - getDistance() - nextCar->data->getlength();
            double dv = getSpeed() - nextCar->getSpeed();
            delta = (data->getfMin() +
                     std::max(0.0, v0 + ((v0 * dv) / (2 * sqrt(data->getaMax() * data->getbMax()))))) / dx;
        }
        a = (data->getaMax()) * (1.0 - (pow(v0 / getMaxSpeed(), 4)) - pow(delta, 2));
    } else {
        a = -(data->getbMax() * v0) / getMaxSpeed();
    }
    setAcceleration(a);
    ensureAcceleration = a;
    double v1 = v0 + a * t;
    if (v1 < 0) {
        distance = distance - pow(v0, 2) / (2 * a);
        ensurePos = distance;
        setSpeed(0);
        ensureSpeed = 0;
    } else {
        setSpeed(v1);
        ensureSpeed = v1;
        distance = distance + v0 * t + a * (pow(t, 2) / 2.0);
        ensurePos = distance;

    }

        //near Junction
    if (!onJunction) {
        std::vector<std::pair<Junction *, double *> > junctions = road->getJunctions();
        for (unsigned int i = 0; i < junctions.size(); i++) {
            if (std::abs(distance - *junctions[i].second) <= gStopDistance) {
                junctions[i].first->addCar(this);
            }
        }
        //car off the road
        if (!onRoad()) {
            returnValue = false;
        }
    }
    ENSURE(ensureMaxSpeed == maxSpeed, "MaxSpeed is not right");
    ENSURE(ensureAcceleration == acceleration, "Acceleration is not right");
    ENSURE(ensureSpeed == speed, "speed is not right");
    ENSURE(ensurePos == distance, "Position is not right");
    return returnValue;
}


void Car::moveCar(Road *r, double position) {
    REQUIRE(this->properlyInitialized(), "Car is not properly initialised");
    REQUIRE(r->properlyInitialized(), "Road is not properly initialised");
    REQUIRE(r->isValid(), "road isn't valid");
    REQUIRE(position>=0 and position<=r->getLength(), "Car is not on road");
    road->removeCar(this);
    road = r;
    distance = position;
    road->addCar(this);
    bool added = road->getCars()[road->getCars().size()-1] == this;
    ENSURE(this->getDistance() == position, "position hasn't changed");
    ENSURE(road==r, "Road hasn't changed");
    ENSURE(added, "Car is not added to the new road");
}








//////////////

Road *Car::getRoad() const {
    REQUIRE(this->properlyInitialized(), "Car wasn't initialized when calling getRoad");
    ENSURE(road->properlyInitialized(), "Road is not properly initialised");
    return road;
}


void Car::setRoad(Road *r) {
    REQUIRE(this->properlyInitialized(), "Car wasn't initialized when calling setRoad");
    REQUIRE(r->properlyInitialized(), "Road is not properly initialised");
    REQUIRE(r->isValid(),"Road isn't valid");
    Car::road = r;
    ENSURE(road == r,"Road hasn't changed");
}


double Car::getDistance() {
    REQUIRE(this->properlyInitialized(), "Car wasn't initialized when calling getDistance");
    ENSURE(onRoad(), "Car is not on road");
    return distance;
}

double Car::getDistanceNV() {
    REQUIRE(this->properlyInitialized(), "Car wasn't initialized when calling getDistance");
    ENSURE(distance>=0, "Distance cannot be negative");
    return distance;
}


void Car::setDistance(double d) {
    REQUIRE(this->properlyInitialized(), "Car wasn't initialized when calling setDistance");
    REQUIRE(onRoad(d,road), "Car not on road");
    Car::distance = d;
    ENSURE(distance == d,"Distance hasn't changed");
}


double Car::getSpeed() {
    REQUIRE(this->properlyInitialized(), "Car wasn't initialized when calling getSpeed");
    ENSURE(speed>=0, "Speed cannot be negative");
    return speed;
}


void Car::setSpeed(double s) {
    REQUIRE(this->properlyInitialized(), "Car wasn't initialized when calling setSpeed");
    REQUIRE(s>=0, "Speed can not be negative");
    Car::speed = s;
    ENSURE(speed == s,"Speed hasn't changed");
}


double Car::getMaxSpeed() {
    REQUIRE(this->properlyInitialized(), "Car wasn't initialized when calling getMaxSpeed");
    ENSURE(maxSpeed>=0, "Maxspeed cannot be negative");
    return maxSpeed;
}


void Car::setMaxSpeed(double s) {
    REQUIRE(this->properlyInitialized(), "Car wasn't initialized when calling setMaxSpeed");
    REQUIRE(s>=0, "Speed can not be negative");
    Car::maxSpeed = s;
    ENSURE(maxSpeed == s, "Maxspeed hasn't changed");
}


double Car::getAcceleration() {
    REQUIRE(this->properlyInitialized(), "Car wasn't initialized when calling getAcceleration");
    return acceleration;
}


void Car::setAcceleration(double a) {
    REQUIRE(this->properlyInitialized(), "Car wasn't initialized when calling setAcceleration");
    Car::acceleration = a;
    ENSURE(acceleration == a,"Acceleration hasn't changed");
}


Action Car::getAction() {
    REQUIRE(this->properlyInitialized(), "Car wasn't initialized when calling getAction");
    ENSURE(action == fast or action == slow or action == stop, "This action does not exist");
    return action;
}


void Car::setAction(Action a) {
    REQUIRE(this->properlyInitialized(), "Car wasn't initialized when calling setAction");
    REQUIRE(a==fast or a==slow or a==stop, "action does not exist");
    Car::action = a;
    ENSURE(action == a,"Action hasn't changed");
}


CarData* Car::getData() {
    REQUIRE(this->properlyInitialized(), "Car wasn't initialized when calling getData");
    ENSURE(data->properlyInitialized(), "The data is not properly initialised");
    return data;
}
//////////////



//////////////

bool Car::properlyInitialized() const{
    return _initCheck == this;
}
bool Car::onRoad() const{
    REQUIRE(road->properlyInitialized(),"Road wasn't initialized when calling onRoad");
    if (distance<0 or distance>road->getLength()){
        return false;
    }
    return true;
}

bool Car::onRoad(int d, Road* r) const{
    if (d<0 or d> r->getLength()){
        return false;
    }
    return true;
}

bool Car::isValid(Road* r) const {
    if (!properlyInitialized()){
        return false;
    }
    if(!r->properlyInitialized()){
        return false;
    }
    if(road != r){
        return false;
    }
    if (!(onRoad())){
        return false;
    }
    if(speed <0){
        return false;
    }
    if (action != slow and action != fast and action != stop){
        return false;
    }
    if(!data->properlyInitialized()){
        return false;
    }
    return true;
}


//////////////
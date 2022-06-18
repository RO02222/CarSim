//============================================================================
// Name        : Junction.cpp
// Date        : 18/06/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 4
//============================================================================

#include <cmath>

#include <fstream>
#include "Junction.h"
#include "Car.h"
#include "Road.h"
#include "Light.h"
#include "World.h"
#include "Clock.h"
#include "../Basic_Values.h"
#include "../DesignByContract.h"
#include "../Functions.h"

Junction::Junction(std::vector<std::pair<Road*, double> > r, std::ofstream* error) : error(error){
    REQUIRE(isvalid(roads), "Roads to form the junction are not valid");
    roads = r;
    _initCheck = this;
    for (unsigned int i = 0; i < roads.size(); i++){
        roads[i].first->addJunction(std::pair<Junction*,double*> (this,&this->roads[i].second));
    }
    ENSURE(this->properlyInitialized(), "constructor must end in properlyInitialized state");
}

Junction::~Junction() {
    if (lights.size() > 1){
        delete clock;
    }
}


void Junction::updateJunction(double t) {
    REQUIRE(this->properlyInitialized(), "Junction wasn't initialized when calling updateJunction");
    REQUIRE(t>=0, "Time cannot be negative");
    unsigned int ensureNumlight = numLight;
    for (unsigned int i = 0; i < cars.size(); i++) {
        double oldPos = cars[i]->getDistance();
        cars[i]->updateCar(t, true);
        for (unsigned int j = 0; j < roads.size(); j++) {
            if (roads[j].first == cars[i]->getRoad()) {
                //move car
                if (oldPos < roads[j].second and cars[i]->getDistanceNV() >= roads[j].second) {
                    unsigned int x = rand() % roads.size();
                    while (roads[x].first->getLength() == roads[x].second) {

                        x = rand() % roads.size();
                    }
                    if (x != j) {
                        double newPos = cars[i]->getDistanceNV() - roads[j].second + roads[x].second;
                        cars[i]->moveCar(roads[x].first, newPos);
                        break;
                    }
                }
                //check if car is still near
                if (std::abs(cars[i]->getDistance() - roads[j].second) <= gStopDistance) {
                    break;
                }
            }
        }
        if (!cars[i]->onRoad()){
            cars[i]->getRoad()->removeCar(cars[i], true);
        }
    }
    cars.clear();
    //update lights
    if (lights.size() != 0) {
        clock->updateClock(t);
        lights[numLight]->setState(clock->getState());
        if (clock->getState() == red) {
            clock->setState(green);
            numLight = (numLight + 1)%lights.size();
            ensureNumlight = numLight;
            lights[numLight]->setState(clock->getState());
        }
    }
    ENSURE(isValid(),"Junction isn't valid");
    ENSURE(cars.empty(), "There are still cars that needs to be updated");
    ENSURE(ensureNumlight == numLight, "NumLight is not right");
}


void Junction::addCar(Car *car) {
    REQUIRE(this->properlyInitialized(), "Junction wasn't initialized when calling addCar");
    REQUIRE(car->properlyInitialized(), "Car is not properly initialised");
    cars.push_back(car);
    ENSURE(cars[cars.size()-1] == car, "Car is not added");
}

void Junction::checkJunctionLights() {
    REQUIRE(this->properlyInitialized(), "Junction is not properly initialised");
    double cycle = 0;
    std::vector<Light*> light;
    for (std::vector<std::pair<Road*,double> >::iterator itR = roads.begin(); itR != roads.end(); itR++){
        if ((*itR).second == 0){
            continue;
        }
        std::vector<Light*> L = (*itR).first->getLights();
        bool lightOnRoad = false;
        for (std::vector<Light*>::iterator itL = L.begin();itL != L.end(); itL++){
            if ((*itL)->getPosition() == (itR->second)){
                if (cycle == 0){
                    cycle = (*itL)->getCycle();
                }
                lightOnRoad = true;
                light.push_back(*itL);
                break;
            }
        }
        if (!lightOnRoad){
            return;
        }
    }
    if (cycle == 0 or light.size() < 2){
        return;
    }
    lights = light;
    clock = new Clock(cycle);
    clock->setState(green);
    numLight = 0;
    for (std::vector<Light*>::iterator itL = lights.begin(); itL != lights.end(); itL++){
        (*itL)->setClock(false);
        (*itL)->setState(red);
    }
    lights[numLight]->setState(clock->getState());
}


/////////////

Road* Junction::getRoad(int n) {
    REQUIRE(this->properlyInitialized(), "Junction wasn't initialized when calling getRoad");
    ENSURE(roads[n].first->properlyInitialized(), "Road is not properly initialised");
    return roads[n].first;
}


std::vector<Car*> Junction::getCars() {
    REQUIRE(this->properlyInitialized(), "Junction wasn't initialized when calling getCars");
    bool checkProperly = true;
    for(unsigned int i=0; i<cars.size(); i++){
        if(!cars[i]->properlyInitialized()){
            checkProperly = false;
        }
    }
    ENSURE(checkProperly == true, "A car is not properly initialised");
    return cars;
}


void Junction::setRoad(Road *r,unsigned int n) {
    REQUIRE(this->properlyInitialized(), "Junction wasn't initialized when calling setRoad");
    REQUIRE(r->properlyInitialized(), "Road is not properly initialised");
    REQUIRE(r->isValid(), "Road isn't valid");
    REQUIRE(n>=0, "The number of the road cannot be negative");
    REQUIRE(n<=roads.size(), "there aren't that many roads");
    roads[n].first = r;
    ENSURE(roads[n].first == r, "Road hasn't changed");
}


double Junction::getPosition(int n) {
    REQUIRE(this->properlyInitialized(), "Junction wasn't initialized when calling getPosition");
    ENSURE(onRoad(n), "Junction is not on road");
    return roads[n].second;
}


double Junction::getPosition(std::string roadname) {
    REQUIRE(this->properlyInitialized(), "Junction wasn't initialized when calling getPosition");
    REQUIRE(onRoad(roadname), "Junction not on road");
    for (std::vector<std::pair<Road*,double> >::iterator x = roads.begin(); x != roads.end(); x++){
        if (x->first->getName() == roadname){
            return x->second;
        }
    }
    return roads[0].second;
}


void Junction::setPosition(double p,unsigned int n) {
    REQUIRE(this->properlyInitialized(), "Junction wasn't initialized when calling setPosition");
    REQUIRE(n<roads.size(), "There aren't that many roads");
    REQUIRE(p>=0 and p<roads[n].first->getLength(), "junction is not on the road");
    roads[n].second = p;
    ENSURE(roads[n].second == p, "Position hasn't changed");
}


Clock* Junction::getClock() {
    REQUIRE(this->properlyInitialized(), "Junction wasn't initialized when calling getClock");
    ENSURE(clock->properlyInitialized(), "clock is not initialized");
    return clock;
}


void Junction::setClock(Clock *c) {
    REQUIRE(this->properlyInitialized(), "Junction wasn't initialized when calling setClock");
    REQUIRE(c->isvalid(), "clock is not valid");
    clock = c;
    ENSURE(clock == c, "clock hasn't changed");
}

std::vector<std::pair<Road* , double> > Junction::getRoads(){
    REQUIRE(this->properlyInitialized(), "Junction wasn't initialized when calling getRoads");
    bool checkProperly = true;
    bool checkOnRoad = true;
    for(unsigned int i=0; i<roads.size(); i++){
        if(!roads[i].first->properlyInitialized()){
            checkProperly = false;
        }
        if(roads[i].second <0 or roads[i].second>roads[i].first->getLength()){
            checkOnRoad = false;
        }
    }
    ENSURE(checkProperly == true, "Road on junction is not properly initialised");
    ENSURE(checkOnRoad == true, "Junction is not on road");
    return roads;
}

/////////////



//////////////
bool Junction::properlyInitialized() const{
    return _initCheck == this;
}

bool Junction::onRoad(long unsigned int n) const{
    REQUIRE(this->properlyInitialized(),"Road wasn't initialized when calling onRoad");
    REQUIRE(n>=0 and n<roads.size(), "There aren't that many roads");
    if (roads[n].second<0 or roads[n].second>roads[n].first->getLength()){
        return false;
    }
    return true;
}

bool Junction::onRoad(std::string roadname){
    REQUIRE(this->properlyInitialized(),"Road wasn't initialized when calling onRoad");
    for (std::vector<std::pair<Road*,double> >::iterator x = roads.begin(); x != roads.end(); x++){
        if (x->first->getName() == roadname){
            if(x->second<0 or x->second>x->first->getLength()){
                return false;
            }
        }
    }
    return true;
}

bool Junction::isValid() const {
    if (!properlyInitialized()){
        return false;
    }
    std::vector<std::pair<Road *, double> > RoadIt = roads;
    for (std::vector<std::pair<Road*, double> >::iterator itR = RoadIt.begin(); itR != RoadIt.end(); itR++) {
        if (!itR->first->properlyInitialized()) {
            return false;
        }
        if(itR->second < 0 or itR->second > itR->first->getLength()){
            return false;
        }
    }
    std::vector<Car*> CarIt = cars;
    for (std::vector<Car*>::iterator itC = CarIt.begin(); itC != CarIt.end(); itC++) {
        if(!(*itC)->properlyInitialized()) {
            return false;
        }
    }
    if (lights.size() > 1 and !clock->isvalid()){
        return false;
    }
    return true;
}
//////////////
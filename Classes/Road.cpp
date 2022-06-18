//============================================================================
// Name        : Road.cpp
// Date        : 18/06/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 4
//============================================================================

#include <cmath>
#include "Road.h"
#include "Light.h"
#include "Car.h"
#include "CarGen.h"
#include "CarData.h"
#include "BusStop.h"
#include "Junction.h"
#include "../DesignByContract.h"
#include "../Basic_Values.h"

Road::Road(const std::string &name, double l, std::ofstream* error) : error(error), name(name)  {
    REQUIRE(l>=gStopDistance, "Road is not long enough");
    length = l;
    _initCheck = this;
    ENSURE(properlyInitialized(),"constructor must end in properlyInitialized state");
}

Road::~Road() {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling ~Road");
    std::vector<Car *> carIt = getCars();
    for (std::vector<Car *>::iterator itC = carIt.begin(); itC != carIt.end(); itC++) {
        delete(*itC);
    }
    std::vector<Light *> lightIt = getLights();
    for (std::vector<Light *>::iterator itL = lightIt.begin(); itL != lightIt.end(); itL++) {
        delete(*itL);
    }
    std::vector<CarGen *> carGenIt = getCarGen();
    for (std::vector<CarGen *>::iterator itG = carGenIt.begin(); itG != carGenIt.end(); itG++) {
        delete(*itG);
    }
    std::vector<BusStop *> busStopIt = getBusStops();
    for (std::vector<BusStop *>::iterator itB = busStopIt.begin(); itB != busStopIt.end(); itB++) {
        delete(*itB);
    }
}


void Road::updateRoad(double t) {
    REQUIRE(properlyInitialized(), "Road wasn't initialized when calling updateRoad");
    REQUIRE(t>=0, "Time cannot be negative");
    std::vector<Car *> carIt = getCars();
    for (std::vector<Car *>::iterator itC = carIt.begin(); itC != carIt.end(); itC++) {
        bool update = true;
        for (unsigned int i = 0; i < junctions.size(); i++) {
            if (std::abs((*itC)->getDistance() - *junctions[i].second) <= gStopDistance) {
                update = false;
                junctions[i].first->addCar(*itC);
                break;
            }
        }
        if (update) {
            if (!(*itC)->updateCar(t)){
                removeCar((*itC),true);
            }
        }
    }
    std::vector<Light *> lightIt = getLights();
    for (std::vector<Light *>::iterator itL = lightIt.begin(); itL != lightIt.end(); itL++) {
        (*itL)->updateLight(t);
    }
    std::vector<CarGen *> carGenIt = getCarGen();
    for (std::vector<CarGen *>::iterator itG = carGenIt.begin(); itG != carGenIt.end(); itG++) {
        (*itG)->updateCarGen(t);
    }
    for (std::vector<BusStop *>::iterator itB = busStops.begin(); itB != busStops.end(); itB++) {
        (*itB)->updateBusStop(t);
    }
    ENSURE(isvalidSimulation(), "Part of the simulation isn't valid");
}


void Road::removeCar(Car* car, bool del) {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling removeCars");
    REQUIRE(car->properlyInitialized(), "car wasn't properly initialised");
    std::vector<Car *> carIt = getCars();
    for (unsigned int i = 0; i<cars.size();i++) {
        if (cars[i] == car){
            cars.erase(cars.begin()+i);
            break;
        }
    }
    if (del){
        delete car;
    }
    ENSURE(!findCar(car),"Car is not deleted");
}

/////////////

void Road::addLight(double position, double cycle) {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling addLight");
    REQUIRE(isValidToAdd(position),"Light cannot be added");
    REQUIRE(cycle>=1, "Cycle is not valid");
    Light* l = new Light(position, cycle,this, error);
    lights.push_back(l);
    ENSURE(true, "Light is not added");
}

void Road::addCar(double distance, CarData* data) {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling addCar");
    if (distance > getLength() or distance < 0) {
        *error<<"Failed to add car: position is not on the road"<<std::endl;
        return;
    }
    Car* c = new Car (distance, data, this);
    Road::cars.push_back(c);
    ENSURE(c==Road::cars[Road::cars.size()-1], "Car is not added");
}

void Road::addCar(Car *car) {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling addCar");
    cars.push_back(car);
    car->setRoad(this);
    ENSURE(cars[cars.size()-1] == car, "Car is not added");
    ENSURE(car->getRoad() == this, "Road hasn't changed");
}

void Road::addCarGen(double frequency, CarData* data) {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling addCarGen");
    if (frequency < 1){
        frequency = 1;
    }
    CarGen* cg = new CarGen(frequency, this, data);
    carGen.push_back(cg);
    ENSURE(carGen[carGen.size()-1] == cg, "Cargen is not added");
}

void Road::addCarGen(double frequency, std::vector<CarData*>* allData) {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling addCarGen");
    if (frequency < 1){
        frequency = 1;
    }
    CarGen* cg = new CarGen(frequency, this, allData);
    carGen.push_back(cg);
    ENSURE(carGen[carGen.size()-1] == cg, "Cargen is not added");
}


void Road::addBusStop(double position, double stoptime) {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling addCarGen");
    if (stoptime < 1){
        stoptime = 1;
    }
    if (position > getLength() or position < 0) {
        *error<<"Failed to add BusStop: position is not on the road"<<std::endl;
        return;
    }
    BusStop* b = new BusStop(position, stoptime, this);
    busStops.push_back(b);
    ENSURE(busStops[busStops.size()-1] == b, "Busstop is not added");
}


void Road::addJunction(std::pair<Junction*, double*> junction) {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling addJuction");
    if (*junction.second > getLength() or *junction.second < 0) {
        *error<<"Failed to add Junction: position is not on the road"<<std::endl;
        return;
    }
    junctions.push_back(junction);
    ENSURE(junctions[junctions.size()-1] == junction, "Junction is not added");
}
/////////////



/////////////

const std::string &Road::getName() {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling getName");
    return name;
}


void Road::setName(const std::string &n) {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling setName");
    Road::name = n;
    ENSURE(name == n,"Name hasn't changed");
}


double Road::getLength() {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling getLength");
    ENSURE(length>0, "length of a road cannot be negative");
    return length;
}


void Road::setLength(double l) {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling setLength");
    REQUIRE(l>0, "length of a road cannot be negative");
    Road::length = l;
    ENSURE(length == l,"Length hasn't changed");
}


const std::vector<Light *> &Road::getLights() {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling getLights");
    ENSURE(lightsProperly(lights) == true, "A Light is not initialised");
    return lights;
}


void Road::setLights(const std::vector<Light *> &l) {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling setLights");
    REQUIRE(lightsProperly(l) == true, "Light is not initialised");
    Road::lights = l;
    ENSURE(lights == l,"Lights hasn't changed");
}


const std::vector<Car *> &Road::getCars() {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling getCars");
    ENSURE(carsProperly(cars), "A car is not initialised");
    return cars;
}


void Road::setCars(const std::vector<Car *> &c) {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling setCars");
    REQUIRE(carsProperly(c), "A car is not initialised");
    Road::cars = c;
    ENSURE(cars == c,"Cars hasn't changed");
}


const std::vector<CarGen *> &Road::getCarGen()  {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling getCarGen");
    ENSURE(carGenProperly(carGen), "CarGen is not initialised");
    return carGen;
}


void Road::setCarGen(const std::vector<CarGen *> &carGens) {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling setCarGen");
    REQUIRE(carGenProperly(carGens), "CarGen is not initialised");
    Road::carGen = carGens;
    ENSURE(Road::carGen == carGens,"carGen hasn't changed");
}

const std::vector<BusStop *> &Road::getBusStops() {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling getBusStops");
    ENSURE(busStopProperly(busStops), "A busstop is not initialised");
    return busStops;
}


void Road::setbusStops(const std::vector<BusStop *> &BusStops) {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling setBusStops");
    REQUIRE(busStopProperly(BusStops), "A busstop is not initialised");
    Road::busStops = BusStops;
    ENSURE(Road::busStops == BusStops,"busStops hasn't changed");
}


const std::vector<std::pair<Junction *, double *> > &Road::getJunctions() {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling getJunctions");
    ENSURE(junctionsValid(junctions), "Junction is not valid");
    return junctions;
}


void Road::setJunctions(const std::vector<std::pair<Junction *, double *> > &Junctions) {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling setJunctions");
    REQUIRE(goodJuntion(Junctions), "Junction is not good");
    Road::junctions = Junctions;
    ENSURE(Road::junctions == Junctions,"Junctions hasn't changed");
}
/////////////



//////////////
bool Road::properlyInitialized() const{
    return _initCheck == this;
}

bool Road::onRoad(double p) const{
    if (p < 0 or p > length){
        return false;
    }
    return true;
}

bool Road::isValid() const{
    if (!properlyInitialized()){
        return false;
    }
    if (name.size() <= (unsigned int) 0){
        return false;
    }
    if (length <= (unsigned int) 0){
        return false;
    }
    return true;
}


bool Road::isValidToAdd(double position) const {
    if (!isValid()){
        return false;
    }
    if (position < gStopDistance or !onRoad(position)){
        return false;
    }
    std::vector<Light*> light = lights;
    for (std::vector<Light*>::iterator itL = light.begin(); itL != light.end(); itL++){
        if (!(*itL)->properlyInitialized()){
            return false;
        }
        if (std::abs((*itL)->getPosition() - position) < gSlowFactor){
            return false;
        }
    }
    std::vector<BusStop*> busstop = busStops;
    for (std::vector<BusStop*>::iterator itB = busstop.begin(); itB != busstop.end(); itB++){
        if (!(*itB)->properlyInitialized()){
            return false;
        }
        if (std::abs((*itB)->getPosition() - position) < gSlowFactor){
            return false;
        }
    }
    return true;
}

bool Road::isValidToAddCar(double position, double len) const {
    if (!isValid()){
        return false;
    }
    if (!onRoad(position)){
        return false;
    }

    std::vector<Car *> carsOnRoad = cars;
    for (std::vector<Car *>::iterator itC = carsOnRoad.begin(); itC != carsOnRoad.end(); itC++) {
        if (position < (*itC)->getDistance()){
            if (position + (*itC)->getData()->getlength() *2 > (*itC)->getDistance()) {
                return false;
            }
        } else{
            if (position - len * 2 < (*itC)->getDistance()) {
                return false;
            }
        }
    }
    return true;
}


bool Road::isvalidSimulation(){
    if (!isValid()){
        return false;
    }
    std::vector<Car *> carIt = getCars();
    for (std::vector<Car *>::iterator itC = carIt.begin(); itC != carIt.end(); itC++) {
        if (!(*itC)->isValid(this)){
            return false;
        };
    }
    std::vector<Light *> lightIt = getLights();
    for (std::vector<Light *>::iterator itL = lightIt.begin(); itL != lightIt.end(); itL++) {
        if(!(*itL)->isvalid(this)){
            return false;
        };
    }
    std::vector<CarGen *> carGenIt = getCarGen();
    for (std::vector<CarGen *>::iterator itG = carGenIt.begin(); itG != carGenIt.end(); itG++) {
        if(!(*itG)->isValid(this)){
            return false;
        }
    }
    std::vector<BusStop *> busStopIt = getBusStops();
    for (std::vector<BusStop *>::iterator itB = busStopIt.begin(); itB != busStopIt.end(); itB++) {
        if(!(*itB)->isValid(this)){
            return false;
        }
    }
    return true;
}

bool Road::findCar(Car *car) {
    if (car == NULL){
        return true;
    }
    std::vector<Car*> c = cars;
    for (std::vector<Car*>::iterator itC = c.begin(); itC != c.end(); itC++){
        if (*itC == car){
            return true;
        }
    }
    return false;
}

bool Road::findLight(Light *light) {
    if (light == NULL){
        return true;
    }
    std::vector<Light*> l = lights;
    for (std::vector<Light*>::iterator itC = l.begin(); itC != l.end(); itC++){
        if (*itC == light){
            return true;
        }
    }
    return false;
}

bool Road::lightsProperly(std::vector<Light *> l) {
    bool checkProperly = true;
    for(unsigned int i=0; i<l.size(); i++){
        if(!l[i]->properlyInitialized()){
            checkProperly = false;
            break;
        }
    }
    return checkProperly;
}

bool Road::carsProperly(std::vector<Car *> c) {
    bool check = true;
    for(unsigned int i=0; i<c.size(); i++){
        if(!c[i]->properlyInitialized()){
            check = false;
            break;
        }
    }
    return check;
}

bool Road::carGenProperly(std::vector<CarGen *> cG) {
    bool check = true;
    for(unsigned int i=0; i<cG.size(); i++){
        if(!cG[i]->properlyInitialized()){
            check = false;
            break;
        }
    }
    return check;
}

bool Road::busStopProperly(std::vector<BusStop *> bS) {
    bool check = true;
    for(unsigned int i=0; i<bS.size(); i++){
        if(!bS[i]->properlyInitialized()){
            check = false;
            break;
        }
    }
    return check;
}

bool Road::junctionsValid(std::vector<std::pair<Junction *, double *> > j) {
    bool check = true;
    for(unsigned int i=0; i<j.size(); i++){
        if(!j[i].first->isValid()){
            check = false;
            break;
        }
    }
    return check;
}

bool Road::goodJuntion(std::vector<std::pair<Junction *, double *> > j) {
    bool check = true;
    for(unsigned int i=0; i<j.size(); i++){
        if(!j[i].first->properlyInitialized() or *j[i].second <= 0.0 or *j[i].second>=this->getLength()){
            check = false;
            break;
        }
    }
    return check;
}
//////////////
//============================================================================
// Name        : CarGen.cpp
// Date        : 18/06/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 4
//============================================================================

#include <stdlib.h>
#include <cmath>
#include "CarGen.h"
#include "Road.h"
#include "Car.h"
#include "CarData.h"
#include "Junction.h"
#include "../DesignByContract.h"
#include "../Functions.h"

CarGen::CarGen(double f, Road *r, CarData *da) : random(false), AllData(NULL) {
    REQUIRE(f>=1, "Frequency is not valid");
    REQUIRE(da->properlyInitialized(), "Data is not valid");
    REQUIRE(isValidToAdd(r), "Road is not valid to be added");
    data = da;
    _initCheck = this;
    frequency = f;
    lastCycle = rand() % lround(frequency);
    road = r;
    ENSURE(properlyInitialized(),"constructor must end in properlyInitialized state");
}

CarGen::CarGen(double f, Road *r, std::vector<CarData *>* da)  :  random(true), data(NULL) {
    REQUIRE(f>=1, "Frequency is not valid");
    REQUIRE(isvalid(da), "AllData is not valid");
    REQUIRE(isValidToAdd(r), "Road is not valid to be added");
    _initCheck = this;
    AllData = da;
    road = r;
    data = (*AllData)[0];
    frequency = f;
    lastCycle = f;
    ENSURE(properlyInitialized(),"constructor must end in properlyInitialized state");
}


void CarGen::updateCarGen(double t) {
    REQUIRE(isValid(road), "CarGen wasn't initialized when calling updateCarGen");
    REQUIRE(t >= 0, "Time cannot be negative");
    REQUIRE(isValidData(), "Not all data is valid");
    double ensureLastcycle = lastCycle;
    Car* ensureNewCar = NULL;
    CarData* ensureData = data;
    lastCycle += t;
    ensureLastcycle = lastCycle;
    if (lastCycle >= frequency) {
        lastCycle = std::fmod(lastCycle, frequency);
        ensureLastcycle = lastCycle;
        if (random) {
            unsigned int v1 = rand() % 10;
            if (v1 < 6) {
                data = (*AllData)[v1];
                ensureData = data;
            } else {
                for (std::vector<CarData *>::iterator alldata = (*AllData).begin();
                     alldata != (*AllData).end(); alldata++) {
                    if ((*alldata)->getType() == car) {
                        data = *alldata;
                        ensureData = data;
                        continue;
                    }
                }
            }
            if (data == NULL) {
                data = (*AllData)[0];
                ensureData = data;
            }
        }
        std::vector<Car *> carsOnRoad = getRoad()->getCars();
        if (road->isValidToAddCar(0,data->getlength())){
            getRoad()->addCar(0, data);
            ensureNewCar = getRoad()->getCars()[getRoad()->getCars().size()-1];
        }
    }

    ENSURE(ensureLastcycle == lastCycle, "LatCycle is not right");
    ENSURE(ensureData == data, "Data is not right");
    ENSURE(road->findCar(ensureNewCar),"New car cannot be found");
}





/////////////

Road *CarGen::getRoad() {
    REQUIRE(this->properlyInitialized(), "CarGen wasn't initialized when calling getRoad");
    ENSURE(road->properlyInitialized(), "Road is not properly initialised");
    return road;
}


void CarGen::setRoad(Road *r) {
    REQUIRE(this->properlyInitialized(), "CarGen wasn't initialized when calling setRoad");
    REQUIRE(r->properlyInitialized(), "Road is not properly initialised");
    REQUIRE(r->isValid(), "Road isn't valid");
    CarGen::road = r;
    ENSURE(road == r,"Road hasn't changed");
}


double CarGen::getFrequency() {
    REQUIRE(this->properlyInitialized(), "CarGen wasn't initialized when calling getFrequency");
    ENSURE(frequency>0, "Frequency cannot be negative or zero");
    return frequency;
}


void CarGen::setFrequency(double f) {
    REQUIRE(this->properlyInitialized(), "CarGen wasn't initialized when calling setFrequency");
    REQUIRE(f>0, "frequency cannot be negative or zero");
    CarGen::frequency = f;
    ENSURE(frequency == f,"Road hasn't changed");
}


double CarGen::getCycle() {
    REQUIRE(this->properlyInitialized(), "CarGen wasn't initialized when calling getCycle");
    ENSURE(lastCycle>=0, "Lastcycle cannot be negative");
    return lastCycle;
}


void CarGen::setCycle(double c) {
    REQUIRE(this->properlyInitialized(), "CarGen wasn't initialized when calling setCycle");
    REQUIRE(c>=0, "Lastcycle cannot be negative");
    CarGen::lastCycle = c;
    ENSURE(lastCycle == c,"Road hasn't changed");
}

CarData* CarGen::getData() {
    REQUIRE(this->properlyInitialized(), "CarGen wasn't initialized when calling getCycle");
    ENSURE(data->properlyInitialized(), "The data is not properly initialised");
    return data;
}
/////////////



//////////////

bool CarGen::properlyInitialized() const{
    return _initCheck == this;
}

bool CarGen::isValid(Road* r) const{
    if (!properlyInitialized()){
        return false;
    }
    if (!r->properlyInitialized()){
        return false;
    }
    if(road != r){
        return false;
    }
    if(frequency < 1){
        return false;
    }
    if(lastCycle > frequency){
        return false;
    }
    if(lastCycle < 0){
        return false;
    }
    if(data != NULL and !data->properlyInitialized()){
        return false;
    }
    return true;
}

bool CarGen::isValidToAdd(Road *r) const {
    std::vector<std::pair<Junction*, double*> > junction = r->getJunctions();
    for (std::vector<std::pair<Junction*,double*> >::iterator itJ = junction.begin(); itJ != junction.end(); itJ++){
        if (*(itJ->second) == 0){
            return false;
        }
    }
    return true;
}

bool CarGen::isValidData() const {
    if (random) {
        return isvalid(AllData);
    }
    return data->isValid();
}

//////////////
//
// Created by robbe on 05.04.22.
//

#include "CarData.h"
#include "Car.h"
#include "../Basic_Values.h"
#include "../DesignByContract.h"

CarData::CarData(Type type) {
    _initCheck = this;
    switch (type) {
        case bus:
            this->type = type;
            priority = false;
            l = 12;
            vMax = 11.4;
            aMax = 1.22;
            bMax = 4.29;
            fMin = 12;
            return;
        case fire:
            this->type = type;
            priority = true;
            l = 10;
            vMax = 14.6;
            aMax = 1.33;
            bMax = 4.56;
            fMin = 10;
            return;
        case ambulance:
            this->type = type;
            priority = true;
            l = 8;
            vMax = 15.5;
            aMax = 1.44;
            bMax = 4.47;
            fMin = 8;
            return;
        case police:
            this->type = type;
            priority = true;
            l = 6;
            vMax = 17.2;
            aMax = 1.55;
            bMax = 4.92;
            fMin = 6;
            return;
        case bugatti:
            this->type = bugatti;
            priority = false;
            l = 4.5;
            vMax = 100.0;
            aMax = 4;
            bMax = 40;
            fMin = 1;
            return;
        default:
            this->type = car;
            priority = false;
            l = 4;
            vMax = 16.6;
            aMax = 1.44;
            bMax = 4.61;
            fMin = 4;
            return;
    }
}



Type CarData::getType() const {
    REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling getType");
    ENSURE(type == bus or type == bugatti or type == police or type == fire or type == ambulance or type == car, "This type does not exist");
    return type;
}

bool CarData::getpriority() const {
    REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling getpriority");
    return priority;
}

double CarData::getlength() const {
    REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling getlength");
    ENSURE(l>0, "Length cannot be negative or zero");
    return l;
}

double CarData::getvMax() const {
    REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling getvMax");
    ENSURE(vMax>=0, "vMax cannot be negative");
    return vMax;
}

double CarData::getaMax() const {
    REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling getaMax");
    ENSURE(aMax>=0, "aMax cannot be negative");
    return aMax;
}

double CarData::getbMax() const {
    REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling getbMax");
    ENSURE(bMax>=0, "bMax cannot be negative");
    return bMax;
}

double CarData::getfMin() const {
    REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling getfMin");
    ENSURE(fMin>=0, "fMin cannot be negative");
    return fMin;
}


//////////////

bool CarData::properlyInitialized () const{
    return _initCheck == this;
}

bool CarData::isValid() const {
    if (!properlyInitialized()){
        return false;
    }
    if (type != car and type != bus and type != bugatti and type != ambulance and type != fire and type != police){
        return false;
    }
    if (l<1){
        return false;
    }
    if (vMax<=1){
        return false;
    }
    if (aMax<=0){
        return false;
    }
    if (bMax<=0){
        return false;
    }
    if (fMin<1){
        return false;
    }
    return true;
}
//////////////
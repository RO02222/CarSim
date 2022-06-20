//============================================================================
// Name        : CarData.h
// Date        : 18/06/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 4
//============================================================================


#ifndef CAR_SIMULATION_CARDATA_H
#define CAR_SIMULATION_CARDATA_H

enum Type{car,bus,fire,police,ambulance,bugatti,none};
class Road;
class CarData {
private:
    CarData* _initCheck;

    Type type;
    bool priority;
    double l;
    double vMax;
    double aMax;
    double bMax;
    double fMin;
public:
/**
 * create organised data for the cars
 * @param type: the type of the car
 * @return: None
*/
    CarData(Type type);

/**
 * get the type of the car
 * @return: (Type), the type of the car
\n REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling getType");
    ENSURE(type == bus or type == bugatti or type == police or type == fire or type == ambulance or type == car, "This type does not exist");
*/
    Type getType() const;

/**
 * get the priority of the car
 * @return: (bool),  the priority of the car
\n REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling getpriority");
*/
    bool getpriority() const;

/**
 * get the length of the car
 * @return: (double), the length of the car
\n REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling getlength");
    ENSURE(l>0, "Length cannot be negative or zero");
*/
    double getlength() const;

/**
 * get the default max speed of the car
 * @return: (double), the default max speed of the car
\n  REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling getvMax");
    ENSURE(vMax>=0, "vMax cannot be negative");
*/
    double getvMax() const;

/**
 * get the max velocity of the car
 * @return: (double), the max velocity of the car
\n REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling getaMax");
    ENSURE(aMax>=0, "aMax cannot be negative");
*/
    double getaMax() const;

/**
 * get the max break of the car
 * @return: (double), the max break of the car
\n REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling getbMax");
    ENSURE(bMax>=0, "bMax cannot be negative");
*/
    double getbMax() const;

/**
 * get the minimal following distance of the car
 * @return: (double), the  minimal following distance of the car
\n REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling getfMin");
    ENSURE(fMin>=0, "fMin cannot be negative");
*/
    double getfMin() const;


//////////////
public:

    /**
 * see if the Data is properly initialised
 * @return: (bool), if Data is properly initialised
*/
    bool properlyInitialized() const;

    /**
* see if the Data is valid
* @return: (bool), if Data is valid
*/
    bool isValid() const;

//////////////
};

#endif //CAR_SIMULATION_CARDATA_H

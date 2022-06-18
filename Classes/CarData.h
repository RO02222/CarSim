//
// Created by robbe on 05.04.22.
//

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
 * create orgeniszed data for the cars
 * @param type: the type of the car
 * @return: None
\n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    CarData(Type type);

/**
 * get the type of the car
 * @return: (Type), the type of the car
\n REQUIRE(properlyInitialized(), "CarData wasn't initialized when calling getType);
\n ENSURE(type == bus or type == bugatti or type == police or type == fire or type == ambulance or type == car, "This type does not exist");

*/
    Type getType() const;

/**
 * get the priority of the car
 * @return: (bool),  the priority of the car
\n REQUIRE(properlyInitialized(), "CarData wasn't initialized when calling getpriority);
*/
    bool getpriority() const;

/**
 * get the length of the car
 * @return: (double), the length of the car
\n REQUIRE(properlyInitialized(), "CarData wasn't initialized when calling getlength);
\n ENSURE(l>0, "Length cannot be negative or zero");
*/
    double getlength() const;

/**
 * get the default max speed of the car
 * @return: (double), the default max speed of the car
\n REQUIRE(properlyInitialized(), "CarData wasn't initialized when calling getvMax);
\n ENSURE(vMax>=0, "vMax cannot be negative");
*/
    double getvMax() const;

/**
 * get the max velocity of the car
 * @return: (double), the max velocity of the car
\n REQUIRE(properlyInitialized(), "CarData wasn't initialized when calling getaMax);
\n ENSURE(aMax>=0, "aMax cannot be negative");
*/
    double getaMax() const;

/**
 * get the max break of the car
 * @return: (double), the max break of the car
\n REQUIRE(properlyInitialized(), "CarData wasn't initialized when calling getbMax);
\n ENSURE(bMax>=0, "bMax cannot be negative");
*/
    double getbMax() const;

/**
 * get the minimal following distance of the car
 * @return: (double), the  minimal following distance of the car
\n REQUIRE(properlyInitialized(), "CarData wasn't initialized when calling getfMin);
\n ENSURE(fMin>=0, "fMin cannot be negative");
*/
    double getfMin() const;


//////////////
public:
    bool properlyInitialized() const;

    bool isValid() const;

//////////////
};

#endif //CAR_SIMULATION_CARDATA_H

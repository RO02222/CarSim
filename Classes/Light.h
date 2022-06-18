//============================================================================
// Name        : Light.h
// Date        : 18/06/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 4
//============================================================================


#ifndef CAR_SIMULATOR_LIGHT_H
#define CAR_SIMULATOR_LIGHT_H
#include <iostream>
#include "Clock.h"


class Road;
class Junction;

class Light : public Clock{
public:
    std::ofstream* error;
private:
    Light* _initCheck;
    Road* road;

    double position;

    bool clock;
public:
/**
 * create a traffic light
 * @param position: position of the traffic light
 * @param cycle: the time a cycle takes for a traffic light
 * @param road: the road where the traffic light is placed on
 * @param error: errorfile
 * @return: None
\n REQUIRE(r->isValidToAdd(p), "Light cannot be added");
    REQUIRE(c>=1, "Cycle is not valid");
    ENSURE(this->properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    Light(double position, double cycle, Road* road, std::ofstream* error);

/**
 * delete a light
 * @return: None
*/
    ~Light();


/**
 * Update the traffic light, changes the first (not priority) car his behavior depending on the lights state
 * @param t: time since last update
 * @return: None

    REQUIRE(isvalid(road), "Light wasn't initialized when calling updateLight");
    REQUIRE(t >= 0, "Time cannot be negative");
    ENSURE(isvalid(road), "Light wasn't initialized when calling updateLight");

*/
    void updateLight(double t);


/////////////
/**
 * get the road where the traffic light is positioned
 * @return: (Road*), the road where the traffic light is driving
\n REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling getRoad");
    ENSURE(road->properlyInitialized(), "Road is not properly initialised");
*/
    Road* getRoad();

protected:
/**
 * change the road of the traffic light
 * @param road: the new road of the traffic light
 * @return: None
\n REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling setRoad");
    REQUIRE(r->properlyInitialized(), "Road is not properly initialised");
    REQUIRE(r->isValid(), "Road is not valid");
    ENSURE(road == r,"Road hasn't changed");
*/
    void setRoad(Road* road);

public:
/**
 * get the position of the traffic light on the road
 * @return: (double), the position of the traffic light on the road
\n REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling getPosition");
    ENSURE(onRoad(), "Light is not on road");
*/
    double getPosition();
/**
 * change the position of the traffic light
 * @param position: the new position of the traffic light
 * @return: None
\n REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling setPosition");
    REQUIRE(onRoad(p), "Light not on road");
    ENSURE(position == p,"Position hasn't changed");
*/
    void setPosition(double position);
/**
 * get the state the traffic light
 * @return: (color), the state the traffic light
\n REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling getClock");
    ENSURE(clock >= 0.0, "Clock cannot be negative");
*/
    bool getClock();
/**
 * enable/disable the clock of the traffic light
 * @param state: the new state of the traffic light
 * @return: None
\n REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling setState");
    REQUIRE(s >= 0.0, "Clock cannot be negative");
    ENSURE(clock == s,"clock hasn't changed");
*/
    void setClock(bool state);
/////////////



/////////////
public:
    bool properlyInitialized() const;

    bool onRoad() const;

    bool onRoad(int d) const;

    bool isvalid(Road* road) const;
/////////////
};



#endif //CAR_SIMULATOR_LIGHT_H

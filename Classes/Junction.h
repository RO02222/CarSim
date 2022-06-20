//============================================================================
// Name        : Junction.h
// Date        : 18/06/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 4
//============================================================================


#ifndef CAR_SIMULATION_JUNCTION_H
#define CAR_SIMULATION_JUNCTION_H

#include <iostream>
#include <vector>
#include "Light.h"

class Road;
class Car;
class Light;
class Junction {
public:
    std::ofstream* error;
private:
    Junction* _initCheck;
    std::vector<std::pair<Road* , double> > roads;
    std::vector<Car*> cars;

private:
    Clock* clock;
    std::vector<Light*> lights;
    unsigned int numLight;


public:
/**
 * create a Junction
 * @param roads: the roads connected to the junction
 * @param error: errorfile
 * @return: None
\n REQUIRE(isvalid(roads), "Roads to form the junction are not valid");
   ENSURE(this->properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    Junction(std::vector<std::pair<Road* , double> > roads, std::ofstream* error);

/**
 * delete a Junction
 * @return: None
*/
    ~Junction();


/**
 * Update the junction, update cars near the junction and switch lanes.
 * @param time: time since last update
 * @return: None
\n REQUIRE(this->properlyInitialized(), "Junction wasn't initialized when calling updateJunction");
    REQUIRE(t>=0, "Time cannot be negative");
     ENSURE(isValid(),"Junction isn't valid");
    ENSURE(cars.empty(), "There are still cars that needs to be updated");
    ENSURE(ensureNumlight == numLight, "NumLight is not right");
*/
    void updateJunction(double time);

/**
 * add a car the junction, junction takes control of the car.
 * @param car: new car on the Junction
 * @return: None
\n REQUIRE(this->properlyInitialized(), "Junction wasn't initialized when calling addCar");
    REQUIRE(car->properlyInitialized(), "Car is not properly initialised");
    ENSURE(cars[cars.size()-1] == car, "Car is not added");
*/
    void addCar(Car* car);

/**
 * check the Junction for lights and change on all road  of the Junction
 * @return: None
\n REQUIRE(this->properlyInitialized(), "Junction is not properly initialised");
*/
    void checkJunctionLights();


/////////////
/**
 * get the n'th road of the junction (starting from 0)
 * @param n: which road you want
 * @return: (Road*), the n'th road of the junction
\n REQUIRE(this->properlyInitialized(), "Junction wasn't initialized when calling getRoad");
    ENSURE(roads[n].first->properlyInitialized(), "Road is not properly initialised");
*/
    Road* getRoad(int n);

/**
 * get the cars near the junction that aren't updated by the road
 * @return: (std::vector<Car*>), the cars near the junction that aren't updated by the road
\n REQUIRE(this->properlyInitialized(), "Junction wasn't initialized when calling getCars");
   ENSURE(checkProperly == true, "A car is not properly initialised");
*/
    std::vector<Car*> getCars();

/**
 * change the n'th road of the Junction (starting from 0)
 * @param road: the new road of the Junction
 * @param n: the n'th road of the Junction
 * @return: None
\n REQUIRE(this->properlyInitialized(), "Junction wasn't initialized when calling setRoad");
    REQUIRE(r->properlyInitialized(), "Road is not properly initialised");
    REQUIRE(r->isValid(), "Road isn't valid");
    REQUIRE(n>=0, "The number of the road cannot be negative");
    REQUIRE(n<=roads.size(), "there aren't that many roads");
    ENSURE(roads[n].first == r, "Road hasn't changed");
*/
    void setRoad(Road* road,unsigned int n);

/**
 * get the position of the Junction on the n'th road
 * @param n: the n'th road of the Junction
 * @return: (double), the position of the Junction on the n'th road
\n REQUIRE(this->properlyInitialized(), "Junction wasn't initialized when calling getPosition");
    ENSURE(onRoad(n), "Junction is not on road");
*/
    double getPosition(int n);

/**
 * get the position of the Junction on the road
 * @param roadname: the name of the road from the Junction
 * @return: (double), the position of the Junction on the road
\n REQUIRE(this->properlyInitialized(), "Junction wasn't initialized when calling getPosition");
    REQUIRE(onRoad(roadname), "Junction not on road");
*/
    double getPosition(std::string roadname);

/**
 * change the position of the Junction
 * @param n: the n'th road of the Junction
 * @param position: the new position of the Junction
 * @return: None
\n REQUIRE(this->properlyInitialized(), "Junction wasn't initialized when calling setPosition");
    REQUIRE(n<roads.size(), "There aren't that many roads");
    REQUIRE(p>=0 and p<roads[n].first->getLength(), "junction is not on the road");
    ENSURE(roads[n].second == p, "Position hasn't changed");
*/
    void setPosition(double position,unsigned int n);

/**
 * get the clock of the junction
 * @return: (Clock*), the clock of the Junction on the road
\n REQUIRE(this->properlyInitialized(), "Junction wasn't initialized when calling getClock");
    ENSURE(clock->properlyInitialized(), "clock is not initialized");
*/
    Clock* getClock();

/**
 * change the clock of the Junction
 * @param clock: the n road of the Junction
 * @return: None
\n REQUIRE(this->properlyInitialized(), "Junction wasn't initialized when calling setClock");
    REQUIRE(c->isvalid(), "clock is not valid");
    ENSURE(clock == c, "clock hasn't changed");
*/
    void setClock(Clock* clock);

/**
 * get all the roads of the Junction
 * @return: (std::vector<std::pair<Road* , double> >), all the roads on the junction
\n REQUIRE(this->properlyInitialized(), "Junction wasn't initialized when calling getRoads");
    ENSURE(checkProperly == true, "Road on junction is not properly initialised");
    ENSURE(checkOnRoad == true, "Junction is not on road");
*/
    std::vector<std::pair<Road* , double> > getRoads();

/**
 * true if the junction has trafficlights
 * @return: (bool), true or false
\n REQUIRE(this->properlyInitialized(), "Junction wasn't initialized when calling hasLights");
*/
    bool hasLights();

/**
 * get all the lights on the Junction
 * @return: (std::vector<Lights*>), the lights on the junction
\n REQUIRE(this->properlyInitialized(), "Junction wasn't initialized when calling getLights");
    ENSURE(checkProperly == true, "Road on junction is not properly initialised");
*/
    std::vector<Light*> getLights();
/////////////



/////////////
public:

    /**
* see if the junction is properly initialised
* @return: (bool), if junction is properly initialised
*/
    bool properlyInitialized() const;

    /**
* see if the junction is on the n'th road
* @param: n: the number of which road to check
* @return: (bool), if junction is on the n'th road
*/
    bool onRoad(long unsigned int n) const;

    /**
* see if the junction is on the road with given name
* @param: roadname: the name of the road to check
* @return: (bool), if junction is on the road with given name
*/
    bool onRoad(std::string roadname);

    /**
* see if the junction is valid
* @return: (bool), if junction isvalid
*/
    bool isValid() const;
/////////////
};


#endif //CAR_SIMULATION_JUNCTION_H

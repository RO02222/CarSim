//============================================================================
// Name        : Car_SimDomainTest.cpp
// Date        : 19/03/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 1
//============================================================================

#ifndef CAR_SIMULATION_BUSSTOP_H
#define CAR_SIMULATION_BUSSTOP_H

class Light;
class Road;
class Car;
class BusStop {
private:
    BusStop *_initCheck;

    Road *road;
    double position;
    double stoptime;
    double timestopped;
    Car *currentBus;
    bool bussy;
public:
/**
 * create a BusStop
 * @param position: position of the BusStop light
 * @param road: the road where the Busstop is placed on
 * @param stoptime: the minimum time how long a bus is waiting before leaving
 * @return: None
\n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    BusStop(double position, double stoptime, Road *road);

/**
 * Update the BusStop, changes the first bus his behavior
 * @param t: the time over which the simulation is updated
 * @return: None
\n REQUIRE(isvalid(road), "Busstop wasn't initialized when calling updateBusStop");
    REQUIRE(t>=0, "Time cannot be negative");
    REQUIRE(road->isvalidSimulation(),"part of the Simulation wasn't valid when calling updateBusStop");

*/
    void updateBusStop(double t);


/////////////
/**
 * get the road where the BusStop is positioned
 * @return: (Road*), the road where the BusStop is positioned
\n REQUIRE(this->properlyInitialized(), "BusStop wasn't initialized when calling getRoad");
    ENSURE(road->properlyInitialized(), "Road is not properly initialised");

*/
    Road *getRoad();

protected:
/**
 * change the road of the BusStop
 * @param road: the new road of the BusStop
 * @return: None
\n REQUIRE(this->properlyInitialized(), "BusStop wasn't initialized when calling setRoad");
    REQUIRE(r->properlyInitialized(), "Road is not properly initialised");
    REQUIRE(r->isvalid(),"Road isn't valid");
    ENSURE(road == r,"Road hasn't changed");
*/
    void setRoad(Road *road);

public:
/**
 * get the position of the BusStop on the road
 * @return: (double), the position of the BusStop on the road
\n REQUIRE(this->properlyInitialized(), "BusStop wasn't initialized when calling getPosition");
    ENSURE(onRoad(), "Busstop is not on road");
*/
    double getPosition();

/**
 * change the position of the BusStop
 * @param position: the new position of the BusStop
 * @return: None
\n REQUIRE(this->properlyInitialized(), "BusStop wasn't initialized when calling setPosition");
    REQUIRE(onRoad(p), "Busstop is not on road");
    ENSURE(position == p,"Position hasn't changed");
*/
    void setPosition(double position);

/**
 * get the stoptime of the Busstop
 * @return: (double), the stoptime of the Busstop
\n REQUIRE(this->properlyInitialized(), "BusStop wasn't initialized when calling getStopTime");
    ENSURE(stoptime>=0, "stoptime cannot be negative");
*/
    double getStopTime();

/**
* get the timeStopped of the getTimeStopped
* @return: (double), the time stopped of the bus
\n REQUIRE(this->properlyInitialized(), "BusStop wasn't initialized when calling getTimeStopped");
    ENSURE(timestopped>=0, "Timestopped cannot be negative");
*/
    double getTimeStopped();

/**
 * get the state of the Busstop
 * @return: (bool), the state of the Busstop
\n REQUIRE(properlyInitialized(), "Busstop wasn't initialized when calling getbussy");
*/
    bool getbussy();

/**
 * set the state of the Busstop
 * @param bussy: the new state of the BusStop
 * @return: none
\n REQUIRE(properlyInitialized(), "Busstop wasn't initialized when calling setbussy");
   ENSURE(bussy==b, "Bussy hasn't changed");
*/
    void setbussy(bool bussy);

/////////////
/**
 * See if busstop is properly initialised
 * @return: (bool) if busstop is properly initialised
*/
    bool properlyInitialized() const;

/**
 * See if busstop is on the road
 * @return: (bool) if busstop is on road
*/
    bool onRoad() const;

/**
 * see if given position is on road
 * @param p: the given position to check if on road
 * @return: (bool) if position is on road
*/
    bool onRoad(Road* r, int p) const;

/**
 * See if busstop is valid
 * @param road: the road on which to check if the busstop is valid
 * @return: (bool) see if busstop is valid
*/
    bool isValid(Road *road);

/////////////
};
#endif //CAR_SIMULATION_BUSSTOP_H

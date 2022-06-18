//============================================================================
// Name        : Car_SimDomainTest.cpp
// Date        : 19/03/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 1
//============================================================================


#ifndef CAR_SIMULATION_CLOCK_H
#define CAR_SIMULATION_CLOCK_H

enum color {green,red,orange};

class Clock {
private:
    Clock* _initCheck;

    double cycle;
    double lastCycle;
    color state;

public:
/**
 * create a clock
 * @param cycle: the time a cycle takes for a traffic light
 * @return: None
\n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    Clock(double cycle);

/**
 * delete a clock
 * @return: None
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling ~Road);
*/
    virtual ~Clock();

/**
 * Update the traffic light, changes the first (not priority) car his behavior depending on the lights state
 * @param t: time since last update
 * @return: None
*/
    void updateClock(double t);

/**
 * get the cycleTime the traffic light
 * @return: (double), the cycleTime the traffic light
\n REQUIRE(properlyInitialized(), "Light wasn't initialized when calling getCycle");
*/
    double getCycle();
/**
 * change cycle of the traffic light
 * @param cycle: the new cycle of the traffic light
 * @return: None
\n REQUIRE(properlyInitialized(), "Light wasn't initialized when calling setCycle");
*/
    void setCycle(double cycle);
/**
 * get the time since the last cycle the traffic light
 * @return: (double), the cycleTime the traffic light
\n REQUIRE(properlyInitialized(), "Light wasn't initialized when calling getCycle");
*/
    double getLastCycle();
/**
 * set the time since the last cycle the traffic light
 * @param cycle: the new cycle of the traffic light
 * @return: None
\n REQUIRE(properlyInitialized(), "Light wasn't initialized when calling setCycle");
*/
    void setLastCycle(double cycle);
/**
 * get the state the traffic light
 * @return: (color), the state the traffic light
\n REQUIRE(properlyInitialized(), "Light wasn't initialized when calling getState");
*/
    color getState();
/**
 * change state of the traffic light
 * @param state: the new state of the traffic light
 * @return: None
\n REQUIRE(properlyInitialized(), "Light wasn't initialized when calling setState");
*/
    void setState(color state);



    virtual bool properlyInitialized() const;

    bool isvalid() const;
};


#endif //CAR_SIMULATION_CLOCK_H

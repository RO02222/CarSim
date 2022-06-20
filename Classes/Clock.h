//============================================================================
// Name        : Clock.h
// Date        : 18/06/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 4
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
\n REQUIRE(c>=1, "Cycle is not valid");
   ENSURE(this->properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    Clock(double cycle);

/**
 * delete a clock
 * @return: None
*/
    virtual ~Clock();

/**
 * Update the traffic light, changes the first (not priority) car his behavior depending on the lights state
 * @param time: time since last update
 * @return: None
   REQUIRE(t>0, "Time cannot be negative");
    REQUIRE(isvalid(), "Clock is not valid");
    ENSURE(ensureLastCycle == lastCycle, "lastCycle is not right");
*/
    void updateClock(double time);

/**
 * get the cycleTime of the traffic light
 * @return: (double), the cycleTime the traffic light
\n REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling getCycle");
    ENSURE(cycle>0, "Cycle cannot be negative or zero");
*/
    double getCycle();
/**
 * change cycle of the traffic light
 * @param cycle: the new cycle of the traffic light
 * @return: None
\n REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling setCycle");
    REQUIRE(c>0, "Cycle cannot be negative or zero");
    ENSURE(cycle == c,"Cycle hasn't changed");
*/
    void setCycle(double cycle);
/**
 * get the time since the last cycle of the traffic light
 * @return: (double), the cycleTime of the traffic light
\n REQUIRE(properlyInitialized(), "Light wasn't initialized when calling getCycle");
*/
    double getLastCycle();
/**
 * set the time since the last cycle the traffic light
 * @param cycle: the new cycle of the traffic light
 * @return: None
\n REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling setLastCycle");
    REQUIRE(c>=0, "LastCycle cannot be negative");
    ENSURE(lastCycle == c,"Lastcycle hasn't changed");
*/
    void setLastCycle(double cycle);
/**
 * get the state of the traffic light
 * @return: (color), the state of the traffic light
\n REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling getState");
    ENSURE(state==green or state==red or state==orange, "Color does not exist ");
*/
    color getState();
/**
 * change state of the traffic light
 * @param state: the new state of the traffic light
 * @return: None
\n REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling setState");
    REQUIRE(s==green or s==red or s==orange, "Color does not exist ");
    ENSURE(state == s,"State hasn't changed");
*/
    void setState(color state);


    /**
 * see if the Clock is properly initialised
 * @return: (bool), if Clock is properly initialised
*/
    virtual bool properlyInitialized() const;

    /**
* see if the Clock is valid
* @return: (bool), if Clock is valid
*/
    bool isvalid() const;
};


#endif //CAR_SIMULATION_CLOCK_H

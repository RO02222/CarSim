//============================================================================
// Name        : Car_SimDomainTest.cpp
// Date        : 19/03/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 1
//============================================================================


#ifndef CAR_SIMULATOR_CARGEN_H
#define CAR_SIMULATOR_CARGEN_H
#include "Car.h"
#include "vector"
class Road;

class CarGen {
private:
    CarGen* _initCheck;

    Road *road;
    double frequency;
    double lastCycle;

    bool random;
    CarData* data;
    std::vector<CarData*>* AllData;


public:

/**
 * create a CarGen which generate a specific type of car
 * @param frequency: frequency of the CarGen
 * @param road: road where the CarGen is positioned
 * @param data: data of the car to generate
 * @return: None
\n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    CarGen(double frequency,Road *road, CarData* data);

/**
 * create a CarGen which generate a random type of car
 * @param frequency: frequency of the CarGen
 * @param road: road where the CarGen is positioned
 * @param allData: data of all the posible cars to generate
 * @return: None
\n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    CarGen(double frequency,Road *road, std::vector<CarData*>* allData);

/**
 * Update the CarGen his cycle and create a car if needed
 * @param t: time since last update
 * @return: None
\n REQUIRE(isvalid(road), "CarGen wasn't initialized when calling updateCarGen");
    REQUIRE(t >= 0, "Time cannot be negative");
    ENSURE(lastCycle == ensureLastcycle + t, "cycle hasn't updated");
*/
    void updateCarGen(double t);






/////////////
public:
/**
 * get the road where the CarGen is positioned
 * @return: (Road*), the road where the CarGen is positioned
\n REQUIRE(properlyInitialized(), "CarGen wasn't initialized when calling getRoad);
*/
    Road *getRoad();

protected:
/**
 * change the road of the CarGen
 * @param road: the new road of the CarGen
 * @return: None
\n REQUIRE(properlyInitialized(), "CarGen wasn't initialized when calling setRoad);
*/
    void setRoad(Road *road);

public:
/**
 * get the frequency of the CarGen
 * @return: (double), the frequency of the CarGen
\n REQUIRE(properlyInitialized(), "CarGen wasn't initialized when calling getFrequency);
*/
    double getFrequency();
/**
 * change the frequency of the CarGen
 * @param frequency: the frequency of the CarGen
 * @return: None
\n REQUIRE(properlyInitialized(), "CarGen wasn't initialized when calling setFrequency);
*/
    void setFrequency(double frequency);

/**
 * get the cycleTime of the CarGen
 * @return: (double), the cycleTime of the CarGen
\n REQUIRE(properlyInitialized(), "CarGen wasn't initialized when calling getCycle);
*/
    double getCycle();

/**
 * change the time since last cycle of the CarGen
 * @param cycle: the time since last cycle of the CarGen
 * @return: None
\n REQUIRE(properlyInitialized(), "CarGen wasn't initialized when calling setCycle);
*/
    void setCycle(double cycle);

/**
 * get the data to generate a car
 * @return: (Cardata*), the data
\n REQUIRE(properlyInitialized(), "CarGen wasn't initialized when calling setCycle);
*/
    CarData* getData();

/////////////



/////////////
public:
    bool properlyInitialized() const;

    bool isValid(Road* road) const;

    bool isValidToAdd(Road *road) const;

    bool isValidData() const;
/////////////
};


#endif //CAR_SIMULATOR_CARGEN_H

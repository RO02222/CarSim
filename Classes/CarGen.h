//============================================================================
// Name        : CarGen.h
// Date        : 18/06/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 4
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
\n  REQUIRE(f>=1, "Frequency is not valid");
    REQUIRE(da->properlyInitialized(), "Data is not valid");
    REQUIRE(isValidToAdd(r), "Road is not valid to be added");
    ENSURE(properlyInitialized(),"constructor must end in properlyInitialized state");
*/
    CarGen(double frequency,Road *road, CarData* data);

/**
 * create a CarGen which generate a random type of car
 * @param frequency: frequency of the CarGen
 * @param road: road where the CarGen is positioned
 * @param allData: data of all the possible cars to generate
 * @return: None
\n REQUIRE(f>=1, "Frequency is not valid");
    REQUIRE(isvalid(da), "AllData is not valid");
    REQUIRE(isValidToAdd(r), "Road is not valid to be added");
    ENSURE(properlyInitialized(),"constructor must end in properlyInitialized state");
*/
    CarGen(double frequency,Road *road, std::vector<CarData*>* allData);

/**
 * Update the CarGen his cycle and create a car if needed
 * @param time: time since last update
 * @return: None
\n REQUIRE(isValid(road), "CarGen wasn't initialized when calling updateCarGen");
    REQUIRE(t >= 0, "Time cannot be negative");
    REQUIRE(isValidData(), "Not all data is valid");
    ENSURE(ensureLastcycle == lastCycle, "LatCycle is not right");
    ENSURE(ensureData == data, "Data is not right");
    ENSURE(road->findCar(ensureNewCar),"New car cannot be found");
*/
    void updateCarGen(double time);






/////////////
public:
/**
 * get the road where the CarGen is positioned
 * @return: (Road*), the road where the CarGen is positioned
\n REQUIRE(this->properlyInitialized(), "CarGen wasn't initialized when calling getRoad");
    ENSURE(road->properlyInitialized(), "Road is not properly initialised");
*/
    Road *getRoad();

protected:
/**
 * change the road of the CarGen
 * @param road: the new road of the CarGen
 * @return: None
\n REQUIRE(this->properlyInitialized(), "CarGen wasn't initialized when calling setRoad");
    REQUIRE(r->properlyInitialized(), "Road is not properly initialised");
    REQUIRE(r->isValid(), "Road isn't valid");
    ENSURE(road == r,"Road hasn't changed");
*/
    void setRoad(Road *road);

public:
/**
 * get the frequency of the CarGen
 * @return: (double), the frequency of the CarGen
\n REQUIRE(this->properlyInitialized(), "CarGen wasn't initialized when calling getFrequency");
    ENSURE(frequency>0, "Frequency cannot be negative or zero");
*/
    double getFrequency();
/**
 * change the frequency of the CarGen
 * @param frequency: the frequency of the CarGen
 * @return: None
\n REQUIRE(this->properlyInitialized(), "CarGen wasn't initialized when calling setFrequency");
    REQUIRE(f>0, "frequency cannot be negative or zero");
    ENSURE(frequency == f,"Road hasn't changed");
*/
    void setFrequency(double frequency);

/**
 * get the cycleTime of the CarGen
 * @return: (double), the cycleTime of the CarGen
\n REQUIRE(this->properlyInitialized(), "CarGen wasn't initialized when calling getCycle");
    ENSURE(lastCycle>=0, "Lastcycle cannot be negative");
*/
    double getCycle();

/**
 * change the time since last cycle of the CarGen
 * @param cycle: the time since last cycle of the CarGen
 * @return: None
\n REQUIRE(this->properlyInitialized(), "CarGen wasn't initialized when calling setCycle");
    REQUIRE(c>=0, "Lastcycle cannot be negative");
    ENSURE(lastCycle == c,"Road hasn't changed");
*/
    void setCycle(double cycle);

/**
 * get the data to generate a car
 * @return: (Cardata*), the data
\n REQUIRE(this->properlyInitialized(), "CarGen wasn't initialized when calling getCycle");
    ENSURE(data->properlyInitialized(), "The data is not properly initialised");
*/
    CarData* getData();

/////////////



/////////////
public:

    /**
 * see if the CarGen is properly initialised
 * @return: (bool), if CarGen is properly initialised
*/
    bool properlyInitialized() const;

    /**
* see if the CarGen is valid
* @return: (bool), if CarGen is valid
*/
    bool isValid(Road* road) const;

    /**
* see if the junctions are valid to add something
* @return: (bool), if junctions are valid
*/
    bool isValidToAdd(Road *road) const;

    /**
* see if the data is valid
* @return: (bool), if data is valid
*/
    bool isValidData() const;
/////////////
};


#endif //CAR_SIMULATOR_CARGEN_H

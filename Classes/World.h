//============================================================================
// Name        : Car_SimDomainTest.cpp
// Date        : 19/03/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 1
//============================================================================


#ifndef CAR_SIMULATOR_WORLD_H
#define CAR_SIMULATOR_WORLD_H
#include <vector>
#include <iostream>
#include <cmath>
#include <fstream>
#include "../tinyxml/tinyxml.h"
#include "../tinyxml/tinystr.h"
#include "Road.h"
#include "Car.h"
#include "CarGen.h"
#include "Light.h"
#include "Clock.h"
#include "BusStop.h"
#include "Junction.h"
#include "CarData.h"


class Junction;
class CarData;

class World {
public:
    std::ofstream error;
private:
    World *_initCheck;

    std::vector<CarData*> carData;
    std::vector<Junction*> junctions;
    std::vector<Road *> roads;
    double time;
public:
/**
 * create a simulationWorld
 * @return: None
\n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    World();

/**
function:
 * delete a simulationWorld and everything in the world
 * @return: None
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling ~Road);
*/
    ~World();


/**
 * write the current state of all cars to the file
 * @param onStream: a stream where the current state of all cars is written to
 * @return: None
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling simpleSimulateWorld);
\n REQUIRE(isvalidSimulation(), "Simulation is not valid";
*/
    void simpleSimulateWorld(std::ostream &onStream);

/**
 * draw the current state of the simulation to the file
 * @param onStream: a stream where the current state of all cars is written to
 * @return: None
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling graficImpSimulateWorld);
\n REQUIRE(isvalidSimulation(), "Simulation is not valid";
*/
    void graficImpSimulateWorld(std::ostream &onStream);

/**
 * Update the world, update all the roads
 * @param t: time since last update
 * @return: None
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling updateWorld);
\n REQUIRE(isvalidSimulation(), "Simulation is not valid");
\n ENSURE(isvalidSimulation(),"Simulation isn't Valid")");
*/
    void updateWorld(double t);


/////////////
public:
/**
 * get all the roads of the simulationWorld
 * @return: (std::vector<Road*>), the roads in the simulationWorld
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling getRoads);
\n ENSURE(roads[i]->properlyInitialized(), "Road is not properly initialised");
*/
    const std::vector<Road *> &getRoads();

/**
 * change the roads of the simulationWorld
 * @param r: the new roads of the simulationWorld
 * @return: None
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling setRoad);
\n REQUIRE(r[i]->properlyInitialized(), "Road not properly initialised");
\n ENSURE(roads == r,"Roads hasn't changed");
*/
    void setRoad(const std::vector<Road *> &r);

/**
 * add a road to the simulationWorld
 * @param name: the name of the new road
 * @param length: the length of the new road
 * @return: None
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling addRoad);
\n ENSURE(roads[-1] == newRoad, "Road is not added");
*/
    void addRoad(std::string name, double length);

/**
 * add a road to the simulationWorld
 * @param road: the new road
 * @return: None
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling addRoad);
\n REQUIRE(road->isvalid(), "Road isn't valid");
\n ENSURE(roads[-1] == r, "Road is not added");
*/
    void addRoad(Road* road);


/**
 * get all the Junctions of the simulationWorld
 * @return: (std::vector<Junction*>), the Junctions in the simulationWorld
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling getJunctions);
\n ENSURE(junctions[i]->properlyInitialized(), "Junction is not initialised");
*/
    std::vector<Junction *> &getJunctions();

/**
 * change the Junctions of the simulationWorld
 * @param junction: the new Junctions of the simulationWorld
 * @return: None
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling setJunctions);
\n REQUIRE(junction[i]->properlyInitialized(), "Junction not properly initialised");
\n ENSURE(junctions == junction,"Junctions hasn't changed");
*/
    void setJunctions(const std::vector<Junction *> & junction);

/**
 * add a Junction to the simulation
 * @param roads: roads with the position of the junction on that road
 * @return: None
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling addJunction);
*/
    void addJunction(std::vector<std::pair<Road* , double> > roads);

/**
 * get the time of the simulationWorld
 * @return: (double), the simulationTime
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling getTime);
*/
    double getTime() const;

/**
 * change the simulationTime of the simulationWorld
 * @param t: the new simulationTime of the simulationWorld
 * @return: None
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling setTime);
*/
    void setTime(double t);

/**
 * get data of a specific carType
 * @param type: the type of carData
 * @return: (double), the carData
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling getCarData);
*/
    CarData* getCarData(Type type);

/**
 * get the data of all the cars
 * @return: (std::vector<CarData*>*), all the carData
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling getAllData);
*/
    std::vector<CarData*>* getAllData();
/////////////



//////////////
public:
    bool properlyInitialized() const;

    bool isValid() const;

    bool isValidToAddJunction(std::vector<std::pair<Road*,double> >& roads) const;

    bool isValidSimulation() const;
//////////////
};



#endif //CAR_SIMULATOR_WORLD_H

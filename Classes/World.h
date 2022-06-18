//============================================================================
// Name        : World.h
// Date        : 18/06/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 4
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
\n ENSURE(properlyInitialized(),"constructor must end in properlyInitialized state");
*/
    World();

/**
function:
 * delete a simulationWorld and everything in the world
 * @return: None
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling ~World");
*/
    ~World();


/**
 * write the current state of all cars to the file
 * @param onStream: a stream where the current state of all cars is written to
 * @return: None
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling simpleSimulateWorld");
    REQUIRE(isValidSimulation(), "Simulation is not valid");
*/
    void simpleSimulateWorld(std::ostream &onStream);

/**
 * draw the current state of the simulation to the file
 * @param onStream: a stream where the current state of all cars is written to
 * @return: None
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling graficImpSimulateWorld");
    REQUIRE(isValidSimulation(), "Simulation is not valid");
*/
    void graficImpSimulateWorld(std::ostream &onStream);

/**
 * Update the world, update all the roads
 * @param t: time since last update
 * @return: None
\n REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling updateWorld");
    REQUIRE(isValidSimulation(), "Simulation is not valid");
    REQUIRE(t > 0, "time must be positive");
    ENSURE(time == ensureTime,"time hasn't updated");
*/
    void updateWorld(double t);


/////////////
public:
/**
 * get all the roads of the simulationWorld
 * @return: (std::vector<Road*>), the roads in the simulationWorld
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling getRoads");
    ENSURE(roadsProperly(roads), "A road is not properly initialised");
*/
    const std::vector<Road *> &getRoads();

/**
 * change the roads of the simulationWorld
 * @param r: the new roads of the simulationWorld
 * @return: None
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling setRoad");
    REQUIRE(roadsProperly(banen), "A Road is not properly initialised");
    ENSURE(World::roads == banen,"Roads hasn't changed");
*/
    void setRoad(const std::vector<Road *> &r);

/**
 * add a road to the simulationWorld
 * @param name: the name of the new road
 * @param length: the length of the new road
 * @return: None
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling addRoad");
    REQUIRE(length > 0, "length is not long enough");
    ENSURE(roads[roads.size()-1] == r, "Road is not added");
*/
    void addRoad(std::string name, double length);

/**
 * add a road to the simulationWorld
 * @param road: the new road
 * @return: None
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling addRoad");
    REQUIRE(r->isValid(), "Road isn't valid");
    ENSURE(roads[roads.size()-1] == r, "Road is not added");
*/
    void addRoad(Road* road);


/**
 * get all the Junctions of the simulationWorld
 * @return: (std::vector<Junction*>), the Junctions in the simulationWorld
\n REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling getJunctions");
    ENSURE(junctionsProperly(junctions), "A Junction is not initialised");
*/
    std::vector<Junction *> &getJunctions();

/**
 * change the Junctions of the simulationWorld
 * @param junction: the new Junctions of the simulationWorld
 * @return: None
\n REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling setJunctions");
    REQUIRE(junctionsProperly(junction), "A Junction is not initialised");
    ENSURE(World::junctions == junction,"Junctions hasn't changed");
*/
    void setJunctions(const std::vector<Junction *> & junction);

/**
 * add a Junction to the simulation
 * @param roads: roads with the position of the junction on that road
 * @return: None
\n  REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling addJuction");
    REQUIRE(isValidToAddJunction(road),"Junction is on a invalid position");
    Junction* j = new Junction(road, &error);
    ENSURE(junctions[junctions.size()-1] == j, "Junction is not added");
*/
    void addJunction(std::vector<std::pair<Road* , double> > roads);

/**
 * get the time of the simulationWorld
 * @return: (double), the simulationTime
\n REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling getTime");
    ENSURE(time>=0, "Time cannot be negative");
*/
    double getTime() const;

/**
 * change the simulationTime of the simulationWorld
 * @param t: the new simulationTime of the simulationWorld
 * @return: None
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling setTime");
    REQUIRE(t>=0, "time cannot be negative");
    ENSURE(World::time == t,"Time hasn't changed");
*/
    void setTime(double t);

/**
 * get data of a specific carType
 * @param type: the type of carData
 * @return: (double), the carData
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling getCarData");
    REQUIRE(isvalid(&carData),"Data is not properly initialised");
    ENSURE(returnData->properlyInitialized(), "The cardata is not properly initialised");
*/
    CarData* getCarData(Type type);

/**
 * get the data of all the cars
 * @return: (std::vector<CarData*>*), all the carData
\n REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling getCarData");
    ENSURE(dataProperly(carData), "Cardata is not properly initialised");
*/
    std::vector<CarData*>* getAllData();
/////////////



//////////////
public:
    bool properlyInitialized() const;

    bool isValid() const;

    bool isValidToAddJunction(std::vector<std::pair<Road*,double> >& roads) const;

    bool isValidSimulation() const;

    bool roadsProperly(std::vector<Road *> r);

    bool junctionsProperly(std::vector<Junction*> j);

    bool dataProperly(std::vector<CarData*> cD);
//////////////
};



#endif //CAR_SIMULATOR_WORLD_H

//============================================================================
// Name        : Car_SimDomainTest.cpp
// Date        : 19/03/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 1
//============================================================================


#ifndef CAR_SIMULATOR_ROAD_H
#define CAR_SIMULATOR_ROAD_H
#include <vector>
#include <iostream>

class Light;
class Car;
class CarGen;
class BusStop;
class Junction;
class CarData;

class Road {
public:
    std::ofstream* error;
private:
    Road* _initCheck;

    std::string name;
    double length;

    std::vector<Light*> lights;
    std::vector<Car*> cars;
    std::vector<CarGen*> carGen;
    std::vector<BusStop*> busStops;
    std::vector<std::pair<Junction*,double*> > junctions;
public:
/**
 * create a road
 * @param name: name of the road
 * @param length: lengt of the road
 * @param error: errorfile
 * @return: None
\n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    Road(const std::string &name, double length, std::ofstream* error);


/**
 * delete a road and everything on the road
 * @return: None
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling ~Road);
*/
    ~Road();

/**
 * Update the road, update everything on the road: Cars, light, CarGen.
 * @param t: time since last update
 * @return: None
\n REQUIRE(properlyInitialized(), "Car wasn't initialized when calling updateRoad");
\n REQUIRE(t>=0, "Time cannot be negative");
\n ENSURE(isvalidSimulation(), "Part of the simulation isn't valid");
*/
    void updateRoad(double t);


/**
 * remove a car from the road.
 * @param car: the car that needs to be removed
 * @return: None
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling removeCars);
\n REQUIRE(car->properlyInitialized(), "car wasn't properly initialised");
*/
    void removeCar(Car* car, bool del = false);






/////////////
public:
/**
 * add a new traffic light to the road
 * @param position: position of the traffic light on the road
 * @param cycle: cycle time of the trafficlight
 * @return: None
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling addLights);
*/
    void addLight(double position, double cycle);
/**
 * add a new car to the road
 * @param distance: distance of the car on the road
 * @param data: the data of the car
 * @return: None
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling addCars);
*/
    void addCar(double distance, CarData* data);
/**
 * add a car to the road
 * @param car: the new car car on the road
 * @return: None
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling addCars);
*/
    void addCar(Car* car);
/**
 * add a new carGen at the beginning of the road
 * @param frequency: frequency of the carGen
 * @param data: the data of the car
 * @return: None
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling addCarGen);
*/
    void addCarGen(double frequency, CarData* data);
/**
 * add a new carGen at the beginning of the road
 * @param frequency: frequency of the carGen
 * @param allData: data of all the posible cars to generate
 * @return: None
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling addCarGen);
*/
    void addCarGen(double frequency, std::vector<CarData*>* allData);
/**
 * add a new Busstop to the road
 * * @param position: position of the Busstop
 * @param stoptime: stoptime of the Busstop
 * @return: None
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling addBusstop);
*/
    void addBusStop(double position, double stoptime);
/**
 * add a Junction to the road
 * @param junction: the Junction and the position
 * @return: None
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling addJunction);
*/
    void addJunction(std::pair<Junction*,double*> junction);
/////////////



/////////////
public:
/**
 * get the name of the road
 * @return: (std::string), the name of the road
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling getName);
*/
    const std::string &getName();
/**
 * change the name of the road
 * @param name: the new name of the road
 * @return: None
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling setName);
*/
    void setName(const std::string &name);
/**
 * get the length of the road
 * @return: (double), the length of the road
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling getLength);
*/
    double getLength();
/**
 * change the length of the road
 * @param length: the new length of the road
 * @return: None
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling setLength);
*/
    void setLength(double length);


/**
 * get all the traffic lights on the the road
 * @return: (std::vector<Light*>), all the traffic lights on the the road
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling getLights);
*/
    const std::vector<Light *> &getLights();
/**
 * change the lights of the road
 * @param lights: the new lights of the road
 * @return: None
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling setLights);
*/
    void setLights(const std::vector<Light *> &lights);
/**
 * get all the Cars on the the road
 * @return: (std::vector<Car*>), all the Cars on the the road
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling getCars);
*/
    const std::vector<Car *> &getCars();
/**
 * change the cars of the road
 * @param cars: the new cars of the road
 * @return: None
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling setCars);
*/
    void setCars(const std::vector<Car *> &cars);
/**
 * get all the CarGens on the the road
 * @return: (std::vector<CarGen*>), all the CarGens on the the road
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling getCarGen);
*/
    const std::vector<CarGen *> &getCarGen();
/**
 * change the carGens of the road
 * @param carGens: the new carGens of the road
 * @return: None
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling setCarGen);
*/
    void setCarGen(const std::vector<CarGen *> &carGens);

/**
 * get all the BusStops on the the road
 * @return: (std::vector<BusStops*>), all the BusStops on the the road
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling getbusStops);
*/
    const std::vector<BusStop *> &getBusStops();
/**
 * change the BusStops of the road
 * @param BusStops: the new BusStops of the road
 * @return: None
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling setbusStops);
*/
    void setbusStops(const std::vector<BusStop *> &BusStops);

/**
 * get all the BusStops on the the road
 * @return: (std::vector<BusStops*>), all the BusStops on the the road
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling getbusStops);
*/
    const std::vector<std::pair<Junction*,double*> >  &getJunctions();
/**
 * change the BusStops of the road
 * @param BusStops: the new BusStops of the road
 * @return: None
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling setbusStops);
*/
    void setJunctions(const std::vector<std::pair<Junction*,double*> >  &Junctions);
/////////////



/////////////
public:
    bool properlyInitialized() const;

    bool onRoad(double position) const;

    bool isValid() const;

    bool isValidToAdd(double position) const;

    bool isValidToAddCar(double position, double length) const;

    bool isvalidSimulation();

    bool findCar(Car* car);

    bool findLight(Light* light);
/////////////
};

#endif //CAR_SIMULATOR_ROAD_H

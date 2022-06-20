//============================================================================
// Name        : Road.h
// Date        : 18/06/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 4
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
\n REQUIRE(l>=gStopDistance, "Road is not long enough");
 ENSURE(properlyInitialized(),"constructor must end in properlyInitialized state");
*/
    Road(const std::string &name, double length, std::ofstream* error);


/**
 * delete a road and everything on the road
 * @return: None
\n REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling ~Road");
*/
    ~Road();

/**
 * Update the road, update everything on the road: Cars, light, CarGen.
 * @param time: time since last update
 * @return: None
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling updateRoad");
 ENSURE(isvalidSimulation(), "Part of the simulation isn't valid");
    REQUIRE(t>=0, "Time cannot be negative");
*/
    void updateRoad(double time);


/**
 * remove a car from the road.
 * @param car: the car that needs to be removed
 * @param: del: if the car needs to be deleted
 * @return: None
\n REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling removeCars");
    REQUIRE(car->properlyInitialized(), "car wasn't properly initialised");
    ENSURE(!findCar(car),"Car is not deleted");
*/
    void removeCar(Car* car, bool del = false);






/////////////
public:
/**
 * add a new traffic light to the road
 * @param position: position of the traffic light on the road
 * @param cycle: cycle time of the traffic light
 * @return: None
\n REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling addLight");
    REQUIRE(isValidToAdd(position),"Light cannot be added");
    REQUIRE(cycle>=1, "Cycle is not valid");
    ENSURE(true, "Light is not added");
*/
    void addLight(double position, double cycle);
/**
 * add a new car to the road
 * @param distance: distance of the car on the road
 * @param data: the data of the car
 * @return: None
\n REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling addCar");
*/
    void addCar(double distance, CarData* data);
/**
 * add a car to the road
 * @param car: the new car on the road
 * @return: None
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling addCars);
 ENSURE(c==Road::cars[Road::cars.size()-1], "Car is not added");
*/
    void addCar(Car* car);
/**
 * add a new carGen at the beginning of the road
 * @param frequency: frequency of the carGen
 * @param data: the data of the car
 * @return: None
\n REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling addCarGen");
 ENSURE(carGen[carGen.size()-1] == cg, "Cargen is not added");
*/
    void addCarGen(double frequency, CarData* data);
/**
 * add a new carGen at the beginning of the road
 * @param frequency: frequency of the carGen
 * @param allData: data of all the possible cars to generate
 * @return: None
\n REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling addCarGen");
 ENSURE(carGen[carGen.size()-1] == cg, "Cargen is not added");
*/
    void addCarGen(double frequency, std::vector<CarData*>* allData);
/**
 * add a new Busstop to the road
 * @param position: position of the Busstop
 * @param stoptime: stoptime of the Busstop
 * @return: None
\n REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling addBusStop");
 ENSURE(busStops[busStops.size()-1] == b, "Busstop is not added");
*/
    void addBusStop(double position, double stoptime);
/**
 * add a Junction to the road
 * @param junction: the Junction and the position
 * @return: None
\n REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling addJuction");
 ENSURE(junctions[junctions.size()-1] == junction, "Junction is not added");
*/
    void addJunction(std::pair<Junction*,double*> junction);
/////////////



/////////////
public:
/**
 * get the name of the road
 * @return: (std::string), the name of the road
\n REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling getName");
*/
    const std::string &getName();
/**
 * change the name of the road
 * @param name: the new name of the road
 * @return: None
\n REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling setName");
    ENSURE(name == n,"Name hasn't changed");
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
\n REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling setLength");
    REQUIRE(l>0, "length of a road cannot be negative");
    ENSURE(length == l,"Length hasn't changed");
*/
    void setLength(double length);


/**
 * get all the traffic lights on the the road
 * @return: (std::vector<Light*>), all the traffic lights on the the road
\n REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling getLights");
    ENSURE(lightsProperly(lights) == true, "A Light is not initialised");
*/
    const std::vector<Light *> &getLights();
/**
 * change the lights of the road
 * @param lights: the new lights of the road
 * @return: None
\n REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling setLights");
    REQUIRE(lightsProperly(l) == true, "Light is not initialised");
    ENSURE(lights == l,"Lights hasn't changed");
*/
    void setLights(const std::vector<Light *> &lights);
/**
 * get all the Cars on the the road
 * @return: (std::vector<Car*>), all the Cars on the road
\n REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling getCars");
    ENSURE(carsProperly(cars), "A car is not initialised");
*/
    const std::vector<Car *> &getCars();
/**
 * change the cars of the road
 * @param cars: the new cars of the road
 * @return: None
\n REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling setCars");
    REQUIRE(carsProperly(c), "A car is not initialised");
    ENSURE(cars == c,"Cars hasn't changed");
*/
    void setCars(const std::vector<Car *> &cars);
/**
 * get all the CarGens on the the road
 * @return: (std::vector<CarGen*>), all the CarGens on the road
\n REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling getCarGen");
    ENSURE(carGenProperly(carGen), "CarGen is not initialised");
*/
    const std::vector<CarGen *> &getCarGen();
/**
 * change the carGens of the road
 * @param carGens: the new carGens of the road
 * @return: None
\n REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling setCarGen");
    REQUIRE(carGenProperly(carGens), "CarGen is not initialised");
    ENSURE(Road::carGen == carGens,"carGen hasn't changed");
*/
    void setCarGen(const std::vector<CarGen *> &carGens);

/**
 * get all the BusStops on the road
 * @return: (std::vector<BusStops*>), all the BusStops on the road
\n  REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling getBusStops");
    ENSURE(busStopProperly(busStops), "A busstop is not initialised");
*/
    const std::vector<BusStop *> &getBusStops();
/**
 * change the BusStops of the road
 * @param BusStops: the new BusStops of the road
 * @return: None
\n REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling setBusStops");
    REQUIRE(busStopProperly(BusStops), "A busstop is not initialised");
    ENSURE(Road::busStops == BusStops,"busStops hasn't changed");
*/
    void setbusStops(const std::vector<BusStop *> &BusStops);

/**
 * get all the junctions on the road
 * @return: (std::vector<BusStops*>), all the junctions on the the road
\n REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling getJunctions");
    ENSURE(junctionsValid(junctions), "Junction is not valid");
*/
    const std::vector<std::pair<Junction*,double*> >  &getJunctions();
/**
 * change the junctions of the road
 * @param BusStops: the new junctions on the road
 * @return: None
\n REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling setJunctions");
    REQUIRE(goodJuntion(Junctions), "A Junction is not good");
    ENSURE(Road::junctions == Junctions,"Junctions hasn't changed");
*/
    void setJunctions(const std::vector<std::pair<Junction*,double*> >  &Junctions);
/////////////



/////////////
public:
    /**
* see if the road is properly initialised
* @return: (bool), if road is properly initialised
*/
    bool properlyInitialized() const;

    /**
* see if the a specific position is on the road
* @param:position: the position to check
* @return: (bool), if a specific position is on the road
*/
    bool onRoad(double position) const;

    /**
* see if the road is valid
* @return: (bool), if the road isvalid
*/
    bool isValid() const;

    /**
* see if it is possible to add something on a specific position
* @param: position: the position to check
* @return: (bool), if it is possible to add something on a specific position
*/
    bool isValidToAdd(double position) const;

    /**
* see if it is possible to add something on a specific position
* @param: position: the position to check
* @param: length: length of car
* @return: (bool), if it is possible to add a car with specific length on a specific position
*/
    bool isValidToAddCar(double position, double length) const;

    /**
* see if everything of the simulation is valid
* @return: (bool), if everything of the simulation is valid
*/
    bool isvalidSimulation();

    /**
* see if a specific car is on the road
* @param: car: the car to check
* @return: (bool), if a specific car is on the road
*/
    bool findCar(Car* car);

    /**
* see if a specific light is on the road
* @param: light: the light to check
* @return: (bool), if a specific light is on the road
*/
    bool findLight(Light* light);

    /**
* see if every light is properly initialised
* @param: lights: the lights to check
* @return: (bool), if every light is properly initialised
*/
    bool lightsProperly(std::vector<Light*> lights);


    /**
* see if every car is properly initialised
* @param: cars: the cars to check
* @return: (bool), if every car is properly initialised
*/
    bool carsProperly(std::vector<Car*> cars);

    /**
* see if every cargen is properly initialised
* @param: cargens: the cargens to check
* @return: (bool), if every cargen is properly initialised
*/
    bool carGenProperly(std::vector<CarGen*> carGens);

    /**
* see if every busstop is properly initialised
* @param: busstops: the busstops to check
* @return: (bool), if every busstop is properly initialised
*/
    bool busStopProperly(std::vector<BusStop*> busStops);

    /**
* see if every junction is valid
* @param: junctions: the junctions to check
* @return: (bool), if every junction is valid
*/
    bool junctionsValid(std::vector<std::pair<Junction*,double*> > junctions);

    /**
* see if every junction is right
* @param: junctions: the junctions to check
* @return: (bool), if every junction is right
*/
    bool goodJuntion(std::vector<std::pair<Junction *, double *> > junctions);
/////////////
};

#endif //CAR_SIMULATOR_ROAD_H

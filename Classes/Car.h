//============================================================================
// Name        : Car.h
// Date        : 18/06/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 4
//============================================================================


#ifndef CAR_SIMULATOR_CAR_H
#define CAR_SIMULATOR_CAR_H
class Road;
class CarData;
enum Action{fast,slow,stop};
class Car{
private:
    Car* _initCheck;
    Road* road;
    double distance;
    double speed;
    double maxSpeed;
    double acceleration;
    Action action;
    CarData* data;

public:
/**
 * create a Car
 * @param distance: position on the road
 * @param data: the data of the car
 * @param road: road where the Car is positioned.
 * @return: None
\n REQUIRE(da->properlyInitialized(), "Data is not valid");
    REQUIRE(onRoad(d,r), "Car is not on road");
    REQUIRE(r->isValid(), "Road is not valid");
    ENSURE(properlyInitialized(),"constructor must end in properlyInitialized state");
*/
    Car (double distance, CarData* data, Road* road);


/**
 * Update the Car his position, speed and acceleration
 * @param time: time to update
 * @param onJunction: if car is near Junction
 * @return: (bool), if car is on road
\n REQUIRE(isValid(road), "Car is not valid");
    REQUIRE(t >= 0, "Time cannot be negative");
    REQUIRE(road->isvalidSimulation(), "Road of the simulation is not valid");
    ENSURE(ensureMaxSpeed == maxSpeed, "MaxSpeed is not right");
    ENSURE(ensureAcceleration == acceleration, "Acceleration is not right");
    ENSURE(ensureSpeed == speed, "speed is not right");
    ENSURE(ensurePos == distance, "Position is not right");
*/
    bool updateCar(double time, bool onJunction = false);


/**
 * move the Car to a onother road
 * @param road: the new road
 * @param position: the new position of the car
 * @return: None
\n REQUIRE(this->properlyInitialized(), "Car is not properly initialised");
    REQUIRE(r->properlyInitialized(), "Road is not properly initialised");
    REQUIRE(r->isValid(), "road isn't valid");
    REQUIRE(position>=0 and position<=r->getLength(), "Car is not on road");
    ENSURE(this->getDistance() == position, "position hasn't changed");
    ENSURE(road==r, "Road hasn't changed");
    ENSURE(added, "Car is not added to the new road");
*/
    void moveCar(Road* road, double position);








//////////////
public:
/**
 * get the road where the Car is positioned
 * @return: (Road*), the road where the Car is positioned
\n REQUIRE(this->properlyInitialized(), "Car wasn't initialized when calling getRoad");
    ENSURE(road->properlyInitialized(), "Road is not properly initialised");
*/
    Road *getRoad() const;


/**
 * change the road of the Car
 * @param road: the new road of the Car
 * @return: None
\n REQUIRE(this->properlyInitialized(), "Car wasn't initialized when calling setRoad");
    REQUIRE(r->properlyInitialized(), "Road is not properly initialised");
    REQUIRE(r->isValid(),"Road isn't valid");
    ENSURE(road == r,"Road hasn't changed");
*/
    void setRoad(Road *road);

public:
/**
 * get the distance of the car
 * @return: (double), the distance of the car
\n REQUIRE(this->properlyInitialized(), "Car wasn't initialized when calling getDistance");
    ENSURE(onRoad(), "Car is not on road");
*/
    double getDistance();

/**
 * get the distance of the car that is not always on a road
 * @return: (double), the distance of the car
\n REQUIRE(this->properlyInitialized(), "Car wasn't initialized when calling getDistance");
    ENSURE(distance>=0, "Distance cannot be negative");
*/
    double getDistanceNV();
/**
 * change the distance of the car
 * @param distance: the new distance of the car
 * @return: None
\n REQUIRE(properlyInitialized(), "Car wasn't initialized when calling setDistance");
*/
    void setDistance(double distance);
/**
 * get the speed of the car
 * @return: (double), the speed of the car
\n REQUIRE(this->properlyInitialized(), "Car wasn't initialized when calling setDistance");
    REQUIRE(onRoad(d,road), "Car not on road");
    ENSURE(distance == d,"Distance hasn't changed");
*/
    double getSpeed();
/**
 * change the speed of the car
 * @param speed: the new speed of the car
 * @return: None
\n REQUIRE(this->properlyInitialized(), "Car wasn't initialized when calling getSpeed");
    ENSURE(speed>=0, "Speed cannot be negative");
*/
    void setSpeed(double speed);
/**
 * get the maxSpeed of the car
 * @return: (double), the maxSpeed of the car
\n REQUIRE(this->properlyInitialized(), "Car wasn't initialized when calling setSpeed");
    REQUIRE(s>=0, "Speed can not be negative");
    ENSURE(speed == s,"Speed hasn't changed");
*/
    double getMaxSpeed();
/**
 * change the maxSpeed of the car
 * @param maxSpeed: the new maxSpeed of the car
 * @return: None
\n REQUIRE(this->properlyInitialized(), "Car wasn't initialized when calling getMaxSpeed");
    ENSURE(maxSpeed>=0, "Maxspeed cannot be negative");
*/
    void setMaxSpeed(double maxSpeed);
/**
 * get the acceleration of the car
 * @return: (double), the acceleration of the car
\n REQUIRE(this->properlyInitialized(), "Car wasn't initialized when calling setMaxSpeed");
    REQUIRE(s>=0, "Speed can not be negative");
    ENSURE(maxSpeed == s, "Maxspeed hasn't changed");
*/
    double getAcceleration();
/**
 * change the acceleration of the car
 * @param acceleration: the new acceleration of the car
 * @return: None
\n REQUIRE(this->properlyInitialized(), "Car wasn't initialized when calling getAcceleration");
*/
    void setAcceleration(double acceleration);
/**
 * get the Acton that the car is doing
 * @return: (Action), the Acton that the car is doing
\n REQUIRE(this->properlyInitialized(), "Car wasn't initialized when calling setAcceleration");
    ENSURE(acceleration == a,"Acceleration hasn't changed");
*/
    Action getAction();
/**
 * change the Action of the car
 * @param action: the new Action of the car
 * @return: None
\n REQUIRE(this->properlyInitialized(), "Car wasn't initialized when calling setAction");
    REQUIRE(a==fast or a==slow or a==stop, "action does not exist");
    ENSURE(action == a,"Action hasn't changed");
*/
    void setAction(Action action);

/**
 * get the data of the car
 * @return: (CarData*), the data of the car
\n  REQUIRE(this->properlyInitialized(), "Car wasn't initialized when calling getData");
    ENSURE(data->properlyInitialized(), "The data is not properly initialised");
*/
    CarData* getData();
//////////////



/////////////
public:

    /**
 * See if Car is properly initialised
 * @return: (bool), if car is properly initialised
*/
    bool properlyInitialized() const;

    /**
* See if Car is on road
* @return: (bool), if car is on road
*/
    bool onRoad() const;

    /**
* See if distance is on given road
* @param distance: the distance to check
* @param road: the road on which to check
* @return: (bool), if car is on road
*/
    bool onRoad(int distance, Road* road) const;

    /**
* See if road is valid
* @param road: the road to check
* @return: (bool), if road is valid
*/
    bool isValid(Road* road) const;
/////////////
};


#endif //CAR_SIMULATOR_CAR_H

//============================================================================
// Name        : Car_SimDomainTest.cpp
// Date        : 19/03/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 1
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
\n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    Car (double distance, CarData* data, Road* road);


/**
 * Update the Car his position, speed and acceleration
 * @param t: time to update
 * @param onJunction: if car is near Junction
 * @return: None
\n REQUIRE(this->properlyInitialized(), "Car wasn't initialized when calling updateCar");
    REQUIRE(t>=0, "Time cannot be negative");
    ENSURE(acceleration == a, "accelration is not updated");
*/
    bool updateCar(double t, bool onJunction = false);


/**
 * move the Car to a onother road
 * @param road: the new road
 * @param position: the new position of the car
 * @return: None
\n REQUIRE(this->properlyInitialized(), "Car is not properly initialised");
    REQUIRE(r->properlyInitialized(), "Road is not properly initialised");
    REQUIRE(r->isvalid(), "road isn't valid");
    REQUIRE(position>=0 and position<=r->getLength(), "Car is not on road");
    ENSURE(this->getDistance() == position, "position hasn't changed");
    ENSURE(road==r, "Road hasn't changed");
    ENSURE(road->getCars()[road->getCars().size()-1] == this, "Car is not added to the new road");
*/
    void moveCar(Road* road, double position);








//////////////
public:
/**
 * get the road where the Car is positioned
 * @return: (Road*), the road where the Car is positioned
\n REQUIRE(properlyInitialized(), "Car wasn't initialized when calling getRoad");
*/
    Road *getRoad() const;


/**
 * change the road of the Car
 * @param road: the new road of the CarG
 * @return: None
\n REQUIRE(properlyInitialized(), "Car wasn't initialized when calling setRoad");
*/
    void setRoad(Road *road);

public:
/**
 * get the distance of the car
 * @return: (double), the distance of the car
\n REQUIRE(properlyInitialized(), "Car wasn't initialized when calling getDistance");
*/
    double getDistance();

/**
 * get the distance of the car that is not always on a road
 * @return: (double), the distance of the car
\n REQUIRE(properlyInitialized(), "Car wasn't initialized when calling getDistance");
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
\n REQUIRE(properlyInitialized(), "Car wasn't initialized when calling getSpeed");
*/
    double getSpeed();
/**
 * change the speed of the car
 * @param speed: the new speed of the car
 * @return: None
\n REQUIRE(properlyInitialized(), "Car wasn't initialized when calling setSpeed");
*/
    void setSpeed(double speed);
/**
 * get the maxSpeed of the car
 * @return: (double), the maxSpeed of the car
\n REQUIRE(properlyInitialized(), "Car wasn't initialized when calling getMaxSpeed");
*/
    double getMaxSpeed();
/**
 * change the maxSpeed of the car
 * @param maxSpeed: the new maxSpeed of the car
 * @return: None
\n REQUIRE(properlyInitialized(), "Car wasn't initialized when calling setMaxSpeed");
*/
    void setMaxSpeed(double maxSpeed);
/**
 * get the acceleration of the car
 * @return: (double), the acceleration of the car
\n REQUIRE(properlyInitialized(), "Car wasn't initialized when calling getAcceleration");
*/
    double getAcceleration();
/**
 * change the acceleration of the car
 * @param acceleration: the new acceleration of the car
 * @return: None
\n REQUIRE(properlyInitialized(), "Car wasn't initialized when calling setAcceleration");
*/
    void setAcceleration(double acceleration);
/**
 * get the Acton that the car is doing
 * @return: (action), the Acton that the car is doing
\n REQUIRE(properlyInitialized(), "Car wasn't initialized when calling getAction");
*/
    Action getAction();
/**
 * change the Action of the car
 * @param action: the new Action of the car
 * @return: None
\n REQUIRE(properlyInitialized(), "Car wasn't initialized when calling setAction");
*/
    void setAction(Action action);

/**
 * get the data of the car
 * @return: (CarData*), the data of the car
\n REQUIRE(properlyInitialized(), "Car wasn't initialized when calling getData");
*/
    CarData* getData();
//////////////



/////////////
public:
    bool properlyInitialized() const;

    bool onRoad() const;

    bool onRoad(int d, Road* r) const;

    bool isValid(Road* road) const;
/////////////
};


#endif //CAR_SIMULATOR_CAR_H

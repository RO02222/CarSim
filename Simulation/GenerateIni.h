//
// Created by robbe on 07.05.22.
//

#ifndef CAR_SIMULATION_GENERATEINI_H
#define CAR_SIMULATION_GENERATEINI_H
#include <fstream>
#include <vector>

class World;
class Road;

class GenerateIni {
public:
    GenerateIni* _initcheck;
    World* world;
    std::string filename;
    int filenumber;

public:
    std::vector<std::pair<Road*, std::pair<double,double> > > roads;

public:
    GenerateIni(World *world, const std::string &filename);
    void generate();

private:
    unsigned int parralellRoads();
    unsigned int singleCrossing();
};


#endif //CAR_SIMULATION_GENERATEINI_H

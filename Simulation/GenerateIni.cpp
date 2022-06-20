//
// Created by robbe on 07.05.22.
//

#include "GenerateIni.h"
#include "../Classes/World.h"
#include "../DesignByContract.h"
#include "../Classes/Light.h"
#include "../Classes/BusStop.h"
#include "../Functions.h"
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>

GenerateIni::GenerateIni(World *world, const std::string &filename)
    : world(world),filename(filename), filenumber(1) {
    _initcheck = this;
    std::ofstream file;
    file.open( "../outputFile/Ini/filelist");
    file<<"";
    file.close();
}




void GenerateIni::generate() {
    REQUIRE(world->isValidSimulation(), "World is not valid when calling generate");
    REQUIRE(world->getRoads().size() >= (unsigned int) 1, "At least 1 Road to simulate");
    unsigned int fignum = generateTemp();

    ////////////////

    std::ofstream iniFile;
    std::string name = filename + std::string(3 - floor(log10(filenumber)), '0') + std::itos(filenumber) +".ini";
    iniFile.open(("../outputFile/Ini/" + name).c_str());

    ////////////////
    std::string line;
    std::ifstream General("../Simulation/General");
    ENSURE(General.is_open(),"file is not open");
    if (General && iniFile) {
        while (!General.eof()) {
            getline(General, line);
            if (line == "nrFigures ="){
                iniFile << line << " " << std::itos(fignum) << "\n";
                continue;
            }
            iniFile << line << "\n";
        }
    } else {
        std::cout<<"Cannot read File"<<std::endl;
    }
    General.close();

    ////////////////
    std::ifstream temp2("../Simulation/temp");
    ENSURE(temp2.is_open(),"file is not open");
    if (temp2 && iniFile) {

        while (getline(temp2, line)) {
            iniFile << line << "\n";
        }
    } else {
        std::cout<<"Cannot read File"<<std::endl;
    }
    temp2.close();

    ////////////////

    std::ofstream filelist;
    filelist.open("../outputFile/Ini/filelist", std::ofstream::app);
    filelist << name.c_str();
    filelist << '\n';
    filelist.close();

    filenumber++;
}


unsigned int GenerateIni::generateTemp() {
    std::ofstream temp("../Simulation/temp");
    std::string line;
    unsigned int fignum = 0;
    for (unsigned int r = 0; r < world->getRoads().size(); r++) {
        Road* road = world->getRoads()[r];

        temp << "[Figure" + std::itos(fignum) + "]\ntype = \"LineDrawing\" ";
        temp << "rotateX = 0\nrotateY = 0\nrotateZ = 0\nscale = 1.0";
        temp << "center = (0.1, " + std::dtos(road->getLength() / 2.0 +2.5) + ", " +
                std::itos(r * 25 - 2.5) + ")\n";
        temp << "color = (0.7529, 0.7529, 0.7529)\n";
        temp << "nrPoints = 8\nnrLines = 6\n";

        temp << "point0 = (0.0, 0.0, 0.0)\n";
        temp << "point1 = (0.0, 0.0, 5.0)\n";
        temp << "point2 = (0.0, -" + std::dtos((road->getLength() + 5)) + ", 5.0)\n";
        temp << "point3 = (0.0, -" + std::dtos((road->getLength() + 5)) + ", 0.0)\n";
        temp << "point4 = (1.0, 0.0, 0.0)\n";
        temp << "point5 = (1.0, 0.0, 5.0)\n";
        temp << "point6 = (1.0, -" + std::dtos((road->getLength() + 5)) + ", 5.0)\n";
        temp << "point7 = (1.0, -" + std::dtos((road->getLength() + 5)) + ", 0.0)\n";
        temp
                << "line0 = (0,3,2,1)\nline1 = (4,7,6,5)\nline2 = (0,4,5,1)\nline3 = (0,4,7,3)\nline4 = (3,7,6,2)\nline5 = (1,5,6,2)\n";
        fignum += 1;

        std::vector<std::pair<Junction*,double*> > junctionIt = road->getJunctions();
        for (std::vector<std::pair<Junction*,double*> >::iterator itJ = junctionIt.begin(); itJ != junctionIt.end();itJ++) {
            temp << "[Figure" + std::itos(fignum) + "]\ntype = \"LineDrawing\" ";
            temp << "rotateX = 0\nrotateY = 0\nrotateZ = 0\nscale = 1.0";
            temp << "center = (0.1, " + std::dtos((*itJ->second) - road->getLength() / 2.0) + ", " +
                    std::itos(r * 25 - 2.5) + ")\n";
            temp << "color = (0.7529, 0.7529, 0.7529)\n";
            temp << "nrPoints = 8\nnrLines = 6\n";

            temp << "point0 = (0.0, 0.0, -7.5)\n";
            temp << "point1 = (0.0, 5.0, -7.5)\n";
            temp << "point2 = (0.0, 5.0, 12.5)\n";
            temp << "point3 = (0.0, 0.0, 12.5)\n";
            temp << "point4 = (1.0, 0.0, -7.5)\n";
            temp << "point5 = (1.0, 5.0, -7.5)\n";
            temp << "point6 = (1.0, 5.0, 12.5)\n";
            temp << "point7 = (1.0, 0.0, 12.5)\n";
            temp
                    << "line0 = (0,3,2,1)\nline1 = (4,7,6,5)\nline2 = (0,4,5,1)\nline3 = (0,4,7,3)\nline4 = (3,7,6,2)\nline5 = (1,5,6,2)\n";
            fignum += 1;
            if (itJ->first->hasLights()) {
                std::vector<Light*> l = itJ->first->getLights();
                color c = l[0]->getState();
                bool next = false;
                for (std::vector<Light*>::iterator itL = l.begin(); itL!= l.end(); itL++){
                    if (next){
                        c = (*itL)->getState();
                        break;
                    }
                    if ((*itL)->getRoad() == road){
                        next = true;
                    }
                }
                std::ifstream light;
                if (c == green) {
                    light.open("../Simulation/lightgreen");
                } else if (c == orange) {
                    light.open("../Simulation/lightorange");
                } else if (c == red) {
                    light.open("../Simulation/lightred");
                }
                while (!light.eof()) {
                    getline(light, line);
                    if (line.substr(0, 7) == "[Figure") {
                        temp << "[Figure" + std::itos(fignum) + "]" << "\n";
                        fignum++;
                        continue;
                    }
                    if (line.substr(0, 6) == "center") {
                        std::vector<std::string> strings = std::splitString(line.substr(10, line.size() - 11));
                        temp << "center = (" + strings[0] + "," +
                                std::dtos(std::stod(strings[1]) + *itJ->second -
                                          road->getLength() / 2.0) + "," +
                                std::dtos(std::stod(strings[2]) - 10 + 25 * r) + ")" + "\n";
                    } else {
                        temp << line << "\n";
                    }
                }
            }
        }

        std::vector<Car *> carIt = road->getCars();
        for (std::vector<Car *>::iterator itC = carIt.begin(); itC != carIt.end(); itC++) {
            Type t = (*itC)->getData()->getType();
            std::ifstream car;
            if (t == bus) {
                car.open("../Simulation/bus");
            } else if (t == ambulance) {
                car.open("../Simulation/ambulance");
            } else if (t == police) {
                car.open("../Simulation/politiewagen");
            } else if (t == fire) {
                car.open("../Simulation/brandweer");
            } else if (t == bugatti) {
                car.open("../Simulation/bugatti");
            } else {
                car.open("../Simulation/auto");
            }
            while (!car.eof()) {
                getline(car, line);
                if (line.substr(0, 7) == "[Figure") {
                    temp << "[Figure" + std::itos(fignum) + "]" << "\n";
                    fignum++;
                    continue;
                }
                if (line.substr(0, 6) == "center") {
                    std::vector<std::string> strings = std::splitString(line.substr(10, line.size() - 11));
                    temp << "center = (" + strings[0] + ","
                            + std::dtos(
                            std::stod(strings[1]) + (*itC)->getDistance() - road->getLength() / 2.0) +
                            ","
                            + std::itos(std::stod(strings[2]) + r * 25) + ")" + "\n";
                } else {
                    temp << line << "\n";
                }
            }
        }

        std::vector<Light *> lightIt = road->getLights();
        for (std::vector<Light *>::iterator itL = lightIt.begin(); itL != lightIt.end(); itL++) {
            color c = (*itL)->getState();
            std::ifstream light;
            if (c == green) {
                light.open("../Simulation/lightgreen");
            } else if (c == orange) {
                light.open("../Simulation/lightorange");
            } else if (c == red) {
                light.open("../Simulation/lightred");
            }
            while (!light.eof()) {
                getline(light, line);
                if (line.substr(0, 7) == "[Figure") {
                    temp << "[Figure" + std::itos(fignum) + "]" << "\n";
                    fignum++;
                    continue;
                }
                if (line.substr(0, 6) == "center") {
                    std::vector<std::string> strings = std::splitString(line.substr(10, line.size() - 11));
                    temp << "center = (" + strings[0] + "," +
                            std::dtos(std::stod(strings[1]) + (*itL)->getPosition() -
                                      road->getLength() / 2.0 - 3) + "," +
                            std::dtos(std::stod(strings[2]) + 2.5 + 25 * r) + ")" + "\n";
                } else {
                    temp << line << "\n";
                }
            }
        }

        std::vector<BusStop *> BusstopIt = road->getBusStops();
        for (std::vector<BusStop *>::iterator itBuss = BusstopIt.begin(); itBuss != BusstopIt.end(); itBuss++) {
            std::ifstream busstop("../Simulation/busstop");
            while (!busstop.eof()) {
                getline(busstop, line);
                if (line.substr(0, 7) == "[Figure") {
                    temp << "[Figure" + std::itos(fignum) + "]" << "\n";
                    fignum++;
                    continue;
                }
                if (line.substr(0, 6) == "center") {
                    std::vector<std::string> strings = std::splitString(line.substr(10, line.size() - 11));
                    temp << "center = (" + strings[0] + "," +
                            std::dtos(std::stod(strings[1]) + (*itBuss)->getPosition() -
                                      road->getLength() / 2.0 - 5) + "," +
                            std::dtos(std::stod(strings[2]) + 2.5 + 25 * r) + ")" + "\n";
                } else {
                    temp << line << "\n";
                }
            }
        }
    }
    temp.close();
    return fignum;
}
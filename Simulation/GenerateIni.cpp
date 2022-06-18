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
    unsigned int fignum = 0;
    bool parralellRoad = true;
    for (unsigned int r = 0; r < world->getRoads().size(); r++) {
        if (world->getRoads()[r]->getJunctions().size() != (unsigned int) 0){
            parralellRoad = false;
            break;
        }
    }
    if (parralellRoad){
        fignum = parralellRoads();
    } else{
        return;
    }

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


unsigned int GenerateIni::parralellRoads() {
    std::ofstream temp("../Simulation/temp");
    std::string line;
    unsigned int fignum = 0;
    if(world->getJunctions().size() == 0) {
        for (unsigned int r = 0; r < world->getRoads().size(); r++) {
            temp << "[Figure" + std::itos(fignum) +"]\ntype = \"LineDrawing\" ";
            temp << "rotateX = 0\nrotateY = 0\nrotateZ = 0\nscale = 1.0";
            temp << "center = (0.1, " + std::dtos(world->getRoads()[r]->getLength()/2.0) + ", " + std::itos(r*20 -2.5) + ")\n";
            temp << "color = (0.7529, 0.7529, 0.7529)\n";
            temp << "nrPoints = 10\nnrLines = 6\n";

            temp << "point0 = (0.0, 0.0, 0.0)\n";
            temp << "point1 = (0.0, 0.0, 5.0)\n";
            temp << "point2 = (0.0, -" + std::dtos((world->getRoads()[r]->getLength() + 5)) + ", 5.0)\n";
            temp << "point3 = (0.0, -" + std::dtos((world->getRoads()[r]->getLength() + 5)) + ", 0.0)\n";
            temp << "point4 = (1.0, 0.0, 0.0)\n";
            temp << "point5 = (1.0, 0.0, 5.0)\n";
            temp << "point6 = (1.0, -" + std::dtos((world->getRoads()[r]->getLength() + 5)) + ", 5.0)\n";
            temp << "point7 = (1.0, -" + std::dtos((world->getRoads()[r]->getLength() + 5)) + ", 0.0)\n";
            temp << "point8 = (-10.0, 0.0, 0.0)\n";
            temp << "point9 = (8.0, 0.0, 0.0)\n";
            temp << "line0 = (0,3,2,1)\nline1 = (4,7,6,5)\nline2 = (0,4,5,1)\nline3 = (0,4,7,3)\nline4 = (3,7,6,2)\nline5 = (1,5,6,2)\n";
            fignum += 1;

            std::vector<Car *> carIt = world->getRoads()[r]->getCars();
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
                                + std::dtos(std::stod(strings[1]) + (*itC)->getDistance() - world->getRoads()[r]->getLength()/2.0) + ","
                                + std::itos(std::stod(strings[2]) + r*20) + ")" + "\n";
                    } else {
                        temp << line << "\n";
                    }
                }
            }

            std::vector<Light *> lightIt = world->getRoads()[r]->getLights();
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
                                std::dtos(std::stod(strings[1]) + (*itL)->getPosition() - world->getRoads()[r]->getLength()/2.0 -5) + "," +
                                std::dtos(std::stod(strings[2]) + 2.5 +20*r) + ")" + "\n";
                    } else {
                        temp << line << "\n";
                    }
                }
            }

            std::vector<BusStop *> BusstopIt = world->getRoads()[r]->getBusStops();
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
                                std::dtos(std::stod(strings[1]) + (*itBuss)->getPosition() - world->getRoads()[r]->getLength()/2.0 -5) + "," +
                                std::dtos(std::stod(strings[2]) + 2.5+20*r) + ")" + "\n";
                    } else {
                        temp << line << "\n";
                    }
                }
            }
        }
    }
    temp.close();
    return fignum;
}



unsigned int GenerateIni::singleCrossing() {
    std::ofstream temp("../Simulation/temp");
    std::string line;
    unsigned int fignum = 0;
    if(world->getJunctions().size() == 0) {
        for (unsigned int r = 0; r < world->getRoads().size(); r++) {
            temp << "[Figure" + std::itos(fignum) +"]\ntype = \"LineDrawing\" ";
            temp << "rotateX = 0\nrotateY = 0\nrotateZ = 0\nscale = 1.0";
            temp << "center = (0.1, " + std::dtos(world->getRoads()[r]->getLength()/2.0) + ", " + std::itos(r*20 -2.5) + ")\n";
            temp << "color = (0.7529, 0.7529, 0.7529)\n";
            temp << "nrPoints = 10\nnrLines = 6\n";

            temp << "point0 = (0.0, 0.0, 0.0)\n";
            temp << "point1 = (0.0, 0.0, 5.0)\n";
            temp << "point2 = (0.0, -" + std::dtos((world->getRoads()[r]->getLength() + 5)) + ", 5.0)\n";
            temp << "point3 = (0.0, -" + std::dtos((world->getRoads()[r]->getLength() + 5)) + ", 0.0)\n";
            temp << "point4 = (1.0, 0.0, 0.0)\n";
            temp << "point5 = (1.0, 0.0, 5.0)\n";
            temp << "point6 = (1.0, -" + std::dtos((world->getRoads()[r]->getLength() + 5)) + ", 5.0)\n";
            temp << "point7 = (1.0, -" + std::dtos((world->getRoads()[r]->getLength() + 5)) + ", 0.0)\n";
            temp << "point8 = (-10.0, 0.0, 0.0)\n";
            temp << "point9 = (8.0, 0.0, 0.0)\n";
            temp << "line0 = (0,3,2,1)\nline1 = (4,7,6,5)\nline2 = (0,4,5,1)\nline3 = (0,4,7,3)\nline4 = (3,7,6,2)\nline5 = (1,5,6,2)\n";
            fignum += 1;

            std::vector<Car *> carIt = world->getRoads()[r]->getCars();
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
                                + std::dtos(std::stod(strings[1]) + (*itC)->getDistance() - world->getRoads()[r]->getLength()/2.0) + ","
                                + std::itos(std::stod(strings[2]) + r*20) + ")" + "\n";
                    } else {
                        temp << line << "\n";
                    }
                }
            }

            std::vector<Light *> lightIt = world->getRoads()[r]->getLights();
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
                                std::dtos(std::stod(strings[1]) + (*itL)->getPosition() - world->getRoads()[r]->getLength()/2.0 -5) + "," +
                                std::dtos(std::stod(strings[2]) + 2.5 +20*r) + ")" + "\n";
                    } else {
                        temp << line << "\n";
                    }
                }
            }

            std::vector<BusStop *> BusstopIt = world->getRoads()[r]->getBusStops();
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
                                std::dtos(std::stod(strings[1]) + (*itBuss)->getPosition() - world->getRoads()[r]->getLength()/2.0 -5) + "," +
                                std::dtos(std::stod(strings[2]) + 2.5+20*r) + ")" + "\n";
                    } else {
                        temp << line << "\n";
                    }
                }
            }
        }
    }
    temp.close();
    return fignum;
}
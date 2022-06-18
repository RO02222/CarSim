#include "Input.h"
#include "Functions.h"
#include "tinyxml/tinyxml.h"
#include "Classes/World.h"
#include "Classes/Road.h"
#include "Classes/Light.h"
#include "Classes/Car.h"
#include "Classes/CarGen.h"
#include "Classes/Junction.h"
#include "DesignByContract.h"
#include "Exception/ParserException.h"



namespace input {
    World *loadWorldXML(const char *worldName) {
        World *world = new World();
        TiXmlDocument doc;
        if (!doc.LoadFile(worldName)) {
            world->error << doc.ErrorDesc() << std::endl;
            return world;
        }
        TiXmlElement *root = doc.FirstChildElement();
        if (root == NULL) {
            world->error << "Failed to load file: No root element." << std::endl;
            return world;
        }
        TiXmlElement *elem = root;
        if ((std::string) elem->Value() != "World") {
            world->error << "Failed to load file: <World> ... </World>" << std::endl;
            return world;
        }
        for (TiXmlElement *elem1 = elem->FirstChildElement(); elem1 != 0; elem1 = elem1->NextSiblingElement()) {
            if ((std::string) elem1->Value() == "BAAN") {
                _::loadRoadXML(world, elem1);
            }
        }
        for (TiXmlElement *elem1 = elem->FirstChildElement(); elem1 != 0; elem1 = elem1->NextSiblingElement()) {
            if ((std::string) elem1->Value() == "KRUISPUNT") {
                _::loadJunctionXML(world, elem1);
                continue;
            }
        }
        for (TiXmlElement *elem1 = elem->FirstChildElement(); elem1 != NULL; elem1 = elem1->NextSiblingElement()) {
            if ((std::string) elem1->Value() == "BAAN") {
                continue;
            }
            if ((std::string) elem1->Value() == "VERKEERSLICHT") {
                _::loadLightXML(world, elem1);
                continue;
            }
            if ((std::string) elem1->Value() == "VOERTUIG") {

                _::loadCarXML(world, elem1);
                continue;
            }
            if ((std::string) elem1->Value() == "VOERTUIGGENERATOR") {
                _::loadCarGenXML(world, elem1);
                continue;
            }
            if ((std::string) elem1->Value() == "BUSHALTE") {
                _::loadBusstopXML(world, elem1);
                continue;
            }
            if ((std::string) elem1->Value() == "KRUISPUNT") {
                continue;
            }
            world->error << "Failed to load file: <" + (std::string) elem1->Value() + "> is not valid" << std::endl;
        }
        for (std::vector<Junction*>::iterator itJ = world->getJunctions().begin(); itJ != world->getJunctions().end();itJ++){
            (*itJ)->checkJunctionLights();
        }
        return world;
    }

    namespace _ {

        void loadRoadXML(World *world, TiXmlElement *elem1) {
            REQUIRE(world->properlyInitialized(),
                    "World wasn't initialized when calling private function of loadWorldXML");
            std::string name = "";
            std::string length = "";
            for (TiXmlElement *elem2 = elem1->FirstChildElement(); elem2 != 0; elem2 = elem2->NextSiblingElement()) {
                if (elem2->GetText() == NULL) {
                    world->error << "Failed to load file: <" + (std::string) elem2->Value() + "> has no value"
                              << std::endl;
                    continue;
                }
                if ((std::string) elem2->Value() == "naam") {
                    name = elem2->GetText();
                    continue;
                }
                if ((std::string) elem2->Value() == "lengte") {
                    length = elem2->GetText();
                    continue;
                }
                world->error << "Failed to load file: <BAAN> : <" + (std::string) elem2->Value()
                             + "> is not valid" << std::endl;
            }
            if (name.empty()) {
                world->error << "Failed to load file: invalid <BAAN> : 'missing argument' <naam>" << std::endl;
                return;
            }
            if (length.empty()) {
                world->error << "Failed to load file: invalid <BAAN> : 'missing argument' <lengte>" << std::endl;
                return;
            }
            world->addRoad(name, std::stoi(length));
        }


        void loadLightXML(World *world, TiXmlElement *elem1) {
            REQUIRE(world->properlyInitialized(),
                    "World wasn't initialized when calling private function of loadWorldXML");
            std::string roadName = "";
            std::string position = "";
            std::string cycle = "";
            for (TiXmlElement *elem2 = elem1->FirstChildElement(); elem2 != 0; elem2 = elem2->NextSiblingElement()) {
                if (elem2->GetText() == NULL) {
                    world->error << "Failed to load file: <" + (std::string) elem2->Value() + "> has no value"
                                 << std::endl;
                    continue;
                }
                if ((std::string) elem2->Value() == "baan") {
                    roadName = elem2->GetText();
                    continue;
                }
                if ((std::string) elem2->Value() == "positie") {
                    position = elem2->GetText();
                    continue;
                }
                if ((std::string) elem2->Value() == "cyclus") {
                    cycle = elem2->GetText();
                    continue;
                }
                world->error << "Failed to load file: <VERKEERSLICHT> : <"
                                + (std::string) elem2->Value() + "> is not valid" << std::endl;
            }
            if (roadName.empty()) {
                world->error << "Failed to load file: invalid <VERKEERSLICHT> : 'missing argument' <baan>" << std::endl;
                return;
            }
            if (position.empty()) {
                world->error << "Failed to load file: invalid <VERKEERSLICHT> : 'missing argument' <positie>"
                             << std::endl;
                return;
            }
            if (cycle.empty()) {
                world->error << "Failed to load file: invalid <VERKEERSLICHT> : 'missing argument' <cyclus>"
                             << std::endl;
                return;
            }
            Road *road = NULL;
            std::vector<Road *> roadIt = world->getRoads();
            for (std::vector<Road *>::iterator it = roadIt.begin(); it != roadIt.end(); it++) {
                if ((*it)->getName() == roadName) {
                    road = (*it);
                    break;
                }
            }

            if (road == NULL) {
                world->error << "Failed to load file: invalid <VERKEERSLICHT> : '<baan>' does not exist" << std::endl;
                return;
            }
            if (std::stoi(cycle) < 1) {
                world->error << "Failed to load file: invalid <VERKEERSLICHT> : '<cyclus>' must be at least 1"
                             << std::endl;
                return;
            }
            if (!road->isValidToAdd(std::stoi(position))) {
                world->error << "Failed to load file: invalid <VERKEERSLICHT> : 'cannot add <VERKEERSLICHT>"
                             << std::endl;
                return;
            }
            road->addLight(std::stoi(position), std::stoi(cycle));
        }


        void loadCarXML(World *world, TiXmlElement *elem1) {
            REQUIRE(world->properlyInitialized(),
                    "World wasn't initialized when calling private function of loadWorldXML");
            std::string roadName = "";
            std::string position = "";
            std::string type = "";
            Type Type;
            for (TiXmlElement *elem2 = elem1->FirstChildElement(); elem2 != 0; elem2 = elem2->NextSiblingElement()) {
                if (elem2->GetText() == NULL) {
                    world->error << "Failed to load file: <" + (std::string) elem2->Value() + "> has no value"
                              << std::endl;
                    return;
                }
                if ((std::string) elem2->Value() == "baan") {
                    roadName = elem2->GetText();
                    continue;
                }
                if ((std::string) elem2->Value() == "positie") {
                    position = elem2->GetText();
                    continue;
                }
                if ((std::string) elem2->Value() == "type") {
                    type = elem2->GetText();
                    continue;
                }
                world->error << "Failed to load file: <VOERTUIG> : <" + (std::string) elem2->Value()
                             + "> is not valid" << std::endl;
            }
            if (roadName.empty()) {
                world->error << "Failed to load file: invalid <VOERTUIG> : 'missing argument' <baan>" << std::endl;
                return;
            }
            if (position.empty()) {
                world->error << "Failed to load file: invalid <VOERTUIG> : 'missing argument' <positie>" << std::endl;
                return;
            }
            if (type.empty()) {
                world->error << "Failed to load file: invalid <VOERTUIG> : 'missing argument' <type>" << std::endl;
                return;
            }
            if (type == "auto" or type == "car") {
                Type = car;
            }else if (type == "bus") {
                Type = bus;
            }else if (type == "brandweerwagen" or type == "firetruck") {
                Type = fire;
            }else if (type == "ziekenwagen" or type == "ambulance") {
                Type = ambulance;
            }else if (type == "politiecombi" or type == "politiewagen" or type == "cop") {
                Type = police;
            }else if (type == "bugatti") {
                Type = bugatti;
            }else{
                world->error << "Failed to load file: invalid <VOERTUIG> : 'invalid argument' <type>" << std::endl;
                return;
            }

            Road *road = NULL;
            std::vector<Road *> roadIt = world->getRoads();
            for (std::vector<Road *>::iterator it = roadIt.begin(); it != roadIt.end(); it++) {
                if ((*it)->getName() == roadName) {
                    road = (*it);
                    break;
                }
            }
            if (road == NULL) {
                world->error << "Failed to load file: invalid <VOERTUIG> : '<baan> does not exist" << std::endl;
                return;
            }
            if (!road->isValidToAddCar(std::stoi(position),world->getCarData(Type)->getlength())) {
                world->error << "Failed to load file: invalid <VOERTUIG> : cannot add car to the road" << std::endl;
            } else {
                road->addCar(std::stoi(position), world->getCarData(Type));
            }
        }


        void loadCarGenXML(World *world, TiXmlElement *elem1) {
            REQUIRE(world->properlyInitialized(),
                    "World wasn't initialized when calling private function of loadWorldXML");
            std::string roadName = "";
            std::string frequency = "";
            std::string type = "";
            Type Type;
            for (TiXmlElement *elem2 = elem1->FirstChildElement(); elem2 != 0; elem2 = elem2->NextSiblingElement()) {
                if (elem2->GetText() == NULL) {
                    world->error << "Failed to load file: <" + (std::string) elem2->Value()
                                 + "> has no value" << std::endl;
                    continue;
                }
                if ((std::string) elem2->Value() == "baan") {
                    roadName = elem2->GetText();
                    continue;
                }
                if ((std::string) elem2->Value() == "frequentie") {
                    frequency = elem2->GetText();
                    continue;
                }
                if ((std::string) elem2->Value() == "type") {
                    type = elem2->GetText();
                    continue;
                }
                world->error << "Failed to load file: <VOERTUIGGENERATOR> : <" + (std::string) elem2->Value()
                             + "> is not valid" << std::endl;
            }
            if (roadName.empty()) {
                world->error << "Failed to load file: invalid <VOERTUIGGENERATOR> : 'missing argument' <baan>"
                          << std::endl;
                return;
            }
            if (frequency.empty()) {
                world->error << "Failed to load file: invalid <VOERTUIGGENERATOR> : 'missing argument' <frequentie>"
                          << std::endl;
                return;
            }
            if (type.empty() or type == "none" or type == "None" or type == "random") {
                Type = none;
            } else if (type == "auto" or type == "car") {
                Type = car;
            }else if (type == "bus") {
                Type = bus;
            }else if (type == "brandweerwagen" or type == "firetruck") {
                Type = fire;
            }else if (type == "ziekenwagen" or type == "ambulance") {
                Type = ambulance;
            }else if (type == "politiecombi" or type == "politiewagen" or type == "cop") {
                Type = police;
            }else if (type == "bugatti") {
                Type = bugatti;
            }else{
                world->error << "Failed to load file: invalid <VOERTUIGGENERATOR> : 'invalid argument' <type>" << std::endl;
                return;
            }
            Road *road = NULL;
            std::vector<Road *> roadIt = world->getRoads();
            for (std::vector<Road *>::iterator it = roadIt.begin(); it != roadIt.end(); it++) {
                if ((*it)->getName() == roadName) {
                    road = (*it);
                    break;
                }
            }
            if (road == NULL) {
                world->error << "Failed to load file: invalid <VOERTUIGGENERATOR> : '<baan> does not exist" << std::endl;
                return;
            }
            if (std::stoi(frequency) < 1){
                world->error << "Failed to load file: invalid <VOERTUIGGENERATOR> : '<frequentie> must be at least 1" << std::endl;
            }
            if (Type == none){
                road->addCarGen(std::stoi(frequency),world->getAllData());
            } else {
                road->addCarGen(std::stoi(frequency), world->getCarData(Type));
            }
        }

        void loadBusstopXML(World *world, TiXmlElement *elem1) {
            REQUIRE(world->properlyInitialized(),
                    "World wasn't initialized when calling private function of loadWorldXML");
            std::string roadName = "";
            std::string position = "";
            std::string stoptime = "";
            for (TiXmlElement *elem2 = elem1->FirstChildElement(); elem2 != 0; elem2 = elem2->NextSiblingElement()) {
                if (elem2->GetText() == NULL) {
                    world->error << "Failed to load file: <" + (std::string) elem2->Value() + "> has no value"
                              << std::endl;
                    continue;
                }
                if ((std::string) elem2->Value() == "baan") {
                    roadName = elem2->GetText();
                    continue;
                }
                if ((std::string) elem2->Value() == "positie") {
                    position = elem2->GetText();
                    continue;
                }
                if ((std::string) elem2->Value() == "wachttijd") {
                    stoptime = elem2->GetText();
                    continue;
                }
                world->error << "Failed to load file: <BUSHALTE> : <"
                             + (std::string) elem2->Value() + "> is not valid" << std::endl;
            }
            if (roadName.empty()) {
                world->error << "Failed to load file: invalid <BUSHALTE> : 'missing argument' <baan>" << std::endl;
                return;
            }
            if (position.empty()) {
                world->error << "Failed to load file: invalid <BUSHALTE> : 'missing argument' <positie>" << std::endl;
                return;
            }
            if (stoptime.empty()) {
                world->error << "Failed to load file: invalid <BUSHALTE> : 'missing argument' <wachttijd>" << std::endl;
                return;
            }
            Road *road = NULL;
            std::vector<Road *> roadIt = world->getRoads();
            for (std::vector<Road *>::iterator it = roadIt.begin(); it != roadIt.end(); it++) {
                if ((*it)->getName() == roadName) {
                    road = (*it);
                    break;
                }
            }
            if (road == NULL) {
                world->error << "Failed to load file: invalid <BUSHALTE> : '<baan>' does not exist" << std::endl;
                return;
            }
            if (std::stoi(stoptime) < 0) {
                world->error << "Failed to load file: invalid <BUSHALTE> : '<wachttijd>' cannot be negative" << std::endl;
                return;
            }
            if (!road->isValidToAdd(std::stoi(position))){
                world->error << "Failed to load file: invalid <BUSHALTE> : 'cannot add <BUSHALTE> to the road" << std::endl;
                return;
            }
            road->addBusStop(std::stoi(position), std::stoi(stoptime));
        }


        void loadJunctionXML(World *world, TiXmlElement *elem1) {
            REQUIRE(world->properlyInitialized(),
                    "World wasn't initialized when calling private function of loadWorldXML");
            std::vector<std::string> roadNames;
            std::vector<std::string> positions;
            for (TiXmlElement *elem2 = elem1->FirstChildElement(); elem2 != 0; elem2 = elem2->NextSiblingElement()) {
                if (elem2->GetText() == NULL) {
                    world->error << "Failed to load file: <" + (std::string) elem2->Value() + "> has no value"
                                 << std::endl;
                    continue;
                }
                if ((std::string) elem2->Value() == "baan") { ;
                    if (elem2->LastAttribute() != 0) {
                        roadNames.push_back(elem2->GetText());
                        positions.push_back(elem2->LastAttribute()->Value());
                    }
                }
            }
            if (roadNames.empty()) {
                world->error << "Failed to load file: invalid <KRUISPUNT> : 'missing argument' <baan>" << std::endl;
                return;
            }
            if (positions.empty()) {
                world->error << "Failed to load file: invalid <KRUISPUNT> : 'missing argument' <positie>" << std::endl;
                return;
            }
            std::vector<std::pair<Road *, double> > roads;
            std::vector<Road *> roadIt = world->getRoads();
            for (unsigned int i = 0; i < roadNames.size(); i++) {
                bool found = false;
                for (std::vector<Road *>::iterator it = roadIt.begin(); it != roadIt.end(); it++) {
                    if ((*it)->getName() == roadNames[i]) {
                        roads.push_back(std::pair<Road *, double>(*it, std::stoi(positions[i])));
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    world->error << "Failed to load file: invalid <KRUISPUNT> : '<baan>' does not exist"
                                 << std::endl;
                }
            }
            if (roads.size() < 2){
                world->error << "Failed to load file: invalid <KRUISPUNT> : not enough roads" << std::endl;
                return;
            }
            if (!world->isValidToAddJunction(roads)){
                world->error << "Failed to load file: invalid <KRUISPUNT> : cannot add <KRUISPUNT>" << std::endl;
                return;
            }
            world->addJunction(roads);
        }
    }
}
///////////////////////
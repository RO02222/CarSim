//
// Created by robbe on 30.03.22.
//

#ifndef CAR_SIMULATION_INPUT_H
#define CAR_SIMULATION_INPUT_H
class World;
class TiXmlElement;
namespace input {
/**
 * load a World from a file XML file
 * @param worldName: name of the XML file
 * @return: (World*), the loaded world
\n
*/
    World* loadWorldXML(const char *worldName);

    namespace _ { //private
/**
 * load a Road from a XML file
 * @param world: world that will be loaded to
 * @param elem1: part of the XML file
 * @return: None
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling private function of loadWorldXML);
*/
        void loadRoadXML(World *world, TiXmlElement *elem1);

/**
 * load a Light from a XML file
 * @param world: world that will be loaded to
 * @param elem1: part of the XML file
 * @return: None
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling private function of loadWorldXML);
*/
        void loadLightXML(World *world, TiXmlElement *elem1);

/**
 * load a Car from a XML file
 * @param world: world that will be loaded to
 * @param elem1: part of the XML file
 * @return: None
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling private function of loadWorldXML);
*/
        void loadCarXML(World *world, TiXmlElement *elem1);

/**
 * load a CarGen from a XML file
 * @param world: world that will be loaded to
 * @param elem1: part of the XML file
 * @return: None
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling private function of loadWorldXML);
*/
        void loadCarGenXML(World *world, TiXmlElement *elem1);

/**
 * load a CarGen from a XML file
 * @param world: world that will be loaded to
 * @param elem1: part of the XML file
 * @return: None
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling private function of loadWorldXML);
*/
        void loadBusstopXML(World *world, TiXmlElement *elem1);

/**
 * load a junction from a XML file
 * @param world: world that will be loaded to
 * @param elem1: part of the XML file
 * @return: None
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling private function of loadWorldXML);
*/
        void loadJunctionXML(World *world, TiXmlElement *elem1);
    }
}


#endif //CAR_SIMULATION_INPUT_H

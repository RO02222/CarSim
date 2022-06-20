//============================================================================
// Name        : TestMain.cpp
// Date        : 18/06/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 4
//============================================================================

#include "Test/Car_SimDomainTest.cpp"
#include "Test/CarGenDomainTest.cpp"
#include "Test/CarDomainTest.cpp"
#include "Test/LightDomainTest.cpp"
#include "Test/RoadDomainTest.cpp"
#include "Test/WorldDomainTest.cpp"
#include "Test/Car_SimInputTest.cpp"
#include "Test/Car_SimOutputTest.cpp"
#include "Test/BusStopDomainTest.cpp"
#include "Test/JunctionDomainTest.cpp"
#include "Test/ClockDomainTest.cpp"
#include <iostream>
#include <fstream>
#include <sys/stat.h>


using namespace std;


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
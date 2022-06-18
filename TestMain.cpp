//============================================================================
// Name        : TicTactToeOutputTest.cpp
// Author      : Serge Demeyer
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Serge Demeyer - University of Antwerp
// Description : TicTactToe in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <sys/stat.h>


using namespace std;

#include "Test/Car_SimDomainTest.cpp"
#include "Test/CarGenDomainTest.cpp"
#include "Test/LightDomainTest.cpp"
#include "Test/RoadDomainTest.cpp"
#include "Test/WorldDomainTest.cpp"
#include "Test/Car_SimInputTest.cpp"
#include "Test/Car_SimOutputTest.cpp"
#include "Test/BusStopDomainTest.cpp"
#include "Test/JunctionDomainTest.cpp"
#include "Test/ClockDomainTest.cpp"



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
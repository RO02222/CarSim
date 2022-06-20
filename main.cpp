//============================================================================
// Name        : Main.cpp
// Date        : 18/06/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 4
//============================================================================


#include <iostream>
#include <fstream>
#include "Classes/World.h"
#include "Basic_Values.h"
#include "Input.h"
#include "Classes/BusStop.h"
#include "Classes/Junction.h"
#include "Classes/CarData.h"
#include "Simulation/GenerateIni.h"
#include <syscall.h>

#if VERSION == 14
#include <chrono>
#include <thread>

int main() {
    World* w = input::loadWorldXML("../testInput/testCase5.xml");
    w->isValid();
    std::ofstream myFile;
    std::ofstream myFile2;
    myFile.open("../outputFile/Car_sim.txt");
    myFile2.open("../outputFile/Car_sim2.txt");
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    for (unsigned int i =0; i < 10000; i++) {
        w->simpleSimulateWorld(myFile);
        w->graficImpSimulateWorld(myFile2);
        std::cout<<w->getTime()<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(40));
        for (unsigned int _ = 0; _ < 10; _ += 1) {
            w->updateWorld(0.01);
        }
    }
    myFile.close();
    myFile2.close();
    delete w;
    return 0;
}
#endif
#if VERSION == 98
int main() {
    //World* w = input::loadWorldXML("../XML/bugattiVScar.xml");
    //World* w = input::loadWorldXML("../XML/case1.xml");

    //World* w = input::loadWorldXML("../XML/case3.xml");
    srand(123);
    World* w = input::loadWorldXML("../XML/case1.xml");
    GenerateIni g(w, "sim");
    std::ofstream myFile;
    std::ofstream myFile1;
    myFile.open("../outputFile/Car_sim.txt");
    myFile1.open("../outputFile/Car_sim2.txt");
    for (unsigned int i = 0; i<300; i++) {
        g.generate();
        w->graficImpSimulateWorld(myFile1);
        w->simpleSimulateWorld(myFile);
        for (unsigned int _ = 0; _<2; _++) {
            w->updateWorld(0.05);
        }
    }
    /*
    //World* w = input::loadWorldXML("../testInput/testFail13.xml");
    //World* w = input::loadWorldXML("../testInput/testFail2.xml");
    //World* w = input::loadWorldXML("../testInput/test1.xml");
    std::ofstream myFile;
    std::ofstream myFile2;
    myFile.open("../outputFile/Car_sim.txt");
    myFile2.open("../outputFile/Car_sim2.txt");
    for (unsigned int i =0; i < 10000; i++) {
        w->simpleSimulateWorld(myFile);
        w->graficImpSimulateWorld(myFile2);
        for (unsigned int _ = 0; _ < 5; _ += 1) {
            w->updateWorld(0.01);
        }
    }
    myFile.close();
    myFile2.close();
     */
    delete w;

    //system("../new_engine.exe");
    return 0;
}/*

    srand(123);
    World *w = input::loadWorldXML("../testInput/testCase2.xml");
    std::ofstream myFile;
    std::ofstream myFile1;
    myFile.open("../outputFile/Car_sim.txt");
    myFile1.open("../outputFile/Car_sim2.txt");
    w->graficImpSimulateWorld(myFile1);
    w->simpleSimulateWorld(myFile);
    for (unsigned int i = 0; i < 200; i++) {
        for (unsigned int _ = 0; _ < 50; _++) {
            w->updateWorld(0.01);
        }
        w->graficImpSimulateWorld(myFile1);
        w->simpleSimulateWorld(myFile);
    }
    myFile.close();
    delete w;
}*/
#endif
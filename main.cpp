//============================================================================
// Name        : Main.cpp
// Date        : 18/06/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 4
//============================================================================


#include <iostream>
#include <fstream>
#include "Basic_Values.h"
#include "Input.h"
#include "Classes/World.h"
#include "Classes/BusStop.h"
#include "Classes/Junction.h"
#include "Classes/CarData.h"
#include "Simulation/GenerateIni.h"
#include <syscall.h>

#if VERSION == 14
#include <chrono>
#include <thread>

int main(int argc, char **argv) {
    if (argc == 1){
        std::cout << "requires inputfile"<<std::endl;
        return 0;
    }
    World* w = input::loadWorldXML(argv[1]);
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
/*
int main() {
    srand(123);
    World *w = input::loadWorldXML("../testInput/testCase8.xml");
    GenerateIni g(w, "sim");
    for (unsigned int i = 0; i < 5; i++) {
        g.generate();
        for (unsigned int _ = 0; _ < 10; _++) {
            w->updateWorld(0.1);
        }
    }
    std::ofstream myFile;
    myFile.close();
    delete w;
}*/

int main(int argc, char **argv) {
    if (argc == 1){
        std::cout << "requires inputfile"<<std::endl;
        return 0;
    }
    std::cout<<"loading "<<argv[1]<<std::endl;
    World* w = input::loadWorldXML(argv[1]);
    w->isValid();
    GenerateIni g(w, "sim");
    std::ofstream myFile;
    std::ofstream myFile2;
    myFile.open("../outputFile/Car_sim.txt");
    myFile2.open("../outputFile/Car_sim2.txt");
    for (unsigned int i =0; i < 1000; i++) {
        w->simpleSimulateWorld(myFile);
        w->graficImpSimulateWorld(myFile2);
        g.generate();
        for (unsigned int _ = 0; _ < 10; _ += 1) {
            w->updateWorld(0.01);
        }
    }
    myFile.close();
    myFile2.close();
    delete w;
    return 0;
}


/*
{
    srand(123);
    World *w = input::loadWorldXML("../testInput/testCase2.xml");
    std::ofstream myFile;
    std::ofstream myFile2;
    myFile2.open("../outputFile/Car_sim.txt");
    myFile.open("../outputFile/Car_sim2.txt");
    w->graficImpSimulateWorld(myFile);
    w->simpleSimulateWorld(myFile2);
    for (unsigned int i = 0; i < 200; i++) {
        for (unsigned int _ = 0; _ < 50; _++) {
            w->updateWorld(0.01);
        }
        w->graficImpSimulateWorld(myFile);
        w->simpleSimulateWorld(myFile2);
    }
    myFile.close();
    myFile2.close();
    delete w;
    return 0;
}*/
#endif
//============================================================================
// Name        : Car_SimDomainTest.cpp
// Date        : 19/03/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 1
//============================================================================


#include "Functions.h"
#include "Classes/CarData.h"
#include "Classes/Road.h"
#include <iostream>
#include <sstream>
#include <cstdlib>

namespace std {
    int stoi(std::string &text) {
        std::istringstream iss(text);
        int number;
        iss >> number;
        return number;
    }

    string itos(int a) {
        stringstream ss;
        ss << a;
        string str = ss.str();
        return str;
    }

    double stod(std::string& x) {
        double temp = ::atof(x.c_str());
        return temp;
    }

    string dtos(double d){
        stringstream ss;
        ss << d;
        string str = ss.str();
        return str;
    }

    std::vector<std::string> splitString(std::string str) {
        vector<std::string> strings;
        string w = "";
        for (unsigned int i=0; i<str.size(); i++) {
            if (str[i] == ',') {
                strings.push_back(w);
                w = "";
            } else {
                w = w + str[i];
            }
        }
        if (w.size()!=0 and w!=" "){
            strings.push_back(w);
        }
        return strings;
    }
}

bool isvalid(std::vector<CarData*>* data){
    for (std::vector<CarData*>::iterator da = data->begin(); da != data->end(); da++){
        if (!(*da)->isValid()) {
            return false;
        }
    }
    return true;
}

bool isvalid(std::vector<std::pair<Road*, double> > roads){
    for (std::vector<std::pair<Road*, double> >::iterator itR = roads.begin(); itR != roads.end(); itR++){
        if (!itR->first->isValid()) {
            return false;
        }

    }
    return true;
}

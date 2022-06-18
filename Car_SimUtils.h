//============================================================================
// Name        : TicTacToeUtils.cpp
// Author      : Serge Demeyer
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Serge Demeyer - University of Antwerp
// Description : TicTactToe in C++, Ansi-style
//============================================================================

#ifndef CAR_SIMULATION_CAR_SIMUTILS_H
#define CAR_SIMULATION_CAR_SIMUTILS_H

#include "Classes/World.h"
#include <iostream>

bool DirectoryExists(const std::string dirname);

bool FileExists(const std::string dirname);

bool FileIsEmpty(const std::string filename);

bool FileCompare(const std::string leftFileName, const std::string rightFileName);


#endif //CAR_SIMULATION_CAR_SIMUTILS_H

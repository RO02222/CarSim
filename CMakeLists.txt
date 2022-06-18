cmake_minimum_required(VERSION 3.6)
project(CarSim)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Werror")
set(CMAKE_EXE_LINKER_FLAGS -pthread)

# Set include dir
include_directories(gtest/include)

# Set Library dir
link_directories(gtest/lib)

# Set source files for RELEASE target
set(RELEASE_SOURCE_FILES
        main.cpp
        tinyxml/tinystr.h tinyxml/tinystr.cpp tinyxml/tinyxml.h tinyxml/tinyxml.cpp tinyxml/tinyxmlparser.cpp tinyxml/tinyxmlerror.cpp
        Classes/World.cpp Classes/World.h
        Classes/Road.cpp Classes/Road.h
        Classes/Light.cpp Classes/Light.h
        Classes/Car.cpp Classes/Car.h
        Classes/BusStop.cpp Classes/BusStop.h
        Classes/Junction.cpp Classes/Junction.h
        Classes/CarData.cpp Classes/CarData.h
        Classes/Clock.cpp Classes/Clock.h
        Input.cpp Input.h
        Exception/ParserException.h
        Classes/CarGen.cpp Classes/CarGen.h
        DesignByContract.h Basic_Values.h
        Functions.cpp Functions.h
        Car_SimUtils.cpp Car_SimUtils.h
        Simulation/GenerateIni.cpp Simulation/GenerateIni.h)

# Set source files for DEBUG target
set(DEBUG_SOURCE_FILES
        TestMain.cpp
        tinyxml/tinystr.h tinyxml/tinystr.cpp tinyxml/tinyxml.h tinyxml/tinyxml.cpp tinyxml/tinyxmlparser.cpp tinyxml/tinyxmlerror.cpp
        Classes/World.cpp Classes/World.h
        Classes/Road.cpp Classes/Road.h
        Classes/Light.cpp Classes/Light.h
        Classes/Car.cpp Classes/Car.h
        Classes/BusStop.cpp Classes/BusStop.h
        Classes/Junction.cpp Classes/Junction.h
        Classes/CarData.cpp Classes/CarData.h
        Classes/Clock.cpp Classes/Clock.h
        Input.cpp Input.h
        Exception/ParserException.h
        Classes/CarGen.cpp Classes/CarGen.h DesignByContract.h Basic_Values.h Functions.cpp Functions.h
        Car_SimUtils.cpp Car_SimUtils.h
        Simulation/GenerateIni.cpp Simulation/GenerateIni.h
        )

# Create RELEASE target
add_executable(Car_Simulation ${RELEASE_SOURCE_FILES})

# Create DEBUG target
add_executable(Car_Simulation_debug ${DEBUG_SOURCE_FILES})

# Link library
target_link_libraries(Car_Simulation_debug gtest)
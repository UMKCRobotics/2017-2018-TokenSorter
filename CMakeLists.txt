cmake_minimum_required(VERSION 3.6)
project(2017_2018_TokenSorter)

set(CMAKE_CXX_STANDARD 11)

include_directories(
        color-sensor-test/lib/Adafruit_TCS34725
        navigation-test/lib/Movement
        navigation-test/lib/Navigation)

set(SOURCE_FILES
        color-sensor-test/lib/Adafruit_TCS34725/Adafruit_TCS34725.cpp
        color-sensor-test/lib/Adafruit_TCS34725/Adafruit_TCS34725.h
        color-sensor-test/sketch/sketch.ino
        color-sensor-test/jno.jno
        navigation-test/lib/Movement/Movement.cpp
        navigation-test/lib/Movement/Movement.h
        navigation-test/lib/Navigation/Gameboard.cpp
        navigation-test/lib/Navigation/Intersection.cpp
        navigation-test/lib/Navigation/IntersectionState.cpp
        navigation-test/lib/Navigation/Navigation.cpp
        navigation-test/lib/Navigation/Navigation.h
        navigation-test/lib/ScrapController/ScrapController.cpp
        navigation-test/lib/ScrapController/ScrapController.h
        navigation-test/lib/ScrapController/ScrapDefinitions.h
        navigation-test/lib/ScrapController/ScrapDualController.cpp
        navigation-test/lib/ScrapController/ScrapEncoder.cpp
        navigation-test/lib/ScrapController/ScrapFullController.cpp
        navigation-test/lib/ScrapController/ScrapMotor.cpp
        navigation-test/lib/ScrapController/ScrapMotorControl.cpp
        navigation-test/sketch/sketch.ino
        navigation-test/jno.jno)

add_executable(2017_2018_TokenSorter ${SOURCE_FILES})
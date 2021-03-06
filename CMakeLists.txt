cmake_minimum_required(VERSION 3.6)
project(2017_2018_TokenSorter)
project(Navigation_Test)

set(CMAKE_CXX_STANDARD 11)

include_directories(
        color-sensor-test/libraries/Adafruit_TCS34725
        navigation-test/libraries  # fake arduino for pc testing
        navigation-test/libraries/Movement
        navigation-test/libraries/Navigation
        F:/Arduino/hardware/arduino/avr/cores/arduino
        F:/Arduino/hardware/arduino/avr/libraries/Wire/src
        /usr/share/arduino/hardware/arduino/cores/arduino
        /usr/share/arduino/hardware/arduino/libraries/Wire/src)

set(SOURCE_FILES
        color-sensor-test/sketch/sketch.ino
        color-sensor-test/jno.jno
        navigation-test/libraries/Movement/Movement.cpp
        navigation-test/libraries/Movement/Movement.h
        navigation-test/libraries/Navigation/Gameboard.cpp
        navigation-test/libraries/Navigation/Intersection.cpp
        navigation-test/libraries/Navigation/IntersectionState.cpp
        navigation-test/libraries/Navigation/Navigation.cpp
        navigation-test/libraries/Navigation/Navigation.h
        navigation-test/libraries/ScrapController/ScrapController.cpp
        navigation-test/libraries/ScrapController/ScrapController.h
        navigation-test/libraries/ScrapController/ScrapDefinitions.h
        navigation-test/libraries/ScrapController/ScrapDualController.cpp
        navigation-test/libraries/ScrapController/ScrapEncoder.cpp
        navigation-test/libraries/ScrapController/ScrapFullController.cpp
        navigation-test/libraries/ScrapController/ScrapMotor.cpp
        navigation-test/libraries/ScrapController/ScrapMotorControl.cpp
        navigation-test/sketch/sketch.ino
        navigation-test/jno.jno
        navigation-test/libraries/Navigation/Navigation17.cpp
        navigation-test/libraries/Navigation/Navigation17.h
        navigation-test/libraries/Navigation/Coordinate.h
        navigation-test/libraries/Arduino.h
        navigation-test/nav_pc_test.cpp)
set(NAV_TEST_SOURCE_FILES
        navigation-test/libraries/Movement/Movement.cpp
        navigation-test/libraries/Movement/Movement.h
        navigation-test/libraries/Navigation/Navigation17.cpp
        navigation-test/libraries/Navigation/Navigation17.h
        navigation-test/libraries/Navigation/Coordinate.h
        navigation-test/libraries/Arduino.h
        navigation-test/nav_pc_test.cpp)

add_executable(2017_2018_TokenSorter ${SOURCE_FILES})
add_executable(Navigation_Test ${NAV_TEST_SOURCE_FILES})
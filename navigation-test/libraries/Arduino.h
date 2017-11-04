// fake arduino library for pc testing

#ifndef INC_2017_2018_TOKENSORTER_ARDUINO_H
#define INC_2017_2018_TOKENSORTER_ARDUINO_H

#include <string>
#include <iostream>

typedef std::string String;

#define String(x) std::to_string(x)

class SerialClass {
public:
    static void println(const String& s) {
        std::cout << s << std::endl;
    }
    static void println(const int& s) {
        std::cout << s << std::endl;
    }
    static void print(const String& s) {
        std::cout << s;
    }
    static void print(const int& s) {
        std::cout << s;
    }
};

static SerialClass Serial;

#endif //INC_2017_2018_TOKENSORTER_ARDUINO_H

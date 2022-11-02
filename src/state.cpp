#include <iostream>

#include "state.h"


State::State()
    : output(&std::cout){
}

void State::reset() {
    pc = 0;
}

size_t State::addVar(std::string value) {
    varString.push_back(value);

    return varString.size() - 1;
}

size_t State::addVar(uint64_t value) {
    varInt.push_back(value);

    return varInt.size() - 1;
}

std::string State::fetchVarString(size_t index) {
    return varString[index];
}

uint64_t State::fetchVarInt(size_t index) {
    return varInt[index];
}

std::ostream &State::getOutput() {
    return *output;
}

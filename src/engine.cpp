#include <iostream>

#include "engine.h"

using std::string;
using std::vector;
using std::optional;
using std::nullopt;
using std::cout;
using std::cerr;
using std::endl;


bool operator==(const Instruction &a, const Instruction &b) {
    return a.id == b.id;
}

bool operator<(const Instruction &a, const Instruction &b) {
    return a.id < b.id;
}

Engine::Engine(const Program &program, const InstructionSet &instructionSet)
    : program(program),
      instructionSet(instructionSet) {
    state.reset();
}

void Engine::run() {
    for(auto i=0; i<program.size(); i++) {
        CodeId f = program[i];
        optional<string> p = nullopt;
        if(program[i + 1].isBox()) {
            p = program[++i];
        }
        cerr << "EXE[" << i - 1 << "]: (" << f << ")";
        if(p) {
            cerr << "{" << (p.has_value() ? *p : "") << "}";
        }
        cerr << endl;

        const auto inst = getInstruction(f);
        if(inst) {
            (*inst).executor(p, state);
        } else {
            cerr << "Instruction (" << f << ") not defined" << endl;
            // TODO: configurable behaviour: terminate, ignore
        }
    }
}

optional<Instruction> Engine::getInstruction(const CodeId code) {
    auto it = std::find_if(instructionSet.begin(), instructionSet.end(), [code](const auto &i) {
       return i.id == code;
    });

    if (it != instructionSet.end()) {
        return *it;
    } else {
        return {};
    }
}

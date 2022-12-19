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

Engine::Engine(const Program &program, const InstructionSet &instructionSet, const bool verbose)
    : program(program),
      instructionSet(instructionSet),
      verbose(verbose) {
    state.reset();
}

void Engine::run() {
//    for(auto i=0; i<program.size(); i++) {
    while(state.getPc() < program.size()) {
        const auto pc = state.getPc();
        bool withParam = false;

        if(!program[pc].isCode()) {
            cerr << "[pc:" << pc << "] Invalid state: program counter doesn't point to a code" << endl;
            break;
        }

        CodeId f = program[pc];
        optional<string> p = nullopt;
        if(program[pc + 1].isBox()) {
            p = program[pc + 1];
            withParam = true;
        }

        if (verbose)
        {
            cerr << "EXE[" << pc << "]: (" << f << ")";
            if(p) {
                cerr << "{" << (p.has_value() ? *p : "") << "}";
            }
            cerr << endl;
        }

        const auto inst = getInstruction(f);
        if(inst) {
            (*inst).executor(p, state);
        } else {
            cerr << "Instruction (" << f << ") not defined" << endl;
            // TODO: configurable behaviour: terminate, ignore
        }

        state.pcNext();
        if(withParam) {
            state.pcNext();
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

#pragma once

#include <functional>
#include <vector>
#include <map>
#include <optional>
#include <set>

#include "element.h"
#include "state.h"
#include "seqseq.h"


typedef std::optional<std::string> ExecutorParam;
typedef std::function<void(ExecutorParam, State&)> Executor;

struct Instruction {
    CodeId id;
    Executor executor;
    std::string description;
    std::string mnemonic;

    friend bool operator==(const Instruction &a, const Instruction &b);
    friend bool operator<(const Instruction &a, const Instruction &b);
};

typedef std::set<Instruction> InstructionSet;

class Engine
{
public:
    Engine(const Program &program, const InstructionSet &instructionSet, const bool verbose);
    void run();

private:
    std::optional<Instruction> getInstruction(const CodeId code);
    Program program;
    InstructionSet instructionSet;
    State state;
    bool verbose;
};


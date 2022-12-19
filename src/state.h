#pragma once

#include <string>
#include <vector>
#include <ostream>

#include "seqseq.h"


class State {
public:
    State();
    void reset();
    size_t addVar(TypeString value);
    size_t addVar(TypeInt value);
    TypeString fetchVarString(size_t index);
    TypeInt fetchVarInt(size_t index);
    std::ostream &getOutput();
    ProgramCounter getPc() const;
    void pcNext();
    void pcSet(const ProgramCounter newPc);

private:
    std::vector<TypeString> varString;
    std::vector<TypeInt> varInt;
    ProgramCounter pc;
    std::ostream *output;
    // Add ostream, switchable between stdout, stderr and file
};

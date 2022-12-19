#include <iostream>
#include <optional>
#include <vector>

#include "state.h"
#include "standard.h"


using std::string;
using std::endl;
using std::optional;
using std::set;

void outputBox(ExecutorParam p, State &state) {
    state.getOutput() << *p;
}

void outputContString(ExecutorParam p, State &state) {
    state.getOutput() << state.fetchVarString(stoll(*p));
}

void outputContNumber(ExecutorParam p, State &state) {
    state.getOutput() << state.fetchVarInt(stoll(*p));
}

void outputSpace(ExecutorParam p, State &state) {
    state.getOutput() << " ";
}

void outputNewLine(ExecutorParam p, State &state) {
    state.getOutput() << endl;
}

void makeContString(ExecutorParam p, State &state) {
    state.addVar(*p);
}

void makeContNumber(ExecutorParam p, State &state) {
    state.addVar(stoll(*p));
}

    // Proposals:
    /*
     * MATH:
     * clear int acc
     * *add int var to acc
     * *subtract var from acc
     * *multiply acc by int var
     * *divide acc by int var
     * *raise acc to the var
     * *take varth root of acc
     * make int container from acc
     * *replace int container from acc
     * Do the math! - calculate value of an expression;
     *
     * STRING:
     * clear string acc
     * *add string var to string acc
     *
     * CONTROL:
     * *jump
     * *jump if acc zero
     * *jump if acc not zero
     *
     * OTHER:
     * *make a HTTP(S) request, put content in a new string container
     * *make a HTTP(S) request, put content in a new int container
     */
const set<Instruction> instructionSet = {
    {1, outputBox, "Output a box", "outb"},
    {2, outputContString, "Output stringy container", "outs"},
    {3, outputContNumber, "Output number container", "outn"},
    {4, outputSpace, "Output stringy container", "outsp"},
    {5, outputNewLine, "Output new line", "outnl"},
    {10, makeContString, "Make string container", "mks"},
    {11, makeContNumber, "Make number container", "mkn"}
};

InstructionSet standardInstructionSet() {
    return instructionSet;
}

#include <algorithm>

#include "parser.h"

/*
 * theSequence[]
 * code is build from theSequence - one or more characters, can be more than the
 * sequence length - it wraps around, circular buffer
 */

using std::string;
using std::vector;


Sequencer::Sequencer(const std::string &sequence)
    : sequence(sequence), index(0) {
}

void Sequencer::reset() {
    index = 0;
}

string::value_type Sequencer::next() {
    if(index >= sequence.length()) {
        index = 0;
    }
    return sequence[index++];
}

string::value_type Sequencer::first() {
    return sequence[0];
}

void Sequencer::set(unsigned long index) {
    this->index = index;
}

Parser::Parser(const std::string &sequence)
    : sequencer(sequence) {
}

//#define PARSER_DEBUG

vector<Element> Parser::parse(const string source) {
    vector<Element> output;

#ifdef PARSER_DEBUG
    std::cerr << "DEBUG: parse(\"" << source << "\")" << std::endl;
#endif
    unsigned short codeAcc = 0;
    string boxAcc = "";
    sequencer.reset();
    for_each(source.cbegin(), source.cend(), [this, &codeAcc, &boxAcc, &output](auto c) {
        switch(c) {
        case ' ':
        case '\t':
        case '\r':
        case '\n':
            return;
        };

        auto cs = sequencer.next();
        bool captureBox = false;
        if(c == cs) {
#ifdef PARSER_DEBUG
            std::cerr << "SEQ CONT" << std::endl;
#endif
            if(!boxAcc.empty()) {
                captureBox = true;
            }
            codeAcc++;
        } else if(c == sequencer.first()){
#ifdef PARSER_DEBUG
            std::cerr << "SEQ RESET" << std::endl;
#endif
            if(!boxAcc.empty()) {
                captureBox = true;
            }
            if(codeAcc > 0) {
                output.push_back(Code{codeAcc});
            }
            sequencer.set(1);
            codeAcc = 1;
        } else {
#ifdef PARSER_DEBUG
            std::cerr << "NONCODE: " << c << std::endl;
#endif
            if (codeAcc > 0) {
                output.push_back(Code{codeAcc});
                sequencer.reset();
                codeAcc = 0;
            }
            boxAcc += c;
        }
        if(captureBox) {
#ifdef PARSER_DEBUG
            std::cerr << "BOX CAPTURE: \"" << boxAcc << "\"" << std::endl;
#endif
            output.push_back(Box{boxAcc});
            boxAcc = "";
        }
    });
    if(codeAcc > 0) {
        output.push_back(Code{codeAcc});
    }
    if(!boxAcc.empty()) {
        output.push_back(Box{boxAcc});
    }

    return output;
}

#include <iostream>
#include <sstream>
#include <map>
#include <tclap/CmdLine.h>

#include "parser.h"
#include "engine.h"
#include "standard.h"


using namespace std;

bool testParser();
void dumpProgram(vector<Element> program);

int main(int argc, char **argv)
{
    TCLAP::CmdLine cmd("Command description message", ' ', "0.9");
    TCLAP::ValueArg<std::string> nameArg("s", "seq", "The Sequence", true, "seqseq", "string", cmd);
    try {
//        TCLAP::SwitchArg reverseSwitch("r","reverse","Print name backwards", cmd, false);
        cmd.parse(argc, argv);
//        bool reverseName = reverseSwitch.getValue();
    } catch(TCLAP::ArgException &e) {
        cerr << "error: " << e.error() << " for arg " << e.argId() << endl;
    }

    string code = "";
    for (string line; getline(cin, line);) {
        code += line;
    }

    const auto theSequence = nameArg.getValue();
    Parser p(theSequence);
    //    auto program = p.parse("seqseqseqsHelloseqseqseqsworld!se0seqseqsese1seqseqseq");
//    auto program = p.parse("?HelloworlHello?Helloworlworld!?H0?Hellowo?H1?Hellowor");
    auto program = p.parse(code);
    dumpProgram(program);

    Engine e(program, standardInstructionSet());

    e.run();

//    cerr.rdbuf(ostringstream().rdbuf());
//    if(testParser()) {
//        cout << "Parser tests PASSED" << endl;
//    } else {
//        cout << "Parser test(s) FAILED" << endl;
//    }
}

void dumpProgram(vector<Element> program) {
    cout << "Program: ";
    for_each(program.begin(), program.end(), [](const auto e) {
        cout << e;
    });
    cout << endl;
}

bool testParser() {
    Parser p("abcdef");
    map<string, vector<Element>> tests {
        {"a", {Code{1}}},
        {"abc", {Code{3}}},
        {"abcabc", {Code{3}, Code{3}}},
        {"abcabca", {Code{3}, Code{3}, Code{1}}},
        {"aa", {Code{1}, Code{1}}},
        {"ac", {Code{1}, Box{"c"}}},
        {"aca", {Code{1}, Box{"c"}, Code{1}}},
        {"aaXa", {Code{1}, Code{1}, Box{"X"}, Code{1}}},
        {"Xa", {Box{"X"}, Code{1}}},
        {"!@#$%^&*()_+", {Box{"!@#$%^&*()_+"}}},
        {" ac  a", {Code{1}, Box{"c"}, Code{1}}},
        {"\r\naa    X   a", {Code{1}, Code{1}, Box{"X"}, Code{1}}},
        {"      X       \ra      ", {Box{"X"}, Code{1}}},
        {" ! @ # $ %        ^ &* ( \n)\r_+\r\n", {Box{"!@#$%^&*()_+"}}}
    };

    bool passed = true;
    cout << "Start testing" << endl;
    for(const auto &t : tests) {
        cout << "Test: \"" << t.first << "\" -> ";
        auto result = p.parse(t.first);
        auto pass = result == t.second;
        passed &= pass;
        cout << (pass ? "PASS" : "FAIL") << " [" << t.second.size() << "](";
        for(const auto &e : t.second) {
            cout << e;
        }
        cout << ") vs (";
        for(const auto &e : result) {
            cout << e;
        }
        cout << ")" << endl;
    }

    return passed;
}

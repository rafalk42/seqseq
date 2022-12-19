#include <iostream>
#include <sstream>
#include <map>
#include <tclap/CmdLine.h>
#include <fstream>

#include "parser.h"
#include "engine.h"
#include "standard.h"


using namespace std;

bool testParser();
void dumpProgram(vector<Element> program);

int main(int argc, char **argv)
{
    TCLAP::CmdLine cmd("By default program is read from standard input.", ' ', "0.9");
    TCLAP::ValueArg<string> seqArg("s", "seq", "The Sequence", true, "", "string", cmd);
    TCLAP::ValueArg<string> fileArg("f", "file", "file to read instead of standard input", false, "", "string", cmd);
    TCLAP::SwitchArg verboseSwitch("v", "verbose", "Verbose/debug output", cmd, false);

    try {
        cmd.parse(argc, argv);
    } catch(TCLAP::ArgException &e) {
        cerr << "error: " << e.error() << " for arg " << e.argId() << endl;
    }

    string code = "";
    if(fileArg.isSet()) {
        ifstream t(fileArg);
        code = string((std::istreambuf_iterator<char>(t)),
                         std::istreambuf_iterator<char>());
    } else {
        for (string line; getline(cin, line);) {
            code += line;
        }
    }

    const auto theSequence = seqArg.getValue();
    Parser p(theSequence);
    //    auto program = p.parse("seqseqseqsHelloseqseqseqsworld!se0seqseqsese1seqseqseq");
//    auto program = p.parse("?HelloworlHello?Helloworlworld!?H0?Hellowo?H1?Hellowor");
    auto program = p.parse(code);
    if(verboseSwitch) dumpProgram(program);

    const auto is = standardInstructionSet();
    if(verboseSwitch) {
        for(const auto &i : is) {
            std::cerr << "(" << i.id << ":" << i.mnemonic << ")" << i.description << std::endl;
        }
    }

    Engine e(program, is, verboseSwitch);

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

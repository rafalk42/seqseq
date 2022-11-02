#pragma once

#include <string>
#include <variant>
#include <vector>

#include "seqseq.h"


struct Code {
    CodeId id;

    const std::string toString() const;
    friend bool operator==(const Code &a, const Code &b);
};

struct Box {
    std::string value;

    const std::string toString() const;
    friend bool operator==(const Box &a, const Box &b);
};

class Element {
public:
    Element(const Code code);
    Element(const Box box);
    bool isCode() const;
    bool isBox() const;

    friend bool operator==(const Element &a, const Element &b);
    friend std::ostream &operator<<(std::ostream &s, const Element &e);
    operator std::string() const { return std::get<Box>(thing).value; }
    operator CodeId() const { return std::get<Code>(thing).id; }

private:
    std::variant<Code, Box> thing;
};

typedef std::vector<Element> Program;

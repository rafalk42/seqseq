#include <sstream>

#include "element.h"

using std::string;
using std::stringstream;
using std::ostream;
using std::holds_alternative;
using std::get;


const string Code::toString() const {
    stringstream s;
    s << "(";
    s << id;
    s << ")";
    return s.str();
}

const string Box::toString() const {
    stringstream s;
    s << "{\"";
    s << value;
    s << "\"}";
    return s.str();
}


bool operator==(const Code &a, const Code &b) {
    return a.id == b.id;
}

bool operator==(const Box &a, const Box &b) {
    return a.value == b.value;
}

Element::Element(const Code code) {
    thing = code;
}

Element::Element(const Box box) {
    thing = box;
}

bool Element::isCode() const {
    return holds_alternative<Code>(thing);
}

bool Element::isBox() const {
    return holds_alternative<Box>(thing);
}

bool operator==(const Element &a, const Element &b) {
    return a.thing == b.thing;
}

ostream &operator<<(ostream &s, const Element &e) {
    s << (e.isCode() ? get<Code>(e.thing).toString() : get<Box>(e.thing).toString());
    return s;
}

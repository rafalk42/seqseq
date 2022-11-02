#pragma once

#include <string>
#include <variant>
#include <vector>

#include "element.h"


class Sequencer {
public:
  Sequencer(const std::string &sequence);
  void reset();
  std::string::value_type next();
  std::string::value_type first();
  void set(unsigned long index);

private:
  const std::string sequence;
  unsigned long index;
};

class Parser
{
public:
    Parser(const std::string &sequence);
    std::vector<Element> parse(const std::string source);

private:
    Sequencer sequencer;
};

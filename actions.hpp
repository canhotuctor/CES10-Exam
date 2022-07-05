#include <string>

struct Action{
  std::string name = "";
  std::string description = "";
  int index = 0;
  // related to effect of the spell
  int value1 = 0;
  // related to time the effect will be on
  int value2 = 0;
  
  Action();
  Action(std::string, std::string, int, int, int);
};

// action templates will be defined in defs.cpp

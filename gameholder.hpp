#include <vector>
#include "characters.hpp"

struct GameHolder{
  std::vector<Character> allies = {};
  std::vector<Character> enemies = {};

  Character* get_next_player();
  void time_pass(int);
  bool round();
  void initialize();
  void print_players();
  void load(char*);
};
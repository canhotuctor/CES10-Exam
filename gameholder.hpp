#include <vector>
#include "characters.hpp"

struct GameHolder{
  std::vector<Character> allies = {};
  std::vector<Character> enemies = {};

  Character* get_next_player();
  void time_pass(int);
  bool round();
  void initialize(std::vector<Character>);
  void print_players();
  bool save(std::string);
  void load(char*, std::vector<Character>);
  void remove_player(Character*);
};
#include "actions.hpp"

struct Character
{
  std::string name = "";
  char job = 'n';
  bool is_dead = false;
  bool is_enemy = false;
  Action special;

  int hp = 0;
  int atk = 0;
  int def = 0;

  int base_hp = 0;
  int base_atk = 0;
  int base_def = 0;

  int speed = 0;
  int healing_power = 0;

  int time_dizzy = 0;
  int time_stunned = 0;
  int time_to_wait = 0;
  int time_atk_buffed = 0;
  int time_atk_nerfed = 0;
  int time_def_nerfed = 0;

  Character();
  Character(std::string, char, int, int, int, int, int, Action);

  int take_damage(int);
  int heal_self();
  int heal_self(int);
  void update_status(int);
  void print_info();
};

// character templates will be defined in defs.cpp
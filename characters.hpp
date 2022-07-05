#include "actions.hpp"

struct Character
{
  std::string name = "";
  char job = 'n';
  bool is_dead = false;
  bool is_enemy = false;
  Action special = null_action;

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

  Character(std::string, char, int, int, int, int, int, Action);

  int take_damage(int);
  int heal_self();
  int heal_self(int);
  void update_status(int);
  // void print_info();
};

static const Character null_character = Character("", 'n', 0, 0, 0, 0, 0, null_action);

static const Character warrior = Character("Warrior", 'w', 200, 25, 15, 4, 0, grow);
static const Character mage = Character("Mage", 'm', 120, 15, 5, 6, 5, stun);
static const Character rogue = Character("Rogue", 'r', 90, 25, 5, 16, 10, za_knife);
static const Character healer = Character("Healer", 'h', 80, 5, 8, 8, 20, big_heal);
static const Character archer = Character("Archer", 'a', 140, 20, 10, 12, 5, za_arrow);
static const Character bard = Character("Bard", 'b', 100, 5, 5, 10, 10, weaken);
// int this order, the arguments are: name, job, hp, atk, def, spd, heal, special action;

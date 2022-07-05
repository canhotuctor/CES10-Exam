#include <iostream>
#include <fstream>
#include "defs.hpp"

void clear_screen()
{
#ifdef __linux__
  system("clear");
#endif

#ifdef _WIN32
  system("cls");
#endif

#ifdef _WIN64
  system("cls");
#endif
}

void wait_enter()
{
  std::cout << "Press <ENTER> to continue...";
  std::cin.ignore();

  return;
}

bool check_emptiness(char *in)
{
  auto inf = std::ifstream(in);
  if(!inf.is_open()){
    return true;
  }
  std::string s;
  inf >> s;
  if (s == "")
    return true;
  else
    return false;
}
bool check_emptiness(int a, char *args[])
{
  for (int i = 1; i < a; i++)
  {
    if (!check_emptiness(args[i]))
    {
      return false;
    }
  }
  return true;
}

char init_screen(int number_of_args, char* args[])
{
  clear_screen();
  std::cout << "----------------------------------------\n"
            << "-      Welcome to Only Survivors!      -\n"
            << "----------------------------------------\n";
  wait_enter();

  if (number_of_args > 1 && !check_emptiness(number_of_args, args))
  {
    if (number_of_args == 2)
    {
      std::cout << "Received a save state. Wanna load it? (y/n)\n";
    }
    else
    {
      std::cout << "Received some valid save states. Wanna load any of'em? (y/n)\n";
    }
    char option;
    std::cin >> option;
    std::cin.ignore();
    if (option == 'y')
    {
      return 'l';
    }
  }
  else if(number_of_args > 1){
    std::cout << "The files that you tried to load are empty or corrupted...\n";
    wait_enter();
    std::cout << "You may re-initialize the program with the correct files or start a game on an empty file\n";
  }
  else
  {
    std::cout << "Didn't receive any save state...\n";
  }
  std::cout << "Wanna start a new game? (y/n)\n";
  char option;
  std::cin >> option;
  std::cin.ignore();
  if (option == 'y')
  {
    return 'n';
  }
  return 'q';
}


Action::Action(std::string n, std::string d, int i, int v1, int v2)
{
  this->name = n;
  this->description = d;
  this->index = i;
  this->value1 = v1;
  this->value2 = v2;
}

Action::Action(){

}

Character::Character(std::string n, char j, int h, int a, int d, int s, int heal, Action act)
{
  this->name = n;
  this->job = j;
  this->hp = h;
  this->base_hp = h;
  this->atk = a;
  this->base_atk = a;
  this->def = d;
  this->base_def = d;
  this->speed = s;
  this->healing_power = heal;
  this->special = act;
}


std::array<Character, 7> character_presets(){
  Action null_action;

  Action grow = Action("Pump Up", "The warrior's blood heats as it fills with rage. Increases his strength for some time.", 1, 7, 350);
  Action stun = Action("Ice Prison", "The mage condenses the cold air around the tip of his staff as he fires the blow at the enemy, freezing him for some time.", 2, 20, 350);
  Action za_knife = Action("Poisoned Knife", "The rogue soaks his blade in an oriental poison, delivering a slash that weaken the foe's defense for some time.", 3, 7, 350);
  Action big_heal = Action("Grand Heal", "The healer channels his inner energy to close even the deadliest of wounds. Heals the target in 40 HP, but takes some time to recharge", 4, 45, 350);
  Action za_arrow = Action("Clean Shot", "The archer holds his breath, aims his arrow well, and hits an enemy vital point, making it deal less damage for some time.", 5, 7, 350);
  Action dizzit = Action("Lullaby", "The bard plays a song that make his opponent confused, disorienting him for some time. ", 6, 10, 350);

  Character null_character = Character("", 'n', 0, 0, 0, 0, 0, null_action);
  Character warrior = Character("Warrior", 'w', 200, 25, 15, 4, 0, grow);
  Character mage = Character("Mage", 'm', 120, 15, 5, 6, 5, stun);
  Character rogue = Character("Rogue", 'r', 90, 25, 5, 16, 10, za_knife);
  Character healer = Character("Healer", 'h', 80, 5, 8, 8, 20, big_heal);
  Character archer = Character("Archer", 'a', 140, 20, 10, 12, 5, za_arrow);
  Character bard = Character("Bard", 'b', 100, 5, 5, 10, 10, dizzit);
  // in this order, the arguments are: name, job, hp, atk, def, spd, heal, special action;

  return {null_character, warrior, mage, rogue, healer, archer, bard};
}


int Character::take_damage(int base)
{
  int temp = this->hp;
  base = base * (100 - this->def) / 100;
  this->hp -= base;
  if (this->hp < 0)
  {
    this->hp = 0;
    this->is_dead = true;
  }
  return temp - this->hp;
}

int Character::heal_self(){
  int temp = this->hp;
  this->hp += this->healing_power;
  if (this->hp > this->base_hp)
  {
    this->hp = this->base_hp;
  }
  return this->hp - temp;
}
int Character::heal_self(int base)
{
  int temp = this->hp;
  this->hp += base;
  if (this->hp > this->base_hp)
  {
    this->hp = this->base_hp;
  }
  return this->hp - temp;
}

void Character::update_status(int time_passed)
{
  if (this->time_to_wait > 0)
  {
    this->time_to_wait -= time_passed;
    if (this->time_to_wait < 0)
      this->time_to_wait = 0;
  }
  if (this->time_dizzy > 0)
  {
    this->time_dizzy -= time_passed;
    if (this->time_dizzy < 0)
      this->time_dizzy = 0;
  }
  if (this->time_stunned > 0)
  {
    this->time_stunned -= time_passed;
    if (this->time_stunned < 0)
      this->time_stunned = 0;
  }
  return;
}

void Character::print_info(){
  std::cout << (this->is_enemy? "Enemy " : "Ally ") << this->name << '\n'
            << " -> Base HP: " << this->base_hp << '\n'
            << " -> Base Atk: " << this->base_atk << '\n'
            << " -> Base Def: " << this->base_def << '\n'
            << " -> Speed: " << this->speed << '\n'
            << " -> Healing Power: " << this->healing_power << '\n'
            << " -> Special Action: " << this->special.name << '\n'
            << "  \\-> " << this->special.description << '\n'
            << " -> Time to wait: " << this->time_to_wait << '\n';  
}


bool GameHolder::round(){
  clear_screen();

  std::cout << "Alive Enemies:\n";
  for(size_t i = 0; i < this->enemies.size(); i++){
    this->enemies[i].print_info();
  }
  std::cout << "\nAlive Heroes:\n";
  for(size_t i = 0; i < this->allies.size(); i++){
    this->allies[i].print_info();
  }
  wait_enter();
  clear_screen();
  Character* cur_char = this->get_next_player();
  this->time_pass(cur_char->time_to_wait);
  cur_char->print_info();
  cur_char->time_to_wait += 100;
  wait_enter();
  return true;
}

Character* GameHolder::get_next_player(){
  Character* x = &this->allies[0];
  for(size_t i = 0; i < this->allies.size(); i++){
    Character* y = &this->allies[i];
    if(x->time_to_wait > y->time_to_wait){
      x = y;
    }
    else if(x->time_to_wait == y->time_to_wait && x->speed < y->speed){
      x = y;
    }
  }
  for(size_t i = 0; i < this->enemies.size(); i++){
    Character* y = &this->enemies[i];
    if(x->time_to_wait > y->time_to_wait){
      x = y;
    }
    else if(x->time_to_wait == y->time_to_wait && x->speed < y->speed){
      x = y;
    }
  }
  return x;
}

void GameHolder::time_pass(int a){
  for (size_t i = 0; i < this->allies.size(); i++)
  {
    this->allies[i].update_status(a);
  }
  for (size_t i = 0; i < this->enemies.size(); i++)
  {
    this->enemies[i].update_status(a);
  }
}

void GameHolder::print_players(){
  for (size_t i = 0; i < this->enemies.size(); i++)
  {
    /* code */
  }
  for (size_t i = 0; i < this->allies.size(); i++)
  {
    /* code */
  }
  
  
}
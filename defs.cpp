#include "characters.hpp"

Action::Action(std::string n, std::string d, int v1, int v2)
{
  this->name = n;
  this->description = d;
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

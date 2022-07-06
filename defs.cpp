#include <iostream>
#include <fstream>
#include <random>
#include "defs.hpp"

std::vector<Character> character_presets(){
  Action null_action;

  Action grow = Action("Pump Up", "The warrior's blood heats as it fills with rage. Increases his strength for some time.", 1, 7, 350);
  Action stun = Action("Ice Prison", "The mage condenses the cold air around the tip of his staff as he fires the blow at the enemy, freezing him for some time.", 2, 0, 350);
  Action za_knife = Action("Poisoned Knife", "The rogue soaks his blade in an oriental poison, delivering a slash that weaken the foe's defense for some time.", 3, 7, 350);
  Action big_heal = Action("Grand Heal", "The healer channels his inner energy to close even the deadliest of wounds. Heals the target(may be self) in 45 HP, but takes some time to recharge", 4, 45, 0);
  Action za_arrow = Action("Clean Shot", "The archer holds his breath, aims his arrow well, and hits an enemy vital point, making it deal less damage for some time.", 5, 7, 350);
  Action dizzit = Action("Lullaby", "The bard plays a song that make his opponent confused, disorienting him for some time. ", 6, 0, 350);

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
bool check_emptiness(std::string in){
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
    std::cout << "Input: ";
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

  if (this->time_atk_buffed > 0)
  {
    this->time_atk_buffed -= time_passed;
    if (this->time_atk_buffed <= 0){
      this->time_atk_buffed = 0;
      this->atk -= this->atk_buff;
      this->atk_buff = 0;
    }
  }
  if (this->time_atk_nerfed > 0)
  {
    this->time_atk_nerfed -= time_passed;
    if (this->time_atk_nerfed <= 0){
      this->time_atk_nerfed = 0;
      this->atk += this->atk_nerf;
      this->atk_nerf = 0;
    }
  }

  if(this->time_atk_buffed == 0 && this->time_atk_nerfed == 0){
    this->atk = this->base_atk;
  }

  if (this->time_def_nerfed > 0)
  {
    this->time_def_nerfed -= time_passed;
    if (this->time_def_nerfed <= 0){
      this->time_def_nerfed = 0;
      this->def += this->def_nerf;
      this->def_nerf = 0;
    }
  }
}

void Character::print_detailed_info(){
  std::cout << (this->is_enemy? "Enemy " : "Ally ") << this->name << '\n'
            << " -> Base HP: " << this->base_hp << '\n'
            << " -> Base Atk: " << this->base_atk << '\n'
            << " -> Base Def: " << this->base_def << '\n'
            << " -> Speed: " << this->speed << '\n'
            << " -> Healing Power: " << this->healing_power << '\n'
            << " -> Special Action: " << this->special.name << '\n'
            << "  \\-> " << this->special.description << '\n';
}

void Character::print_info(){
  std::cout << (this->is_enemy? "Enemy " : "Ally ") << this->name
            << " " << this->hp << '/' << this->base_hp
            << " - Cooldown: " << this->time_to_wait 
            << (this->time_to_wait != 1 ? " seconds\n" : " second\n");
}

bool GameHolder::round(){
  clear_screen();

  Character* cur_char = this->get_next_player();
  if(cur_char->time_to_wait > 0){
    this->time_pass(cur_char->time_to_wait);
  }

  std::cout << "Alive Enemies:\n";
  for(size_t i = 0; i < this->enemies.size(); i++){
    std::cout << i+1 << ". ";
    this->enemies[i].print_info();
  }
  std::cout << "\nAlive Heroes:\n";
  for(size_t i = 0; i < this->allies.size(); i++){
    std::cout << i+1 << ". ";
    this->allies[i].print_info();
  }

  std::cout << '\n';
  std::cout << "It's " << (cur_char->is_enemy ? "Enemy ": "Ally ") << cur_char->name << " turn.\n\n";
  
  // actions in each round
  if(!cur_char->is_enemy){
    std::cout << "Choose your next move:\n\n";
    std::cout << "1. Attack\n"
              << "  \\-> Base damage = " << cur_char->atk << " HP\n"
              << "  \\-> self-Cooldown = " << (120 - (3 * cur_char->speed)) << " seconds\n\n";
    std::cout << "2. Secondary Attack: " << cur_char->special.name << "\n"
              << "  \\-> " << cur_char->special.description << '\n'
              << "  \\-> self-Cooldown = " << (240 - (5 * cur_char->speed)) << " seconds\n\n";
    std::cout << "3. Power Attack\n"
              << "  \\-> Base Damage = " << 3 * cur_char->atk << "HP, but takes some time to recharge\n"
              << "  \\-> self-Cooldown = " << (500 - (8 * cur_char->speed)) << " seconds\n\n";
    if (cur_char->healing_power > 0)
    {
      std::cout << "4. Minor Heal\n"
                << "  \\-> Heals self in " << cur_char->healing_power << " HP\n"
                << "  \\-> self-Cooldown = " << (168 - (4 * cur_char->speed)) << " seconds\n\n";
    }
    std::cout << "9. Save Game and Quit:\n"
              << "  \\-> Ends game and save your progress up until now\n\n";
    std::cout << "0. Quit Game without saving:\n"
              << "  \\-> Ends game without saving it in any slot\n\n";
    
    std::cout << "Input:";
    int action;
    std::cin >> action;
    std::cin.ignore();

    if (action == 1)
    {
      int targ;
      std::cout << "Set your target, then:";
      std::cin >> targ;
      std::cin.ignore();
      Character* target = &this->enemies[targ - 1];
      std::cout << "Enemy " << target->name << " took "
                << target->take_damage(cur_char->atk)
                << " points of damage\n";

      if (target->is_dead)
      {
        std::cout << "Enemy " << target->name << " died" << std::endl;
        this->remove_player(target);
      }
      cur_char->time_to_wait += (120 - (3 * cur_char->speed));
    }
    else if (action == 2)
    {
      int targ;
      Action act = cur_char->special;
      Character* target;
      if (act.index == 1)
      {
        cur_char->atk += act.value1;
        cur_char->atk_buff += act.value1;
        cur_char->time_atk_buffed += act.value2;
        std::cout << "Ally " << cur_char->name << " pumped his strength up in " << act.value1 << " points\n\n";
      }
      else if (act.index == 2)
      {
        std::cout << "Set your target, then:";
        std::cin >> targ;
        std::cin.ignore();
        target = &this->enemies[targ - 1];
        target->time_stunned += act.value2;
        if(target->time_to_wait < target->time_stunned){
          target->time_to_wait = target->time_stunned;
        }
        std::cout << "Enemy " << target->name << " is now frozen\n\n";
      }
      else if (act.index == 3)
      {
        std::cout << "Set your target, then:";
        std::cin >> targ;
        std::cin.ignore();
        target = &this->enemies[targ - 1];
        int temp = target->def;
        target->def -= cur_char->special.value1;
        temp -= target->def;
        target->def_nerf += temp;
        target->time_def_nerfed += cur_char->special.value2;
        std::cout << "Enemy " << target->name << "'s Defense decreased by " << temp << " points\n\n";
      }
      else if (act.index == 4)
      {
        std::cout << "Set your target, then:";
        std::cin >> targ;
        std::cin.ignore();
        target = &this->allies[targ - 1];
        if(target->hp != target->base_hp){
          std::cout << cur_char->name << " healed " << target->name << '\n'
                  << "Healed " << target->heal_self(act.value1) << " HP\n\n";
        }
        else{
          std::cout << "It seems like the Healer couldn't heal its target...\n";
        }
      }
      else if (act.index == 5)
      {
        std::cout << "Set your target, then:";
        std::cin >> targ;
        std::cin.ignore();
        target = &this->enemies[targ - 1];
        int temp = target->atk;
        target->atk -= cur_char->special.value1;
        if (target->atk < 0)
        {
          target->atk = 0;
        }
        temp -= target->atk;
        target->atk_nerf += temp;
        target->time_atk_nerfed += act.value2;
        if(temp == 0){
          std::cout << "Couldn't decrease target's Strength. It was already 0...\n\n";
        }
        else{
          std::cout << "Enemy " << target->name << "'s Strength decreased by " << temp << " points\n\n";
        }
      }
      else if (act.index == 6)
      {
        std::cout << "Set your target, then:";
        std::cin >> targ;
        std::cin.ignore();
        target = &this->enemies[targ - 1];
        target->time_dizzy += act.value2;
        std::cout << "Enemy " << target->name << " is now dizzy\n\n";
      }
      cur_char->time_to_wait += (240 - (5 * cur_char->speed));
    }
    else if (action == 3)
    {
      int targ;
      std::cout << "Set your target, then:";
      std::cin >> targ;
      std::cin.ignore();
      Character *target = &this->enemies[targ - 1];
      std::cout << "Enemy " << target->name << " took "
                << target->take_damage(3 * cur_char->atk)
                << " points of damage\n";
      if (target->is_dead)
      {
        std::cout << "Enemy " << target->name << " died\n\n";
        this->remove_player(target);
      }
      else{
        std::cout << "Ally " << cur_char->name << " now needs to recover his stamina\n\n";
      }
      cur_char->time_to_wait += (500 - (8 * cur_char->speed));
    }
    else if (action == 4 && cur_char->healing_power > 0)
    {
      int a = cur_char->heal_self();
      if (a == 0)
      {
        std::cout << "It looks like the " << cur_char->name << " couldn't heal himself. His life was already full..." << std::endl;
      }
      else{
        std::cout << "Healed " << a << " HP\n\n";
      }
      cur_char->time_to_wait += (168 - (4 * cur_char->speed));
    }
    else if (action == 9)
    {
      while(true){
        clear_screen();
        std::cout << "Type the desired save state name:\n";
        std::string filename;
        std::cin >> filename;
        std::cin.ignore();
        if(!check_emptiness(filename)){
          std::cout << "That file is not empty. Wanna overwrite its contents? It may be risky... (y/n)\n"
                    << "Input: ";
          char opt;
          std::cin >> opt;
          std::cin.ignore();
          if(opt != 'y'){
            continue;
          }
        }
        bool x = this->save(filename);
        if(x){
          std::cout << "Save was sucessfull in file: " << filename << std::endl;
          wait_enter();
          return false;
        }
        else{
          std::cout << "Save was unsucessfull... try again with another name\n";
          wait_enter();
          continue;
        }
      }
    }
    else if (action == 0)
    {
      clear_screen();
      return false;
    }
    else{
      std::cout << "Invalid option...\n";
      wait_enter();
      return true;
    }
  }
  else{
    // action if is computer's turn;
    Character *less_healthy = &this->allies[0];
    for (size_t i = 0; i < this->allies.size(); i++)
    {
      if (this->allies[i].hp < less_healthy->hp)
        less_healthy = &this->allies[i];
    }

    std::uniform_int_distribution<long> dist2(0, 100);
    std::random_device dev2;
    std::mt19937 gen2(dev2());
    long var = dist2(gen2);
    if (cur_char->hp / cur_char->base_hp < 0.2)
    { // case the enemy's life is below 20%...
      // 80% heal, 20% attack chances, except if the enemy is a warrior, in case it will only attack in this case
      if (var <= 20 || cur_char->healing_power == 0)
      {
        if (cur_char->time_dizzy == 0)
        {
          std::cout << cur_char->name << " attacked " << less_healthy->name << ". " << less_healthy->name << " lost "
                    << less_healthy->take_damage(cur_char->atk) << " HP.\n\n";
          cur_char->time_to_wait += (120 - (3 * cur_char->speed));
        }
        else
        {
          std::cout << "Enemy " << cur_char->name << " tried to attack while dizzy and failed..." << std::endl;
          cur_char->time_to_wait += (80 - (3 * cur_char->speed));
          std::cout << "\nPress <ENTER> to continue:";
          std::cin.ignore();
        }
      }
      else
      {
        std::cout << cur_char->name << " healed and regenerated " << cur_char->heal_self(cur_char->healing_power) << "HP.\n\n";
        cur_char->time_to_wait += (168 - (4 * cur_char->speed));
      }
    }
    else
    {
      // 20% heal, 50% atacar, 30% atacar forte
      if (var < 30 && cur_char->healing_power != 0)
      { // tries to heal
        std::cout << cur_char->name << " healed and regenerated " << cur_char->heal_self(cur_char->healing_power) << "HP.\n";
        cur_char->time_to_wait += (168 - (4 * cur_char->speed));
      }
      else if (var < 30 && cur_char->healing_power == 0)
      {
        std::cout << cur_char->name << " attacked " << less_healthy->name << ". " << less_healthy->name << " lost "
                  << less_healthy->take_damage(cur_char->atk) << " HP.\n\n";
        cur_char->time_to_wait += (120 - (3 * cur_char->speed));
      }
      else if (var < 70 && var >= 30)
      {
        std::cout << cur_char->name << " attacked " << less_healthy->name << ". " << less_healthy->name << " lost "
                  << less_healthy->take_damage(cur_char->atk) << " HP.\n\n";
        cur_char->time_to_wait += (120 - (3 * cur_char->speed));
      }
      else if (var >= 70)
      {
        std::cout << cur_char->name << " power attacked " << less_healthy->name << ". " << less_healthy->name << " lost "
                  << less_healthy->take_damage(3 * cur_char->atk) << " HP.\n\n";
        cur_char->time_to_wait += (500 - (8 * cur_char->speed));
      }
    }
    if (less_healthy->hp == 0)
    {
      std::cout << "Unfortunately, your hero, the " << less_healthy->name << " died.\n";
      this->remove_player(less_healthy);
    }
  }

  //check if one of the teams is entirely dead. if so, break
  if(this->allies.size() == 0){
    std::cout << "All your heroes are dead...\n";
    wait_enter();
    return false;
  }
  else if(this->enemies.size() == 0){
    return false;
  }

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

void GameHolder::initialize(std::vector<Character> prefabs){
  clear_screen();
  std::cout << "Only Survivors\n\n";
  std::cout << "After a terrible inexplicable plague wiped out life on earth, small groups of human beings began to live in complete isolation for thousands of years. 40,000 years later, the surviving groups observed that some people born in the village had characteristics that were strange to the conventional ones and, afraid they would harm the villagers, they began to expel them. So begins the saga of the Only Survivors, who allied and fought for their own survival in this vast devastated world, just because they were different.\n\n"

            << "Fleeing the battle is not an option, but who will fight by your side is...\n\n";
  
  wait_enter();

  std::cout << "Select Your Gamemode:\n\n"
  
            << " 1. 1v1\n"
            << " 2. 2v2\n"
            << " 3. 3v3\n"
            << " 4. 4v4\n"
            << " 5. 5v5\n\n"

            << "Enemies will be randomly selected...\n\n"
            
            << "Input: ";
  
  int gamemode;
  std::cin >> gamemode;
  std::cin.ignore();

  std::cout << "\nYou selected " << gamemode << "v"
            << gamemode << "\n\n";
  wait_enter();

  clear_screen();
  std::cout << "Select your Party:\n(e.g.:";
  for (int i = 0; i < gamemode; i++)
    std::cout << " " << i + 1;
  std::cout << ")\n\n";

  for (int i = 1; i <= 6; i++)
  {
    std::cout << i << ". " << prefabs[i].name << "\n";
  }

  std::cout << "\nInput: ";
  for (int i = 0; i < gamemode; i++)
  {
    int a;
    std::cin >> a;
    std::cin.ignore();
    this->allies.push_back(prefabs[a]);
  }
  std::cout << std::endl;
  std::cout << "You selected:\n\n";

  for (int i = 0; i < gamemode; i++)
  {
    this->allies[i].print_detailed_info();
    std::cout << '\n';
  }

  wait_enter();
  clear_screen();

  // define enemies
  std::random_device dev1;
  std::mt19937 gen1(dev1());
  for (int i = 0; i < gamemode; i++)
  {
    std::uniform_int_distribution<int> dist(1, 6);
    this->enemies.push_back(prefabs[dist(gen1)]);
    this->enemies[i].is_enemy = true;
  }
  std::cout << "The enemy selected the following champions:\n\n";
  for (int i = 0; i < gamemode; i++)
  {
    this->enemies[i].print_detailed_info();
    std::cout << '\n';
  }

  std::cout << "Press <ENTER> to start the battle:";
  std::cin.ignore();
  clear_screen();
}

void GameHolder::load(char* cc, std::vector<Character> prefabs){
  auto ifile = std::ifstream(cc);
  int num;
  ifile >> num;
  for (int i = 0; i < num; i++)
  {
    char jacob;
    ifile >> jacob;
    for (size_t j = 1; j < prefabs.size(); j++)
    {
      if (prefabs[j].job == jacob)
      {
        this->allies.push_back(prefabs[j]);
        break;
      }
    }
    Character &baz = this->allies[i];
    ifile 
    >> baz.hp
    >> baz.atk
    >> baz.def
    >> baz.time_stunned
    >> baz.time_dizzy
    >> baz.time_to_wait
    >> baz.atk_buff
    >> baz. time_atk_buffed
    >> baz.atk_nerf
    >> baz.time_atk_nerfed
    >> baz.def_nerf
    >> baz.time_def_nerfed;
  }
  ifile >> num;
  for (int i = 0; i < num; i++)
  {
    char jacob;
    ifile >> jacob;
    for (size_t j = 1; j < prefabs.size(); j++)
    {
      if (prefabs[j].job == jacob)
      {
        this->enemies.push_back(prefabs[j]);
        break;
      }
    }
    Character &baz = this->enemies[i];
    ifile 
    >> baz.hp
    >> baz.atk
    >> baz.def
    >> baz.time_stunned
    >> baz.time_dizzy
    >> baz.time_to_wait
    >> baz.atk_buff
    >> baz. time_atk_buffed
    >> baz.atk_nerf
    >> baz.time_atk_nerfed
    >> baz.def_nerf
    >> baz.time_def_nerfed;
  }
}

void GameHolder::remove_player(Character* dead_guy){
  for (size_t i = 0; i < this->allies.size(); i++)
  {
    if(&this->allies[i] == dead_guy){
      this->allies.erase(this->allies.begin() + i);
      std::cout << "debug\n";
      return;
    }
  }
  for (size_t i = 0; i < this->allies.size(); i++)
  {
    if(&this->enemies[i] == dead_guy){
      this->enemies.erase(this->enemies.begin() + i);
      std::cout << "debug\n";
      return;
    }
  }  
}

bool GameHolder::save(std::string filename){
  auto ofile = std::ofstream(filename);
  ofile << this->allies.size() << '\n';
  for (std::size_t i = 0; i < this->allies.size(); ++i)
  {
    auto *t = &this->allies[i];
    ofile << t->job << " "
          << t->hp << " "
          << t->atk << " "
          << t->def << " "
          << t->time_dizzy << " "
          << t->time_stunned << " "
          << t->time_to_wait << " "
          << t->atk_buff << " "
          << t->time_atk_buffed << " "
          << t->atk_nerf << " "
          << t->time_atk_nerfed << " "
          << t->def_nerf << " "
          << t->time_def_nerfed << '\n';
  }
  ofile << "\n\n";
  ofile << this->enemies.size() << '\n';
  for (std::size_t i = 0; i < this->enemies.size(); ++i)
  {
    auto *t = &this->enemies[i];
    ofile << t->job << " "
          << t->hp << " "
          << t->atk << " "
          << t->def << " "
          << t->time_dizzy << " "
          << t->time_stunned << " "
          << t->time_to_wait << " "
          << t->atk_buff << " "
          << t->time_atk_buffed << " "
          << t->atk_nerf << " "
          << t->time_atk_nerfed << " "
          << t->def_nerf << " "
          << t->time_def_nerfed << '\n';
  }
  ofile << '\n';

  return true;
}

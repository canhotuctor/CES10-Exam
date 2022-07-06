#include <iostream>
#include <fstream>
#include "defs.hpp"

int main(int a, char *args[])
{
  auto templates = character_presets();
  GameHolder game;
  char opt = init_screen(a, args);
  if (opt == 'l')
  {
    if (a == 2)
    {
      std::cout << "tryin to load the file...\n\n";
      wait_enter();
      game.load(args[1], templates);
      // clear screen and show allies and enemies in the game...
    }
    else
    {
      std::cout << "These were the inputs... which one will you load?\n";
      for (int i = 1; i < a; i++)
      {
        std::cout << i << ". " << args[i];
        if (check_emptiness(args[i]))
        {
          std::cout << " - (empty/not-found)";
        }
        std::cout << '\n';
      }
      int foo;
      std::cin >> foo;
      std::cin.ignore();
      if(check_emptiness(args[foo])){
        std::cout << "I tried to advise you...\nPlease initialize with valid save files\n\nShutting down...\n";
        wait_enter();
        return 0;
      }
      else{
        game.load(args[foo], templates);
      }
    }
  }
  else if (opt == 'n')
  {
    game.initialize(templates);
  }
  else
  {
    std::cout << "It's a shame you don't wanna play...\n\n";
    wait_enter();
    return 0;
  }

  while(true){
    auto x = game.round();
    if(!x) break;
  }

  if(game.allies.size() == 0){
    std::cout << "Well, it looks like you really didn't deserved to stay alive\n\nIf you want to prove yourself worthy, try again\n\n";
    wait_enter();
    return 0;
  }
  else if(game.enemies.size() == 0){
    std::cout << "Well done! You proved yourself worthy.\n\nHope you play again anytime soon...\n\n";
    wait_enter();
    return 0;
  }
  
  clear_screen();
  std::cout << "Hope you come back...\n\n";
  wait_enter();

  return 0;
}

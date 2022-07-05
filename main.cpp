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
      std::cout << "tryin to load the file...\n";
      wait_enter();
      // game.load(args[2]);
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
        // game.load(args[foo]);
      }
    }
  }
  else if (opt == 'n')
  {
    game.initialize(templates);
  }
  else
  {
    std::cout << "zannen dakara...\n";
    wait_enter();
    return 0;
  }

  // check if load was sucessfull

  while(true){
    auto x = game.round();
    if(!x) break;
  }
  return 0;
}

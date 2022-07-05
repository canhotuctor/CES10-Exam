#include <iostream>
#include <fstream>
#include <string>
#include "characters.hpp"

// #include "gameholder.hpp"

void clear_screen();
void wait_enter();
bool check_emptiness(char *);
bool check_emptiness(int, char **);
char init_screen(int, char**);

int main(int a, char *args[])
{
  // GameHolder game;
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
        std::cout << "I tried to advise you...\n Please initialize valid saves\n\nShutting down...\n";
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
    std::cout << "initializin...\n";
    wait_enter();
  }
  else
  {
    std::cout << "zannen dakara...\n";
    wait_enter();
    return 0;
  }

  // game.round() infinitely many times

  return 0;
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

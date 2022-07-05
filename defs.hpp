#include "gameholder.hpp"
#include <array>

void clear_screen();
void wait_enter();
bool check_emptiness(char *);
bool check_emptiness(int, char **);
char init_screen(int, char**);

std::vector<Character> character_presets();

#pragma once
#include <stdbool.h>

extern const char* const INVALID_INPUT_MESSAGE;
extern const char* const INVALID_CHOICE_MESSAGE;
extern const char* const EXIT_MESSAGE;
extern const char* const ALLOCATE_FAILURE_MESSAGE;
extern const char* const START_NEW_GAME_MESSAGE;
extern const char* const PRESS_KEY_MESSAGE;

extern const int OPTION_PLAY;
extern const int OPTION_QUIT;

void print_menu();
bool choose_option(int* choice);
void press_any_key();

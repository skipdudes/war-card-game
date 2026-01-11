#include "../include/utils.h"
#include <stdio.h>

const char* const INVALID_INPUT_MESSAGE = "Invalid input";
const char* const INVALID_CHOICE_MESSAGE = "Please provide a proper number";
const char* const EXIT_MESSAGE = "Quitting the application...";
const char* const ALLOCATE_FAILURE_MESSAGE = "Failed to allocate memory";
const char* const START_NEW_GAME_MESSAGE = "Starting a new War card game...";
const char* const PRESS_KEY_MESSAGE = "Press any key to continue...";

const int OPTION_PLAY = 1;
const int OPTION_QUIT = 2;

void print_menu()
{
	printf("Welcome to War card game!\n");
	printf("%d. Play\n", OPTION_PLAY);
	printf("%d. Exit\n", OPTION_QUIT);
}

bool choose_option(int* choice)
{
	printf("Your choice: ");

	char buffer[32];
	if (!fgets(buffer, sizeof(buffer), stdin)) return false;

	return sscanf(buffer, "%d", choice) == 1;
}

void press_any_key()
{
	printf("%s", PRESS_KEY_MESSAGE);
	(void)getchar();
	printf("\n");
}
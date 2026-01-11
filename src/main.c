#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../include/utils.h"
#include "../include/game.h"

int main()
{
	srand((unsigned)time(NULL));
	bool running = true;
	int choice = 0;

	while (running)
	{
		print_menu();
		if (!choose_option(&choice))
		{
			printf("\n%s\n", INVALID_INPUT_MESSAGE);
			printf("%s\n", EXIT_MESSAGE);
			running = false;
		}
		else if (choice == OPTION_QUIT)
		{
			printf("\n%s\n", EXIT_MESSAGE);
			running = false;
		}
		else if (choice != OPTION_PLAY)
		{
			printf("\n%s\n\n", INVALID_CHOICE_MESSAGE);
		}
		else
		{
			printf("\n%s\n", START_NEW_GAME_MESSAGE);
			game card_game;

			if (!init_game(&card_game)) running = false;
			else
			{
				print_game(&card_game);

				if (run_game(&card_game))
				{
					print_game(&card_game);
					free_game(&card_game);
					press_any_key();
				}
				else running = false;
			}
		}
	}

	return 0;
}
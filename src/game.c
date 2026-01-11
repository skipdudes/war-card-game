#include "../include/game.h"
#include "../include/card.h"
#include "../include/hand.h"
#include "../include/deck.h"
#include "../include/utils.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

const int RESULT_P1_WON = 1;
const int RESULT_P2_WON = 2;
const int RESULT_TIE = 3;

bool init_game(game* game)
{
	if (!game) return false;

	memset(game, 0, sizeof(*game));
	card* cards = NULL;

	cards = malloc(DECK_SIZE * sizeof(card));
	game->cards_p1 = malloc(DECK_SIZE * sizeof(card));
	game->cards_p2 = malloc(DECK_SIZE * sizeof(card));

	if (!cards || !game->cards_p1 || !game->cards_p2)
	{
		printf("\n%s\n", ALLOCATE_FAILURE_MESSAGE);

		free(cards);
		free_game(game);

		printf("%s\n", EXIT_MESSAGE);
		return false;
	}

	set_hand_empty(game->cards_p1, DECK_SIZE);
	set_hand_empty(game->cards_p2, DECK_SIZE);

	create_deck(cards);
	shuffle_deck(cards);
	deal_cards(cards, game->cards_p1, game->cards_p2);
	game->size_p1 = game->size_p2 = DECK_SIZE / 2;

	free(cards);
	return true;
}

void free_game(game* game)
{
	if (!game) return;

	free(game->cards_p1);
	free(game->cards_p2);

	game->cards_p1 = NULL;
	game->cards_p2 = NULL;
}

bool is_game_over(const game* game)
{
	if (game->result == RESULT_P1_WON
		|| game->result == RESULT_P2_WON
		|| game->result == RESULT_TIE)
		return true;

	return false;
}

void print_game(const game* game)
{
	bool game_over = is_game_over(game);
	if (game_over)
	{
		printf("Game Over!\n");
		printf("\nNumber of turns: %d\n", game->turns);

		if (game->result == RESULT_P1_WON) printf("\nPlayer #1 wins!\n");
		else if (game->result == RESULT_P2_WON) printf("\nPlayer #2 wins!\n");
		else if (game->result == RESULT_TIE) printf("\nIt's a tie!\n");
		else printf("\nThere are no winners\n");
	}

	printf("\nPlayer #1 card number: %zu\n", game->size_p1);
	printf("Player #2 card number: %zu\n", game->size_p2);

	printf("\nPlayer #1 hand value: %d\n", hand_value(game->cards_p1, game->size_p1));
	printf("Player #2 hand value: %d\n", hand_value(game->cards_p2, game->size_p2));

	printf("\nPlayer #1 hand:\n");
	if (game_over) print_hand(game->cards_p1, DECK_SIZE);
	else print_hand(game->cards_p1, game->size_p1);

	printf("\nPlayer #2 hand:\n");
	if (game_over) print_hand(game->cards_p2, DECK_SIZE);
	else print_hand(game->cards_p2, game->size_p2);

	printf("\n");
}

bool run_game(game* game)
{
	turn current_turn;
	memset(&current_turn, 0, sizeof(current_turn));

	current_turn.cards_table_p1 = malloc(DECK_SIZE * sizeof(card));
	current_turn.cards_table_p2 = malloc(DECK_SIZE * sizeof(card));

	if (!current_turn.cards_table_p1 || !current_turn.cards_table_p2)
	{
		printf("\n%s\n", ALLOCATE_FAILURE_MESSAGE);

		free(current_turn.cards_table_p1);
		free(current_turn.cards_table_p2);
		free_game(game);

		printf("%s\n", EXIT_MESSAGE);
		return false;
	}

	while (!is_game_over(game))
	{
		game->turns++;
		reset_turn(&current_turn);
		run_turn(&current_turn, game);
	}

	free(current_turn.cards_table_p1);
	free(current_turn.cards_table_p2);

	return true;
}

void reset_turn(turn* turn)
{
	turn->size_table_p1 = 0;
	turn->size_table_p2 = 0;
	turn->battle_result = 0;
}

void run_turn(turn* turn, game* game)
{
	while (!is_battle_over(turn))
	{
		if (player_empty(turn, game)) return;

		print_battle_info(game);
		run_battle(turn, game);
	}
}

bool is_battle_over(const turn* turn)
{
	if (turn->battle_result == RESULT_P1_WON
		|| turn->battle_result == RESULT_P2_WON
		|| turn->battle_result == RESULT_TIE)
		return true;

	return false;
}

void collect_table_cards(card* cards, card* cards_table_winner, card* cards_table_loser,
	size_t* size, size_t* size_table_winner, size_t* size_table_loser)
{
	if (!cards || !cards_table_winner || !cards_table_loser
		|| !size || !size_table_winner || !size_table_loser)
		return;

	for (size_t i = 0; i < *size_table_winner; i++)
		cards[*size + i] = cards_table_winner[i];
	*size += *size_table_winner;

	for (size_t i = 0; i < *size_table_loser; i++)
		cards[*size + i] = cards_table_loser[i];
	*size += *size_table_loser;

	*size_table_winner = 0;
	*size_table_loser = 0;
}

bool player_empty(turn* turn, game* game)
{
	bool p1_empty = is_card_empty(&game->cards_p1[0]);
	bool p2_empty = is_card_empty(&game->cards_p2[0]);

	if (p1_empty || p2_empty)
	{
		if (!p1_empty && p2_empty)
		{
			collect_table_cards(game->cards_p1, turn->cards_table_p1, turn->cards_table_p2,
				&game->size_p1, &turn->size_table_p1, &turn->size_table_p2);
			game->result = RESULT_P1_WON;
		}
		else if (p1_empty && !p2_empty)
		{
			collect_table_cards(game->cards_p2, turn->cards_table_p2, turn->cards_table_p1,
				&game->size_p2, &turn->size_table_p2, &turn->size_table_p1);
			game->result = RESULT_P2_WON;
		}
		else if (p1_empty && p2_empty)
		{
			game->result = RESULT_TIE;
		}

		return true;
	}

	return false;
}

void print_battle_info(const game* game)
{
	char buffer[32];
	card_to_string(&game->cards_p1[0], buffer, sizeof(buffer));
	printf("%s vs ", buffer);
	card_to_string(&game->cards_p2[0], buffer, sizeof(buffer));
	printf("%s\n", buffer);
}

card draw_card(const card* cards)
{
	return cards[0];
}

void remove_top_card(card* cards)
{
	set_card_empty(&cards[0]);
}

int compare_cards(const card p1, const card p2)
{
	if (p1.value > p2.value) return RESULT_P1_WON;
	if (p1.value < p2.value) return RESULT_P2_WON;
	return RESULT_TIE;
}

player_deck get_player_deck(turn* turn, game* game, const int player)
{
	if (player == RESULT_P1_WON)
		return (player_deck) { game->cards_p1, turn->cards_table_p1, & game->size_p1, & turn->size_table_p1 };

	return (player_deck) { game->cards_p2, turn->cards_table_p2, & game->size_p2, & turn->size_table_p2 };
}

void move_card_to_table(card* hand, size_t* hand_size, card* table, size_t* table_size)
{
	if (*hand_size == 0) return;

	table[*table_size] = hand[0];
	(*table_size)++;

	remove_top_card(hand);
	move_empty(hand, DECK_SIZE);
	(*hand_size)--;
}

void resolve_turn_win(turn* turn, game* game, const int winner)
{
	const int loser = (winner == RESULT_P1_WON) ? RESULT_P2_WON : RESULT_P1_WON;

	player_deck deck_winner = get_player_deck(turn, game, winner);
	player_deck deck_loser = get_player_deck(turn, game, loser);

	collect_table_cards(deck_winner.cards, deck_winner.cards_table, deck_loser.cards_table,
		deck_winner.size, deck_winner.size_table, deck_loser.size_table);

	turn->battle_result = winner;
	printf("Player #%d wins\n\n", winner == RESULT_P1_WON ? 1 : 2);
}

void run_battle(turn* turn, game* game)
{
	move_card_to_table(game->cards_p1, &game->size_p1, turn->cards_table_p1, &turn->size_table_p1);
	move_card_to_table(game->cards_p2, &game->size_p2, turn->cards_table_p2, &turn->size_table_p2);

	card p1_card = turn->cards_table_p1[turn->size_table_p1 - 1];
	card p2_card = turn->cards_table_p2[turn->size_table_p2 - 1];

	int result = compare_cards(p1_card, p2_card);
	if (result != RESULT_TIE) resolve_turn_win(turn, game, result);
	else run_war(turn, game);
}

void run_war(turn* turn, game* game)
{
	printf("War!\n");
	
	// Hidden cards
	if (player_empty(turn, game)) return;
	move_card_to_table(game->cards_p1, &game->size_p1, turn->cards_table_p1, &turn->size_table_p1);
	move_card_to_table(game->cards_p2, &game->size_p2, turn->cards_table_p2, &turn->size_table_p2);
	game->turns++;

	// Battle cards
	if (player_empty(turn, game)) return;
	move_card_to_table(game->cards_p1, &game->size_p1, turn->cards_table_p1, &turn->size_table_p1);
	move_card_to_table(game->cards_p2, &game->size_p2, turn->cards_table_p2, &turn->size_table_p2);

	card p1_card = turn->cards_table_p1[turn->size_table_p1 - 1];
	card p2_card = turn->cards_table_p2[turn->size_table_p2 - 1];

	int result = compare_cards(p1_card, p2_card);
	if (result == RESULT_TIE) run_war(turn, game);
	else resolve_turn_win(turn, game, result);
}
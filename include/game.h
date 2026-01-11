#pragma once
#include "../include/card.h"
#include <stdbool.h>
#include <stddef.h>

typedef struct game
{
	card* cards_p1, * cards_p2;
	size_t size_p1, size_p2;
	int result, turns;
} game;

typedef struct turn
{
	card* cards_table_p1, * cards_table_p2;
	size_t size_table_p1, size_table_p2;
	int battle_result;
} turn;

typedef struct player_deck
{
	card* cards, * cards_table;
	size_t* size, * size_table;
} player_deck;

extern const int RESULT_P1_WON;
extern const int RESULT_P2_WON;
extern const int RESULT_TIE;

bool init_game(game* game);
void free_game(game* game);
bool is_game_over(const game* game);
void print_game(const game* game);
bool run_game(game* game);
void reset_turn(turn* turn);
void run_turn(turn* turn, game* game);
bool is_battle_over(const turn* turn);
void collect_table_cards(card* cards, card* cards_table_winner, card* cards_table_loser,
	size_t* size, size_t* size_table_winner, size_t* size_table_loser);
bool player_empty(turn* turn, game* game);
void print_battle_info(const game* game);
card draw_card(const card* cards);
void remove_top_card(card* cards);
int compare_cards(const card p1, const card p2);
player_deck get_player_deck(turn* turn, game* game, const int player);
void move_card_to_table(card* hand, size_t* hand_size, card* table, size_t* table_size);
void resolve_turn_win(turn* turn, game* game, const int winner);
void run_battle(turn* turn, game* game);
void run_war(turn* turn, game* game);

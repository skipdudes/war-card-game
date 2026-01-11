#pragma once
#include "card.h"

extern const size_t DECK_SIZE;
extern const size_t CARDS_PER_SUIT;

void create_deck(card* cards);
void shuffle_deck(card* cards);
void deal_cards(card* cards, card* hand_p1, card* hand_p2);

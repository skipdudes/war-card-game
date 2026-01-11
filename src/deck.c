#include "../include/deck.h"
#include <stdlib.h>
#include <time.h>

const size_t DECK_SIZE = 52;
const size_t CARDS_PER_SUIT = 13;

void create_deck(card* cards)
{
    for (size_t i = 0; i < DECK_SIZE; i++)
    {
        size_t value = i % CARDS_PER_SUIT;
        size_t suit = i / CARDS_PER_SUIT;

        cards[i].value = value;
        cards[i].suit = suit;
    }
}

void shuffle_deck(card* cards)
{
    // Fisher-Yates
    for (size_t i = DECK_SIZE - 1; i > 0; i--)
    {
        int r = rand() % (i + 1);
        card c = cards[i];
        cards[i] = cards[r];
        cards[r] = c;
    }
}

void deal_cards(card* cards, card* hand_p1, card* hand_p2)
{
    for (size_t i = 0; i < DECK_SIZE; i++)
    {
        if (i < (DECK_SIZE / 2))
            hand_p1[i] = cards[i];
        else
            hand_p2[i - (DECK_SIZE / 2)] = cards[i];
    }
}
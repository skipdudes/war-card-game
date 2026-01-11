#include "../include/card.h"
#include <stdio.h>

const int CARD_VALUE_POINTS[CARD_VALUE_EMPTY] =
{
	3, 4, 5, 6, 7, 8, 9,
	10, 11, 12, 13, 14, 15
};

const char* const CARD_VALUE_NAMES[CARD_VALUE_EMPTY] =
{
	"2", "3", "4", "5", "6", "7",
	"8", "9", "10", "J", "Q", "K", "A"
};

const char* const CARD_SUIT_NAMES[CARD_SUIT_EMPTY] =
{
	"Spades", "Hearts", "Clubs", "Diamonds"
};

const char* const CARD_EMPTY_NAME = "Free spot";
const char* const CARD_INVALID_NAME = "Invalid card";

bool is_card_empty(const card* card)
{
	return card->value == CARD_VALUE_EMPTY && card->suit == CARD_SUIT_EMPTY;
}

void set_card_empty(card* card)
{
	card->value = CARD_VALUE_EMPTY;
	card->suit = CARD_SUIT_EMPTY;
}

bool is_card_value_valid(const card* card)
{
	return card->value >= CARD_VALUE_TWO && card->value <= CARD_VALUE_ACE;
}

bool is_card_suit_valid(const card* card)
{
	return card->suit >= CARD_SUIT_SPADE && card->suit <= CARD_SUIT_DIAMOND;
}

bool is_card_valid(const card* card)
{
	return is_card_value_valid(card) && is_card_suit_valid(card);
}

void card_to_string(const card* card, char* buffer, const size_t size)
{
	if (!card || !buffer || size == 0) return;

	if (is_card_empty(card))
	{
		snprintf(buffer, size, "%s", CARD_EMPTY_NAME);
		return;
	}

	if (is_card_valid(card))
	{
		snprintf(buffer, size, "%s %s",
			CARD_VALUE_NAMES[card->value],
			CARD_SUIT_NAMES[card->suit]);
	}
	else snprintf(buffer, size, "%s", CARD_INVALID_NAME);
}
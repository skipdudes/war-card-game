#pragma once
#include <stdbool.h>
#include <stddef.h>

typedef struct card
{
	enum card_value
	{
		CARD_VALUE_TWO, CARD_VALUE_THREE, CARD_VALUE_FOUR,
		CARD_VALUE_FIVE, CARD_VALUE_SIX, CARD_VALUE_SEVEN,
		CARD_VALUE_EIGHT, CARD_VALUE_NINE, CARD_VALUE_TEN,
		CARD_VALUE_JACK, CARD_VALUE_QUEEN, CARD_VALUE_KING,
		CARD_VALUE_ACE, CARD_VALUE_EMPTY
	} value;

	enum card_suit
	{
		CARD_SUIT_SPADE, CARD_SUIT_HEART,
		CARD_SUIT_CLUB, CARD_SUIT_DIAMOND,
		CARD_SUIT_EMPTY
	} suit;
} card;

extern const int CARD_VALUE_POINTS[CARD_VALUE_EMPTY];
extern const char* const CARD_VALUE_NAMES[CARD_VALUE_EMPTY];
extern const char* const CARD_SUIT_NAMES[CARD_SUIT_EMPTY];
extern const char* const CARD_EMPTY_NAME;
extern const char* const CARD_INVALID_NAME;

bool is_card_empty(const card* card);
void set_card_empty(card* card);
bool is_card_value_valid(const card* card);
bool is_card_suit_valid(const card* card);
bool is_card_valid(const card* card);
void card_to_string(const card* card, char* buffer, const size_t size);

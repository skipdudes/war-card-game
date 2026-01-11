#include "../include/hand.h"
#include <stdio.h>

bool is_hand_empty(const card* cards, const size_t size)
{
	for (size_t i = 0; i < size; i++)
		if (!is_card_empty(&cards[i]))
			return false;

	return true;
}

void set_hand_empty(card* cards, const size_t size)
{
	for (size_t i = 0; i < size; i++)
		set_card_empty(&cards[i]);
}

void print_hand(const card* cards, const size_t size)
{
	char buffer[32];

	for (size_t i = 0; i < size; i++)
	{
		card_to_string(&cards[i], buffer, sizeof(buffer));
		printf("#%zu: %s\n", i + 1, buffer);
	}
}

void move_empty(card* cards, const size_t size)
{
	size_t j = 0;

	for (size_t i = 0; i < size; i++)
	{
		if (!is_card_empty(&cards[i]))
		{
			if (j != i)
				cards[j] = cards[i];
			j++;
		}
	}

	for (; j < size; j++)
		set_card_empty(&cards[j]);
}

int hand_value(const card* cards, const size_t size)
{
	int value = 0;

	for (size_t i = 0; i < size; i++)
		if (is_card_value_valid(&cards[i]))
			value += CARD_VALUE_POINTS[cards[i].value];

	return value;
}
#pragma once
#include "card.h"

bool is_hand_empty(const card* cards, const size_t size);
void set_hand_empty(card* cards, const size_t size);
void print_hand(const card* cards, const size_t size);
void move_empty(card* cards, const size_t size);
int hand_value(const card* cards, const size_t size);

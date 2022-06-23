#pragma once
#include <unordered_map>

#include "letter_sequence.h"

class letter_node final
{
public:
	letter_node();

	letter_node(const char value, const unsigned long priority = 0);

	void insert_next_letters_sequence(letter_sequence& input_letter_sequence, const unsigned long priority_increasement);

	void increase_next_letter_priority(const char next_letter, const unsigned long priority_increasement);

	const letter_node& try_reach_end_of_sequence(letter_sequence& input_letter_sequence) const;

	void get_prioritized_sequence_completion(letter_sequence& output_letter_sequence) const;

	bool has_prioritized_next() const;

	const letter_node& get_prioritized_next() const;

private:
	char value_;
	unsigned long priority_;

	char prioritized_next_value_;
	unsigned long prioritized_next_priority_;

	std::unordered_map<char, letter_node> next_letters_;
};

#include "letter_node.h"

#include "no_prioritized_value_exception.h"
#include "reach_node_exception.h"

letter_node::letter_node() : value_('\0'), priority_(0),
                             prioritized_next_value_('\0'),
                             prioritized_next_priority_(0)
{
}

letter_node::letter_node(const char value, const unsigned long priority) : value_(value), priority_(priority),
prioritized_next_value_('\0'),
prioritized_next_priority_(0)
{
}

void letter_node::insert_next_letters_sequence(letter_sequence& input_letter_sequence,
	const unsigned long priority_increasement)
{
	if (input_letter_sequence.empty())
	{
		return;
	}

	const char next_letter = input_letter_sequence.top();

	input_letter_sequence.pop();

	if (next_letters_.find(next_letter) == next_letters_.end())
	{
		next_letters_[next_letter] = letter_node(next_letter, 0);
	}

	increase_next_letter_priority(next_letter, priority_increasement);

	next_letters_[next_letter].insert_next_letters_sequence(input_letter_sequence, priority_increasement);
}

void letter_node::increase_next_letter_priority(const char next_letter, const unsigned long priority_increasement)
{
	next_letters_[next_letter].priority_ += priority_increasement;

	const unsigned long next_letter_new_priority = next_letters_[next_letter].priority_;

	if (next_letter_new_priority > prioritized_next_priority_)
	{
		prioritized_next_value_ = next_letter;
		prioritized_next_priority_ = next_letter_new_priority;
	}
}

const letter_node& letter_node::try_reach_end_of_sequence(letter_sequence& input_letter_sequence) const
{
	if (input_letter_sequence.empty())
	{
		return *this;
	}

	const char next_letter = input_letter_sequence.top();

	input_letter_sequence.pop();

	const auto next_letter_it = next_letters_.find(next_letter);

	if (next_letter_it == next_letters_.end())
	{
		throw reach_node_exception("sequence does not exist");
	}

	return next_letter_it->second.try_reach_end_of_sequence(input_letter_sequence);
}

void letter_node::get_prioritized_sequence_completion(letter_sequence& output_letter_sequence) const
{
	if (next_letters_.empty() || prioritized_next_priority_ < priority_)
	{
		output_letter_sequence.push(value_);
		return;
	}

	const auto next_letter_it = next_letters_.find(prioritized_next_value_);

	if (next_letter_it == next_letters_.end())
	{
		throw reach_node_exception("next node is supposed to exist");
	}

	next_letter_it->second.get_prioritized_sequence_completion(output_letter_sequence);

	output_letter_sequence.push(value_);
}

bool letter_node::has_prioritized_next() const
{
	if (next_letters_.find(prioritized_next_value_) != next_letters_.end())
	{
		return true;
	}

	return false;
}

const letter_node& letter_node::get_prioritized_next() const
{
	if (!has_prioritized_next())
	{
		throw no_prioritized_value_exception("no prioritized value");
	}

	return next_letters_.find(prioritized_next_value_)->second;
}
#include "letter_sequence.h"

letter_sequence::letter_sequence()
{
}

letter_sequence::letter_sequence(const std::string& str)
{
	for (int idx = static_cast<int>(str.size()) - 1; idx >= 0; idx--)
	{
		sequence_.push(str[idx]);
	}
}

void letter_sequence::push(const char letter)
{
	sequence_.push(letter);
}

void letter_sequence::pop()
{
	sequence_.pop();
}

char letter_sequence::top() const
{
	return sequence_.top();
}

bool letter_sequence::empty() const
{
	return sequence_.empty();
}

std::string letter_sequence::move_to_string()
{
	std::string str;

	while (!sequence_.empty())
	{
		str += sequence_.top();

		sequence_.pop();
	}

	return str;
}
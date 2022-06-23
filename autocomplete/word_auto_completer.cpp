#include "word_auto_completer.h"

#include <fstream>
#include <ostream>
#include <sstream>

#include "reach_node_exception.h"

void word_auto_completer::increase_word_priority(const std::string& word, const unsigned long priority_increasement)
{
	if (word.empty() || priority_increasement == 0)
	{
		return;
	}

	letter_sequence input_letter_sequence(word);

	const char first_letter = input_letter_sequence.top();

	input_letter_sequence.pop();

	if (letters_priority_tree_.find(first_letter) == letters_priority_tree_.end())
	{
		letters_priority_tree_[first_letter] = letter_node(first_letter, 1);
	}

	letters_priority_tree_[first_letter].insert_next_letters_sequence(input_letter_sequence, priority_increasement);

	words_priority_stat_[word] += priority_increasement;
}

std::string word_auto_completer::get_word_auto_complete(const std::string& input) const
{
	if (input.empty())
	{
		return "";
	}

	letter_sequence input_letter_sequence(input);

	const char first_letter = input_letter_sequence.top();

	input_letter_sequence.pop();

	const auto first_node_it = letters_priority_tree_.find(first_letter);

	if (first_node_it == letters_priority_tree_.end())
	{
		return "";
	}

	try
	{
		letter_sequence output_letter_sequence;

		const letter_node& input_last_node = first_node_it->second.try_reach_end_of_sequence(input_letter_sequence);

		if (!input_last_node.has_prioritized_next())
		{
			return "";
		}

		const letter_node& prioritized_next = input_last_node.get_prioritized_next();

		prioritized_next.get_prioritized_sequence_completion(output_letter_sequence);

		return output_letter_sequence.move_to_string();
	}
	catch (const reach_node_exception& exception)
	{
		return "";
	}

}

bool word_auto_completer::load_stat_from_file(std::ifstream& in)
{
	clear_stat();

	if (!in.is_open())
	{
		return false;
	}

	std::string line;

	while (std::getline(in, line))
	{
		std::stringstream ss(line);

		std::string word;

		unsigned long count = 0;

		ss >> word >> count;

		if (word.empty() || count == 0)
		{
			continue;
		}

		increase_word_priority(word, count);
	}

	return true;
}

bool word_auto_completer::load_database_from_text(std::ifstream& in)
{
	if (!in.is_open())
	{
		return false;
	}

	while (!in.eof())
	{
		std::string word;

		in >> word;

		increase_word_priority(word);
	}

	return true;
}

bool word_auto_completer::save_stat_to_file(std::ofstream& out) const
{
	if (!out.is_open())
	{
		return false;
	}

	for (auto [word, count] : words_priority_stat_)
	{
		out << word << " " << count << std::endl;
	}

	return out.good();
}

void word_auto_completer::clear_stat()
{
	words_priority_stat_.clear();
	letters_priority_tree_.clear();
}
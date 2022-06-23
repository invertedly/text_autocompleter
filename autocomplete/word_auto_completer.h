#pragma once
#include <string>
#include <unordered_map>

#include "letter_node.h"

class word_auto_completer final
{
public:
	void increase_word_priority(const std::string& word, const unsigned long priority_increasement = 1);

	std::string get_word_auto_complete(const std::string& input) const;

	bool load_stat_from_file(std::ifstream& in);

	bool load_database_from_text(std::ifstream& in);

	bool save_stat_to_file(std::ofstream& out) const;

	void clear_stat();

private:
	std::unordered_map<char, letter_node> letters_priority_tree_;

	std::unordered_map<std::string, unsigned long> words_priority_stat_;
};

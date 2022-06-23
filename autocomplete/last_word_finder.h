#pragma once

#include <string>

class last_word_finder final
{
public:
	last_word_finder() = delete;

	static std::pair<size_t, std::string> get_last_word(const std::string& str);

private:
	static size_t get_last_word_position(const std::string& str);
};
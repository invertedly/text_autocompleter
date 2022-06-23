#pragma once
#include <string>
#include <utility>

#include "word_auto_completer.h"

enum class setup_choice
{
	old_stat, new_stat, exit
};

class user_interface final
{
public:
	user_interface() = delete;

	static setup_choice get_setup_choice();

	static bool try_setup_autocompleter(const setup_choice choice, word_auto_completer& dict);

	static bool load_stat(word_auto_completer& dict);

	static void user_input(word_auto_completer& dict, std::ofstream& user_output_file);

	static std::ofstream try_open_user_output_file();

	static bool save_stat(const word_auto_completer& dict);

	static std::pair<std::string, bool> user_word_input(
		word_auto_completer& dict);

private:
	static bool get_new_stat_from_file(
		word_auto_completer& dict);

	static void print_with_completion(
		const std::string& buffer,
		const word_auto_completer& dict);

	static void print_with_no_completion(
		const std::string& buffer);

	static std::tuple<std::string, std::string, std::string, size_t> get_completion(
		const std::string& buffer,
		const word_auto_completer& dict);
};

#include <string>
#include <iostream>
#include <conio.h>

#include "interface.h"

#include <fstream>

#include "console_operations.h"
#include "last_word_finder.h"
#include "word_auto_completer.h"

static const int backspace = 8;
static const int tab = 9;
static const int enter = 13;
static const int esc = 27;
static const int space = 32;

static const int symbols_low_bound = 32;
static const int symbols_high_bound = 127;

static const short predict_color = 10;
static const short input_color = 5;
static const short console_color = 7;

static const std::string stat_file_path = "stat.txt";

void user_interface::print_with_completion(const std::string& buffer, const word_auto_completer& dict)
{
    auto [completion, prefix, last_word, last_word_pos] = user_interface::get_completion(buffer, dict);

    console_operations::clear_line(std::cout);

    console_operations::set_console_color(input_color);
    std::cout << "\r" << prefix + last_word;

    console_operations::set_console_color(predict_color);
    std::cout << completion;

	console_operations::set_console_color(input_color);
}

void user_interface::print_with_no_completion(const std::string& buffer)
{
    console_operations::clear_line(std::cout);

    console_operations::set_console_color(input_color);

    std::cout << "\r" << buffer;
}

std::tuple<std::string, std::string, std::string, size_t> user_interface::get_completion(
    const std::string& buffer, const word_auto_completer& dict)
{
    auto [last_word_pos, last_word] = last_word_finder::get_last_word(buffer);

    const std::string completion = dict.get_word_auto_complete(last_word);

    const std::string prefix = buffer.substr(0, last_word_pos);

    return std::make_tuple(completion, prefix, last_word, last_word_pos);
}

setup_choice user_interface::get_setup_choice()
{
    std::cout << "\n# Choose how to obtain the database:" << std::endl;
    std::cout << "# 1. From previous history (if any)" << std::endl;
    std::cout << "# 2. From human text" << std::endl;
    std::cout << "# 0. Exit\n" << std::endl;

    char input;

    while (std::cin >> input && input != '1' && input != '2' && input != '0')
    {
        std::cout << "# Please enter correct input" << std::endl;
    }
    switch (input)
    {
    case '1': return setup_choice::old_stat;
    case '2': return setup_choice::new_stat;
    default:  return setup_choice::exit;
    }
}

bool user_interface::try_setup_autocompleter(const setup_choice choice, word_auto_completer& dict)
{
    switch (choice)
    {
    case setup_choice::old_stat: return load_stat(dict);
    case setup_choice::new_stat: return get_new_stat_from_file(dict);
    case setup_choice::exit:     return true;
    }
    return true;
}

bool user_interface::load_stat(word_auto_completer& dict)
{
    std::ifstream in;

    in.open(stat_file_path);

    return dict.load_stat_from_file(in);
}

bool user_interface::get_new_stat_from_file(word_auto_completer& dict)
{
    std::ifstream in;

    std::cout << "# Please enter path to a .txt file with text OR print 'back' to go back:" << std::endl;

    std::string input;

    while (std::cin >> input && input != "back")
    {
        in.open(input);

        if (!in.is_open())
        {
            std::cout << "# Please enter correct input" << std::endl;
        }
        else
        {
            return dict.load_database_from_text(in);
        }
    }

    return false;
}

void user_interface::user_input(word_auto_completer& dict, std::ofstream& user_output_file)
{
    std::cout << "\n# We are ready to start! Here are the rules:\n" << std::endl;

    std::cout << "# ENTER       - finish line" << std::endl;
    std::cout << "# BACKSPACE   - delete symbol" << std::endl;
    std::cout << "# TAB         - apply autocomplete" << std::endl;
    std::cout << "# ESC         - save and exit\n" << std::endl;

    std::cout << "# Type your text below:" << std::endl;

    bool exit = false;

    while (!exit)
    {
        auto [str, end_of_input] = user_word_input(dict);

        std::cout << std::endl;

        if (user_output_file.is_open())
        {
            user_output_file << str << std::endl;
        }

        exit = end_of_input;
    }

    user_output_file.close();

    console_operations::set_console_color(console_color);
}

std::ofstream user_interface::try_open_user_output_file()
{
    std::cout << "\n# If you want to save your typing enter .txt filepath where to save OR type 'next':" << std::endl;

    std::string input;

    std::ofstream user_output_file;

    while (std::cin >> input && input != "next")
    {
        user_output_file.open(input);

        if (!user_output_file.is_open())
        {
            std::cout << "# Please enter correct input" << std::endl;
        }
        else
        {
            break;
        }
    }

    return user_output_file;
}

bool user_interface::save_stat(const word_auto_completer& dict)
{
    std::ofstream out;

    out.open(stat_file_path);

    return dict.save_stat_to_file(out);
}

std::pair<std::string, bool> user_interface::user_word_input(word_auto_completer& dict)
{
    console_operations::set_console_color(input_color);

    std::string buffer;

    const short y_cur = console_operations::get_cursor_y_pos();

    char ch;

    while (true)
    {
        print_with_completion(buffer, dict);

        const auto x_cur = static_cast<short>(buffer.length());

        console_operations::set_cursor_pos(x_cur, y_cur);

        ch = _getch();

    	if (ch == enter || ch == esc)
        {
            print_with_no_completion(buffer);

            break;
        }

        if (ch == space)
        {
            auto [_, last_word] = last_word_finder::get_last_word(buffer);

            dict.increase_word_priority(last_word);

            buffer += ch;

            continue;
        }

        if (ch == backspace && !buffer.empty())
        {
            buffer.erase(buffer.length() - 1, 1);

            continue;
        }

        if (ch == tab)
        {
            auto [completion, prefix, last_word, last_word_pos] = get_completion(buffer, dict);

            buffer = prefix + last_word + completion;

            continue;
        }

        if (ch >= symbols_low_bound && ch < symbols_high_bound)
        {
            buffer += ch;
        }
    }

    if (!buffer.empty())
    {
        auto [_, last_word] = last_word_finder::get_last_word(buffer);

        dict.increase_word_priority(last_word);
    }

    if (ch == esc)
    {
        return {buffer, true};
    }

    console_operations::set_console_color(console_color);

    return { buffer, false };
}

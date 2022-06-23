#include <fstream>
#include <iostream>

#include "console_operations.h"
#include "interface.h"
#include "word_auto_completer.h"

int main()
{
    word_auto_completer dict;

    std::cout << "# This is Word Auto-Complete program." << std::endl;

    setup_choice command = setup_choice::exit;

    bool setup_success = false;

    while (!setup_success)
    {
        command = user_interface::get_setup_choice();

        setup_success = user_interface::try_setup_autocompleter(command, dict);
    }

    if (command == setup_choice::exit)
    {
        std::cout << "\n# Goodbye!" << std::endl;

        return 0;
    }

    std::ofstream user_output_file = user_interface::try_open_user_output_file();

    user_interface::user_input(dict, user_output_file);

    if (user_interface::save_stat(dict))
    {
        std::cout << "\n# All the statistics is saved and can be used again." << std::endl;
    }
    else
    {
        std::cout << "\n# Oops.. An error occured trying to save new statistics. Sorry!" << std::endl;
    }

    std::cout << "\n# Goodbye!" << std::endl;

    return 0;
}


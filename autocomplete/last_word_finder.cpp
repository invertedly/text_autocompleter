#include "last_word_finder.h"

std::pair<size_t, std::string> last_word_finder::get_last_word(const std::string& str)
{
    size_t last_word_pos = get_last_word_position(str);

    const std::string last_word = str.substr(last_word_pos);

    return std::make_pair(last_word_pos, last_word);
}

size_t last_word_finder::get_last_word_position(const std::string& str)
{
    if (static_cast<size_t>(std::count(str.begin(), str.end(), ' ')) == str.size())
    {
        return 0;
    }

    const size_t last_word_pos = str.rfind(' ');

    return last_word_pos == std::string::npos ? 0 : last_word_pos + 1;
}
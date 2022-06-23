#include "console_operations.h"

#include "Windows.h"

std::ostream& console_operations::clear_line(std::ostream& os)
{
    const size_t width = console_width();

    os << '\r' << std::string(width, ' ');

    return os;
}

void console_operations::set_console_color(const unsigned short color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

short console_operations::get_cursor_y_pos()
{
    CONSOLE_SCREEN_BUFFER_INFO info;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

    return info.dwCursorPosition.Y;
}

short console_operations::get_cursor_x_pos()
{
    CONSOLE_SCREEN_BUFFER_INFO info;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

    return info.dwCursorPosition.X;
}

void console_operations::set_cursor_pos(const short x, const short y)
{
    const COORD xy{ static_cast<short>(x - 1), y };

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
}

size_t console_operations::console_width()
{
    CONSOLE_SCREEN_BUFFER_INFO info;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

    const int width = info.dwSize.X - 1;

    return static_cast<size_t>(width < 0 ? 0 : width);
}

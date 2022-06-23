#pragma once
#include <ostream>

class console_operations final
{
public:
	console_operations() = delete;

	static std::ostream& clear_line(std::ostream& os);

	static void set_console_color(unsigned short color);

	static short get_cursor_y_pos();

	static short get_cursor_x_pos();

	static void set_cursor_pos(short x, short y);

private:
	static size_t console_width();
};

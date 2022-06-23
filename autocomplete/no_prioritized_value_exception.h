#pragma once
#include <exception>
#include <string>

class no_prioritized_value_exception final : public std::exception
{
public:
	explicit no_prioritized_value_exception(const std::string& message) : exception(message.data()) { }
};

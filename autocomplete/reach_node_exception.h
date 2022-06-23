#pragma once
#include <exception>
#include <string>

class reach_node_exception final : public std::exception
{
public:
	explicit reach_node_exception(const std::string& message) : exception(message.data()) { }
};

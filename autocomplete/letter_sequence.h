#pragma once
#include <stack>
#include <string>

class letter_sequence final
{
public:
	letter_sequence();

	letter_sequence(const std::string& str);

	void push(const char letter);

	void pop();

	char top() const;

	bool empty() const;

	std::string move_to_string();

private:
	std::stack<char> sequence_;
};

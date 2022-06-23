#include "gtest/gtest.h"

#include <fstream>

#include "../autocomplete/word_auto_completer.h"

TEST(word_auto_completer, get_word_auto_complete_common)
{
	word_auto_completer completer;

	completer.increase_word_priority("cat", 1);
	completer.increase_word_priority("dog", 1);
	completer.increase_word_priority("dogss", 1);

	ASSERT_EQ(completer.get_word_auto_complete("d"), "og");
	ASSERT_EQ(completer.get_word_auto_complete("do"), "g");
	ASSERT_EQ(completer.get_word_auto_complete("dog"), "ss");
	ASSERT_EQ(completer.get_word_auto_complete("c"), "at");
}

TEST(word_auto_completer, get_word_auto_complete_border)
{
	word_auto_completer completer;

	ASSERT_EQ(completer.get_word_auto_complete("d"), "");

	completer.increase_word_priority("a", 1);
	ASSERT_EQ(completer.get_word_auto_complete("a"), "");

	completer.increase_word_priority("a b", 1);
	ASSERT_EQ(completer.get_word_auto_complete("a"), " b");

	completer.increase_word_priority("ac", 2);
	ASSERT_EQ(completer.get_word_auto_complete("a"), "c");

	completer.increase_word_priority(" a b", 1);
	ASSERT_EQ(completer.get_word_auto_complete(" "), "a b");
}

TEST(word_auto_completer, get_word_auto_complete_incorrect_input)
{
	word_auto_completer completer;

	ASSERT_EQ(completer.get_word_auto_complete(""), "");

	completer.increase_word_priority("a", 1);

	ASSERT_EQ(completer.get_word_auto_complete(""), "");
}
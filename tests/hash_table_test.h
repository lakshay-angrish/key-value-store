#include "hash_table.h"
#include <gtest/gtest.h>

TEST(HashTable, open_close) {
	HashTable h;
	Status s = h.create("test_table.dat");
	ASSERT_TRUE(s) << s.to_string();

	EXPECT_EQ(123, h.file_size());

	s = h.remove_table();
	ASSERT_TRUE(s) << s.to_string();
}

TEST(HashTable, hash_function) {
	std::string key = "abc";
	int expected_hash = 590;

	EXPECT_EQ(expected_hash, HashTable::hash(key));
}

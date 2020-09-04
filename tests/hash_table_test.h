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

TEST(HashTable, put) {
	HashTable h;
	h.create("test_table.dat");

	Status s = h.put("abc", "123");
	ASSERT_TRUE(s) << s.to_string();
	EXPECT_EQ(123, h.file_size());

	s = h.put("abc", "124");
	ASSERT_TRUE(!s);
	EXPECT_EQ("Error: ERROR - Bucket Full", s.to_string());

	s = h.put("1234567890", "abc");
	ASSERT_TRUE(!s);
	EXPECT_EQ("Error: ERROR - Key/Value Size Limit Exceeded.", s.to_string());

	s = h.put("a", "1234567890");
	ASSERT_TRUE(!s);
	EXPECT_EQ("Error: ERROR - Key/Value Size Limit Exceeded.", s.to_string());

	s = h.put("6", "123");
	ASSERT_TRUE(s) << s.to_string();
	EXPECT_EQ(123, h.file_size());

	s = h.put("123", "123");
	ASSERT_TRUE(s) << s.to_string();
	EXPECT_EQ(123, h.file_size());

	h.remove_table();
}
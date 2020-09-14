#include "hash_table.h"
#include <gtest/gtest.h>

TEST(HashTable, open_close) {
	HashTable h;
	Status s = h.create("test_table.dat");
	ASSERT_TRUE(s) << s.to_string();

	EXPECT_EQ(13 + h.NUMBER_OF_BUCKETS * h.bucket_size(), h.file_size());

	s = h.remove_table();
	ASSERT_TRUE(s) << s.to_string();
}

TEST(HashTable, hash_function) {
	std::string key = "abc";
	unsigned int expected_hash = 2859854335;

	EXPECT_EQ(expected_hash, HashTable::hash(key));
}

TEST(HashTable, put_get) {
	HashTable h;
	h.create("test_table.dat");

	{
		Status s = h.put("abc", "123");
		ASSERT_TRUE(s) << s.to_string();
		EXPECT_EQ(13 + h.NUMBER_OF_BUCKETS * h.bucket_size(), h.file_size());

		s = h.put("abc", "124");
		ASSERT_TRUE(!s);
		EXPECT_EQ("Error: ERROR - Bucket Full", s.to_string());

		s = h.put("1234567890", "abc");
		ASSERT_TRUE(!s);
		EXPECT_EQ("Error: ERROR - Key/Value Size Must be <= 9.", s.to_string());

		s = h.put("a", "1234567890");
		ASSERT_TRUE(!s);
		EXPECT_EQ("Error: ERROR - Key/Value Size Must be <= 9.", s.to_string());

		s = h.put("6666666", "abcd");
		ASSERT_TRUE(s) << s.to_string();
		EXPECT_EQ(13 + h.NUMBER_OF_BUCKETS * h.bucket_size(), h.file_size());
	}

	{
		std::string value;
		Status s = h.get("abc", &value);
		ASSERT_TRUE(s) << s.to_string();
		EXPECT_EQ("123", value);

		s = h.get("6666666", &value);
		ASSERT_TRUE(s) << s.to_string();
		EXPECT_EQ("abcd", value);

		s = h.get("69", &value);
		ASSERT_TRUE(s) << s.to_string();
		EXPECT_EQ("", value);
	}

	h.remove_table();
}

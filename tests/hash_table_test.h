#include "hash_table.h"
#include <gtest/gtest.h>

TEST(HashTable, open_close) {
	HashTable h;
	Status s = h.create("test_table.dat", 5000);
	ASSERT_TRUE(s) << s.to_string();

	EXPECT_EQ(h.OFFSET_FROM_HEADER + h.NUMBER_OF_BUCKETS * h.bucket_size(), h.file_size());

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
	h.create("test_table.dat", 5);

	{
		Status s = h.put("abc", "123");
		ASSERT_TRUE(s) << s.to_string();
		EXPECT_EQ(h.OFFSET_FROM_HEADER + h.NUMBER_OF_BUCKETS * h.bucket_size(), h.file_size());

		s = h.put("def", "456");
		ASSERT_TRUE(s);

		s = h.put("abcde", "789");
		ASSERT_TRUE(s);

		s = h.put("abcdefg", "000");
		ASSERT_TRUE(s);

		s = h.put("abcdefghi", "0001");
		ASSERT_TRUE(s);

		s = h.put("1234567890", "abc");
		ASSERT_TRUE(!s);
		EXPECT_EQ("Error: ERROR - Key/Value Size Must be <= 9.", s.to_string());

		s = h.put("a", "1234567890");
		ASSERT_TRUE(!s);
		EXPECT_EQ("Error: ERROR - Key/Value Size Must be <= 9.", s.to_string());
	}

	{
		std::string value;
		Status s = h.get("abc", &value);
		ASSERT_TRUE(s) << s.to_string();
		EXPECT_EQ("123", value);

		s = h.get("def", &value);
		ASSERT_TRUE(s) << s.to_string();
		EXPECT_EQ("456", value);

		s = h.get("abcde", &value);
		ASSERT_TRUE(s) << s.to_string();
		EXPECT_EQ("789", value);

		s = h.get("abcdefg", &value);
		ASSERT_TRUE(s) << s.to_string();
		EXPECT_EQ("000", value);

		s = h.get("abcdefghi", &value);
		ASSERT_TRUE(s) << s.to_string();
		EXPECT_EQ("0001", value);

		s = h.get("69", &value);
		ASSERT_TRUE(!s) << s.to_string();
		EXPECT_EQ("", value);
	}

	h.remove_table();
}

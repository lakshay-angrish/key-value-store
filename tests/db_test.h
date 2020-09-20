#include "db.h"
#include <gtest/gtest.h>

TEST(HashDB, open_close) {
	HashDB db;
	Status s = db.open("test_db.dat");
	ASSERT_TRUE(s) << s.to_string();
	s = db.close();
	ASSERT_TRUE(s) << s.to_string();
}

TEST(HashDB, put) {
	HashDB db;
	db.open("test_db.dat");
	Status s = db.put("WITCH", "Freya");
	ASSERT_TRUE(s) << s.to_string();

	std::string val;
	db.get("WITCH", &val);
	EXPECT_EQ("Freya", val);

	s = db.close();
	ASSERT_TRUE(s) << s.to_string();
}

TEST(HashDB, get) {
	HashDB db;
	db.open("test_db.dat");

	{
		std::string value;
		Status s = db.get("WITCH", &value);
		ASSERT_TRUE(s) << s.to_string();
		EXPECT_EQ("Freya", value);
	}
	{
		std::string value;
		Status s = db.get("GOW", &value);
		ASSERT_TRUE(!s);
		EXPECT_EQ("", value);
	}

	Status s = db.close();
	ASSERT_TRUE(s) << s.to_string();

	{
		std::string value;
		Status s = db.get("GOW", &value);
		ASSERT_TRUE(!s);
		EXPECT_EQ("Error: ERROR - DB not opened.", s.to_string());
	}
	std::remove("test_db.dat");
}

TEST(HashDB, stress_test) {
	HashDB db;
	std::size_t size = 100000;
	db.open("test_db.dat", size);

	std::string key = "aaaaa";
	std::string::size_type i;
	while (size--) {
		Status s = db.put(key, key);
		ASSERT_TRUE(s) << s.to_string();

		i = 4;
		while (i != -1) {
			if (key[i] == 'z')	key[i--] = 'a';
			else {
				key[i]++;
				break;
			}
		}
	}

	size = 100000;
	key = "aaaaa";
	std::string val;
	while (size--) {
		Status s = db.get(key, &val);
		ASSERT_TRUE(s) << s.to_string();
		EXPECT_EQ(val, key);

		i = 4;
		while (i != -1) {
			if (key[i] == 'z')	key[i--] = 'a';
			else {
				key[i]++;
				break;
			}
		}
	}

	db.close();
	std::remove("test_db.dat");
}

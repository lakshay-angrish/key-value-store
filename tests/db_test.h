#include "db.h"
#include <gtest/gtest.h>

TEST(HashDB, open_close) {
	HashDB db;
	Status s = db.open("test_db.txt");
	ASSERT_TRUE(s) << s.to_string();
	s = db.close();
	ASSERT_TRUE(s) << s.to_string();
}

TEST(HashDB, get) {
	HashDB db;
	db.open("test_db.txt");

	{
		std::string value;
		Status s = db.get("GOW", &value);
		ASSERT_TRUE(s) << s.to_string();
		EXPECT_EQ("Kratos", value);
	}
	{
		std::string value;
		Status s = db.get("WITCH", &value);
		ASSERT_TRUE(!s);
		EXPECT_EQ("Error: ERROR - Key not found", s.to_string());
	}

	Status s = db.close();
	ASSERT_TRUE(s) << s.to_string();

	{
		std::string value;
		Status s = db.get("GOW", &value);
		ASSERT_TRUE(!s);
		EXPECT_EQ("Error: ERROR - DB not opened", s.to_string());
	}
}

TEST(HashDB, put) {
	{
		HashDB db;
		db.open("test_db.txt");
		Status s = db.put("WITCH", "Freya");
		ASSERT_TRUE(s) << s.to_string();

		std::string val;
		db.get("WITCH", &val);
		EXPECT_EQ("Freya", val);

		s = db.close();
		ASSERT_TRUE(s) << s.to_string();
	}
	{
		HashDB db;
		db.open("test_db.txt");
		std::string val;
		Status s = db.get("WITCH", &val);
		ASSERT_TRUE(s) << s.to_string();

		EXPECT_EQ("Freya", val);

		s = db.close();
		ASSERT_TRUE(s) << s.to_string();
	}
}

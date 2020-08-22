#include "db.h"
#include <gtest/gtest.h>

TEST(DB, open_close) {
	HashDB db;
	Status s = db.open("/home/lakshay/test_db.txt");
	ASSERT_TRUE(s) << s.to_string();
	s = db.close();
	ASSERT_TRUE(s) << s.to_string();
}
#include "status.h"
#include <gtest/gtest.h>

TEST(StatusTest, Constructor) {
	{
		Status s = Status::OK();
		ASSERT_TRUE(s);
	}

	{
		Status e = Status::Error();
		ASSERT_TRUE(!e);
	}
}

TEST(StatusTest, to_string) {
	{
		Status s = Status::OK();
		EXPECT_EQ("OK", s.to_string());
	}

	{
		Status e = Status::Error();
		EXPECT_EQ("Error: ERROR - Error occurred", e.to_string());
	}
}
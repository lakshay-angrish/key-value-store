#include <gtest/gtest.h>
#include <fstream>

#include "status_test.h"
#include "hash_table_test.h"
#include "db_test.h"

int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	int result = RUN_ALL_TESTS();

	return result;
}
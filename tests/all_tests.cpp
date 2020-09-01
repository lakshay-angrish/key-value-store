#include <gtest/gtest.h>
#include <fstream>

#include "status_test.h"
#include "db_test.h"
#include "hash_table_test.h"

int main(int argc, char* argv[]) {
	std::ofstream file("test_db.txt", std::ios::trunc);
	file << "GOW Kratos\n";
	file << "BOY Atreus\n";
	file.close();


	testing::InitGoogleTest(&argc, argv);
	int result = RUN_ALL_TESTS();

	std::remove("test_db.txt");

	return result;
}
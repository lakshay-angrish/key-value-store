#ifndef HASH_TABLE
#define HASH_TABLE

#include <status.h>

#include <fstream>
#include <string>

class HashTable {
public:
	HashTable(): file(NULL) {}

	Status create(std::string);
	Status remove_table();

	std::size_t file_size();

	static int hash(std::string);

	Status initialize_new_db();

	Status get(std::string, std::string*);
	Status put(std::string, std::string);

	int OFFSET_FROM_HEADER = 10;
	int BUCKET_SIZE = 22;
	int NUMBER_OF_BUCKETS = 5;

private:
	std::string db_path;
	std::fstream file;
};


#endif
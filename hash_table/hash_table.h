#ifndef HASH_TABLE
#define HASH_TABLE

#include "status.h"
#include "MurmurHash3.h"

#include <fstream>
#include <string>

class HashTable {
public:
	HashTable(): file(NULL) {}

	Status create(std::string);
	Status close();
	Status remove_table();

	std::size_t file_size();

	static unsigned int hash(std::string);

	Status initialize_new_db();

	Status get(std::string, std::string*);
	Status put(std::string, std::string);

	unsigned int OFFSET_FROM_HEADER = 10;
	unsigned int BUCKET_SIZE = 22;
	unsigned int NUMBER_OF_BUCKETS = 1000;
	std::size_t FILE_SIZE = NUMBER_OF_BUCKETS * BUCKET_SIZE + OFFSET_FROM_HEADER + 3;

private:
	std::string db_path;
	std::fstream file;
};


#endif
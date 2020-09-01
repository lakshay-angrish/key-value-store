#include "hash_table.h"

Status HashTable::create(std::string db_path) {
	this->db_path = db_path;

	try {
		file.open(db_path);

		if (!file.is_open()) {
			std::ofstream f(db_path);
			f.close();
			file.open(db_path);
			initialize_new_db();
		}
	} catch (std::exception e) {
		return Status::Error(e.what());
	}

	return Status::OK();
}

Status HashTable::remove_table() {
	try {
		remove(db_path.c_str());
	} catch (std::exception e) {
		return Status::Error("Error deleting file.");
	}
	return Status::OK();
}

std::size_t HashTable::file_size() {
	if (!file.is_open())
		return 0;

	std::size_t size;
	file.seekg(0, std::ios::end);
	size = file.tellg();

	return size;
}

Status HashTable::initialize_new_db() {
	if (!file.is_open())
		return Status::Error("Cannot initialize DB. File not opened.");

	try {
		//add file header that tells the number of buckets in the hash table
		int initial_number_of_buckets = 5;
		file << initial_number_of_buckets << std::string(8, ' ') << '\n';

		for (int i = 0; i != initial_number_of_buckets; i++) {
			file << "0" << '\n';						//0-> bucket is taken, 1-> empty bucket
			file << std::string(9, ' ') << '\n';		//reserving space for a key of upto 9 bytes;
			file << std::string(9, ' ') << '\n';		//reserving space for value
		}

		file << "END";									//footer for end of file
	} catch (std::exception e) {
		return Status::Error(e.what());
	}

	return Status::OK();
}

int HashTable::hash(std::string key) {
	//basic hash to be replaced later
	int h = 0;
	for (std::string::size_type i = 0; i != key.size(); i++)
		h += int(key[i]) * (i + 1);

	return h;
}

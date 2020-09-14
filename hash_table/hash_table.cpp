#include "hash_table.h"

#include <algorithm>
#include <cmath>

Status HashTable::create(std::string db_path) {
	this->db_path = db_path;

	try {
		file.open(db_path);

		if (!file.is_open()) {
			std::ofstream f(db_path);
			f.close();
			file.open(db_path);
			initialize_new_db();
		} else {
			//get the number of buckets from an already established database
			file.seekg(0, std::ios::beg);

			std::string header;
			std::getline(file, header);

			int end = std::find(header.begin(), header.end(), ' ') - header.begin();
			NUMBER_OF_BUCKETS = std::stoi(header.substr(0, end));
			file.seekg(0, std::ios::beg);
		}

	} catch (std::exception e) {
		return Status::Error(e.what());
	}

	return Status::OK();
}

Status HashTable::close() {
	try {
		if (file.is_open()) {
			file.close();
		}
		this->db_path.clear();
		return Status::OK();

	} catch (std::exception e) {
		return Status::Error("Error closing DB");
	}
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
		file << NUMBER_OF_BUCKETS << std::string(FIELD_WIDTH - std::floor(std::log10(NUMBER_OF_BUCKETS) + 1), ' ') << '\n';

		for (int i = 0; i != NUMBER_OF_BUCKETS; i++) {
			file << "0" << '\n';						//0-> bucket is taken, 1-> empty bucket
			file << std::string(FIELD_WIDTH, ' ') << '\n';		//reserving space for a key of upto 9 bytes;
			file << std::string(FIELD_WIDTH, ' ') << '\n';		//reserving space for value
		}

		file << "END";									//footer for end of file
	} catch (std::exception e) {
		return Status::Error(e.what());
	}

	return Status::OK();
}

unsigned int HashTable::hash(std::string key) {
	unsigned int h;
	MurmurHash3_x86_32(key.c_str(), key.size(), 1, &h);

	return h;
}

std::size_t HashTable::find_slot(std::string key) {
	int bucket_number = HashTable::hash(key) % NUMBER_OF_BUCKETS;
	return OFFSET_FROM_HEADER + bucket_number * bucket_size();
}

bool HashTable::is_slot_occupied(std::size_t slot) {
	file.seekg(slot, std::ios::beg);

	char bucket_flag;
	file.get(bucket_flag);

	return bucket_flag == '1';
}

std::string HashTable::get_key_from_slot(std::size_t slot) {
	file.seekg(slot + 2, std::ios::beg);

	std::string key;
	std::getline(file, key);			//read the key

	int end = std::find(key.begin(), key.end(), ' ') - key.begin();
	return key.substr(0, end);
}

std::string HashTable::get_value_from_slot(std::size_t slot) {
	file.seekg(slot + 12, std::ios::beg);

	std::string value;
	std::getline(file, value);		//read the value

	int end = std::find(value.begin(), value.end(), ' ') - value.begin();
	return value.substr(0, end);
}

Status HashTable::put(std::string key, std::string value) {
	if (!file.is_open())
		return Status::Error("DB not opened.");

	if (key.size() > FIELD_WIDTH || value.size() > FIELD_WIDTH)
		return Status::Error("Key/Value Size Must be <= " + std::to_string(FIELD_WIDTH) + ".");

	try {
		std::size_t slot = find_slot(key);

		if (is_slot_occupied(slot))
			return Status::Error("Bucket Full");

		file.seekg(-1, std::ios::cur);
		file << "1\n";
		file.seekg(file.tellg(), std::ios::beg);

		file << key;				//write the key
		file.seekp(FIELD_WIDTH + 1 - key.size(), std::ios::cur);			//move to the next line

		file << value;

	} catch (std::exception e) {
		return Status::Error(e.what());
	}

	return Status::OK();
}

Status HashTable::get(std::string key, std::string* value) {
	if (!file.is_open())
		return Status::Error("DB not opened.");

	if (key.size() > FIELD_WIDTH)
		return Status::Error("Key/Value Size Must be <= " + std::to_string(FIELD_WIDTH) + ".");

	try {
		std::size_t slot = find_slot(key);

		if (!is_slot_occupied(slot)) {
			value->clear();
			return Status::OK();
		}

		std::string key_in_bucket = get_key_from_slot(slot);

		if (key != key_in_bucket) {
			*value = "";
			return Status::OK();
		}

		*value = get_value_from_slot(slot);

	} catch (std::exception e) {
		return Status::Error(e.what());
	}

	return Status::OK();
}

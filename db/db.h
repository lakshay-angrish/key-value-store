#ifndef DB_H
#define DB_H

#include "status.h"
#include "hash_table.h"

#include <fstream>
#include <string>
#include <iostream>

class HashDB {
public:
	HashDB() {}
	~HashDB() {
		Status s = this->close();
		if (!s) {
			std::cerr << s.to_string() << std::endl;
		}
	}

	Status open(std::string db_path) { return hash_map.create(db_path); }
	Status close() { return hash_map.close(); }

	Status get(std::string key, std::string* value) { return hash_map.get(key, value); }
	Status put(std::string key, std::string value) { return hash_map.put(key, value); }

private:
	HashTable hash_map;
};

#endif
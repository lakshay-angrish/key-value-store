#ifndef DB_H
#define DB_H

#include <status.h>
#include <fstream>
#include <map>
#include <string>
#include <iostream>
#include <algorithm>

class HashDB {
public:
	HashDB(): file(NULL) {}
	~HashDB() {
		Status s = this->close();
		if (!s) {
			exit(1);
		}
	}

	Status open(std::string);
	Status close();

	Status get(std::string, std::string*);
	Status put(std::string, std::string);
	Status erase(std::string);

private:
	std::string db_path;
	std::fstream file;
	std::map<std::string, std::string> hash_map;

	Status write_to_file();
};

#endif
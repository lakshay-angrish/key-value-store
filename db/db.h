#ifndef DB_H
#define DB_H

#include <status.h>
#include <fstream>
#include <unordered_map>
#include <string>
#include <iostream>
#include <algorithm>

class HashDB {
public:
	typedef std::unordered_map<std::string, std::string>::const_iterator iterator;

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

	iterator begin() const { return std::cbegin(hash_map); }
	iterator end() const { return std::cend(hash_map); }

private:
	std::string db_path;
	std::fstream file;
	std::unordered_map<std::string, std::string> hash_map;

	Status write_to_file();
};

#endif
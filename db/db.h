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
			std::cout << s.to_string() << '\n';
		}
	}

	Status open(const char*);
	Status close();

private:
	std::fstream file;
	std::map<std::string, std::string> hash_map;
};

#endif
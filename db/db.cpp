#include "db.h"

Status HashDB::open(std::string db_path) {
	if (file.is_open())
		file.close();

	try {
		file.open(db_path);
		if (file) {
			std::string line;
			while (getline(file, line)) {
				size_t space = line.find(' ');
				hash_map.insert({
					line.substr(0, space),
					line.substr(++space, line.size() - space)
				});
			}
			this->db_path = db_path;
			return Status::OK();
		} else {
			return Status::Error("Error opening file");
		}
	} catch (std::exception e) {
		return Status::Error(e.what());
	}
}

Status HashDB::close() {
	try {
		if (file.is_open()) {
			Status s = write_to_file();
			if (!s)
				return s;
			file.close();
		}
		this->db_path.clear();
		return Status::OK();

	} catch (std::exception e) {
		return Status::Error("Error closing DB");
	}
}

Status HashDB::get(std::string key, std::string* value) {
	if (file.is_open()) {
		if (hash_map.find(key) != hash_map.end()) {
			*value = hash_map[key];
			return Status::OK();
		} else {
			return Status::Error("Key not found");
		}
	} else {
		return Status::Error("DB not opened");
	}
}

Status HashDB::put(std::string key, std::string value) {
	if (file.is_open()) {
		hash_map.insert({key, value});
		return Status::OK();
	} else {
		return Status::Error("DB not opened");
	}
}

Status HashDB::write_to_file() {
	try {
		file.close();
		file.open(db_path, std::ios::out);

		for (auto p: hash_map) {
			file << p.first << ' ' << p.second << '\n';
		}

		return Status::OK();

	} catch (std::exception e) {
		return Status::Error(e.what());
	}
}

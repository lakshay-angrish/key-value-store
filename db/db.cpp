#include "db.h"

Status HashDB::open(const char* db_path) {
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
		if (file.is_open())
			file.close();
		return Status::OK();
	} catch (std::exception e) {
		return Status::Error("Error closing DB");
	}
}
#ifndef STATUS_H
#define STATUS_H

#include <string>

class Status {
public:
	std::string to_string() {
		if (code == cOK) {
			return "OK";
		} else {
			return "Error: " + message1 + " - " + message2;
		}
	}

	static Status OK() { return Status(); }
	static Status Error() { return Status(cERROR, "ERROR", "Error occurred"); }

	operator bool() const { return code == cOK; }

private:
	enum Code {
		cOK = 0,
		cERROR = 1
	};

	Status(): code(cOK) {}
	Status(Code code, std::string m1, std::string m2): code(code), message1(m1), message2(m2) {}

	Code code;
	std::string message1;
	std::string message2;
};

#endif
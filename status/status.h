#ifndef STATUS_H
#define STATUS_H

#include <string>

class Status {
public:
	std::string to_string();

	static Status OK() { return Status(); }
	static Status Error(std::string msg = "Error occurred") { return Status(cERROR, "ERROR", msg); }

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
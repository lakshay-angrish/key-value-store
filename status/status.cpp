#include "status.h"

std::string Status::to_string() {
	if (code == cOK) {
		return "OK";
	} else {
		return "Error: " + message1 + " - " + message2;
	}
}
#ifndef EXECUTIVE_H
#define EXECUTIVE_H

#include "TestHarness.h"
#include <fstream>

class Executive {
public:
	std::vector<std::string> ParseXML(std::string);
private:
	std::string RemoveSubString(std::string, std::string);
};
#endif // !EXECUTIVE_H

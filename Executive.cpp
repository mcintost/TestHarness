#include "Executive.h"

/*
 *ParseXML: Takes in a XML and parses it
 */
std::vector<std::string> Executive::ParseXML(std::string xml) {
	std::ifstream inFile(xml);
	std::string given;
	std::string tokenTestName = "<test_name>";
	std::string tokenEndTestName = "</test_name>";
	std::vector<std::string> rawDll;
	std::vector<std::string> parsedContent;

	while (inFile) {
		getline(inFile, given);
		rawDll.push_back(given);
	}
	inFile.close();

	for (int i = 0; i < rawDll.size(); i++) {
		if (rawDll[i].find(tokenTestName) == 0) {
			std::string finalString = RemoveSubString(rawDll[i], tokenTestName);
			finalString = RemoveSubString(finalString, tokenEndTestName);
			parsedContent.push_back(finalString);
		} // End if
	} // End for

	return parsedContent;
}

/*
 * RemoveSubString: Creates the appropraite sub string.  
 */
std::string Executive::RemoveSubString(std::string given, std::string remove) {
	std::string::size_type length = given.find(remove);
	if (length != std::string::npos) {
		given.erase(length, remove.length());
	} // End if. 
	return given;
} 
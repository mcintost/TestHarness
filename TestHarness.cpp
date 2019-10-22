
#include "TestHarness.h"

// Empty Constructor
TestHarness::TestHarness() {}
// Empty Deconstructor
TestHarness::~TestHarness() {}

/*
 * SetReportLevel
 * Allows you to change LogReportLevel.
 * Takes in an enum.
 */
void TestHarness::SetReportLevel(LogReportLevel reportLevel) {
	logReportLevel = reportLevel;
}

/*
 * Executor
 * Executes all items in the TestCases vector and logs the results.
 * return voids
 */
void TestHarness::Executor() {
	int testNumber = 1;
	for (auto& i : this->TestCases) {
		try {
			i();
			Log(1, "Pass", testNumber);
		} catch (std::exception & e) {
			Log(0, e.what(), testNumber);
		} // End of catch.
		testNumber++;
	} // End of for.
	std::cout << "\n";
}

/*
 * Log
 * This Function creates the log report taking in three variables.
 * succeed: bool: test result
 * report: String: the log of all the tests
 * testNumber: int: The testNumber ran
 * return void
 */
void TestHarness::Log(bool succeed, std::string report, int testNumber) {
	std::string logString = "";
	if (succeed) {
		logString = "Test: " + std::to_string(testNumber) + " passed. ";

	} // End if succeed
	else {
		logString = "Test: " + std::to_string(testNumber) + " failed. ";
	} // End else: !succeed
	if (logReportLevel != LogReportLevel::LOW && !succeed) {
		logString += "Error Message: " + report + ". ";
	} // End if Report not Low
	if (logReportLevel == LogReportLevel::HIGH) {
		logString += "Test Ran: " + GetDate();
	} // End if Report High
	fullReport << logString << std::endl;
}

/*
 * GetDate
 * Gets the current timestamp for logging purposes
 * returns string: Current timestamp.
 */
std::string TestHarness::GetDate() {
	time_t result = time(NULL);
	char str[26];
	ctime_s(str, sizeof str, &result);
	return str;
}

/*
 * AddtoTestCases 
 * callable: function point passed in to be added to the TestCases vector.
 * return void
 */
void TestHarness::AddtoTestCases(std::function<void()> callable) {
	TestCases.push_back(callable);
}

/*
 * Template typename Test
 * callable: function: Adds functor to the TestCases vector.
 * return void
 */
template <typename Test>
void TestHarness::AddtoTestCases(Test &test) {
	TestCases.push_back(test);
}

/*
 * ResetTestCases
 * Empties the vector of testcases
 * return void
 */
void TestHarness::ResetTestCases() {
	TestCases.clear();
	fullReport.str(std::string());
}

/* 
 * ToString
 * Returns a String and adds Test Results to the the top of the file.
 * return string: 
 */
std::string TestHarness::ToString() {
	std::cout << "Test Results: " << std::endl;
	std::string returnString = this->fullReport.str();
	return returnString;
}

/*
 * Test Case: Bad Allocation
 * Attempt to allocate an unsinged long to an int
 * return bool true: Should fail though because of error.
 */
bool TestBadAlloc() {
	std::bad_alloc x;
	while (true) {
		new int[99999ul];
	} // End while
	throw x;
	return true;
}

/*Creating classes for TestBadCastTest*/
class Base { virtual void member() {} };
class Derived : Base {};

/*
 * Test case: Bad Cast
 * Attempt to cast derived class to base class 
 * return bool true: Should fail though because of error.
 */
bool TestBadCast() {
	std::bad_cast error;
	Base baseClass;
	Derived& derivedClass = dynamic_cast<Derived&>(baseClass);
	throw error;
	return true;
}

int main() {
	TestHarness testHarness;
	std::cout << "Running Test at a low level of reporting\n";
	testHarness.AddtoTestCases(TestBadAlloc);
	testHarness.AddtoTestCases(TestBadCast);
	Functor Funct;
	testHarness.AddtoTestCases(Funct);
	testHarness.Executor();
	std::cout << testHarness.ToString();
	testHarness.ResetTestCases();
	testHarness.SetReportLevel(TestHarness::LogReportLevel::MEDIUM);
	std::cout << "Running Test at a medium level of reporting\n";
	testHarness.AddtoTestCases(TestBadAlloc);
	testHarness.AddtoTestCases(TestBadCast);
	testHarness.AddtoTestCases(Funct);
	testHarness.Executor();
	std::cout << testHarness.ToString();
	testHarness.ResetTestCases();
	testHarness.SetReportLevel(TestHarness::LogReportLevel::HIGH);
	std::cout << "Running Test at a high level of reporting\n";
	testHarness.AddtoTestCases(TestBadAlloc);
	testHarness.AddtoTestCases(TestBadCast);
	testHarness.AddtoTestCases(Funct);
	testHarness.Executor();
	std::cout << testHarness.ToString();
	testHarness.ResetTestCases();
	
	std::cin.get();
	return 0;
}


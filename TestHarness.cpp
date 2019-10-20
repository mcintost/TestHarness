
#include "TestHarness.h"

TestHarness::TestHarness() {
}

TestHarness::~TestHarness() {
}

void TestHarness::SetReportLevel(LogReportLevel reportLevel) {
	logReportLevel = reportLevel;
}




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
		logString += "Test Ran: " + getDate();
	} // End if Report High
	fullReport << logString << std::endl;
}

std::string TestHarness::getDate() {
	time_t result = time(NULL);
	char str[26];
	ctime_s(str, sizeof str, &result);
	return str;
}

void TestHarness::AddtoTestCases(std::function<void()> callable)
//add function pointer to TestSuite vector
{
	TestCases.push_back(callable);
}

template <typename Test>
void TestHarness::AddtoTestCases(Test &test) {
	TestCases.push_back(test);
}

void TestHarness::ResetTestCases() {
	TestCases.clear();
	fullReport.str(std::string());
}

std::string TestHarness::ToString()
{
	std::cout << "Test Results: " << std::endl;
	std::string returnString = this->fullReport.str();
	return returnString;
}

bool TestBadAlloc();
bool TestBadCast();

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

bool TestBadAlloc()
{
	std::bad_alloc x;
	while (true)
	{
		new int[100000000ul];
	}
	throw x;
	return true;
}

class Base { virtual void member() {} };
class Derived : Base {};

bool TestBadCast()
{
	std::bad_cast e;
	Base b;
	Derived& rd = dynamic_cast<Derived&>(b);
	throw e;
	return true;
}
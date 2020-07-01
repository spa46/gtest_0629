// 12_테스트대역.cpp
//
//  이전에는 Test Double을 총칭해서 Mock으로 불렀다.
//  Test Double - "xUnit Test Pattern 정리"
//  1) Test Stub
//  2) Fake Object
//  3) Test Spy
//  4) Mock Object
//  외) Dummy - 인자 체크용으로 사용하는 객체
//
#include <string>

class FileSystem {
public:
	bool IsValid(const std::string& filename) {
		// ....
		return false;
	}
};

// 단위 테스트
//  결합 국소화: 어떤 테스트가 실패했는지를 보고 버그가 무엇인지를 금방 알아낼 수 있다.

class Logger {
public:
	// hello.log
	//  => 확장자를 제외한 파일이름의 길이가 5글자 이상이어야 한다.
	bool IsValidLogFilename(const std::string& filename) {
		//-----------------
		size_t index = filename.find_last_of(".");
		std::string name = filename.substr(0, index);
		
		if (name.size() < 5) {
			return false;
		}
		//-----------------

		FileSystem fs;
		return fs.IsValid(filename);
	}
};

//------------------------------------------------
#include <gtest/gtest.h>

class LoggerTest : public testing::Test {
};

TEST_F(LoggerTest, IsValidLogFilename_NameLoggerThan5Chars_ReturnsTrue) {
	Logger logger;
	std::string validFilename = "valid.log";

	EXPECT_TRUE(logger.IsValidLogFilename(validFilename))
		<< "파일명이 다섯글자 이상일 때";
}

TEST_F(LoggerTest, IsValidLogFilename_NameShorteThan5Chars_ReturnsFalse) {
	Logger logger;
	std::string wrongFilename = "bad.log";

	bool actual = logger.IsValidLogFilename(wrongFilename);
	
	EXPECT_FALSE(actual) << "파일명이 다섯글자 미만일 때";
}
























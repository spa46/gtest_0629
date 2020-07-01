// 12_테스트대역.cpp
#include <string>

struct IFileSystem {
	virtual ~IFileSystem() {}

	virtual bool IsValid(const std::string& filename) = 0;
};

class FileSystem : public IFileSystem {
public:
	bool IsValid(const std::string& filename) override {
		// ....
		return false;
	}
};

class Logger {
public:
	explicit Logger(IFileSystem* p = nullptr) : fs(p) {
		if (fs == nullptr) {
			fs = new FileSystem;
		}
	}

	bool IsValidLogFilename(const std::string& filename) {
		//-----------------
		size_t index = filename.find_last_of(".");
		std::string name = filename.substr(0, index);

		if (name.size() < 5) {
			return false;
		}
		//-----------------
		// IFileSystem* fs = new FileSystem;
		return fs->IsValid(filename);
	}
private:
	IFileSystem* fs;
};

//------------------------------------------------
#include <gmock/gmock.h>
// GMock을 통해 변경해봅시다.

using testing::NiceMock;

class MockFileSystem : public IFileSystem {
public:
	MOCK_METHOD(bool, IsValid, (const std::string& filename), (override));
};

class LoggerTest : public testing::Test {
};

TEST_F(LoggerTest, IsValidLogFilename_NameLoggerThan5Chars_ReturnsTrue) {
	NiceMock<MockFileSystem> stub;
	ON_CALL(stub, IsValid).WillByDefault([](const std::string& filename) {
		return true;
	});
	Logger logger(&stub);
	std::string validFilename = "valid.log";

	EXPECT_TRUE(logger.IsValidLogFilename(validFilename))
		<< "파일명이 다섯글자 이상일 때";
}

TEST_F(LoggerTest, IsValidLogFilename_NameShorteThan5Chars_ReturnsFalse) {
	NiceMock<MockFileSystem> stub;
	ON_CALL(stub, IsValid).WillByDefault([](const std::string& filename) {
		return true;
	});
	Logger logger(&stub);
	std::string wrongFilename = "bad.log";

	bool actual = logger.IsValidLogFilename(wrongFilename);

	EXPECT_FALSE(actual) << "파일명이 다섯글자 미만일 때";
}

// * 테스트 대역 종류 4가지
// 1. Test Stub
// 2. Fake Object
// 3. Test Spy
// 4. Mock Object

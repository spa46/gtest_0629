
#include <gmock/gmock.h>

enum Level { INFO, WARN };

struct Logger {
	virtual ~Logger() {}

	virtual void Send(Level level, const char* filename, 
		const char* dir, int line) = 0;
};

class User {
public:
	void Do(Logger* logger) {
		// ---
		logger->Send(INFO, "log2.txt", "/tmp", 42);
		// ---
	}
};

//--------------------------------------------------------
class MockLogger : public Logger {
public:
	// 간략화 하는 방법을 이용하면, 필요한 인자에 대해서만 검증할 수 있습니다.
	
	// 1. 검증을 위한 형태를 제공한다.
	MOCK_METHOD(void, Send, (Level level, const char* filename));

	// 2. 기존의 함수가 Mocking 된 함수를 호출하도록 변경한다.
	void Send(Level level, const char* filename, const char* dir, int line) {
		Send(level, filename);  // Mocking 된 함수를 호출한다.
	}


#if 0
	MOCK_METHOD(void, Send, (Level level, const char* filename,
				const char* dir, int line), (override));
#endif
};


TEST(LoggerTest, MockTest) {
	MockLogger mock;
	User user;

	// EXPECT_CALL(mock, Send(INFO, "log.txt", "/tmp", 42));
	EXPECT_CALL(mock, Send(INFO, "log.txt"));

	user.Do(&mock);
}


















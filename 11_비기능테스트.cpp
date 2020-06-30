// 비기능테스트
//  : 기능적인 동작에 대한 검증이 아니라,
//    성능이나 메모리 등의 비기능적인 부분을 검증하는 작업.

// => Google Test 는 비기능적인 기능을 제공하고 있지 않습니다.

#include <unistd.h>

int Job() {
	sleep(2);
	return 42;
}

#include <gtest/gtest.h>

// 방법 1. - 비기능 TestSuite을 만든다.

class JobTest : public testing::Test {
protected:
	time_t startTime;
	void SetUp() override {
		startTime = time(0);
	}

	void TearDown() override {
		time_t endTime = time(0);
		time_t duration = endTime - startTime;

		EXPECT_LE(duration, 1) << "시간 초과: " << duration << " 초가 걸렸습니다.";
	}
};


// 1초 안에 수행되어야 한다.
TEST_F(JobTest, Job) {
	int actual = Job();

	EXPECT_EQ(42, actual);
}











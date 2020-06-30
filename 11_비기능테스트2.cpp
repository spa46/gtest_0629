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


// 방법 2. 별도의 ASSERT 제공한다. - Junit5
#define EXPECT_TIMEOUT(fn, sec) \
	do {                        \
		time_t s = time(0);     \
		fn;                     \
		time_t e = time(0);     \
		time_t d = e - s;       \
		EXPECT_LE(d, sec) << "Timeout : " << d << " sec"; \
	} while(0)

TEST(JobTest, Job) {
	EXPECT_TIMEOUT(Job(), 1);
}

#if 0
TEST(JobTest, Job) {
	{
		time_t s = time(0);
		Job();
		time_t e = time(0);
		time_t d = e - s;
		EXPECT_LE(d, 1) << "Timeout : " << d << " sec";
	}
}
#endif



#if 0
// 방법 1. - 비기능 TestSuite을 만든다.
template <int N>
class JobTest : public testing::Test {
protected:
	time_t startTime;
	void SetUp() override {
		startTime = time(0);
	}

	void TearDown() override {
		time_t endTime = time(0);
		time_t duration = endTime - startTime;

		EXPECT_LE(duration, N) << "시간 초과: " 
				<< duration << " 초가 걸렸습니다.";
	}
};

class Job1Sec : public JobTest<1> {
protected:
	void SetUp() override {
		JobTest::SetUp(); // !!
	}

	void TearDown() override {
		JobTest::TearDown();
	}
};

// 1초 안에 수행되어야 한다.
TEST_F(Job1Sec, Job) {
	int actual = Job();

	EXPECT_EQ(42, actual);
}
#endif

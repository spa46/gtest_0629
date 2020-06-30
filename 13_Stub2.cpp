// Stub: 특수한 상황을 시뮬레이션 할 수 있다.
#include <string>

struct Time {
	virtual ~Time() {}
	
	virtual std::string GetCurrentTime() = 0;
};

class User {
public:
	// 메소드 주입
	int Do(Time* time) {
		std::string t = time->GetCurrentTime();
		if (t == "00:00") {
			return 100;
		}

		return 0;
	}
};

//------------------------
// 자정에 User의 Do를 호출하였을 경우, 100을 반환하는지 여부를 검증하고 싶다.
#include <gtest/gtest.h>

class StubTime : public Time {
public:
	std::string GetCurrentTime() override {
		return "00:00";
	}
};

// 의존성 주입 - 제품 코드를 사용하는 방식 그대로 테스트 코드를 작성할 수 있다.
TEST(UserTest, DoTest) {
	StubTime stub;
	User user;

	int actual = user.Do(&stub);

	EXPECT_EQ(100, actual) << "00:00분에 호출하였을 때";
}

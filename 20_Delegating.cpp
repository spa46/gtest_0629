// 20_Delegating.cpp

// Google Mock - ON_CALL

#include <gmock/gmock.h>

class User {
public:
	virtual ~User() {}

	virtual std::string GetName() const { return "Tom"; }
	virtual int GetAge() const { return 42; };
};

//--------------------
class MockUser : public User {
public:
	MOCK_METHOD(std::string, GetName, (), (const, override));
	MOCK_METHOD(int, GetAge, (), (const, override));
};

// 1. Mocking 함수의 결과값은 초기화값이 반환된다.
//    int - 0
//    std::string - ""
//    T - T()
// 2. Mocking 된 함수의 결과를 제어하기 위해서, gMock은 ON_CALL 이라는
//    매크로를 제공합니다.
//     => 하드코딩 - Stub을 만들때 사용하는 기술입니다.
//              : Return, Throw, ...
//        로직     - Fake를 만들때도 사용할 수 있습니다.


// ON_CALL
//   - WillByDefault
//     : 인자로 함수(함수 객체)를 받도록 되어 있다.

using testing::Return;  // 결과 반환
using testing::Throw;   // 예외를 던진다.
using testing::NiceMock;
// 행위 기반 검증을 수행하지 않을 경우, NiceMock을 통해 경고를 제거하는 것이
// 좋다.

TEST(UserTest, MockTest2) {
	NiceMock<MockUser> user;
	ON_CALL(user, GetName())
		.WillByDefault(Throw(std::invalid_argument("invalid arg")));

	EXPECT_THROW(user.GetName(), std::invalid_argument);
}

TEST(UserTest, MockTest) {
	// User user;
	NiceMock<MockUser> user;
	ON_CALL(user, GetName())
		.WillByDefault(Return("Bob"));
	ON_CALL(user, GetAge())
		.WillByDefault(Return(100));

	std::string name = user.GetName();
	int age = user.GetAge();

	std::cout << name << ", " << age << std::endl;
}

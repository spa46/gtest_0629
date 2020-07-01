

#include <gmock/gmock.h>

class User {
public:
	virtual ~User() {}

	virtual int GetAge() const { return 42; }
	virtual std::string GetName() const { return "Tom"; }
};

class MockUser : public User {
public:
	MOCK_METHOD(int, GetAge, (), (const, override));
	MOCK_METHOD(std::string, GetName, (), (const, override));
};

using testing::NiceMock;

class Functor {
public:
	int operator()() const {
		return 100;
	}
};

// ON_CALL 이용해서 '로직을 작성'하는 것이 가능하다.
//  => Google Mock을 이용해서 Fake를 생성하는 것도 가능하다.
//  => C++11에서는 람다를 이용해서 함수 객체를 생성하는 것이 일반적입니다.
TEST(UserTest, GetTest) {
	NiceMock<MockUser> user;
	ON_CALL(user, GetAge())
		.WillByDefault(Functor());

	std::string expected = "Alice";
	// C++은 클로저에 대한 기술을 명시적으로 사용해야 한다.
	ON_CALL(user, GetName())
		.WillByDefault([&expected] {
			return expected;
		});
	EXPECT_EQ(expected, user.GetName());

#if 0
	ON_CALL(user, GetAge())
		.WillByDefault([]() {
			printf("Lambda!\n");
			return 100;
		});
#endif

	int actual = user.GetAge();
	EXPECT_EQ(100, actual);
}







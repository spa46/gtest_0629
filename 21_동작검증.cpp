
// 21_동작검증
//   = 행위 기반 검증
//   1) 호출 여부 - EXPECT_CALL
//   2) 호출 횟수 - EXPECT_CALL.Times / WillOnce / WillRepeatedly
//   3) 호출 인자 - Matchers
//   4) 호출 순서 - InSequence, Sequence

//  * EXPECT_CALL
//  * Matcher

#include <gmock/gmock.h>

class User {
public:
	virtual ~User() {}

	virtual void Say(const char* message) = 0;
	virtual int Add(int a, int b) = 0;
};

//--------------------------------------
class MockUser : public User {
public:
	MOCK_METHOD(void, Say, (const char* message), (override));
	MOCK_METHOD(int, Add, (int a, int b), (override));
};

void Do(User* user) {
	user->Say("Hello");
	int result = user->Add(10, 20);
	printf("result: %d\n", result);
}

// 1. 호출 여부 검증
//   - EXPECT_CALL
//    : 인자에 대한 부분을 처리하는 Matcher 이용하면, 좀 더 편리하게 
//      행위 검증을 수행할 수 있습니다.

using testing::Lt;
using testing::Gt;
using testing::Eq;
using testing::Ne;
using testing::Le;
using testing::Ge;
using testing::NotNull;
using testing::HasSubstr;
using testing::_;

using testing::AllOf;  // &&
using testing::AnyOf;  // ||
using testing::Not;    // !

using testing::NiceMock;
TEST(UserTest, DoTest4) {
	NiceMock<MockUser> mock;

	EXPECT_CALL(mock, Add(_, 20));

	Do(&mock);
}

TEST(UserTest, DoTest3) {
	// Arrange
	NiceMock<MockUser> mock;

	// Add의 첫번째 인자는 1 ~ 10 - x >= 1 && x <= 10
	// Add의 두번째 인자는 10보다 작거나, 20보다 크거나 - !(x < 10 || x > 20)
	auto firstArgMatcher = AllOf(Ge(1), Le(10));
	auto secondArgMatcher = Not(AnyOf(Lt(10), Ge(20)));
	EXPECT_CALL(mock, Add(firstArgMatcher, secondArgMatcher));

	// Act
	Do(&mock);
}


TEST(UserTest, DoTest2) {
	// Arrange
	MockUser mock;

	// Assert - EXPECT_CALL
	// EXPECT_CALL(mock, Say(NotNull())); 
	EXPECT_CALL(mock, Say(HasSubstr("Hello")));
	EXPECT_CALL(mock, Add(Ne(20), Gt(10)));

	// Act
	Do(&mock);
}


TEST(UserTest, DoTest1) {
	// Arrange
	MockUser mock;

	// Assert - EXPECT_CALL
	EXPECT_CALL(mock, Say("Hello")); 
	EXPECT_CALL(mock, Add(10, 20));

	// Act
	Do(&mock);
}

















































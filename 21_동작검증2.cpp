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
	user->Say("Hello");
	user->Add(10, 20);
	user->Add(10, 20);
	user->Add(10, 20);
}

using testing::_;

// 2. 호출 횟수 검증 
//  - Times
// EXPECT_CALL(...).Times(N)
//   1) AnyNumber
//   2) atLeast - 최소 N번
//   3) atMost  - 최대 N번

using testing::AnyNumber;
using testing::AtLeast;
using testing::AtMost;

TEST(UserTest, DoTest) {
	MockUser mock;

	EXPECT_CALL(mock, Say(_)).Times(AnyNumber());
	EXPECT_CALL(mock, Add(_, _)).Times(AtMost(2));

#if 0
	// 1번에 대한 호출만 고려한다.
	EXPECT_CALL(mock, Say(_));
	EXPECT_CALL(mock, Add(_, _));
#endif

	Do(&mock);
}

void Do2(User* user) {
	user->Add(11, 20);
	user->Add(12, 20);
	user->Add(13, 20);
}

// 호출 횟수를 검증할 때, 인자의 Matching에 따라 횟수가 변한다.
TEST(UserTest, DoTest2) {
	MockUser mock;

	EXPECT_CALL(mock, Add(_, 20)).Times(AtMost(3));

	Do(&mock);
}

// EXPECT_CALL은 행위 기반 검증을 위해 사용합니다.
// 결과를 제어하는 기능도 제공하고 있습니다.
//  - 행위 기반 검증과 동시에 결과를 제어한다면, ON_CALL이 아닌
//    EXPECT_CALL로 처리할 수 있습니다. 
//      1. WillOnce
//         : 한번에 호출에 대한 결과를 제어할 수 있습니다.
//      2. WillRepeatedly
//         : 기본 동작에 대한 결과를 제어할 수 있다.

// EXPECT_CALL - 횟수 룰
//  1. Times 정의하지 않으면, 1번을 가정한다.
//  2. WillOnce()가 N개 있으면, N번을 가정한다.
//  3. N개의 WillOnce()와 WillRepeatedly()가 있을 경우, AtLesat(N)을 가정한다.

using testing::Return;

TEST(UserTest, DoTest3) {
	MockUser mock;

	EXPECT_CALL(mock, Add(_, _))
		.WillOnce(Return(101))
		.WillOnce(Return(102))
		.WillOnce(Return(103))
		.WillOnce(Return(104))
		.WillOnce(Return(105))
		.WillRepeatedly(Return(300));

	printf("%d\n", mock.Add(10, 30));
	printf("%d\n", mock.Add(10, 30));
	printf("%d\n", mock.Add(10, 30));
	printf("%d\n", mock.Add(10, 30));
	printf("%d\n", mock.Add(10, 30));
	printf("%d\n", mock.Add(10, 30));
	printf("%d\n", mock.Add(10, 30));
	printf("%d\n", mock.Add(10, 30));
}



















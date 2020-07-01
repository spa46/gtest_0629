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
TEST(UserTest, DoTest) {
	MockUser mock;

	EXPECT_CALL(mock, Add(_, 20)).Times(AtMost(3));

	Do(&mock);
}





















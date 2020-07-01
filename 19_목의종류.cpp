// 19_목의종류

#include <gmock/gmock.h>

struct Foo {
	virtual ~Foo() {}

	virtual void Say(const std::string& message) = 0;
};

class User {
public:
	void Talk(Foo* p) {
		p->Say("hello");
	}
};

class MockFoo : public Foo {
public:
	MOCK_METHOD(void, Say, (const std::string& message), (override));
};

using testing::NaggyMock;
using testing::NiceMock;
using testing::StrictMock;

TEST(FooTest, SayTest) {
	// MockFoo mock;
	// NaggyMock<MockFoo> mock;
	// NiceMock<MockFoo> mock;
	StrictMock<MockFoo> mock;
	User user;


	user.Talk(&mock); // mock.Say("hello");
}

// Google Mock의 종류
// 1. Naggy - Default
//  : 검증에 대한 부분을 수행하지 않고, 모킹된 함수가 호출된 경우
//    경고를 준다.
//    GMOCK WARNING:
//  Uninteresting mock function call - returning directly.
//  Function call: Say(@0x7ffcdbb31620 "hello")
//    - 테스트의 결과에는 아무런 영향을 주지 않는다.
//
// 2. Nice
//  : 검증에 대한 부분을 수행하지 않고 호출된 함수에 대해서 아무런 메세지도 주지 않는다.
// 3. Strict
//  : 검증에 대한 부분을 수행하지 않고 호출된 함수가 존재할 경우, 테스트는 실패한다.
//  - 주의해서 사용해야 한다.
//  - 테스트 성공에 대한 요구사항이 엄격해지기 때문에, 테스트를 작성하는 비용이 상대적으로 높다.












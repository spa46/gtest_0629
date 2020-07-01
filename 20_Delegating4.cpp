#include <gmock/gmock.h>

class Foo {
public:
	virtual ~Foo() {}

	virtual int PureFunc() = 0;
	virtual int DefaultImpl(const char* str) {
		printf("Foo::DefaultImpl - %s\n", str);
		return 100;
	}
};

class MockFoo : public Foo {
public:
	MOCK_METHOD(int, PureFunc, (), (override));
	MOCK_METHOD(int, DefaultImpl, (const char* str), (override));
};

TEST(FooTest, Foo) {
	MockFoo mock;

	// 문제: ON_CALL을 통해 MockFoo에 대해서 DefaultImpl의 호출을 부모의
	// 기본 기능을 이용하도록 해보세요.

}



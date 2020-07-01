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

	// 부모의 기능을 MockFoo를 통해서 사용하기 위해서는 별도의 함수가 필요합니다.
	int FooDefaultImpl(const char* str) {
		return Foo::DefaultImpl(str);
	}
};

TEST(FooTest, Foo) {
	MockFoo mock;

	ON_CALL(mock, DefaultImpl)
		.WillByDefault([&mock](const char* str) {
			return mock.FooDefaultImpl(str); 
		});
	// 문제: ON_CALL을 통해 MockFoo에 대해서 DefaultImpl의 호출을 부모의
	// 기본 기능을 이용하도록 해보세요.
	#if 0
	ON_CALL(mock, DefaultImpl)
		.WillByDefault([&mock](const char* str) {
			return mock.DefaultImpl(str);  // 재귀!
		});
	#endif
	
	mock.DefaultImpl("hello");
}



#include <gmock/gmock.h>

class Foo {
public:
	virtual ~Foo() {}

	virtual int PureFunc() = 0;
	virtual int DefaultImpl(const char* str) {
		printf("Foo::DefaultImpl - %s\n", str);
		return 100;
	}

	virtual void Move(int x, int y) = 0;
};

class MockFoo : public Foo {
public:
	MOCK_METHOD(int, PureFunc, (), (override));
	MOCK_METHOD(int, DefaultImpl, (const char* str), (override));

	MOCK_METHOD(void, Move, (int x, int y), (override));

	// 부모의 기능을 MockFoo를 통해서 사용하기 위해서는 별도의 함수가 필요합니다.
	int FooDefaultImpl(const char* str) {
		return Foo::DefaultImpl(str);
	}
};

TEST(FooTest, MoveTest) {

	MockFoo mock;
	ON_CALL(mock, Move).WillByDefault([](int a, int b) {
		printf("Move - Lambda\n");
	});
	ON_CALL(mock, Move(10, 20)).WillByDefault([](int a, int b) {
		printf("Move - (10, 20)\n");
	});

	// ON_CALL이 동일한 함수에 대해서 정의되었을 경우,
	// 최근에 등록된것부터 체크해서, 처리한다.
	mock.Move(30, 40);
}



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



#include <gmock/gmock.h>

struct Element {};

class Foo {
public:
	virtual ~Foo() {}  
	// 상속을 통해 모의 객체를 만들 때, 가상 소멸자가 정의되어 있지 않으면
	// 메모리 누수가 발생한다.
	
	// 기본 구현이 부모를 통해 제공된다면, Mocking 하지 않고,
	// 부모의 구현을 그대로 이용할 수 있다.
	virtual int Add() { printf("Foo::Add()\n"); }
	virtual int Add(Element x) { printf("Foo::Add(Element)\n"); }
	virtual int Add(int times, Element x) {
		printf("Add(times, x)\n");
	} // Mocking
};

class MockFoo : public Foo {
public:
	using Foo::Add; // 부모의 구현을 그대로 이용하겠다.
	                // 주의!!!
	                //  MOCK_METHOD 사용하고, 부모의 함수를 호출할 때
	                //  옆의 코드가 없으면 컴파일 오류가 발생한다!!

	MOCK_METHOD(int, Add, (), (override));
	// 아래 메소드는 Mocking을 하지 않고, 부모의 구현을 그대로 사용하고 싶다.
#if 0
	MOCK_METHOD(int, Add, (Element x), (override));
	MOCK_METHOD(int, Add, (int times, Element x), (override));
#endif
};

TEST(MockTest, FooTest) {
	MockFoo mock; // !!

	mock.Add();
	// mock.Add(Element());
	mock.Add(10, Element());
}










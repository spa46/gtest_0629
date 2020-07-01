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
	// 의도: Add(int, Element)에 대한 Mocking만 하고 싶다.
	MOCK_METHOD(int, Add, (int times, Element x), (override));
	// MOCK_METHOD를 추가하는 순간, 부모의 동일 이름을 가진 함수의 구현이 가려진다.
	// 명시적인 선언이 필요하다.
	using Foo::Add;
};

TEST(MockTest, FooTest) {
	MockFoo mock;

	mock.Add();
	mock.Add(Element());
	mock.Add(42, Element());
}


#if 0
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
#endif

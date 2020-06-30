#include <gmock/gmock.h>

struct Gadget {};

// Abstract class - Foo
class Foo {
public:
	virtual ~Foo() {}

	virtual bool Transform(Gadget* g) = 0;
protected:
	virtual void Resume() { printf("Resume\n"); }

private:
	virtual int GetTimeOut() { printf("GetTimeOut\n"); }
};

// 일반 상속이 가능한 클래스에 대해서도 Mocking 가능합니다. 
//  1. 부모의 메소드에 접근 지정 레벨에 상관없이 무조건 public으로 만드는 것이
//     원칙입니다.
//  2. 모의 객체: 실제 동작이 수행되지 않는다.
//                동작이 수행되었는지 여부만 기록한다.
class MockFoo : public Foo {
public:
	MOCK_METHOD(bool, Transform, (Gadget* g), (override));
	MOCK_METHOD(void, Resume, (), (override));

	// private - 허용한다.
	MOCK_METHOD(int, GetTimeOut, (), (override));
};


TEST(FooTest, Foo) {
	MockFoo mock; // !!

	mock.Resume();
	mock.GetTimeOut();
}











#include <gmock/gmock.h>

struct Gadget {};

// Abstract class - Foo
class Foo {
public:
	virtual ~Foo() {}  // 반드시 필요하다.
	                   // 상속을 통해 모의 객체를 생성하는데 가상 소멸자가 없이, 
	                   // 모의 객체를 생성하면 누수가 발생합니다.

	// 상속을 통한 모의 객체 생성시 함수는 반드시 가상함수 이어야 한다.
	virtual bool Transform(Gadget* g) = 0;
protected:
	virtual void Resume() { printf("Resume\n"); }

private:
	virtual int GetTimeOut() { printf("GetTimeOut\n"); }
};

// 일반 상속이 가능한 클래스에 대해서도 Mocking 가능합니다. 
//  1. 부모의 메소드에 접근 지정 레벨에 상관없이 무조건 public으로 만드는 것이
//     원칙입니다.
//      : 테스트 코드 안에서 사용하기 위해서는 반드시 public 이어야 한다.
//  2. 모의 객체: 실제 동작이 수행되지 않는다.
//                동작이 수행되었는지 여부만 기록한다.
class MockFoo : public Foo {
public:
	MOCK_METHOD(bool, Transform, (Gadget* g), (override));
	MOCK_METHOD(void, Resume, (), (override));
	MOCK_METHOD(int, GetTimeOut, (), (override));
};


TEST(FooTest, Foo) {
	MockFoo mock; // !!

	mock.Resume();
	mock.GetTimeOut();
	mock.Transform(nullptr);
}











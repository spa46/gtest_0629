#include <gmock/gmock.h>

// Google Mock - Mocking
// 1) Interface
// 2) Abstract class
// 3) 상속 가능한 class
// 4) Template class

// Template Class에 대해서도 Mocking을 할 수 있다.
template <typename T>
struct StackInterface {
	virtual ~StackInterface() {}

	virtual int GetSize() const = 0;
	virtual void Push(const T& x) = 0;
};


// Template Mocking - 모의 객체를 Template으로 만드는 것도 가능합니다.
template <typename T>
class MockStack : public StackInterface<T> {
public:
	MOCK_METHOD(int, GetSize, (), (override, const));
	MOCK_METHOD(void, Push, (const T& x), (override));
};

TEST(MockStackTest, Sample) {
	MockStack<int> s;

	s.Push(10);
	s.GetSize();
}


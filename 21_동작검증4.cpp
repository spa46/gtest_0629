
// 주의할점
#include <gmock/gmock.h>

struct Bar {
	std::string name;
};

struct Foo {
	virtual ~Foo() {}

	virtual Bar& GetBar() = 0;
	virtual const Bar& GetBar() const = 0;
};

class MockFoo : public Foo {
public:
	MOCK_METHOD(Bar&, GetBar, (), (override));
	MOCK_METHOD(const Bar&, GetBar, (), (override, const));
};

using testing::Return;     // Value Type
using testing::ReturnRef;  // Ref Type
using testing::Const;

void Do(Foo& p) {
	Bar b = p.GetBar(); 
	printf("Non const version - %s\n", b.name.c_str());
}

void Do2(const Foo& p) {
	Bar b = p.GetBar(); 
	printf("Const version - %s\n", b.name.c_str());
}

TEST(MockFoo, FooTest) {
	MockFoo mock;
	Bar bar1, bar2;
	bar1.name = "bar1";
	bar2.name = "bar2";

	EXPECT_CALL(mock, GetBar())
		.WillOnce(ReturnRef(bar1));
	EXPECT_CALL(Const(mock), GetBar())
		.WillOnce(ReturnRef(bar2));

	Do(mock);
	Do2(mock);
}





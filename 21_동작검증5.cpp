#include <gmock/gmock.h>

class Printer {
public:
	virtual ~Printer() {}

	virtual void Print(int c) {}
	virtual void Print(char c) {}
};

class MockPrinter : public Printer {
public:
	MOCK_METHOD(void, Print, (int c), (override));
	MOCK_METHOD(void, Print, (char c), (override));
};

// call of overloaded ‘gmock_Print(int)’ is ambiguous
//  : 함수의 오버로드시에 EXPECT_CALL에서 모호성 오류가 발생할 경우,
//   타입에 대한 정보를 추가적으로 전달해야 한다.

using testing::An;
using testing::TypedEq;
using testing::Matcher;
using testing::Eq;

TEST(PrinterTest, Print) {  
	MockPrinter mock;

	// EXPECT_CALL(mock, Print(An<int>()));
	EXPECT_CALL(mock, Print(Matcher<int>(Eq(10))));
	EXPECT_CALL(mock, Print(TypedEq<char>('a')));

	mock.Print(10);
	mock.Print('a');
}






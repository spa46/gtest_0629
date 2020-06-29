class Calculator {
public:
	double Display() { return 0; }
	
	void Enter(double v) {}
	void PressPlus() {}
	void PressMinus() {}
	void PressEquals() {}

	// Calculator(int n) {}
};

#include <gtest/gtest.h>

// 픽스쳐 설치 방법
// 2. Delegate Setup(위임 설치)

// 1. 명시적인 TestSuite 클래스를 작성해야 합니다.
class CalculatorTest : public testing::Test {
	// 테스트 유틸리티 함수를 제공할 때,  private으로 제공하면, 테스트에서 접근할 수 없습니다. 최소 protected를 사용해야 합니다. 
protected:
	// Test Utility Method
	Calculator* Create() { return new Calculator; }
};


// 2. TEST -> TEST_F
#define SPEC printf
TEST_F(CalculatorTest, PlusTest2) {
	SPEC("2와 2를 더했을 때, 4의 결과가 나오는지를 검증한다.\n");
	Calculator* calc = Create();
	
	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	calc->PressEquals();

	ASSERT_EQ(calc->Display(), 4) << "2+2 하였을 때";
}

TEST_F(CalculatorTest, PlusTest) {
	Calculator* calc = Create();
	
	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	calc->PressEquals();

	if (calc->Display() == 4) {
		SUCCEED();
	} else {
		FAIL() << "2+2 하였을 때";
	}
}



// [gtest]
// TestSuite(TestCase X)
//   - Test1
//   - Test2
//
// [xUnit]
// TestSuite
//    - TestCase1
//    - TestCase2















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

#define SPEC printf
// 픽스쳐 설치 방법
// 3. 암묵적 설치(Implicit Setup)
//  : 여러 테스트에서 같은 테스트 픽스쳐의 코드를 SetUp함수에서 생성한다.
//   => xUnit Test Framework가 지원하는 기능 

class CalculatorTest : public testing::Test {
public:
	CalculatorTest() : calc(nullptr) {}
protected:
	Calculator* calc;

	void SetUp() override {
		printf("SetUp()\n");
		calc = new Calculator;
	}
};


TEST_F(CalculatorTest, PlusTest2) {
	SPEC("2와 2를 더했을 때, 4의 결과가 나오는지를 검증한다.\n");
	// Calculator* calc = new Calculator;
	
	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	calc->PressEquals();

	ASSERT_EQ(calc->Display(), 4) << "2+2 하였을 때";
}

TEST_F(CalculatorTest, PlusTest) {
	// Calculator* calc = new Calculator;
	
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















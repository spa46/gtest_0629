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

// Test Fixture
//  정의: xUnit Test Pattern에서는 SUT를 실행하기 위해서 준비해야 하는 모든 것을 테스트 픽스쳐라고 합니다.
//  픽스쳐를 구성하는 모든 로직부분을 '픽스쳐 설치(Setup)한다' 라고 합니다.
  
// 픽스쳐 설치 방법
// 1. Inline Fixture Setup
//  : 모든 픽스쳐 설치를 테스트 함수 안에서 수행한다.
//  장점: 픽스쳐를 설치하는 과정과 검증 로직이 테스트 함수 안에 존재하기 
//        때문에 인과관계를 쉽게 분석할 수 있다.
//  단점: 모든 테스트 코드 안에서 '코드 중복'이 발생한다.

#define SPEC printf
TEST(CalculatorTest, PlusTest2) {
	SPEC("2와 2를 더했을 때, 4의 결과가 나오는지를 검증한다.\n");
	Calculator* calc = new Calculator;
	
	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	calc->PressEquals();

	ASSERT_EQ(calc->Display(), 4) << "2+2 하였을 때";
}

TEST(CalculatorTest, PlusTest) {
	Calculator* calc = new Calculator;
	
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















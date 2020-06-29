// SUT(System Under Test)
//  : 테스트 대상 시스템 
//   - 단위 테스트를 작성하고자 하는 코드, 모듈, 시스템 등을 의미한다.
//     CUT(Class Under Test or Code Under Test)
class Calculator {
public:
	double Display() { return 0; }
	
	void Enter(double v) {}
	void PressPlus() {}
	void PressMinus() {}
	void PressEquals() {}
};

// 2_3A.cpp
#include <gtest/gtest.h>
  
// Test Suite Name
//  : 테스트 대상 클래스의 마지막에 Test를 붙인 이름을 사용합니다.
//   Calculator -> CalculatorTest / Spec

// CalculatorTest.PlusTest
//  : 실패하지 않는 테스트는 성공을 취급된다.
#if 0
TEST(CalculatorTest, PlusTest) {
	FAIL() << "테스트는 작성 중입니다. ";
}
#endif

// 3A: 테스트를 구성하는 방법.
// 1. Arrange: 객체를 생성하고, 필요한 경우 설정하고 준비한다. - Given
// 2. Act: 객체에 작용을 가한다. - When
// 3. Assert: 기대하는 바를 단언한다. - Then
//

// TDD(테스트 주도 개발) -> BDD(행위 주도 개발)
//  1. 가독성
//  2. 모의 객체의 활용

// 테스트의 이름에서 어떤 테스트를 수행하는지 자세히 명시해야 한다.
//   PlusTest -> Plus_2Plus2_Diplays4

#define SPEC printf
TEST(CalculatorTest, PlusTest2) {
	SPEC("2와 2를 더했을 때, 4의 결과가 나오는지를 검증한다.\n");
	Calculator* calc = new Calculator;
	
	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	calc->PressEquals();

	// 테스트 함수 안에서 제어 구문의 발생이 최소화되어야 한다.
	// => 조건문, 반복문, 예외 처리 등의 코드의 사용이 발생하지 않도록 해야 한다.
	// => xUnit Test Framework - Assertions(Macro)
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















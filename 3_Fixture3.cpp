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
// 3. 암묵적 설치/해체(Implicit Setup/Tear down)
//  : 여러 테스트에서 같은 테스트 픽스쳐의 코드를 SetUp함수에서 생성한다.
//   => xUnit Test Framework가 지원하는 기능 
//   장점: 테스트 코드 중복을 제거하고, 필요하지 않은 상호작용을 제거할 수 있다.
//   단점: 픽스쳐 설치 코드가 테스트 함수 밖에 존재하기 때문에,
//         테스트 함수만으로 테스트 코드를 이해하기 어려울 수 있다. 
//
// [테스트 품질]
// 1. 가독성
// 2. 유지보수성
// 3. 신뢰성

// xUnit Test Pattern - 테스트를 구성하는 방법.
//  => 4단계 테스트 패턴
//  1단계: 테스트의 픽스쳐를 설치하거나, 실제 결과를 관찰하기 위해 필요한 것을 집어넣는 작업을 한다. -> SetUp()
//  2단계: SUT와 상호 작용한다. -> TestBody()
//  3단계: 기대 결과를 확인한다.-> TestBody()
//  4단계: 테스트 픽스쳐를 해체해서, 테스트 시작 이전의 상태로 돌려놓는다. -> TearDown()

// [xUnit Test Framework - Runner]
//  : 신선한 픽스쳐의 전략을 사용하고 있습니다. - 독립적인 테스트
// CalculatorTest *ts = new CalculatorTest;
// ts->SetUp();
// ts->TestBody();
// ts->TearDown();
// delete ts;
//
// CalculatorTest *ts = new CalculatorTest;
// ts->SetUp();
// ts->TestBody();
// ts->TearDown();
// delete ts;

class CalculatorTest : public testing::Test {
public:
	CalculatorTest() : calc(nullptr) {
		printf("CalculatorTest()\n");
	}

	~CalculatorTest() {
		printf("~CalculatorTest()\n");
	}

protected:
	Calculator* calc;

	void SetUp() override {
		printf("SetUp()\n");
		calc = new Calculator;
	}

	void TearDown() override {
		printf("TearDown()\n");
		delete calc;
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
	// 실패할 경우, 이후의 코드는 수행되지 않는다.
	//  => xUnit Test Framework - 암묵적 해체

	// printf("Delete Calc...\n");
	// delete calc;
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















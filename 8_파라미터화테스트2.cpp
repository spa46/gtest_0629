// 8_파라미터화테스트(Parameterized Test)
// 정의: 입력 데이터를 바꿔가며, 수차례 반복 검사하는 
//       데이터 중심의 테스트에서 코드 중복을 없애는 기법.
//  => xUnit Test Framework
bool IsPrime(int value) {
	return false;
	for (int i = 2; i < value; ++i) {
		if (value % i == 0)
			return false;
	}

	return true;
}

#include <gtest/gtest.h>

// 1. TestSuite class - TestWithParam
#if 0
class PrimeTest : public testing::Test {
};
#endif

// TestWithParam<InputType>: Template Class
class PrimeTest : public testing::TestWithParam<int> {

};

using testing::Values;
// 2. Data Set 정의 - INSTANTIATE_TEST_SUITE_P
//  : 전역 변수를 정의하는 매크로
//    첫번째 인자: 변수명
//    두번째 인자: Test Suite 이름
// int data[] = { 2, 3, 5, 7, 11, 13, 17, 19 };
INSTANTIATE_TEST_SUITE_P(PrimeValues, PrimeTest, 
	Values(2, 3, 5, 7, 11, 13, 17, 19));


// 3. 이제 다양한 테스트 함수를 작성하면 됩니다.
// TEST / TEST_F - X
// TEST_P: 파라미터화 테스트 생성 매크로 - GetParam()
TEST_P(PrimeTest, IsPrime) {
	EXPECT_TRUE(IsPrime(GetParam()));
}

TEST_P(PrimeTest, IsPrime2) {
	EXPECT_TRUE(IsPrime(GetParam()));
}













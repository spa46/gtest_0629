// 8_파라미터화테스트3 
#include <string>
#include <iostream>
#include <gtest/gtest.h>
using testing::Values;
using testing::ValuesIn;
using testing::Range;

// 데이터 셋을 정의하는 다양한 방법.
// 1. Values
// 2. ValuesIn
// 3. Range(begin, end, step)
// 4. 데이터를 함수를 통해 정의하고 싶다.

class StlStringTest : public testing::TestWithParam<std::string> {
};

std::vector<std::string> GetParameterStrings() {
	std::vector<std::string> v;
	v.push_back("a");
	v.push_back("abc");
	v.push_back("abcd");
	v.push_back("axx");
	v.push_back("ax");
	v.push_back("axc");
	return v;
}

INSTANTIATE_TEST_SUITE_P(CharSequence, StlStringTest, 
	ValuesIn(GetParameterStrings()));


TEST_P(StlStringTest, Foo) {
	std::cout << GetParam() << std::endl;
}

class SampleTest : public testing::TestWithParam<int> {
};


INSTANTIATE_TEST_SUITE_P(SampleValues, SampleTest,
	Range(1, 100, 10));
	// [1, 100) - 1 ~ 99

#if 0
int data[] = { 1, 2, 3, 4, 5 };
INSTANTIATE_TEST_SUITE_P(SampleValues, SampleTest, 
	ValuesIn(data));
#endif

#if 0
INSTANTIATE_TEST_SUITE_P(SampleValues, SampleTest, 
	Values(1, 2, 3, 4, 5));
#endif

TEST_P(SampleTest, Foo) {
	printf("%d\n", GetParam());
}

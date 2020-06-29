#include <gtest/gtest.h>

// 1. EXPECT
// ASSERT_
//    : EQ, TRUE, FALSE, NE, LT, LE, GT, GE
//    : 테스트가 실패하면, 이후의 코드는 수행되지 않는다.
//      단언문 이후에 단언문이 존재하면, '죽은 단언문'이 될 수 있다.
//    => 테스트 함수 안에 최소환의 단언문을 사용하자.
//      : 테스트의 개수가 늘어날 수 있다.
//
// EXPECT_
//   : EQ, TRUE, FALSE, NE, LT, LE, GT, GE
//   => 단언문이 실패하더라도, 이후의 코드는 계속 수행된다.
//      하지만, 하나라도 실패하면, 테스트의 결과는 실패이다.
TEST(GoogleTest, Sample1) {
	int expected1 = 42;
	int expected2 = 42;

	int actual1 = 42;
	int actual2 = 30;

	EXPECT_EQ(expected1, actual1);
	EXPECT_EQ(expected2, actual2); 
}

#include <string>

// 2. C-Style(const char*) 문자열 비교
//  : EXPECT_STREQ
TEST(GoogleTest, Sample2) {
	std::string s1 = "hello";
	std::string s2 = "hello";
	// EXPECT_EQ(s1, s2);  // ?

	const char* s3 = s1.c_str();
	const char* s4 = "Hello";

	EXPECT_STREQ(s3, s4);     // 대소문자 체크
	EXPECT_STRCASEEQ(s3, s4); // 대소문자 무시

	// EXPECT_EQ(s3, s4); - X
}

// 3. 부동 소수점(float, double)
//  : EXPECT_DOUBLE_EQ
//    EXPECT_NEAR: 오차 범위를 직접 설정하는 것이 가능합니다.
TEST(GoogleTest, Sample3) {
	double a = 0.7;
	double b = 0.1 * 7;

	EXPECT_DOUBLE_EQ(a, b); // 4ULP's(Unit in the last place)
	// EXPECT_NEAR(a, b, 0.00000000001);
	EXPECT_NEAR(a, b, 0);

	// EXPECT_EQ(a, b); // if (a == b) - X
}























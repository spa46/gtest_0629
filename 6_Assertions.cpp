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
TEST(DISABLED_GoogleTest, Sample1) {
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
	const char* s4 = "hello";

	EXPECT_STREQ(s3, s4);     // 대소문자 체크
	EXPECT_STRCASEEQ(s3, s4); // 대소문자 무시

	// EXPECT_EQ(s3, s4); - X
}

// 3. 부동 소수점(float, double)
//  : EXPECT_DOUBLE_EQ
//    EXPECT_NEAR: 오차 범위를 직접 설정하는 것이 가능합니다.
TEST(GoogleTest, DISABLED_Sample3) {
	double a = 0.7;
	double b = 0.1 * 7;

	EXPECT_DOUBLE_EQ(a, b); // 4ULP's(Unit in the last place)
	// EXPECT_NEAR(a, b, 0.00000000001);
	EXPECT_NEAR(a, b, 0);

	// EXPECT_EQ(a, b); // if (a == b) - X
}

void IsValidFilename(const std::string& filename) {
	// throw 1;
	if (filename.empty()) {
		throw std::invalid_argument("파일이름이 비어있음..");
	}
}

// 4. 예외 테스트
//  : IsValidFilename에 빈문자열을 전달하였을 때, invalid_argument 예외가
//    제대로 발생하는지 여부를 검증하고 싶다.
// - 아래의 코드는 xUnit Test Framework에서 예외검증을 제공하지 않을 때
// 사용하던 방법입니다.
//  : EXPECT_THROW / ASSERT_THROW
TEST(GoogleTest, Sample4_withExceptionTest) {
	std::string emptyFilename = "";

	EXPECT_THROW(IsValidFilename(emptyFilename), 
		std::invalid_argument) << "빈 문자열을 전달하였을 때"; 
	
}


TEST(GoogleTest, Sample4) {
	std::string emptyFilename = "";
	
	try {
		IsValidFilename(emptyFilename);
		FAIL() << "예외가 발생하지 않았음...";
	} catch (std::invalid_argument&) {
		SUCCEED();
	} catch (...) {
		FAIL() << "다른 종류의 예외가 발생하였음...";
	}
}


// 5. 테스트 비활성화
//  => Google Test는 TestSuite 또는 Test의 이름이
//     DISABLED_ 시작하면, 비활성화됩니다.
//  왜 필요한가?
//    : 테스트를 주석 처리하면, 잊혀진다.
//      아무도 테스트가 존재했다는 사실을 알 수 없다.
//      유지 보수가 필요한 테스트에 대해서는 비활성화기능을 통해
//      처리하는 것이 좋다.
//   주의할 점
//     : TEST_F에서 TestSuite 이름을 변경할 때는 전체 변경해야 한다.
//   $ ./a.out --gtest_also_run_disabled_test
//     : 비활성화된 테스트도 같이 수행할 수 있다.

class DISABLED_FooTest : public testing::Test {
};

TEST_F(DISABLED_FooTest, foo) {
	// 1. 작성 중인 테스트는 반드시 실패해야 한다.
	FAIL() << "작성중입니다...";
}
































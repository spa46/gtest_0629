
// 1. 헤더 파일을 반드시 포함해야 합니다.
#include <gtest/gtest.h>

// 2. 다양한 테스트를 작성하면 됩니다.
// TEST(TestSuiteName, TestName) 
TEST(FooTest, foo) {

}

TEST(FooTest, goo) {

}




// 2. main 함수
//  : 아래의 main 함수의 내용은 변하지 않습니다.
//  => gtest 라이브러리에 main을 포함하면, 편리하게 사용할 수 있습니다.
#if 0
int main(int argc, char** argv) {
	// 2-1 라이브러리 초기화
	testing::InitGoogleTest(&argc, argv);

	// 2-2 테스트 실행
	return RUN_ALL_TESTS();
}
#endif


// 1. 헤더 파일을 반드시 포함해야 합니다.
#include <gtest/gtest.h>

// 2. main 함수
int main(int argc, char** argv) {
	// 2-1 라이브러리 초기화
	testing::InitGoogleTest(&argc, argv);

	// 2-2 테스트 실행
	return RUN_ALL_TESTS();
}

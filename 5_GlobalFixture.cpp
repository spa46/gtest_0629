#include <gtest/gtest.h>

TEST(FooTest, foo) {

}

TEST(FooTest, goo) {

}


// Global Fixture 
//  - Google Test의 기능입니다.
//  - 프로그램이 시작할 때 수행되는 SetUp()
//    프로그램이 종료하기 전에 수행되는 TearDown()을 정의합니다.
//
class MyTestEnvironment : public testing::Environment {
public:
	void SetUp() override {
		printf("라이브러리 초기화...\n");
	}

	void TearDown() override {
		printf("라이브러리 정리...\n");
	}
};

// [설치 방법]
// 1) main을 직접 정의하지 않을 경우 - 전역 변수
#if 0
testing::Environment* my_env 
	= testing::AddGlobalTestEnvironment(new MyTestEnvironment);
#endif

// 2) main을 직접 정의할 경우 - main() - 권장됩니다.
int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	
	testing::AddGlobalTestEnvironment(new MyTestEnvironment);
	
	return RUN_ALL_TESTS();
}











#include <gtest/gtest.h>


// Global Fixture 
//  - Google Test의 기능입니다.(xUnit Test Pattern X)
//  - 프로그램이 시작할 때 수행되는 SetUp()
//    프로그램이 종료하기 전에 수행되는 TearDown()을 정의합니다.
//
// 주의할 점: MyTestEnvironment를 AddGlobalTestEnvironment 함수를 통해 등록할 때
//  반드시 힙에 생성해야 한다.
class MyTestEnvironment : public testing::Environment {
private:
	MyTestEnvironment() {}
public:
	static MyTestEnvironment& Instance() {
		static MyTestEnvironment* instance = new MyTestEnvironment;
		return *instance;
	}

	// 프로그램 내에 공유되는 테스트 유틸리티 함수
	void foo() { printf("foo\n"); }

	void SetUp() override {
		printf("라이브러리 초기화...\n");
	}

	void TearDown() override {
		printf("라이브러리 정리...\n");
	}
};

TEST(FooTest, foo) {

}

TEST(FooTest, goo) {
	// MyTestEnvironment.foo를 호출하고 싶다.
	MyTestEnvironment::Instance().foo();
}


// [설치 방법]
// 1) main을 직접 정의하지 않을 경우 - 전역 변수
#if 0
testing::Environment* my_env 
	= testing::AddGlobalTestEnvironment(new MyTestEnvironment);
#endif

// 2) main을 직접 정의할 경우 - main() - 권장됩니다.
int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	
	// testing::AddGlobalTestEnvironment(new MyTestEnvironment);
	testing::AddGlobalTestEnvironment(&MyTestEnvironment::Instance());
	
	return RUN_ALL_TESTS();
}











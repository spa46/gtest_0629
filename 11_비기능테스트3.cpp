// 메모리 누수 테스트
#include <gtest/gtest.h>

// 1. new / delete 재정의가 필요하다.
// 2. 테스트에서만 이용 가능하도록 해야 합니다. 
//   => 조건부 컴파일 이용하면 가능합니다.
//   g++ 11_비기능테스트3.cpp -I. -lgtest -L. -pthread -DGTEST_LEAK_TEST

class Image {
public:
	Image() { printf("Image()\n"); }
	~Image() { printf("~Image()\n"); }

#ifdef GTEST_LEAK_TEST
	static int allocCount;

	void* operator new(size_t size) {
		allocCount++;
		return malloc(size);
	}

	void operator delete(void* p, size_t) {
		allocCount--;
		free(p);
	}
#endif
};

#ifdef GTEST_LEAK_TEST
int Image::allocCount = 0;
#endif

void foo() {
	Image* p1 = new Image;
	Image* p2 = new Image;
	Image* p3 = new Image;

	delete p1;
	delete p2;
}

class FooTest : public testing::Test {
	int currentAlloc;
protected:
	void SetUp() override {
#ifdef GTEST_LEAK_TEST
		currentAlloc = Image::allocCount;
#endif
	}

	void TearDown() override {
#ifdef GTEST_LEAK_TEST
		int diff = Image::allocCount - currentAlloc;
		EXPECT_EQ(0, diff) << diff << " object(s) leaks";
#endif
	}
};

TEST_F(FooTest, foo) {
	foo();
}

















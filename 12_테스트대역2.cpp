// 12_테스트대역.cpp
#include <string>

// 테스트 대역을 적용할 수 있는 제품 코드의 설계가 필요합니다. 
//  : 테스트 대역은 무조건 적용이 불가능하다.

// * 테스트 대역을 적용할 수 있는 설계
//  : 의존하는 객체에 대해서 강한 결합이 아닌 약한 결합을 사용해야 합니다. 
//  '강한 결합': 의존 객체의 구체적인 타입에 의존하는 것
//  '약한 결합': 의존 객체를 이용할 때, 구체적인 타입이 아닌 인터페이스나
//               추상 클래스 타입에 의존하는 것
//           1) 인터페이스 / 추상 클래스
//           2) 직접 생성하면 안된다.
//              외부에서 생성해서 전달받아야 한다. - DI(Dependency Injection)
//           3) 의존성 주입 방법
//             - 생성자 주입: 의존객체가 필수적일때
//             - 메소드 주입: 의존객체가 필수적이지 않을때 
//
//           * 의존성 주입 문제점
//             : 보일러플레이트가 발생한다.`
//              => 의존성 주입 프레임워크를 사용하면 없앨 수 있다.
//
//             A - B, C, D
//             B* b = new B;
//             C* c = new C;
//             D* d = new D;
//             A* a = new A(b, c, d);


struct IFileSystem {
	virtual ~IFileSystem() {}

	virtual bool IsValid(const std::string& filename) = 0;
};

class FileSystem : public IFileSystem {
public:
	bool IsValid(const std::string& filename) override {
		// ....
		return false;
	}
};

class Logger {
public:
	// Logger 클래스가 테스트 대역을 적용할 수 있는 설계로 변경하는 작업
	//  => 틈새 만들기
	//  =>  : 기존 클래스의 사용법과 동일하게 만드는 것이 좋다.
	Logger(IFileSystem* p = nullptr) : fs(p) {
		if (fs == nullptr) {
			fs = new FileSystem;
		}
	}

	bool IsValidLogFilename(const std::string& filename) {
		//-----------------
		size_t index = filename.find_last_of(".");
		std::string name = filename.substr(0, index);

		if (name.size() < 5) {
			return false;
		}
		//-----------------
		// IFileSystem* fs = new FileSystem;
		return fs->IsValid(filename);
	}
private:
	IFileSystem* fs;
};

//------------------------------------------------
#include <gtest/gtest.h>

class TestDouble : public IFileSystem {
public:
	bool IsValid(const std::string& filename) override {
		return true;
	}
};

class LoggerTest : public testing::Test {
};

TEST_F(LoggerTest, IsValidLogFilename_NameLoggerThan5Chars_ReturnsTrue) {
	TestDouble stub;
	Logger logger(&stub);
	std::string validFilename = "valid.log";

	EXPECT_TRUE(logger.IsValidLogFilename(validFilename))
		<< "파일명이 다섯글자 이상일 때";
}

TEST_F(LoggerTest, IsValidLogFilename_NameShorteThan5Chars_ReturnsFalse) {
	TestDouble stub;
	Logger logger(&stub);
	std::string wrongFilename = "bad.log";

	bool actual = logger.IsValidLogFilename(wrongFilename);

	EXPECT_FALSE(actual) << "파일명이 다섯글자 미만일 때";
}

// * 테스트 대역 종류 4가지
// 1. Test Stub
// 2. Fake Object
// 3. Test Spy
// 4. Mock Object

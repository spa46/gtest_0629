#include <string>
#include <vector>

enum Level {
	INFO, WARN, ERROR
};

struct DLoggerTarget {
	virtual ~DLoggerTarget() {}

	virtual void Write(Level level, const std::string& message) = 0;
};

class DLogger {
	std::vector<DLoggerTarget*> targets;
public:
	void AddTarget(DLoggerTarget* p) {
		targets.push_back(p);
	}
	
	void Write(Level level, const std::string& message) {
		for (DLoggerTarget* p : targets) {
			//  p->Write(level, message);
		}
	}
};

//-----------------------------------
// 1. Gmock Header include
#include <gmock/gmock.h>

// 2. Mocking - 모의객체를 선언하는 작업
//   Google Mock - Macro를 통해 제공
// MOCK_METHOD{N}(함수의 이름, 함수의 시그니처) - 1.10 이전 버전까지
// MOCK_METHOD(함수의 반환타입, 이름, 인자, 한정자) - 1.10 이후의 매크로

class MockDLoggerTarget : public DLoggerTarget {
public:
	MOCK_METHOD(void, Write, (Level level, const std::string& message));
};

// 3. 이제 테스트를 작성하면 됩니다. 
TEST(DLoggerTest, WriteTest) {
	// Arrange
	DLogger logger;
	MockDLoggerTarget mock1, mock2;
	logger.AddTarget(&mock1);
	logger.AddTarget(&mock2);
	Level test_level = INFO;
	std::string test_message = "test_message";
	
	// EXPECT_CALL의 구문은 Act 이전에 작성되어야 합니다.
	// Assert
	EXPECT_CALL(mock1, Write(test_level, test_message));
	EXPECT_CALL(mock2, Write(test_level, test_message));

	// Act
	logger.Write(test_level, test_message);
}


#if 0
struct DLoggerTarget {
	virtual void Write(Level level, const std::string& message) = 0;
};

이제는 더 이상 사용하지 않습니다.
$ ./gmock_gen.py ~/chansik.yun/DLoggerTarget.h
class MockDLoggerTarget : public DLoggerTarget {
 public:
  MOCK_METHOD2(Write,
      void(Level level, const std::string& message));
  MOCK_METHOD3(Go,
      void(int a, double b, char c));
};
#endif

#if 0
struct DLoggerTarget {
	virtual ~DLoggerTarget() {}

	virtual void Write(Level level, const std::string& message) = 0;
	virtual void Go(int a, double b, char c) = 0;
};
#endif



// Mock Object Pattern
//  의도: 함수를 호출하였을 때, 발생하는 부수효과를 관찰할 수 없어서,
//        테스트 안된 요구사항이 있을 때
//  방법: '상태 기반 검증'이 아닌 '행위 기반 검증'을 수행한다.       
//      상태 검증: 객체에 작용을 가한 후, 단언 함수 등을 통해서 내부의 상태값
//                을 확인하는 테스트 방법.
//      동작 검증: 객체에 작용을 사한 후, 내부적으로 발생하는 함수의 호출 여부
//                 호출 횟수, 순서 등을 검증 작업에 사용하는 방법.
//
//  Mock Object(모의 객체): 내부적으로 발생하는 호출에 관련된 정보를 
//                          기록하는 객체
//  모의 객체를 생성해주는 프레임워크(라이브러리) 
//     => C++  - Google Mock
//              : 1.8부터 Google Test에 기본적으로 포함되었습니다.
//        Java - jMock, EasyMock, 'Mockito', Spock ...

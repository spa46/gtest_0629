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
		// p->Write(level, message);
		}
	}
};

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

#include <gtest/gtest.h>








// 15_Test Spy
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
			p->Write(level, message);
		}
	}
};

// Test Spy Pattern
//  의도: 함수를 호출하였을 때, 발생하는 부수효과를 관찰할 수 없어서,
//        테스트 안된 요구사항이 있을 때
//  방법: 목격한 일을 기록해두었다가, 나중에 테스트에서 확인할 수 있도록
//        만들어진 테스트 대역
//        "다른 컴포턴트로부터의 간접 출력을 저장해두었다가 검증한다."
















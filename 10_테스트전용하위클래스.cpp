// 10_테스트전용하위클래스
// SUT
#include <stdio.h>

// 한계: 테스트 전용 하위 클래스를 적용하기 위해서는,
//       Engine의 클래스가 상속이 가능한 형태로 설계되어야 한다. 
//         1) 가상 소멸자
//         2) 훅 하고자 하는 메소드가 virtual 이어야 한다. 
class Engine {
public:
	Engine() { printf("Engine()\n"); }
	virtual ~Engine() {}

	virtual void Start() {
		printf("Engine start...\n");
	}
};

class Car {
	Engine* engine;
public:
	Car(Engine* p) : engine(p) {}

	void Go() {
		// ....
		engine->Start();
	}
};
//---------------
#include <gtest/gtest.h>
// Gmock을 적용해봅시다.

// 테스트 전용 하위 클래스 패턴
//  : 테스트 하고자 하는 클래스가 테스트를 위한 기능을 제공하고 있지 않다면,
//    테스트 코드 안에서 자식 클래스를 통해 해당 기능을 제공하면 된다.
class TestEngine : public Engine {
	bool isStart;
public:
	TestEngine() : isStart(false) {}

	void Start() override {
		Engine::Start();
		isStart = true;
	}

	bool IsStart() const { return isStart; }
};

TEST(CarTest, GoTest_TestEngine) {
	TestEngine engine;
	Car car(&engine);

	car.Go();

	EXPECT_TRUE(engine.IsStart()) << "자동차가 Go 했을 때";
}

// Car의 Go가 호출되었을 때, Engine 객체에 대해서 Start가 호출되었는지 여부를
// 검증하고 싶다.
TEST(CarTest, GoTest) {
	Engine engine;
	Car car(&engine);

	car.Go();

	// !!!
}


// 단위 테스트의 품질 - Effecive Unit Testing
// 1. 가독성
// 2. 유지보수성
// 3. 신뢰성 

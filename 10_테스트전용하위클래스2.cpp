#include <stdio.h>

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
#include <gmock/gmock.h>

class MockEngine : public Engine {
public:
	MOCK_METHOD(void, Start, (), (override));
};

TEST(CarTest, GoTest_TestEngine) {
	MockEngine engine;
	Car car(&engine);

	EXPECT_CALL(engine, Start());

	car.Go();
}






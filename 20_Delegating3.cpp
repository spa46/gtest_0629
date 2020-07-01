
#include <gmock/gmock.h>

struct Calc {
	virtual ~Calc() {}

	virtual int Add(int a, int b) = 0;
	virtual int Sub(int a, int b) = 0;
};


class FakeCalc : public Calc {
public:
	virtual int Add(int a, int b) override {
		printf("FakeCalc::Add\n");
		return a + b;
	}

	virtual int Sub(int a, int b) override {
		printf("FakeCalc::Sub\n");
		return a - b;
	}
};

void DoCalc(Calc* p) {
	printf("Add: %d\n", p->Add(10, 20));
	printf("Sub: %d\n", p->Sub(10, 20));
}
//--------------------------------

class MockCalc : public Calc {
public:
	MOCK_METHOD(int, Add, (int a, int b), (override));
	MOCK_METHOD(int, Sub, (int a, int b), (override));

	// Add, Sub에 대한 호출이 Fake를 통해 처리되도록 ON_CALL 사용합니다.
	void DelegateToFake() {
		ON_CALL(*this, Add).WillByDefault([this](int a, int b) {
			return fake.Add(a, b);
		});

		ON_CALL(*this, Sub).WillByDefault([this](int a, int b) {
			return fake.Sub(a, b);
		});
	}

private:
	FakeCalc fake;
};

// Mock에 대한 메소드 호출이 가짜 객체를 통해 처리하고 싶다.

TEST(CalcTest, DoCalcTest) {
	// FakeCalc calc;
	MockCalc calc;
	calc.DelegateToFake();
	
	EXPECT_CALL(calc, Add(10, 20)); 
	EXPECT_CALL(calc, Sub(10, 20));
	DoCalc(&calc);
}










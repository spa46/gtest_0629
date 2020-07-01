#include <gmock/gmock.h>


// 1.10 이전
//  - MOCK_METHOD0(Play, void());
//  - MOCK_METHOD1(Stop, void(int n));
//  - MOCK_CONST_METHOD0(GetName, std::string());
// 1.10 이후
//  - MOCK_METHOD(반환타입, 메소드이름, 인자정보, 한정자)

// Mocking
//  - MOCK_METHOD
//     : 매크로를 통해서 실제 함수의 호출등의 정보를 기록하는
//       구현부를 생성하는 작업
//  MOCK_METHOD(반환타입, 메소드이름, 인자정보, 한정자)
//   - 한정자
//   1) override(옵션) - virtual 함수에서 대해서 지정하는 한정자.
//   2) const(필수) - const 함수에 대해서 지정하는 한정자.
//   3) noexcept(필수) - noexcept 함수에 대해서 지정하는 한정자.
//   4) CallType(필수) - STDMETHODCALL(Windows)

struct MP3 {
	virtual ~MP3() {}

	virtual void Play() = 0;
	virtual void Stop(int n) = 0;
	
	virtual std::string GetName() const = 0;
	virtual void Foo() noexcept = 0;

	virtual std::pair<bool, int> GetPair() const = 0;
	virtual bool CheckMap(std::map<int, double> a, bool b) = 0;
};

class MockMP3 : public MP3 {
public:
	// 주의: 한정자를 전달할 때, 괄호로 감싸야 한다.
	MOCK_METHOD(void, Play, (), (override));
	MOCK_METHOD(void, Stop, (int n), (override));

	MOCK_METHOD(std::string, GetName, (), (override, const));
	MOCK_METHOD(void, Foo, (), (override, noexcept));

#if 1
	using BoolAndInt = std::pair<bool, int>;
	MOCK_METHOD(BoolAndInt, GetPair, (), (override, const));

	using MapIntDouble = std::map<int, double>;
	MOCK_METHOD(bool, CheckMap, (MapIntDouble a, bool b), (override));
#endif

#if 0
	// 주의할점
	//  - 반환 타입이 템플릿인 경우, 쉼표가 존재하면, 괄호로 한번더
	//    감싸주어야 한다. 
	MOCK_METHOD((std::pair<bool, int>), GetPair, (), (override, const));

	// - 인자에서 템플릿이 존재하는 경우, 쉼표가 존재하면 괄호로 한번더
	//   감싸주어야 한다.
	MOCK_METHOD(bool, CheckMap, ((std::map<int, double> a), bool b), (override));
#endif
};

TEST(MockTest, Foo) {
	MockMP3 mock; 
}













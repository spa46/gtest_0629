#include <gmock/gmock.h>

// Mocking
//  - MOCK_METHOD
//     : 매크로를 통해서 실제 함수의 호출등의 정보를 기록하는
//       구현부를 생성하는 작업
//  MOCK_METHOD(반환타입, 메소드이름, 인자정보, 한정자)
//   - 한정자
//   1) override - virtual 함수에서 대해서 지정하는 한정자.
//   2) const(필수) - const 함수에 대해서 지정하는 한정자.
//   3) noexcept(필수) - noexcept 함수에 대해서 지정하는 한정자.
//   4) CallType(필수) - STDMETHODCALL(Windows)

struct MP3 {
	virtual ~MP3() {}

	virtual void Play() = 0;
	virtual void Stop(int n) = 0;
	
	virtual std::string GetName() const = 0;
	virtual void Foo() noexcept = 0;

#if 0
	virtual std::pair<bool, int> GetPair() const = 0;
	virtual bool CheckMap(std::map<int, double> a, bool b) = 0;
#endif
};

class MockMP3 : public MP3 {
public:
	MOCK_METHOD(void, Play, (), (override));
	MOCK_METHOD(void, Stop, (int n), (override));

	MOCK_METHOD(std::string, GetName, (), (override, const));
	MOCK_METHOD(void, Foo, (), (override, noexcept));
};

TEST(MockTest, Foo) {
	MockMP3 mock; 

}













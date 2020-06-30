#include <gtest/gtest.h>

// #define private public
// #define class struct
//  - pImpl Idiom 설계를 적용한 경우, 위의 코드는 제대로 동작하지 않습니다.
class User {
public:
	User() : age(42) {}

	FRIEND_TEST(UserTest, AgeTest); // !!
private:
	int GetAge() const { return age; }

	int age;
};

// private 메소드(멤버함수)
//  : 정보 은닉 - 외부에서 호출하면 안돼는 함수
// 테스트 진영
//  : public 메소드의 가독성을 높이기 위해 사용되어야 한다.
//    만약 private 메소드가 public 메소드를 통해 호출되지 않는다면,
//    잘못 설계된 것이다.
//      "로버트 C  마틴 - 클린 코드"
//      "테스트 되지 않은 private 메소드 보다 테스트 된 public메소드가
//       안전하다."
//

// FRIEND_TEST
//  : 테스트 안에서 SUT의 private 필드 또는 메소드에 접근해야 하는 경우
//    FRIEND_TEST로 지정하면 됩니다.
//   문제점: 제품코드에서 gtest 에 의존성이 들어간다.

TEST(UserTest, AgeTest) {
	User user;

	ASSERT_EQ(42, user.age);
}





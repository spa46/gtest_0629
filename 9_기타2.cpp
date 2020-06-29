
class User {
protected:
	void SetAge(int a) { age = a; }
	int GetAge() const { return age; }
private:
	int age;
};
//-------------------------- // User.h


#include <gtest/gtest.h>
// Test 전용 하위 클래스
class TestUser : public User {
public:
	using User::SetAge;
	using User::GetAge;
	// 위의 코드는 부모의 protected를 public으로 변경해서 사용하는 
	// 문법입니다. 
};


TEST(UserTest, AgeTest)  {
	TestUser user;
	user.SetAge(42);

	EXPECT_EQ(user.GetAge(), 42);
}








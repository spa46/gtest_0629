// 14_Fake Object

#include <string>

class User {
	std::string name;
	int age;
public:
	User(const std::string& n, int a) : name(n), age(a) {}

	std::string GetName() const {
		return name;
	}

	int GetAge() const {
		return age;
	}
};

struct IDatabase {
	virtual ~IDatabase() {}

	virtual void SaveUser(const std::string& name, User* user) = 0;
	virtual User* LoadUser(const std::string& name) = 0;
};

// User 객체를 Database에 저장하고, 불러오는 역활을 담당
class UserManager {
	IDatabase* database;
public:
	UserManager(IDatabase* p) : database(p) {}

	void Save(User* u) {
		// ...
		database->SaveUser(u->GetName(), u);
	}

	User* Load(const std::string& name) {
		// ...
		return database->LoadUser(name);
	}
};

//-------------------------------
#include <gtest/gtest.h>
#include <map>

// 문제: 아직 Database 구현체가 준비되지 않았다.
// => Fake Object Pattern
// 의도: '아직 준비되지 않은 의존 객체'로 인해서, 테스트 안된 요구사항이 있다.
// 방법: 동일한 기능을 제공하는 '가벼운 테스트 대역'을 만들어서,
//       문제를 해결하자.
// [활용]
// 1) 아직 준비되지 않은 객체
// 2) 사용하기 어려울 때
// 3) 의존 객체가 너무 느려서, 느린 테스트의 문제가 발생할 때
//
// [문제점]
// : 제품 코드와 상관없는 코드.
//  - Docker
class FakeDatabase : public IDatabase {
	std::map<std::string, User*> data;
public:
	void SaveUser(const std::string& name, User* user) override {
		data[name] = user;
	}

	User* LoadUser(const std::string& name) override {
		return data[name];
	}
};

// EXPECT_EQ(==), NE(!=), LT(<), GT(>), LE(<=), GE(<=)
//  : 연산자 오버로딩 함수
bool operator==(const User& lhs, const User& rhs) {
	return lhs.GetName() == rhs.GetName() &&
		lhs.GetAge() == rhs.GetAge();
}

bool operator!=(const User& lhs, const User& rhs) {
	return !(lhs == rhs);
}

// 객체를 문자열의 형태로 표현할 때 사용하는 함수
std::ostream& operator<<(std::ostream& os, const User& user) {
	return os << "User(name=" << user.GetName() << ", age=" 
		<< user.GetAge() << ")";
}

class UserManagerTest : public ::testing::Test {
};

TEST_F(UserManagerTest, SaveLoadTest) {
	FakeDatabase fake;
	UserManager manager(&fake);
	std::string testName = "test_name";
	int testAge = 42;
	User expected(testName, testAge);

	manager.Save(&expected);
	User* actual = manager.Load(testName);

	EXPECT_EQ(*actual, expected) << "Load 하였을 때";
	// 사용자 정의 객체를 대상으로 단언 함수를 사용할 경우,
	// '연산자 오버로딩'이 필요합니다.
}













































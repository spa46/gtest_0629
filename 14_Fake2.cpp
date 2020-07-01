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
#include <gmock/gmock.h>
#include <map>

class FakeDatabase : public IDatabase {
	std::map<std::string, User*> data;
public:
	MOCK_METHOD(void, SaveUser, (const std::string& name, User* user), (override));
	MOCK_METHOD(User*, LoadUser, (const std::string& name), (override));

	void DelegateToFake() {
		ON_CALL(*this, SaveUser)
			.WillByDefault([this](const std::string& name, User* user) {
				SaveUserImpl(name, user);
			});

		ON_CALL(*this, LoadUser)
			.WillByDefault([this](const std::string& name) {
				return LoadUserImpl(name);
			});
	}

	void SaveUserImpl(const std::string& name, User* user) {
		data[name] = user;
	}

	User* LoadUserImpl(const std::string& name) {
		return data[name];
	}
};

bool operator==(const User& lhs, const User& rhs) {
	return lhs.GetName() == rhs.GetName() &&
		lhs.GetAge() == rhs.GetAge();
}

bool operator!=(const User& lhs, const User& rhs) {
	return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const User& user) {
	return os << "User(name=" << user.GetName() << ", age=" 
		<< user.GetAge() << ")";
}

class UserManagerTest : public ::testing::Test {
};

using testing::NiceMock;
TEST_F(UserManagerTest, SaveLoadTest) {
	NiceMock<FakeDatabase> fake;
	fake.DelegateToFake();
	UserManager manager(&fake);
	std::string testName = "test_name";
	int testAge = 42;
	User expected(testName, testAge);

	manager.Save(&expected);
	User* actual = manager.Load(testName);

	EXPECT_EQ(*actual, expected) << "Load 하였을 때";
}

TEST_F(UserManagerTest, SaveLoadTest2) {
	NiceMock<FakeDatabase> fake;
	fake.DelegateToFake();
	UserManager manager(&fake);
	std::string testName = "test_name";
	int testAge = 42;
	User expected(testName, testAge);

	EXPECT_CALL(fake, SaveUser(testName, &expected));

	manager.Save(&expected);
}















































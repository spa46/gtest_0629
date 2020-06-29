#include <string>
#include <unistd.h>

// 가정:
//   Connect() / Disconnect() 느리다.
//   => 픽스쳐 설치와 해체로 인해서 테스트를 추가할 때 마다 시간이 오래 걸린다.

//   => 느린 테스트(Slow Test)
//    : 테스트를 수행하는 개발자의 생산성을 떨어뜨린다.
//      테스트가 느려서 개발자들이 코드가 변경되어도, 테스트를 수행하지 않는다.
//   "픽스쳐의 설치와 해체로 인해 발생된 느린 테스트"
//    =>  Suite Fixture SetUp / TearDown 
//    => 문제점: "공유 픽스쳐 전략" - xUnit Test Framework
//      -> 이제는 Test Suite안의 모든 테스트는 독립적이지 않다.
//       : 이로 인해서, "변덕스러운 테스트"의 문제가 발생할 위험이 있습니다
//       - 공유 픽스쳐의 상태에 따라 테스트의 결과가 변경될 수 있습니다.
//
//  SuiteFixture Setup
//  DatabaseTest* ts = new DatabaseTest;
//  ts->SetUp();
//  ts->LoginTest();
//  ts->TearDown();
//  delete ts;
//
//  DatabaseTest* ts = new DatabaseTest;
//  ts->SetUp();
//  ts->LogoutTest();
//  ts->TearDown();
//  delete ts;
//  ...
//  SuiteFixture TearDown

class Database {
public:
	void Connect() { 
		sleep(2);
	}

	void Disconnect() {
		sleep(1);
	}

	void Login(const std::string& id, const std::string& password) {}
	void Logout() {}

	bool IsLogin() { return true; }
};

//-----------------------------------
#if 1
// 공유 픽스쳐 전략
#include <gtest/gtest.h>

class DatabaseTest : public testing::Test {
protected:
	static Database* database;

	static void SetUpTestSuite() {
		printf("SetUpTestSuite()\n");
		database = new Database;
		database->Connect();
	}

	static void TearDownTestSuite() {
		printf("TearDownTestSuite()\n");
		delete database;
	}

	void SetUp() override {
		printf("SetUp()\n");
	}

	void TearDown() override {
		printf("TearDown()\n");
	}
};

Database* DatabaseTest::database = nullptr;


namespace {
	std::string test_id = "test_id";
	std::string test_password = "test_password";
};

TEST_F(DatabaseTest, LoginTest) {
	database->Login(test_id, test_password);

	ASSERT_TRUE(database->IsLogin()) 
		<< "데이터베이스에 로그인하였을 때";
}

TEST_F(DatabaseTest, LogoutTest) {
	database->Login(test_id, test_password);
	database->Logout();

	ASSERT_FALSE(database->IsLogin()) 
		<< "데이터베이스에 로그아웃하였을 때";
}

TEST_F(DatabaseTest, foo) {
}
TEST_F(DatabaseTest, goo) {
}
#endif
#if 0
// 신선한 픽스쳐 전략
#include <gtest/gtest.h>

class DatabaseTest : public testing::Test {
protected:
	Database* database;

	DatabaseTest() : database(nullptr) {}

	// 1.10 버전 이전
	// void SetUpTestCase() {}
	
	static void SetUpTestSuite() {
		printf("SetUpTestSuite()\n");
	}

	static void TearDownTestSuite() {
		printf("TearDownTestSuite()\n");
	}

	void SetUp() override {
		printf("SetUp()\n");
		database = new Database;
		database->Connect();
	}

	void TearDown() override {
		printf("TearDown()\n");
		delete database;
	}
};

namespace {
	std::string test_id = "test_id";
	std::string test_password = "test_password";
};

TEST_F(DatabaseTest, LoginTest) {
	database->Login(test_id, test_password);

	ASSERT_TRUE(database->IsLogin()) 
		<< "데이터베이스에 로그인하였을 때";
}

TEST_F(DatabaseTest, LogoutTest) {
	database->Login(test_id, test_password);
	database->Logout();

	ASSERT_FALSE(database->IsLogin()) 
		<< "데이터베이스에 로그아웃하였을 때";
}

TEST_F(DatabaseTest, foo) {
}
TEST_F(DatabaseTest, goo) {
}
#endif

#if 0
	TEST(DatabaseTest, LoginTest) {
		Database* database = new Database;
		database->Connect();
		std::string test_id = "test_id";
		std::string test_password = "test_password";

		database->Login(test_id, test_password);

		// ASSERT_EQ(true, database->IsLogin());
		ASSERT_TRUE(database->IsLogin()) << "데이터베이스에 로그인하였을 때";
	}

	TEST(DatabaseTest, LogoutTest) {
		Database* database = new Database;
		database->Connect();
		std::string test_id = "test_id";
		std::string test_password = "test_password";

		database->Login(test_id, test_password);
		database->Logout();

		ASSERT_FALSE(database->IsLogin()) << "데이터베이스에 로그아웃하였을 때";
	}
#endif













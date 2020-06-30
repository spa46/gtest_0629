// Test Stub Pattern
//  의도: '다른 컴포넌트로부터의 간접 입력'에 의존하는 로직을 독립적으로 검증하고 싶다.
//  방법: 실제 의존하는 객체를 테스트용 객체로 교체해서, SUT가 테스트하는데 필요한 결과를 보내도록 제어한다.
//  => 특수한 상황을 시뮬레이션하고 싶다.
//  => 네트워크 오류, 시간 등의 제어가 불가능한 환경을 제어하기 위해 사용한다.

#include <iostream>

class NetworkException : public std::exception {
public:
	const char* waht() {
		return "Bad Network State";
	}
};

// 인터페이스 문제점
//  : 약한 결합을 형성하지만, 새로운 기능을 추가하기 어렵다.
struct IConnection {
	virtual ~IConnection() {}

	virtual void Move(int x, int y) = 0;
	virtual void Attack() = 0;

	// 기본 구현을 제공하는 함수
	virtual void Foo() {
	}
};

class TCPConnection : public IConnection {
public:
	void Move(int x, int y) override {
	}

	void Attack() override {
	}
};

class Player {
	IConnection* conn;
public:
	Player(IConnection* p) : conn(p) {}

	void Move(int x, int y) {
		try {
			conn->Move(x, y);
		} catch (NetworkException& e) {
			printf("Network 예외에 관한 로직...\n");
			throw e;
		}
	}
};

#include <gtest/gtest.h>

// Stub - 테스트에서 원하는 결과를 주는 협력 객체
// 1. 테스트 대역 규칙 - 협력 객체의 인터페이스를 구현한다.
//  : 협력 객체의 인터페이스가 복잡할 경우, 테스트 대역을 만드는 
//    부담도 커진다.
//     - 인터페이스가 간단할 수록 좋다.
//       : ISP(Interface Segregation Principle)
class StubConnection : public IConnection {
public:
	void Move(int x, int y) override {
		throw NetworkException();
	}

	void Attack() override {
		throw NetworkException();
	}
};

TEST(PlayerTest, MoveTest_Stub) {
	StubConnection conn;
	Player player(&conn);

	EXPECT_THROW(conn.Move(10, 20), NetworkException);
}


// 네트워크 연결이 오류가 발생했을 때, NetworkException이 제대로 전달되어서, 
// 전파되는지 여부를 검증하고 싶다.
TEST(PlayerTest, MoveTest) {
	TCPConnection conn;
	Player player(&conn);

	EXPECT_THROW(conn.Move(10, 20), NetworkException);
}


























#include <gtest/gtest.h>










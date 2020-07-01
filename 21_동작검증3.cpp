#include <gmock/gmock.h>

struct Foo {
	virtual ~Foo() {}

	virtual void First() = 0;
	virtual void Second() = 0;
	virtual void Third() = 0;
	virtual void Forth() = 0;
};


class MockFoo : public Foo {
public:
	MOCK_METHOD(void, First, (), (override));
	MOCK_METHOD(void, Second, (), (override));
	MOCK_METHOD(void, Third, (), (override));
	MOCK_METHOD(void, Forth, (), (override));
};


void Do(Foo* p) {
	p->First();
	p->Second();
	p->Third();
	p->Forth();
}

void Do2(Foo* p) {
	p->First();
	p->Second();
	p->Third();
	p->Forth();
}

// 행위 검증에서 기본적으로 순서는 검증에 포함되지 않는다.
// 호출 순서에 대한 검증이 필요하다면,
// InSequence 를 이용하면 됩니다.
//
// Google Mock의 Mock객체 또는 Sequence 객체는 파괴되는 시점에 평가가 진행된다.

using testing::Sequence;
TEST(FooTest, SequenceTest3) {
	MockFoo* mock = new MockFoo;
	Sequence s1, s2;
	
	EXPECT_CALL(*mock, First()).InSequence(s1, s2);
	EXPECT_CALL(*mock, Second()).InSequence(s1);
	EXPECT_CALL(*mock, Forth()).InSequence(s2);
	EXPECT_CALL(*mock, Third()).InSequence(s2);

	Do2(mock);
	delete mock; // !!
}

//       - Second
//       |
// First -
//       |
//       - Third - Forth
TEST(FooTest, SequenceTest2) {
	MockFoo mock;
	Sequence s1, s2;
	
	EXPECT_CALL(mock, First()).InSequence(s1, s2);
	EXPECT_CALL(mock, Second()).InSequence(s1);
	EXPECT_CALL(mock, Third()).InSequence(s2);
	EXPECT_CALL(mock, Forth()).InSequence(s2);

	Do2(&mock);
}


using testing::InSequence;
// First -> Second -> Third -> Forth
TEST(FooTest, SequenceTest) {
	InSequence seq;  // 해당 객체를 생성하면, 순서 검증이 됩니다.
	MockFoo mock;

	EXPECT_CALL(mock, First());
	EXPECT_CALL(mock, Second());
	EXPECT_CALL(mock, Third());
	EXPECT_CALL(mock, Forth());

	Do(&mock);
}













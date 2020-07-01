
// Hamcrest
//   : 단언문을 사용할 때, 좀더 문장에 가까운 표현할 수 있도록 하는
//     비교표현의 확장 라이브러리이다.

#include <gmock/gmock.h>

int Foo() { return 100; }
const char* Goo() { return "Hello, Goo"; }
const char* Hoo() { return "Line.."; }

std::vector<int> Koo() {
	std::vector<int> v;
	v.push_back(10);
	v.push_back(20);
	v.push_back(30);

	return v;
}

using testing::ElementsAre;
using testing::UnorderedElementsAre;

using testing::ElementsAreArray;
using testing::UnorderedElementsAreArray;

using testing::AllOf;
using testing::Gt;
using testing::Lt;
using testing::Matcher;

// Matcher 중에 Container의 내용을 체크하는 기능도 제공합니다.
TEST(HamcrestTest, KooTest) {
	
	Matcher<int> expected_array[] = { Lt(30), Gt(20), AllOf(Lt(10), Gt(20)) };
	EXPECT_THAT(Koo(), UnorderedElementsAreArray(expected_array));

	EXPECT_THAT(Koo(), ElementsAre(10, 20, 30));
	EXPECT_THAT(Koo(), UnorderedElementsAre(10, 30, 20));
}


using testing::StartsWith;
using testing::MatchesRegex;

TEST(HamcrestTest, FooGooHooTest) {
	EXPECT_THAT(Foo(), AllOf(Gt(50), Lt(100)));
	EXPECT_THAT(Goo(), StartsWith("hello"));
	EXPECT_THAT(Hoo(), MatchesRegex("Line"));
}









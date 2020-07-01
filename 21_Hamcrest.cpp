
// Hamcrest
//   : 단언문을 사용할 때, 좀더 문장에 가까운 표현할 수 있도록 하는
//     비교표현의 확장 라이브러리이다.

#include <gmock/gmock.h>

int Foo() { return 100; }
const char* Goo() { return "Hello, Goo"; }
const char* Hoo() { return "Line.."; }

// EXPECT_THAT(표현식, Matcher)

using testing::AllOf;
using testing::Gt;
using testing::Lt;

using testing::StartsWith;
using testing::MatchesRegex;

TEST(HamcrestTest, FooGooHooTest) {
	EXPECT_THAT(Foo(), AllOf(Gt(50), Lt(100)));
	EXPECT_THAT(Goo(), StartsWith("hello"));
	EXPECT_THAT(Hoo(), MatchesRegex("Line"));
}

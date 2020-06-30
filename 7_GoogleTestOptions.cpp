#include <gtest/gtest.h>
// 4 Test Suites - 6 Tests
// 1) Filter
//  Google Test - filter의 기능을 이용해서, 원하는 테스트를 선택적으로
//                수행할 수 있다.
//    $ ./a.out --gtest_filter=*.foo 
//    $ ./a.out --gtest_filter=*.P_*
//
// 2) 반복 테스트
//   : Suite Fixture Setup / Teardown
//     - 공유 픽스쳐로 인한 변덕스러운 테스트의 문제가 발생하는지 여부를
//       체크할 때 사용할 수 있습니다.
// ./a.out --gtest_repeat=100 --gtest_shuffle --gtest_break_on_failure
//
// 3) Test Result Formatter 
// $ ./a.out --gtest_output=xml,json
//    => test_detail.xml / json
//
// 4) Record Property - xml, json
//  : gtest_output 옵션을 통해 생성되는 xml, json에 추가적인 정보를 기록하는 방법.

TEST(SampleTest, foo) {
	RecordProperty("cpu", "80%");
	RecordProperty("mem", "15%");
}
TEST(SampleTest, goo) {
	RecordProperty("cpu", "80%");
	RecordProperty("mem", "15%");
}
TEST(SampleTest, hoo) {
	RecordProperty("cpu", "80%");
	RecordProperty("mem", "15%");
	FAIL();
}




TEST(FooTest, foo) {
}

TEST(GooTest, goo) {
}

TEST(HooTest, hoo) {
}

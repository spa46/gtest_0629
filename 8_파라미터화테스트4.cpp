#include <gtest/gtest.h>

const char* animals[] = { "dog", "cat" };
enum Color { BLACK, GRAY, WHITE };

class AnimalTest : public testing::TestWithParam
					<std::tuple<const char*, Color, const char*>> {
protected:
};

using testing::Combine;
using testing::ValuesIn;
using testing::Values;

INSTANTIATE_TEST_SUITE_P(AnimalVariations, AnimalTest, 
	Combine(ValuesIn(animals), 
	        Values(BLACK, WHITE, GRAY), 
	        ValuesIn(animals)));

TEST_P(AnimalTest, AnimalLookNice) {
	// std::tuple<const char*, Color> v = GetParam();
	auto v = GetParam();
	const char* animal = std::get<0>(v);
	Color c = std::get<1>(v);
	auto d = std::get<2>(v);

	printf("%s(%d) - %s\n", animal, c, d);
}










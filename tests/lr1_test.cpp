#include <lib/lr1.h>
#include <gtest/gtest.h>
#include <vector>
#include <utility>

struct borderline_value {
	vector<int> input;
	bool expectPair;
};

class CountAndSumTest : public ::testing::Test {
protected:
	void SetUp() override {
		borderlineValues =
		{
			{ { INT_MIN, INT_MIN  }, false },
			{ { INT_MIN, INT_MAX }, true },
			{ { INT_MIN, 5  }, false }, { { INT_MIN, 4  }, false },
			{ { INT_MIN, 6 }, true },

			{ { INT_MAX, INT_MIN }, false },
			{ { INT_MAX, INT_MAX }, false },
			{ { INT_MAX, 5 }, false }, { { INT_MAX, 4 }, false },
			{ { INT_MAX, 6 }, false },

			{ { 5, INT_MIN }, false }, { { 4, INT_MIN }, false },
			{ { 5, INT_MAX }, true },  { { 4, INT_MAX }, true },
			{ { 5, 4 }, false }, { { 4, 4 }, false }, { { 4, 5 }, false }, { { 5, 4 }, false },
			{ { 5, 6 }, true }, { { 4, 6 }, true },

			{ { 6, INT_MIN, }, false },
			{ { 6, INT_MAX, }, false },
			{ { 6, 4, }, false }, { { 6, 5 }, false },
			{ { 6, 6, }, false },
		};
	}

	std::vector<borderline_value> borderlineValues;
};

TEST_F(CountAndSumTest, пустой_вектор) {
	vector<int> emptyVector;
	vector<PairWithIndex> res = findPairs(emptyVector);
	EXPECT_EQ(res.size(), 0);
}

TEST_F(CountAndSumTest, вектор_с_одним_элементом) {
	vector<int> vectorWithOneElement{ 0 };
	vector<PairWithIndex> res = findPairs(vectorWithOneElement);
	EXPECT_EQ(res.size(), 0);
}

TEST_F(CountAndSumTest, вектор_с_несколькими_элементами_без_пар_чёт) {
	vector<int> userInput{ 1, 2, 3, 4 };
	vector<PairWithIndex> res = findPairs(userInput);
	EXPECT_EQ(res.size(), 0);
}

TEST_F(CountAndSumTest, вектор_с_несколькими_элементами_без_пар_нечёт) {
	vector<int> userInput{ 1, 2, 3 };
	vector<PairWithIndex> res = findPairs(userInput);
	EXPECT_EQ(res.size(), 0);
}

#define CHECK_PAIR(p, f, s, i) \
        EXPECT_EQ(p.first, f); \
        EXPECT_EQ(p.second, s); \
        EXPECT_EQ(p.index, i);

TEST_F(CountAndSumTest, вектор_только_из_пары) {
	vector<int> userInput{ 5, 6 };
	vector<PairWithIndex> res = findPairs(userInput);
	EXPECT_EQ(res.size(), 1);
	CHECK_PAIR(res[0], 5, 6, 0);
}

TEST_F(CountAndSumTest, вектор_только_из_пары_погр_знач) {

	for each (borderline_value b in borderlineValues)
	{
		int first = b.input[0];
		int second = b.input[1];
		vector<PairWithIndex> res = findPairs(b.input);
		if (b.expectPair)
		{
			EXPECT_EQ(res.size(), 1);
			CHECK_PAIR(res[0], first, second, 0);
		}
		else
		{
			EXPECT_EQ(res.size(), 0);
		}
	}
}


TEST_F(CountAndSumTest, вектор_с_несколькими_элементами_пара_в_начале_чёт) {
	vector<int> userInput{ 5, 6, 0, 0 };
	vector<PairWithIndex> res = findPairs(userInput);
	EXPECT_EQ(res.size(), 1);
	CHECK_PAIR(res[0], 5, 6, 0);
}

TEST_F(CountAndSumTest, вектор_с_несколькими_элементами_пара_в_начале_чёт_погр_знач) {

	for each (borderline_value b in borderlineValues)
	{
		int first = b.input[0];
		int second = b.input[1];

		vector<int> paddedInput = { first, second, 0, 0 };
		vector<PairWithIndex> res = findPairs(paddedInput);
		if (b.expectPair)
		{
			EXPECT_EQ(res.size(), 1);
			CHECK_PAIR(res[0], first, second, 0);
		}
		else
		{
			EXPECT_EQ(res.size(), 0);
		}
	}
}

TEST_F(CountAndSumTest, вектор_с_несколькими_элементами_пара_в_начале_нечёт) {
	vector<int> userInput{ 5, 6, 0 };
	vector<PairWithIndex> res = findPairs(userInput);
	EXPECT_EQ(res.size(), 1);
	CHECK_PAIR(res[0], 5, 6, 0);
}


TEST_F(CountAndSumTest, вектор_с_несколькими_элементами_пара_в_начале_нечёт_погр_знач) {

	for each (borderline_value b in borderlineValues)
	{
		int first = b.input[0];
		int second = b.input[1];

		vector<int> paddedInput = { first, second, 0 };
		vector<PairWithIndex> res = findPairs(paddedInput);
		if (b.expectPair)
		{
			EXPECT_EQ(res.size(), 1);
			CHECK_PAIR(res[0], first, second, 0);
		}
		else
		{
			EXPECT_EQ(res.size(), 0);
		}
	}
}

TEST_F(CountAndSumTest, вектор_с_несколькими_элементами_пара_в_конце_чёт) {
	vector<int> userInput{ 0, 0, 5, 6 };
	vector<PairWithIndex> res = findPairs(userInput);
	EXPECT_EQ(res.size(), 1);
	CHECK_PAIR(res[0], 5, 6, 2);
}

TEST_F(CountAndSumTest, вектор_с_несколькими_элементами_пара_в_конце_чёт_погр_знач) {

	for each (borderline_value b in borderlineValues)
	{
		int first = b.input[0];
		int second = b.input[1];

		vector<int> paddedInput = { INT_MAX, INT_MAX, first, second };
		vector<PairWithIndex> res = findPairs(paddedInput);
		if (b.expectPair)
		{
			EXPECT_EQ(res.size(), 1);
			CHECK_PAIR(res[0], first, second, 2);
		}
		else
		{
			EXPECT_EQ(res.size(), 0);
		}
	}
}

TEST_F(CountAndSumTest, вектор_с_несколькими_элементами_пара_в_конце_нечёт) {
	vector<int> userInput{ 0, 5, 6 };
	vector<PairWithIndex> res = findPairs(userInput);
	EXPECT_EQ(res.size(), 1);
	CHECK_PAIR(res[0], 5, 6, 1);
}

TEST_F(CountAndSumTest, вектор_с_несколькими_элементами_пара_в_конце_нечёт_погр_знач) {

	for each (borderline_value b in borderlineValues)
	{
		int first = b.input[0];
		int second = b.input[1];

		vector<int> paddedInput = { INT_MAX, first, second };
		vector<PairWithIndex> res = findPairs(paddedInput);
		if (b.expectPair)
		{
			EXPECT_EQ(res.size(), 1);
			CHECK_PAIR(res[0], first, second, 1);
		}
		else
		{
			EXPECT_EQ(res.size(), 0);
		}
	}
}

TEST_F(CountAndSumTest, вектор_с_несколькими_элементами_пара_в_середине_чёт) {
	vector<int> userInput{ 0, 0, 0, 5, 6, 0, 0, 0 };
	vector<PairWithIndex> res = findPairs(userInput);
	EXPECT_EQ(res.size(), 1);
	CHECK_PAIR(res[0], 5, 6, 3);
}

TEST_F(CountAndSumTest, вектор_с_несколькими_элементами_пара_в_середине_чёт_погр_знач) {

	for each (borderline_value b in borderlineValues)
	{
		int first = b.input[0];
		int second = b.input[1];

		vector<int> paddedInput = { INT_MAX, INT_MAX, INT_MAX, first, second, INT_MIN, INT_MIN, INT_MIN };
		vector<PairWithIndex> res = findPairs(paddedInput);
		if (b.expectPair)
		{
			EXPECT_EQ(res.size(), 1);
			CHECK_PAIR(res[0], first, second, 3);
		}
		else
		{
			EXPECT_EQ(res.size(), 0);
		}
	}
}

TEST_F(CountAndSumTest, вектор_с_несколькими_элементами_пара_в_середине_нечёт_правее) {
	vector<int> userInput{ 0, 0, 5, 6, 0 };
	vector<PairWithIndex> res = findPairs(userInput);
	EXPECT_EQ(res.size(), 1);
	CHECK_PAIR(res[0], 5, 6, 2);
}

TEST_F(CountAndSumTest, вектор_с_несколькими_элементами_пара_в_середине_нечёт_правее_погр_знач) {

	for each (borderline_value b in borderlineValues)
	{
		int first = b.input[0];
		int second = b.input[1];

		vector<int> paddedInput = { INT_MAX, INT_MAX, first, second, INT_MIN };
		vector<PairWithIndex> res = findPairs(paddedInput);
		if (b.expectPair)
		{
			EXPECT_EQ(res.size(), 1);
			CHECK_PAIR(res[0], first, second, 2);
		}
		else
		{
			EXPECT_EQ(res.size(), 0);
		}
	}
}

TEST_F(CountAndSumTest, вектор_с_несколькими_элементами_пара_в_середине_нечёт_левее) {
	vector<int> userInput{ 0, 5, 6, 0, 0 };
	vector<PairWithIndex> res = findPairs(userInput);
	EXPECT_EQ(res.size(), 1);
	CHECK_PAIR(res[0], 5, 6, 1);
}

TEST_F(CountAndSumTest, вектор_с_несколькими_элементами_пара_в_середине_нечёт_левее_погр_знач) {

	for each (borderline_value b in borderlineValues)
	{
		int first = b.input[0];
		int second = b.input[1];

		vector<int> paddedInput = { INT_MAX, first, second, INT_MIN, INT_MIN };
		vector<PairWithIndex> res = findPairs(paddedInput);
		if (b.expectPair)
		{
			EXPECT_EQ(res.size(), 1);
			CHECK_PAIR(res[0], first, second, 1);
		}
		else
		{
			EXPECT_EQ(res.size(), 0);
		}
	}
}

TEST_F(CountAndSumTest, вектор_с_несколькими_парами_внач_вконц_всеред) {
	vector<int> userInput{ 4, 6, 0, 3, 7, 0, 1, 9 };
	vector<PairWithIndex> res = findPairs(userInput);
	EXPECT_EQ(res.size(), 3);
	CHECK_PAIR(res[0], 4, 6, 0);
	CHECK_PAIR(res[1], 3, 7, 3);
	CHECK_PAIR(res[2], 1, 9, 6);
}

TEST_F(CountAndSumTest, вектор_с_разными_значениями) {
	vector<int> userInput{ -89, -96, -87, 77, 50, -40, 3, 64, 61, 32, -96, -78, -64, 54, -21, 58, -71, -52, 25, -45 };
	vector<PairWithIndex> res = findPairs(userInput);
	EXPECT_EQ(res.size(), 5);
	CHECK_PAIR(res[0],-87, 77, 2);
	CHECK_PAIR(res[1], 3, 64, 6);
	CHECK_PAIR(res[2], -64, 54, 12);
	CHECK_PAIR(res[3], -21, 58, 14);
	CHECK_PAIR(res[4], -52, 25, 17);
}
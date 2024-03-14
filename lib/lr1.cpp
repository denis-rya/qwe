#include "lr1.h"

using namespace std;

vector<PairWithIndex> findPairs(const vector<int>& userInputArr) {
	vector<PairWithIndex> result; // Stores pairs and their indices

	if (userInputArr.size() == 0)
	{
		return result;
	}

	for (int i = 0; i < userInputArr.size() - 1; ++i) {
		if (userInputArr[i] <= 5 && userInputArr[i + 1] > 5) {
			result.push_back({ userInputArr[i], userInputArr[i + 1], i });
		}
	}

	return result;
}

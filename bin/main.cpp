#include <iostream>
#include <vector>

#include <lib/lr1.h>

using namespace std;

int main() {
	cout << "„B„r„u„t„y„„„u „‰„y„ƒ„|„€ „€„„ 0 „t„€ " << INT_MAX << endl;

	vector<int> asd;
	asd.push_back(1);

	vector<PairWithIndex> a = findPairs(asd);

	int inputCount = 0;
	cin >> inputCount;

	while (cin.fail() || inputCount < 0)
	{
		cin.clear();
		cin.ignore();
		cout << "„N„u„r„u„‚„~„„z „r„r„€„t. „P„€„r„„„€„‚„y„„„u „„€„„„„„{„…." << endl;
		cin >> inputCount;
	}

	vector<int> userInputArr(inputCount);
	int i = 0;
	while (i < inputCount)
	{
		cout << "„B„r„u„t„y„„„u „‰„y„ƒ„|„€ „€„„ " << INT_MIN << " „t„€ " << INT_MAX << endl;

		int number;
		cin >> number;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore();
			cout << "„N„u„r„u„‚„~„„z „r„r„€„t. „P„€„r„„„€„‚„y„„„u „„€„„„„„{„…." << endl;
		}
		else
		{
			userInputArr[i] = number;
			i++;
		}
	}

	vector<PairWithIndex> result = findPairs(userInputArr);

	if (result.empty()) {
		std::cout << "No such pairs found.\n";
	}
	else {
		std::cout << "Pairs (ai, ai+1) and their indices:\n";
		for (const auto& pair : result) {
			std::cout << "(" << pair.first << ", " << pair.second << ") at index " << pair.index << "\n";
		}
	}

	return 0;
}
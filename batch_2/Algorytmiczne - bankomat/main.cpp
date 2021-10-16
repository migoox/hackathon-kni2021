#include <iostream>
#include <vector>

int main()
{
	std::vector<int> denominations;
	std::vector<int> occurances;

	int size;
	int value;
	int inquiries_count;
	bool possible;

	std::cout << "Number of denominations: \n>>";
	std::cin >> size;

	std::cout << "\nWARNING: Denominations must be sorted ascending!\n\n";
	for (size_t i = 0; i < size; i++)
	{
		int input;
		std::cout << "Denomination[" << i + 1 << "]: ";
		std::cin >> input;

		denominations.push_back(input);
		occurances.push_back(0);
	}

	std::cout << "\nHow many withdrawals? \n>>";
	std::cin >> inquiries_count;

	for (size_t j = 0; j < inquiries_count; j++)
	{
		possible = true;

		std::cout << "\n[" << j + 1 << "]How much money do you want to withdraw? \n>>";
		std::cin >> value;

		for (size_t i = 0, x = size - 1; i < size; i++, x--)
		{
			occurances[x] = value / denominations[x];

			if (value % denominations[x] > 0 && x == 0)
			{
				possible = false;
			}

			value = value % denominations[x];
		}

		if (possible)
		{
			std::cout << "Your withdrawal: \n";
			for (size_t i = 0, x = size - 1; i < size; i++, x--)
			{
				if(occurances[x] != 0)
					std::cout << denominations[x] << " x" << occurances[x] << "\n";
			}
		}
		else
		{
			std::cout << "It is impossible to prepare such a withdrawal!\n";
		}

		std::fill(occurances.begin(), occurances.end(), 0);
	}
	return 0;
}
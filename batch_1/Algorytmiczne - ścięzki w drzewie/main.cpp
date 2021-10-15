#include <iostream>
#include <vector>
#include <string>

struct Node
{
	int value = 0;
	Node* left_parent = nullptr;
	Node* right_parent = nullptr;
};

struct Digger
{
	std::vector<std::vector<int>> paths;

	void find_paths(std::vector<std::vector<Node>>& graph)
	{
		for (size_t i = 0; i < graph.size(); i++)
		{
			Node* current = &graph[graph.size() - 1][i];
			std::vector<int> blank;

			dig(current, blank);
		}
	}
	void dig(Node* current, const std::vector<int>& vec_base)
	{
		std::vector<int> vec = vec_base;

		while (true)
		{
			vec.push_back(current->value);

			if (current->left_parent == nullptr && current->right_parent == nullptr)
			{
				paths.push_back(vec);
				break;
			}
			else if (current->left_parent == nullptr)
			{
				current = current->right_parent;
			}
			else if (current->right_parent == nullptr)
			{
				current = current->left_parent;
			}
			else // node has two parents
			{
				dig(current->left_parent, vec);
				dig(current->right_parent, vec);
				break;
			}
		}
	}
};

int sum_vector(const std::vector<int> vec)
{
	int sum = 0;

	for (auto& it : vec)
		sum += it;

	return sum;
}


int main()
{
	srand(NULL);

	int n;								  // number of levels
	int max_weight;						  // maximum possible weight of node 
	std::vector<std::vector<Node>> graph; // graph container

	std::cout << ">--INPUT--<\n\nNumber of levels: \n";
	std::cout << ">>";
	std::cin >> n;

	std::cout << "Max weight: \n";
	std::cout << ">>";
	std::cin >> max_weight;

	// nodes generating and parent assignments
	for (size_t i = 0; i < n; i++)
	{
		std::vector<Node> level;
		graph.push_back(level);

		for (size_t j = 0; j < i + 1; j++)
		{
			Node node;
			node.value = rand() % max_weight + 1;

			if (i == 0) // tip of the graph -> no parents
			{
				node.left_parent = nullptr;
				node.right_parent = nullptr;
			}
			else if (j == i)
			{
				node.left_parent = &graph[i - 1][j - 1];
				node.right_parent = nullptr;
			}
			else if (j == 0)
			{
				node.left_parent = nullptr;
				node.right_parent = &graph[i - 1][0];
			}
			else if (j > 0 && j < i)
			{
				node.left_parent = &graph[i - 1][j - 1];
				node.right_parent = &graph[i - 1][j];
			}

			graph[i].push_back(node);
		}
	}

	std::cout << "\n>--OUTPUT--<\n\nGiven graph: \n";

	// graph drawing
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < n - i; j++)
		{
			std::cout << "    ";
		}
		for (size_t j = 0; j < i + 1; j++)
		{
			std::cout << graph[i][j].value << "        ";
		}
		std::cout << "\n";
	}

	std::cout << "\n\nAll possible paths: \n";

	// pathfinding
	Digger digger;
	digger.find_paths(graph);
	for (size_t i = 0; i < digger.paths.size(); i++)
	{
		std::cout << "[";
		for (size_t j = 0, x = digger.paths[i].size() - 1; 
			j < digger.paths[i].size(); j++, x--)
		{
			std::cout << digger.paths[i][x];

			if (x > 0)
				std::cout << ", ";
		}
		std::cout << "]\n";
	}
	std::cout << "\n\n";

	// finding max and min path
	int max_sum = -INT16_MAX;
	int min_sum = INT16_MAX;
	std::vector<int> max_paths_ids;
	std::vector<int> min_paths_ids;

	for (size_t i = 0; i < digger.paths.size(); i++)
	{
		int curr_sum = sum_vector(digger.paths[i]);

		if (curr_sum > max_sum)
		{
			max_sum = curr_sum;
			max_paths_ids.clear();
		}
		if (curr_sum == max_sum)
		{
			max_paths_ids.push_back(i);
		}

		if (curr_sum < min_sum)
		{
			min_sum = curr_sum;
			min_paths_ids.clear();
		}
		if (curr_sum == min_sum)
		{
			min_paths_ids.push_back(i);
		}
	}

	std::cout << "Max paths: \n";
	for (auto& id : max_paths_ids)
	{
		std::cout << "[";
		for (size_t j = 0, x = digger.paths[id].size() - 1;
			j < digger.paths[id].size(); j++, x--)
		{
			std::cout << digger.paths[id][x];

			if (x > 0)
				std::cout << ", ";
		}
		std::cout << "]\n";
	}

	std::cout << "\nMin paths: \n";
	for (auto& id : min_paths_ids)
	{
		std::cout << "[";
		for (size_t j = 0, x = digger.paths[id].size() - 1;
			j < digger.paths[id].size(); j++, x--)
		{
			std::cout << digger.paths[id][x];

			if (x > 0)
				std::cout << ", ";
		}
		std::cout << "]\n";
	}

	return 0;
}
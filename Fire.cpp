#include<iostream>
#include<vector>
#include<queue>

typedef std::vector<std::vector<int>> adjacency_list;
enum {
	fire = -1,
	pass = 0,
	wall = 4,
	john = 1

};
void BFS(const adjacency_list& graph, int john_pos, int fire_pos, std::vector<bool>& fvisited, 
	std::vector<bool>& jvisited, std::vector<int>& dist_from_start_vertex, 
	int &distance, const int R, const int C,bool& posible)
{
	std::queue<int> jq;
	jq.push(john_pos);
	jvisited[john_pos] = true;
	dist_from_start_vertex[john_pos] = 0;


	std::queue<int> fq;
	fq.push(fire_pos);
	fvisited[fire_pos] = true;
	while (!jq.empty())
	{
		if (!fq.empty())
		{
			int cur = fq.front();
			fq.pop();
			for (int neighbour : graph[cur])
			{
				if (!fvisited[neighbour])
				{
					fq.push(neighbour);
					fvisited[neighbour] = true;

				}
			}
		}

		int cur = jq.front();
		jq.pop();

		for (int neighbour : graph[cur])
		{
			if (!jvisited[neighbour] && !fvisited[neighbour])
			{
				jq.push(neighbour);
				jvisited[neighbour] = true;
				dist_from_start_vertex[neighbour] = dist_from_start_vertex[cur] + 1;
				if (neighbour < C || neighbour % C == 0 || neighbour >= C * (R - 1)
					|| neighbour % C == C - 1)
				// it means that neighbour in a endline of matrix
				{
					distance = dist_from_start_vertex[neighbour];
					posible = true;
					return;
				}
			}
		}

	}
}


int chars_to_int(const char c)
{
	switch (c)
	{
	case '.':
		return pass;
		break;
	case 'F':
		return fire;
		break;
	case '#':
		return wall;
		break;
	case 'J':
		return john;
		break;

	default:
		break;
	}
	return -1;
}
int main()
{
	int test_count;
	std::cin >> test_count;
	int R;//Rows
	int C;//charctrs
	std::vector<int> results;
	for (int i = 0; i < test_count; ++i)
	{
		std::cin >> R >> C;
		adjacency_list matrix(R);
		char c;
		int john_pos;
		int fire_pos;
		for (int i = 0; i < R; ++i)
		{
			for (int j = 0; j < C; ++j)
			{
				std::cin >> c;
				matrix[i].push_back(chars_to_int(c));
				if (c == 'J')
				{
					john_pos = i * C + j;
				}
				if (c == 'F')
				{
					fire_pos = i * C + j;
				}

			}
		}
		adjacency_list my_graph(R * C);
		for (int i = 0; i < R; ++i)
		{
			for (int j = 0; j < C; ++j)
			{
				if (matrix[i][j] != wall)
				{
					int cur_in_graph = i * C + j;
					if (j > 0 && matrix[i][j - 1] != wall) // connecting with left
					{
						//cur2 = i * C + j - 1;
						my_graph[cur_in_graph].push_back(cur_in_graph - 1);
					}
					if (j < C - 1 && matrix[i][j + 1] != wall) // connecting with right
					{
						//cur2 = i * C + j + 1;
						my_graph[cur_in_graph].push_back(cur_in_graph + 1);
					}
					if (i > 0 && matrix[i - 1][j] != wall) // connecting with up
					{
						//cur2 = i * C + j - C;
						my_graph[cur_in_graph].push_back(cur_in_graph - C);
					}
					if (i < R - 1 && matrix[i + 1][j] != wall) // connecting with up
					{
						//cur2 = i * C + j - C;
						my_graph[cur_in_graph].push_back(cur_in_graph + C);
					}
				}
			}
		}
		std::vector<bool> jvisited(my_graph.size());
		std::vector<bool> fvisited(my_graph.size());
		bool posible = false;
		std::vector<int> dist_from_start_vertex(my_graph.size(), -1);
		int distance = -1;
		BFS(my_graph, john_pos, fire_pos, fvisited, jvisited, dist_from_start_vertex,
			distance, R, C, posible);
		if (!posible)
		{
			results.push_back(-1);
		}
		else
		{
			results.push_back(distance + 1);
		}

	}
	for (const auto el : results)
	{
		if (el == -1)
		{
			std::cout << "IMPOSSIBLE\n";
		}
		else
		{
			std::cout << el << "\n";
		}
	}


}
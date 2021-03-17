#include <iostream>
#include <vector>
#include <cstdint>
#include <stdlib.h>
#include <fstream>
#include <cstdint>
#include <queue>
#include <stack>
#include <list>
#include <chrono>
using namespace std;
using namespace std::chrono;

//Global variables
ofstream out_file;
vector<queue<uint32_t>> edges_queues;
uint32_t total_num_of_edges = 0;

//Function prototypes
bool input_parse(uint32_t& number_of_vertices,
	uint32_t& starting_vertex, char const* argv[], uint32_t*& out_degree_array);

int main(int argc, char const* argv[])
{
//	auto start = chrono::high_resolution_clock::now();
	if (argc != 3)
	{
		cout << "Wrong inputs\n";
		return -1;
	}
	out_file.open(argv[2]);

	uint32_t number_of_vertices;
	uint32_t starting_vertex;
	uint32_t* out_degree_array;
	list<uint32_t> eulerian_circuit;

	if (input_parse(number_of_vertices, starting_vertex, argv, out_degree_array) == false)
	{
		out_file << "no path\n";
		return -1;
	}

	//	//Hierholzers Algorithm

	uint32_t current_vertex, toured_vertex, old_vertex;
	//temp_list.in

	eulerian_circuit.push_back(starting_vertex);

	list<uint32_t>::iterator ptr = eulerian_circuit.begin();
	list<uint32_t>::iterator tempptr;
	while (eulerian_circuit.size() < total_num_of_edges)
	{
		current_vertex = *ptr;
		toured_vertex = current_vertex;
		list<uint32_t> temp_list;
		while(edges_queues[current_vertex].empty() == false)
		{
			old_vertex = current_vertex;
			current_vertex = edges_queues[current_vertex].front();
			edges_queues[old_vertex].pop();
			temp_list.push_back(current_vertex);
		}
		tempptr = ptr;
		tempptr++;
		eulerian_circuit.splice(tempptr, temp_list);
		ptr++;
	}

	for (auto v : eulerian_circuit)
		out_file << v << " ";

	out_file.close();

//	auto stop = high_resolution_clock::now();
//	auto duration = duration_cast<seconds>(stop - start);
//	cout << duration.count() << endl;

	return 0;
}

bool input_parse(uint32_t& number_of_vertices,
	uint32_t& starting_vertex, char const* argv[], uint32_t*& out_degree_array)
{
	std::ifstream file(argv[1]);
	uint32_t vertex, out_degree, successor;
	uint8_t* evenness;

	if (file.is_open())
	{
		file >> number_of_vertices;
		out_degree_array = new uint32_t[number_of_vertices];
		evenness = new uint8_t[number_of_vertices] {0};

		for (auto i = 0; i < number_of_vertices; i++)
		{
			queue<uint32_t> tempq;
			file >> vertex >> out_degree;
			out_degree_array[i] = out_degree;
			for (auto j = 0; j < out_degree; j++)
			{
				file >> successor;
				tempq.push(successor);
				total_num_of_edges++;
				evenness[successor]++;
			}
			edges_queues.push_back(tempq);
		}
		for (auto i = 0; i < number_of_vertices; i++)
		{
			if (evenness[i] + out_degree_array[i] % 2 == 1)
				return false;
		}

		file >> starting_vertex;
	}
	return true;
}

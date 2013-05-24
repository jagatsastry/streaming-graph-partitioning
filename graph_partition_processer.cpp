#include <iostream>
#include "dep/InputReader.h"
#include "dep/Graph.h"
#include "dep/Partitioner.h"
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
	InputReader reader;
	Graph &g = reader.getGraph();
	vector<long> &sources = reader.getSources();

	int k = 10; // number_of_partitions.
	Partitioner partitioner = Partitioner(k, g.numOfVertices(), LINEAR);
	cout << g.numOfVertices() << " " << k << endl;
	for(int i = 0; i < g.numOfVertices(); i++) {
		int partion_index = partitioner.get_partition_index(i, g.getNeighbors(i));
		partitioner.add_vertex_to_partition(partion_index, i, g.getNeighbors(i));
		cout << partion_index << endl;
	}
	//cout << "graph_partition_processing ends here!" << endl;

	// partitioner.show_partitions();

	return 0;		
}

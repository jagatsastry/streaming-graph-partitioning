#include "Partitioner.h"

int Partitioner::get_partition_index (long graph_node, vector<long> node_neighbors,
                    Heuristic* heur) {
	// This is the function responsible for all partition heuristic.
	// Heuristic 1: Assign the graph_node to smallest size partition.
    return heur->getPartition(graph_node, partitions, node_neighbors);
}

void Partitioner::show_partitions() {
	for (int i = 0; i < number_of_partitions; i++)
        partitions[i].showVertices();
}

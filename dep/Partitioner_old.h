#include <iostream>
#include <vector>

using namespace std;

class Partitioner {
    int number_of_partition;
    vector<vector<long> > partition;
    
    public:
    Partitioner(int k) : number_of_partition(k), partition(k + 1) {}
    int get_partition_index(long graph_node, vector<long> node_neighbors);
    void add_vertex_to_partition(int partion_index, long graph_node) {
        partition[partion_index].push_back(graph_node);
        //cout << "graph node is added into partition at index " + partion_index << endl;
    }
    void show_partitions();
};

int Partitioner::get_partition_index (long graph_node, vector<long> node_neighbors) {
    // This is the function responsible for all partition heuristic.
    // Heuristic 1: Assign the graph_node to smallest size partition.
    int min_partition_index = 0;
    int partition_size = 0;
    for (int i = 0; i < number_of_partition; i++) {
        partition_size = partition[i].size();
        if (partition_size < partition[min_partition_index].size())
            min_partition_index = i;
    }
    return min_partition_index;
}

void Partitioner::show_partitions() {
    int partition_size = 0;
    for (int i = 0; i < number_of_partition; i++) {
        partition_size = partition[i].size();
        for (int j = 0; j < partition_size; j++)
            cout << partition[i][j] << " ";

        cout << endl;
    }
}

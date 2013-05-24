Implements greedy techniques to partition streaming graph (graph streamed one vertices at a time). 
Useful when a graph is so huge that it cannot be stored on a single node, yet needs to be partitioned.
State-of-the-art tools like Metis partition the whole graph by loading them into memory. This may not be feasible for extremely large graphs.


Original repository: https://bitbucket.org/souravgarg/streaming-graph-partitioning/

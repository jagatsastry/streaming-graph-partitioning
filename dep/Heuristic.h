#ifndef HEURISTIC_H
#define HEURISTIC_H

/** Interface for heuristic. Please inherit this class in building your own heuristic. 
    Helps in making heuristics pluggable.
    */

#include<vector>
#include"Partition.h"
#include"Graph.h"

using namespace std;

class Heuristic {
    
    public:
    virtual int getPartition(long vertex, vector<Partition>& partitions,
    		vector<long>& neighbors) = 0;

    static const int SMALL = 1;
    static const int GREEDY = 2;
    static const int CCF = 3;
    static const int BBIG = 4;
    static const int PBIG = 5;
    static const int RAND = 6;

    virtual long getEdgeCountInPartition(Partition p, vector<long>& neighbors);

    virtual ~Heuristic() {

    }
};

#endif

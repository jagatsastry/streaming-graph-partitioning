#include "Heuristic.h"

long Heuristic::getEdgeCountInPartition(Partition p, vector<long>& neighbors){
    long count =0;
    for(unsigned int i=0, sz = neighbors.size(); i<sz; i++){
        if(p.isVertPresent(neighbors[i]))
            count++;
    }
    return count;
}






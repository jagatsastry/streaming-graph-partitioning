#include "Heuristic.h"
#include<climits>

class CCFHeuristic: public Heuristic {

public:

	virtual int getPartition(long vertex, vector<Partition>& part,
	    		vector<long>& neighbors){
		int maxPart = 0;
		float maxCCF = 0.0;
		bool maxFound = false;

		for(unsigned int i = 0; i < part.size(); i++) {

			int vtxct = part[i].getVerticesPresent(neighbors);
			if(vtxct == 0 || vtxct == 1) continue;
			float ccf = part[i].getWeight() *
						2*part[i].getEdgesPresent(neighbors)/(float)(vtxct*(vtxct-1));

			if(ccf > maxCCF) {
				maxCCF = ccf;
				maxPart = i;
				maxFound = true;
			}
		}
		if(!maxFound) {
			long mnsz = LONG_MAX;
			for(int i = 0, sz = part.size(); i < sz; i++) {
				if(part[i].numVertices() < mnsz) {
					maxPart = i;
					mnsz = part[i].numVertices();
				}
			}
		}
		return maxPart;
	}
};




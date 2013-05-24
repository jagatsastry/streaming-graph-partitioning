#ifndef PARTITION_H
#define PARTITION_H
/*A single Partition. Think of it as a machine abstraction which represents a partition.
All it knows is its vertices*/

#include<set>
#include<vector>
#include<iostream>
#include<map>
#include<cmath>
#include<ext/hash_map>
#include<cassert>
#include<climits>
using namespace std;
using namespace __gnu_cxx;

enum WeightScheme{UNWEIGHTED, LINEAR, EXPONENTIAL};

class Partition {
public:

private:
	long m_C;
	WeightScheme m_weightScheme;
    hash_map<long, bool, hash<long> > m_vertices;

    hash_map<long, set<long>, hash<long> > m_edges;
    static unsigned int MAX_VERTEX_PER_PART;


public:
    static void setMaxVertices(unsigned int v) {
    	MAX_VERTEX_PER_PART = v;
    }

    Partition(int C, WeightScheme w) {
    	m_C = C;
    	m_weightScheme = w;
    }
    
    bool maxVertReached() {
        return false;
    }

    float getWeight() {
    	switch(m_weightScheme) {
    	case LINEAR: return 1 - numVertices()/float(m_C);
    	case EXPONENTIAL: return 1 - exp(float(numVertices() - m_C));
    	case UNWEIGHTED:
    	default:
    		return 1;
    	}
    }

    int numVertices() {
    	return m_vertices.size();
    }

    void addVertex(long v, vector<long> nb) {
    	assert(!maxVertReached());
        m_vertices[v] = true; //.insert(v);
        for(uint i = 0, sz = nb.size(); i < sz; i++) {
        	if(this->isVertPresent(nb[i]))
        		m_edges[v].insert(nb[i]);
        }
    }

    bool isEdgePresent(long v1, long v2) {

    	return m_edges[v1].find(v2) != m_edges[v1].end();
    }

    typedef unsigned int uint;

    int getEdgesPresent(vector<long> vertices) {
    	int ct = 0;
    	for(uint i = 0, sz1 = vertices.size(); i < sz1; i++) {
    		for(uint j = i+1; j < sz1; j++) {
    			if(isEdgePresent(vertices[i], vertices[j]))
    				ct++;
    		}
    	}
    	return ct;
    }

    int getVerticesPresent(vector<long> vertices) {
    	int ct = 0;
    	for(uint i = 0, sz = vertices.size(); i < sz; i++) {
    		if(isVertPresent(vertices[i]))
    			ct++;
    	}
    	return ct;
    }

    bool isVertPresent(long v) {
        return m_vertices.find(v) != m_vertices.end();
    }

    int size() {
        return m_vertices.size();
    }
    void showVertices() {

        hash_map<long, bool>::iterator iter = m_vertices.begin();

        for (; iter != m_vertices.end(); ++iter){
            cout<<(*iter).first<<" ";
        }
        cout<<endl;
    }
};

#endif

#include "Graph.h"
#include<climits>


Graph::Graph(long n): adjList(n+1)
{
	N = n;
	M = 0;
	m_adjMatProcessed = false;
}

Graph::Graph(){
	N = 0;
	M = 0;
	m_adjMatProcessed = false;
}


void Graph::addEdge(long u, long v){
	adjList[u].push_back(v);
}

void Graph::addEdgeWithChecks(long u, long v){
	if(u!=v){
		bool found = false;
		if(adjList[u].size() < adjList[v].size())
			found = !(adjList[u].end() == find(adjList[u].begin(), adjList[u].end(), v));
		else
			found = !(adjList[v].end() == find(adjList[v].begin(), adjList[v].end(), u));
		/*if((adjList[u].end() == find(adjList[u].begin(), adjList[u].end(), v))) &&
				(adjList[v].end() == find(adjList[v].begin(), adjList[v].end(), u)) ){
		*/
		if(!found){
	               	adjList[u].push_back(v);
			adjList[v].push_back(u);
                	M+=2;
		}
        }
}

vector<long>& Graph::getNeighbors(long u){
	return adjList[u];
}

void Graph::setNumOfVertices(long n){
	N = n;
	adjList.reserve(N+1);
}

long Graph::numOfVertices(){
	return N;
}

long Graph::numOfEdges(){
	return M;
}


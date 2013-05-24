#include <iostream>
#include <fstream>
#include "dep/Graph.h"

using namespace std;

//write in normal format
void writeUndirectedGraph(char *filename, Graph &g){
	long N = g.numOfVertices();
	long M = g.numOfEdges();
	ofstream out;
	out.open(filename);
	out<<N<<" "<<M<<endl;
	for(long v=1;v<=N;v++){
		vector<long> neighbors = g.getNeighbors(v);
		for(long j=0;j<neighbors.size();j++){
			out<<v<<" "<<neighbors[j]<<endl;
		}
	}
	out.close();
}

//write as adjacency list
void writeGraphForMetis(char *filename, Graph &g){
	ofstream out;
	out.open(filename);
	long N = g.numOfVertices();
	long M = g.numOfEdges()/2;
	out<<N<<" "<<M<<endl;
	for(long v=1;v<=N;v++){
		//out<<v<<" ";
                vector<long> neighbors = g.getNeighbors(v);
                for(long j=0;j<neighbors.size();j++)
                        out<<neighbors[j]<<" ";
		out<<endl;
        } 
	out.close();
}

void getGraph(Graph &g){
	int i, n, e, u, v;
        cin>>n>>e;
	g.setNumOfVertices(n);
        for(i=0;i<e;i++){
        	cin>>u>>v;
        	g.addEdgeWithChecks(u,v);
                //g.addEdgeWithChecks(v,u);
	}
}

//usage ./a.out corrected-output-file-name metis-output-filename < input-file-name
int main(int c, char *argv[]){
        Graph g;
	getGraph(g);
	writeUndirectedGraph(argv[1], g);
	writeGraphForMetis(argv[2], g);
        return 0;	
}

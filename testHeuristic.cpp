#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include<algorithm>
#include "dep/GreedyHeuristic.h"
#include "dep/SmallestPartHeuristic.h"
#include "dep/CCFHeuristic.cpp"
#include "dep/BalancedBigHeuristic.h"
#include "dep/InputReader.h"
#include "dep/Partitioner.h"
#include "dep/RandomPartHeuristic.h"
#include "dep/PreferBigHeuristic.h"

using namespace std;

void stream_default(Graph &g, Partitioner &pr, Heuristic *h){
    int N = g.numOfVertices();
    int pIndex;
    for(int i = 1; i <= N; i++) {
        vector<long> nb = g.getNeighbors(i);
        pIndex= pr.get_partition_index(i, nb, h);
        if(pIndex >= 0){
            pr.add_vertex_to_partition(pIndex, i, nb);
            //cout << pIndex << endl;
        }
    }

    //print to file
    for(int i=1;i<=N;i++){
        pIndex = pr.get_partition_index(i);
        cout << pIndex <<endl; 
    }
    
}

void stream_random(Graph &g, Partitioner &pr, Heuristic *h){
    int N = g.numOfVertices();
    int pIndex;
    vector<long> shuffled(N+1);
    for(int i = 1; i <= N; i++)
    	shuffled[i] = i;
    std::vector<long>::iterator it=shuffled.begin();
    it++;
   	random_shuffle(it, shuffled.end());

   	ofstream fout;
    fout.open("random_op");
    fout<<g.numOfVertices()<<" "<<g.numOfEdges()<<endl;

    for(int k = 1; k <= N; k++) {
    	int i = shuffled[k];
        vector<long> nb = g.getNeighbors(shuffled[i]);
        random_shuffle(nb.begin(), nb.end());
        for(int j=0; j < nb.size(); j++)
        	fout<<i<<" "<<nb[j]<<endl;
        pIndex= pr.get_partition_index(i, nb, h);
        if(pIndex >= 0){
            pr.add_vertex_to_partition(pIndex, i, nb);
            //cout << pIndex << endl;
        }
    }

    //print to file
    for(int i=1;i<=N;i++){
        pIndex = pr.get_partition_index(i);
        cout << pIndex <<endl;
    }

}

void stream_bfs(Graph &g, Partitioner &pr, Heuristic *h){
    queue<long> Q;
    Q.push(1);//assuming all vertices start with index 1
    long N = g.numOfVertices();
    vector<bool> visited(N+1, false);
    visited[1] = true;
    int pIndex;
    ofstream fout;
    fout.open("bfs_op");
    fout<<g.numOfVertices()<<" "<<g.numOfEdges()<<endl;
    while(!Q.empty()){
        long u = Q.front();
        Q.pop();
        vector<long> nb = g.getNeighbors(u);
        pIndex= pr.get_partition_index(u, nb, h);
        if(pIndex >= 0){
            pr.add_vertex_to_partition(pIndex, u, nb);
            //cout << pIndex << endl;
        }
        for(vector<long>::iterator v = nb.begin();v != nb.end();v++){
            if(!visited[*v]){
                visited[*v] = true;
                Q.push(*v);
            } 
            fout<<u<<" "<<*v<<endl;
        }
    }  
    //print to file
    for(int i=1;i<=N;i++){
        pIndex = pr.get_partition_index(i);
        cout << pIndex <<endl;
    }
    fout.close();
 
}

void stream_dfs(Graph &g, Partitioner &pr, Heuristic *h){
    stack<long> Q;
    Q.push(1);//assuming all vertices start with index 1
    long N = g.numOfVertices();
    vector<bool> visited(N+1, false);
    visited[1] = true;
    int pIndex;
    ofstream fout;
    fout.open("dfs_op");
    fout<<g.numOfVertices()<<" "<<g.numOfEdges()<<endl;

    while(!Q.empty()){
        long u = Q.top();
        Q.pop();
        vector<long> nb = g.getNeighbors(u);
        pIndex= pr.get_partition_index(u, nb, h);
        pr.add_vertex_to_partition(pIndex, u, nb);
        cout << pIndex << endl;
        for(vector<long>::iterator v = nb.begin();v != nb.end();v++){
        	fout<<u<<" "<<*v<<endl;
            if(!visited[*v]){
                visited[*v] = true;
                Q.push(*v);
            } 
        }
    }   
}

int main(int argc, char* argv[]){
    if(argc < 3){
        cout<<"./testHeuristic heuristicType numOfPartitions stream_order [weightingScheme [maxVertPerPartition]] < input-graph > out-partition-file"<<endl;
        cout<<"Weighting scheme (1:Unw, 2:Lin(default), 3:Exp)"<<endl;
        cout<<"Heuristic type: 1:Small, 2:Greedy, 3:CCF 4:BBig 5:PBIG"<<endl;
        cout<<"maxVerPerPartition: float value. Eg: 1.5 indicates maxV = 1.5C"<<endl;
        return 0;
    }

    InputReader reader;
    int heuristicType = atoi(argv[1]);
    int numOfPartitions = atoi(argv[2]); // number_of_partitions.
    int stream_order = atoi(argv[3]);

    int wscheme = 2;
    if(argc == 5)
    	wscheme = atoi(argv[4]);

    if(argc == 6) {
    	Partition::setMaxVertices(atof(argv[5]));
    }

    long highDegree;
    int bufferSize = 1000;
    
    Graph &g = reader.getGraph();
    cerr<<"Graph read \n";    
    Heuristic *h;
    string heurString = "NONE";
    switch(heuristicType) {
    case Heuristic::SMALL:
    	h = new SmallestPartHeuristic();
    	heurString = "SMALL";
    	break;
    case Heuristic::GREEDY:
        h = new GreedyHeuristic();
        heurString = "GREEDY";
        break;
    
    case Heuristic::CCF:
    	h = new CCFHeuristic();
    	heurString = "CCF";
    	break;
    
    case Heuristic::BBIG:
        highDegree = 1.5*(g.numOfEdges()/(float)g.numOfVertices());
        h = new BalancedBigHeuristic(highDegree);
        heurString = "BBIG";
        break;
    case Heuristic::RAND:
        h = new RandomPartHeuristic();
        heurString = "RAND";
        break;
    case Heuristic::PBIG:
        highDegree = 1.5*(g.numOfEdges()/(float)g.numOfVertices());
        h = new PreferBigHeuristic(highDegree, bufferSize);
        heurString = "PBIG";
        break;

    default: cerr<<"Invalid heuristic type"<<endl;
    }

    Partitioner pr(numOfPartitions, g.numOfVertices(), WeightScheme(wscheme - 1));
    cerr<<"Calling heuristic "<<heurString<<" with weight scheme "<<wscheme<<" and stream order "<<stream_order<<endl;
    
    if (stream_order == 1)
        stream_default(g, pr, h);
    else if (stream_order == 2)
        stream_bfs(g, pr, h);
    else if (stream_order == 3)
        stream_dfs(g, pr, h);
    if (stream_order == 4)
        stream_random(g, pr, h);

    cerr<<"Done"<<endl;
    return 0;
}

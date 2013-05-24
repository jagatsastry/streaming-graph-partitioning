#include"dep/Graph.h"
#include"dep/InputReader.h"
#include<fstream>
#include<utility>
#include <map>
#include <stdlib.h>
#include<climits>
#include<cmath>
#include<algorithm>
#include<unistd.h>

using namespace std;

class PartitionEvaluator {
    Graph m_g;
    vector<long> m_partitionIndex;
    vector<pair<long, long> > m_cutEdges;
    map<int, long> partition_size;

    public:
    PartitionEvaluator(char* graphFile, char* partitionFile);
    int evaluate();
    long long runFloydWarshal();

    void printInfo();
    int numCutEdges() {
    	return m_cutEdges.size()/2;
    }
    void evaluateBalance();
};

PartitionEvaluator::PartitionEvaluator(char* graphFile, char* partitionFile) : m_g(InputReader(graphFile).getGraph()){
    InputReader ir(graphFile);
    m_g = ir.getGraph();
    long n = m_g.numOfVertices();
    int maxPartitionIndex = -1;
    ifstream in(partitionFile);
    m_partitionIndex = vector<long>(n+1);
    for(int i = 1; i <= n; i++) {
        in>>m_partitionIndex[i];
        partition_size[m_partitionIndex[i]]++;
    }
}



long long PartitionEvaluator::runFloydWarshal() {
    int n = m_g.numOfVertices();
    long long simulatedTime = 0;
    for(int i = 1; i <= n; i++) {
        vector<long>& nb = m_g.getNeighbors(i);
        for(int j = 0; j < nb.size(); j++)
            if(m_partitionIndex[i] != m_partitionIndex[nb[j]]) simulatedTime+=100;
            else simulatedTime++;
    }
    return simulatedTime;
}

int PartitionEvaluator::evaluate() {
    int n = m_g.numOfVertices();
    for(int i = 1; i <= n; i++) {
       vector<long>& nb = m_g.getNeighbors(i);
       for(int j = 0; j < nb.size(); j++) {
           if(m_partitionIndex[i] != m_partitionIndex[nb[j]]) {
               m_cutEdges.push_back(make_pair(i, nb[j]));
           }
       }
    }
    return m_cutEdges.size()/2;
}

void PartitionEvaluator::printInfo() {
    cout<<"Number of cut edges: "<<m_cutEdges.size()/2<<endl;
    for(int i = 0; i < m_cutEdges.size(); i++) 
        cout<<m_cutEdges[i].first<<"  "<<m_cutEdges[i].second<<endl;
}

void PartitionEvaluator::evaluateBalance(){
    long n = m_g.numOfVertices();
    int numOfPartitions = partition_size.size();
    int avg = n/numOfPartitions;
    cout<<"Ideal no. of vertices per partition: "<<avg<<endl;
    long variance = 0;
    for(map<int, long>::iterator iter = partition_size.begin(); iter != partition_size.end(); iter++){
        variance += abs(iter->second - avg);
    }
    cout<<"Overall imbalance: "<<variance<<endl;
}

int main(int argc, char* argv[]) {
    if(argc <= 2) {
        cout<<"Args: <GraphFile> <PartitionFile>"<<endl;
        return 1;
    }

    char* graphFile = argv[1];
    char* partFile = argv[2];
    PartitionEvaluator eval(graphFile, partFile);
    //eval.evaluate();
    cout<<"Number of cut edges: "<<eval.evaluate()<<endl;
    if(argc > 3)
    	cout<<"All-pairs shortest path simulated time "<<eval.runFloydWarshal()<<endl;
    //eval.printInfo();
    eval.evaluateBalance();
    return 0;
}


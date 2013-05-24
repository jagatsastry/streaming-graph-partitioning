#!/bin/bash
#Input Graph file
#Run through all the heuristics, weight schemes and evaluate partitions for kkt
echo "Weighting scheme (1:Unw, 2:Lin(default), 3:Exp)"
echo "Heuristic type: 1:Small, 2:Greedy, 3:CCF 4:BBig 5:PBIG"
echo "Stream order: 1: Stream_Default, 2: Stream_BFS, 3: Stream_DFS 4:Random"

if [ "$1" = "" ] ; then
 echo "Argument : Input graph file required"
 exit 1
fi

GRAPH_FILE=$1 #"../grapheval/kkt_graph_und"
METIS=$2
OUT_DIR=$HOME/grapheval
NUM_PARTS=4
mkdir -p $OUT_DIR

echo "Given graph: $GRAPH_FILE"
./PartitionEvaluator $GRAPH_FILE  $METIS 1


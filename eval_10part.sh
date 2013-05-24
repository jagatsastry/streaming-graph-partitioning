#!/bin/bash
#Input Graph file
#Run through all the heuristics, weight schemes and evaluate partitions for kkt
echo "Weighting scheme (1:Unw, 2:Lin(default), 3:Exp)"
echo "Heuristic type: 1:Small, 2:Greedy, 3:CCF 4:BBig"

if [ "$1" = "" ] ; then
 echo "Argument : Input graph file required"
 exit 1
fi

GRAPH_FILE=$1 #"../grapheval/kkt_graph_und"
OUT_DIR=$HOME/grapheval
mkdir -p $OUT_DIR

echo "Given graph: $GRAPH_FILE"

graphfile=$(basename $GRAPH_FILE)
for weight in 2 3 ; do
    for heur in 1 2 3 4 ; do
        echo "Heuristic $heur, Weight $weight"
        ./testHeuristic $heur 4 $weight < $GRAPH_FILE > $OUT_DIR/"$graphfile"_heur_"$heur"_weight_"$weight"
        ./PartitionEvaluator $GRAPH_FILE $OUT_DIR/"$graphfile"_heur_"$heur"_weight_"$weight"
        echo
    done
done

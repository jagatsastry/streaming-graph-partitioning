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
OUT_DIR=$HOME/grapheval
NUM_PARTS=4
mkdir -p $OUT_DIR

echo "Given graph: $GRAPH_FILE"

graphfile=$(basename $GRAPH_FILE)
for heur in 2 3 4 1 ; do
	for weight in 2 3; do
        for stream_order in 2 3 ; do
                if [ $heur -eq 4 -o $heur -eq 1 ] ; then
                    if [ $weight -eq 3 ] ; then
                        continue 
                    fi
                fi
#for stream_order in 2; do
#	for weight in 3; do
#    		for heur in 2 ; do
        		echo "Heuristic $heur, Weight $weight, Stream order $stream_order"
        		./testHeuristic $heur $NUM_PARTS $stream_order $weight< $GRAPH_FILE > $OUT_DIR/"$graphfile"_heur_"$heur"_weight_"$weight"_stream_order_"$stream_order"
        		./PartitionEvaluator $GRAPH_FILE $OUT_DIR/"$graphfile"_heur_"$heur"_weight_"$weight"_stream_order_"$stream_order" 1
        		echo
    		done
        if [ $stream_order -eq 2 ] ; then
            mv bfs_op "$GRAPH_FILE".bfs
            echo "File $GRAPH_FILE.bfs generated"
        elif [ $stream_order -eq 3 ] ; then
            mv dfs_op "$GRAPH_FILE".dfs
            echo "File "$GRAPH_FILE".dfs generated"
        elif [ $stream_order -eq 4 ] ; then
            mv random_op "$GRAPH_FILE".random
            echo "File $GRAPH_FILE.random generated"
        fi
	done

done

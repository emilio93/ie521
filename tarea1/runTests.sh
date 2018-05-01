#!/bin/bash

rm results.csv 2> /dev/null
touch results.csv
echo "Identificador,Cache Size(KB),Cache Associativity,Cache Block Size(bytes),Miss penalty(cyc),Cache replacement policy,Execution time(cycles),instructions,Memory accesses,Overall miss rate,Read miss rate,Average memory access time (cycles),Dirty evictions,Load misses,Store misses,Total misses,Load hits,Store hits,Total hits,CPI\
" > results.csv

for trace in ./data/*.gz; do
    echo " "
    echo "-------------- ${trace} --------------"
    echo " "

    ## Sim 1
    echo " "
    echo "-------------- SIM 1 --------------"
    echo " "

    declare -a tamanoCache=("16" "32" "128")
    declare -a cycleMult=("1" "1.05" "1.15")

    cacheBlockSize=16
    missPenalty=5
    cacheRP="LRU"
    cacheAssoc=1

    TEMPFILE=/tmp/$$.tmp
    echo 0 > $TEMPFILE
    COUNTER=$[$(cat $TEMPFILE)]
    for i in "${tamanoCache[@]}"
    do
        echo ./cache -t ${i} -a ${cacheAssoc} -l ${cacheBlockSize} -mp ${missPenalty} -rp ${cacheRP} -f ${trace} -c ${cycleMult[$COUNTER]}
        ./cache -t ${i} -a ${cacheAssoc} -l ${cacheBlockSize} -mp ${missPenalty} -rp ${cacheRP} -f ${trace} -c ${cycleMult[$COUNTER]}
        echo "----------------------------"
        COUNTER=$[$(cat $TEMPFILE) + 1]
        echo $COUNTER > $TEMPFILE
    done
    unlink $TEMPFILE

    ## Sim 2

    echo " "
    echo "-------------- SIM 2 --------------"
    echo " "

    declare -a tamanoBloque=("16" "32" "64")
    declare -a missPenalty=(1 2 6)

    cacheSize=16
    cacheRP="LRU"
    cacheAssoc=1

    TEMPFILE=/tmp/$$.tmp
    echo 0 > $TEMPFILE
    COUNTER=$[$(cat $TEMPFILE)]
    for i in "${tamanoBloque[@]}"
    do
        echo ./cache -t ${cacheSize} -a ${cacheAssoc} -l ${i} -mp ${missPenalty[$COUNTER]} -rp ${cacheRP} -f ${trace}
        ./cache -t ${cacheSize} -a ${cacheAssoc} -l ${i} -mp ${missPenalty[$COUNTER]} -rp ${cacheRP} -f ${trace}
        echo "----------------------------"
        COUNTER=$[$(cat $TEMPFILE) + 1]
        echo $COUNTER > $TEMPFILE
    done
    unlink $TEMPFILE


    ## Sim 3

    echo " "
    echo "-------------- SIM 3 --------------"
    echo " "

    declare -a cacheRP=("LRU" "NRU" "SRRIP" "random")

    declare -a cacheAssoc=(2 4 8 16)
    declare -a cycleMult=(1.04 1.06 1.08 1.16)

    tamanoBloque=16
    cacheSize=16
    missPenalty=5

    for i in "${cacheRP[@]}"
    do
        TEMPFILE=/tmp/$$.tmp
        echo 0 > $TEMPFILE
        COUNTER=$[$(cat $TEMPFILE)]
        for j in "${cacheAssoc[@]}"
        do
            echo ./cache -t ${cacheSize} -a ${j} -l ${tamanoBloque} -mp ${missPenalty} -rp ${i} -f ${trace} -c ${cycleMult[$COUNTER]}
            ./cache -t ${cacheSize} -a ${j} -l ${tamanoBloque} -mp ${missPenalty} -rp ${i} -f ${trace} -c ${cycleMult[$COUNTER]}
            echo "----------------------------"
            COUNTER=$[$(cat $TEMPFILE) + 1]
            echo $COUNTER > $TEMPFILE
        done
        unlink $TEMPFILE
    done

done

# Create a back up of the results
# as results file might be modified
today=`date +%Y-%m-%d.%H:%M:%S`
cp results.csv results.${today}.csv

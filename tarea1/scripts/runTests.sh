#!/bin/bash

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
    printCsv=1
    cacheAssoc=1

    TEMPFILE=/tmp/$$.tmp
    echo 0 > $TEMPFILE
    COUNTER=$[$(cat $TEMPFILE)]
    for i in "${tamanoCache[@]}"
    do
        echo ./cache -t ${i} -a ${cacheAssoc} -l ${cacheBlockSize} -mp ${missPenalty} -rp ${cacheRP} -f ${trace} -c ${cycleMult[$COUNTER]} -print-csv ${printCsv}
        ./cache -t ${i} -a ${cacheAssoc} -l ${cacheBlockSize} -mp ${missPenalty} -rp ${cacheRP} -f ${trace} -c ${cycleMult[$COUNTER]} -print-csv ${printCsv}
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
    printCsv=1
    cacheAssoc=1

    TEMPFILE=/tmp/$$.tmp
    echo 0 > $TEMPFILE
    COUNTER=$[$(cat $TEMPFILE)]
    for i in "${tamanoBloque[@]}"
    do
        echo ./cache -t ${cacheSize} -a ${cacheAssoc} -l ${i} -mp ${missPenalty[$COUNTER]} -rp ${cacheRP} -f ${trace} -print-csv ${printCsv}
        ./cache -t ${cacheSize} -a ${cacheAssoc} -l ${i} -mp ${missPenalty[$COUNTER]} -rp ${cacheRP} -f ${trace} -print-csv ${printCsv}
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
    printCsv=1
    missPenalty=5

    for i in "${cacheRP[@]}"
    do
        TEMPFILE=/tmp/$$.tmp
        echo 0 > $TEMPFILE
        COUNTER=$[$(cat $TEMPFILE)]
        for j in "${cacheAssoc[@]}"
        do
            echo ./cache -t ${cacheSize} -a ${j} -l ${tamanoBloque} -mp ${missPenalty} -rp ${i} -f ${trace} -c ${cycleMult[$COUNTER]} -print-csv ${printCsv}
            ./cache -t ${cacheSize} -a ${j} -l ${tamanoBloque} -mp ${missPenalty} -rp ${i} -f ${trace} -c ${cycleMult[$COUNTER]} -print-csv ${printCsv}
            echo "----------------------------"
            COUNTER=$[$(cat $TEMPFILE) + 1]
            echo $COUNTER > $TEMPFILE
        done
        unlink $TEMPFILE
    done

done

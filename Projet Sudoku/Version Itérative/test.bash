#!/bin/bash
# Code pour executer plusieurs résolutions de sudoku
# Vérifier si les arguments sont passés
if [ "$#" -ne 3 ]; then
    echo "Usage: $0 <n> <arg1> <arg2>"
    exit 1
fi

n=$1
arg1=$2
arg2=$3

# Boucle pour exécuter la commande n fois
for ((i=0; i<n; i++))
do
     echo "Progress: $i / $n"
    ./main "$arg1" 3 0 >> "./Tests/$arg2.txt"
done

# use : ./test.bash 10 sudokuList.txt a.txt num_thread

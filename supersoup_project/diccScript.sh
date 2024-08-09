#!/bin/bash
program1="diccSortedVector"
program2="diccTrie"
program3="diccBloomFilter"
program4="diccDHashing"

for f in ./samplesRandomK/*
do
    echo 
    echo "------------------"
    echo $f
    echo
    echo "Ejecutando $program1: "
    $program1 < $f > salSopa
    egrep "inicialización" salSopa
    egrep "backtracking" salSopa
    egrep "total" salSopa
    egrep "llamadas" salSopa
    egrep "Palabras" salSopa
    echo " "
    echo "Ejecutando $program2: "
    $program2 < $f > salSopa
    egrep "inicialización" salSopa
    egrep "backtracking" salSopa
    egrep "total" salSopa
    egrep "llamadas" salSopa
    egrep "Palabras" salSopa
    echo " "
    echo "Ejecutando $program3: "
    $program3 < $f > salSopa
    egrep "inicialización" salSopa
    egrep "backtracking" salSopa
    egrep "total" salSopa
    egrep "llamadas" salSopa
    egrep "Palabras" salSopa
    echo " "
    echo "Ejecutando $program4: "
    $program4 < $f > salSopa
    egrep "inicialización" salSopa
    egrep "backtracking" salSopa
    egrep "total" salSopa
    egrep "llamadas" salSopa
    egrep "Palabras" salSopa
    echo " "
done
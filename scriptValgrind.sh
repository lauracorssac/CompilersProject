#!/bin/bash

SUCCESS=0
make
v=0


for file in teste/*
do
    echo "TEST FILE $file"
    [[ $file != *.ref.dot ]] || continue
    echo "$file passou"
    
    valgrind ./etapa3 < $file > saida
    
    echo oooooiiii "$(wc -l < saida)"-"$(wc -l < "$file".ref.dot)"

done

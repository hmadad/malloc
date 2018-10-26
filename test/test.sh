#!/bin/bash

FLAGS="-Werror -Wall -Wextra -O3"
nbr=0
while ((nbr<5))
do
	gcc $FLAGS -o test0$nbr src/test0$nbr.c
	((nbr+=1))
done

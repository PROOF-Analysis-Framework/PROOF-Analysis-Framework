#!/bin/bash

for i in 1 2 4 6 10 15 20 30 40 50; do
	sed -e s/%NODES%/$i/g RunScript.C.template > RunScript.C
	for j in {1..10}; do	
		root -l -b -q RunScript.C > Salida-$i-$j.txt
	done
done


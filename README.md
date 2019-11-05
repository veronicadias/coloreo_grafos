#Proyecto de Matematica Discreta 2

##Integrantes
Dias Veronica. 
Salgado Romina. 
Godoy Anahí Rocío. 

##Compilar
gcc -IWahlaan -Wall -Wextra -O3 -std=c99 coloreo.c main.c -o main

##Ejecutar
./main < "_nombre de archivo_"

##Testear
gcc -IWahlaan -Wall -Wextra -O3 -std=c99 coloreo.c test.c -o test
./test < "_nombre de archivo_"

##Valgrind
valgrind --leak-check=yes --show-reachable=yes ./test < "_nombre de archivo_"


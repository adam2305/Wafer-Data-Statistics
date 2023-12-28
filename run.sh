#!/bin/bash


echo "Veuillez Écrire dans ReadData.h les chemins des dossiers 'training' et 'output' et mettre le chemin devant les noms"
sleep 2.5
printf "\e[8;52;127;t"
command1="gedit readData.h"
command="make main > /dev/null && ./main"
eval $command1
eval $command

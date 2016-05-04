/**
* Joc interactiu de la granota.
*/
#include <conio.h>      /* getch */ 
#include <stdio.h>      /* printf */
#include <time.h>   /* time */ 
#include <Windows.h>
#include "lib\Grafic.h"
 

//========================================================================
// Inici del taulell respecte la cantonada superior esquerre
const int INICI_X = 0; //TODO els cotxes comencen aqui
const int INICI_Y = 80;

//========================================================================
// Fi del taulell respecte la cantonada superior esquerre
const int FI_X = 600; //TODO els cotxes arriben fins aquí
const int FI_Y = 450;

//========================================================================
//Constant per desplaçament dels vehicles
const int DESPLACAMENT_VEHICLE = 1;

//Temps màxim per a accedir a una cova
const int TEMPS_MAXIM = 20;

//========================================================================
// Desplaçament inicial de la granota respecte al final del taulell
const int INICI_Y_GRANOTA = FI_Y + 5;

//========================================================================
// nº de píxels que es desplaça la granota a cada moviment
const int DESPLACAMENT_GRANOTA = 2;

int juga(int nivell);

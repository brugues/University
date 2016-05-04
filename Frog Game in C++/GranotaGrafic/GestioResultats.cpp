#include "GestioResultats.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

void iniciaTaulaMillorJugadors(TipusJugador TMillorsJugadors[])
{
	int i;
	for (i = 0; i < MAX_MILLORSJUGADORS; i++)
	{
		strcpy_s(TMillorsJugadors[i].nom, "--------------");
		TMillorsJugadors[i].puntuacio = 0;
	}
}

int haMilloratPuntuacio(TipusJugador TMillorsJugadors[], int punts)
{
	int i = 0;
	int trobat = 0;

	do
	{
		if (TMillorsJugadors[i].puntuacio <= punts)
		{
			trobat = 1;
		}
		i++;

	} while ((i < MAX_MILLORSJUGADORS) && (!trobat));
	if (trobat==1)
	{
		return (i - 1);
	}
	else
	{
		return -1;
	}
}

void desplacaArray(TipusJugador TMillorsJugadors[], int posicio)
{
	int i;

	for (i = MAX_MILLORSJUGADORS - 1; i > posicio; i--)
	{
		strcpy_s(TMillorsJugadors[i].nom, TMillorsJugadors[i - 1].nom);
		TMillorsJugadors[i].puntuacio = TMillorsJugadors[i - 1].puntuacio;
	}
}

void emplenaPosicioArray(TipusJugador &TMillorsJugadors, int punts)
{
	printf("Entra el teu nom\n");
	scanf_s("%s", &(TMillorsJugadors.nom));
	(TMillorsJugadors).puntuacio = punts;
}

void escriuRanking(TipusJugador TMillorsJugadors[])
{
	int i;
	for (i = 0; i < MAX_MILLORSJUGADORS; i++)
	{
		printf("%d.- %s %d\n", i + 1, TMillorsJugadors[i].nom, TMillorsJugadors[i].puntuacio);
	}
}

int lecturaPuntuacio(TipusJugador jugadors[])
{
	ifstream fitxer;
	fitxer.open("Puntuacions.txt"); 
	int nJugadors = 0; 
	if (fitxer.is_open())
	{
		char nom[MAX_NOM];
		int puntuacio;
		fitxer >> nom >> puntuacio;
		while (!fitxer.eof())
		{
			strcpy_s(jugadors[nJugadors].nom, nom);
			jugadors[nJugadors].puntuacio = puntuacio;
			nJugadors++;
			fitxer >> nom >> puntuacio;
		}
	}
	fitxer.close();

	return nJugadors;
}


void escriuPuntuacions(TipusJugador jugadors[], int nJugadors) 
{ 
	ofstream fitxer; 
	fitxer.open("Puntuacions.txt"); 

	if (fitxer.is_open())
	{
		for (int i = 0; i < nJugadors; i++)
			fitxer << jugadors[i].nom << " " << jugadors[i].puntuacio << "\n";
	}
	fitxer.close();
}

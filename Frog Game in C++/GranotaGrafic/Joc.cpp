#include "Joc.h"
#include "lib\libreria.h" 
#include "lib\event.h"
#include "lib\Grafic.h"
#include <iostream>
#include "Pantalla.h"
#include <Windows.h>
#include <time.h> 

using namespace std;

/**
 * Juga una partida de tres vides
 * @param nivell nivell de la partida
 * @return
 */
int juga(int nivell)
{
	// Inicialitzacions necessàries
	t_programStatus estat;
	InitGame(estat);
	
	// Inicialització de variables relacionades amb les vides de la granota
	int vides = 3; // Variable que estableix les vides inicials de la granota
	// Variable que guarda els punts aconseguits pel jugador. 
	int punts = 0; // L'inicialitzem a 0.

	bool esDinsCova = false;
	bool nivellSuperat = false;

	// Mostra el temps per pantalla i dibuixa els gràfics corresponents
	// Actualització de les variables temporals. (Càlcul del temps que portem jugant)
	time_t t;
	time_t t_it; // Agafa el temps actual
	time_t t_max; // Agafa el temps actual. Utilitzat pel comptador que va enrere.
	int t_dif;
	int t_dif_enrere;

	// Inicialitza l'objecte pantalla
	Pantalla pantalla;

	// Dibuixa la pantalla segons el nivell
	Video_ShowWindow();	// Mostrem la finestra

	do{	
		t = time(0);
		pantalla.inicia(nivell);

		do{

			pantalla.iniciaPosicioGranota();
			t_max = time(0) + TEMPS_MAXIM;

			do{
				t_it = time(0);
				t_dif = t_it - t; // La diferències entre el temps actual i el temps jugat EN SEGONS
				t_dif_enrere = t_max - t_it;
				pantalla.dibuixa(t_dif, t_dif_enrere, vides, nivell, punts); // Dibuixa tots els gràfics de la pantalla
				VideoUpdate(estat);	// Actualització dels gràfics del joc				
				ProcessEvents(estat); // Captura els events que s'han produit en el darrer cicle

				if (Keyboard_GetKeyTrg(KEYBOARD_LEFT))
					pantalla.mouGranota(ESQUERRA);
				if (Keyboard_GetKeyTrg(KEYBOARD_RIGHT))
					pantalla.mouGranota(DRETA);
				if (Keyboard_GetKeyTrg(KEYBOARD_UP))
					pantalla.mouGranota(AMUNT);
				if (Keyboard_GetKeyTrg(KEYBOARD_DOWN))
					pantalla.mouGranota(AVALL);

				pantalla.mouVehicles();	// Mobilitat dels vehicles
				pantalla.haAgafatObstacle(punts);

			} while (((!pantalla.esGranotaDinsCova()) && (!pantalla.haMortLaGranota()) && (!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE)) && (!estat.bExit) && (t_dif_enrere > 0)));

			if (pantalla.esGranotaDinsCova())
				nivellSuperat = pantalla.nivellSuperat();
			else
				vides--;

			if (nivellSuperat)
			{
				punts = punts + (100 * nivell);
				nivell++;
			}

		} while ((!nivellSuperat) && (vides > 0) && (!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE)) && (!estat.bExit));


	} while ((!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE)) && (!estat.bExit) && (vides > 0) && (nivell < 4));

	Video_Release();
	return punts;
}
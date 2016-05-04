
#include "Menu.h"
#include "Joc.h"
#include "GestioResultats.h"
#include <iostream>

#define OPCIO_JUGAR '1'
#define OPCIO_CONFIGURAR '2'
#define OPCIO_PUNTUACIO '3'
#define OPCIO_SORTIR '4'
const int NUM_JUGADORS = 5;


/**
 * Programa principal que permet jugar al joc de la granota (frog) desant puntuacions
 * @return
 */
int main()
{
	char opcio;
	int punts = 0;
	int posicio = -1;
	char nivell = '1';
	TipusJugador millorsJugadors[MAX_MILLORSJUGADORS];
	iniciaTaulaMillorJugadors(millorsJugadors);
	lecturaPuntuacio(millorsJugadors);

	do
	{
		mostraMenuPrincipal();
		opcio = _getch(); // Llegeix tecla apretada
		switch (opcio)
		{
		case OPCIO_JUGAR:
				nivell = nivell - '0';
				punts = juga(nivell); // COMPTE!: aquí hi ha una conversió de char a int
				nivell = '1';
				posicio = haMilloratPuntuacio(millorsJugadors, punts);
				if (posicio >= 0) // Ha millorat puntuacio
				{
					desplacaArray(millorsJugadors, posicio);
					emplenaPosicioArray(millorsJugadors[posicio], punts);
				}
				break;
		case OPCIO_CONFIGURAR:
				mostraMenuNivellDificultat();
				do
				{
					nivell = _getch(); // Llegeix tecla apretada
					if ((nivell != '1') && (nivell != '2') && (nivell != '3')) // Comprova si tecla es valida
					{
						printf("Opcio incorrecta.\n"); // Mostra text
					}
				} while ((nivell != '1') && (nivell != '2') && (nivell != '3')); // Repeteix mentre tecla no valida
				break;
			case OPCIO_PUNTUACIO:
				escriuRanking(millorsJugadors);
				printf("Prem una tecla per tornar al menu principal\n");
				_getch(); // Llegeix tecla apretada
				break;
		}
	} while (opcio != OPCIO_SORTIR);

	//escriuPuntuacions(millorsJugadors, NUM_JUGADORS);

	return punts;
}

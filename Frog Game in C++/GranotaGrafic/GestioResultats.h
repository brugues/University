const int  MAX_NOM = 15;

typedef struct
{
	char nom[15];
	int puntuacio;
} TipusJugador;

const int  MAX_MILLORSJUGADORS = 5;


void iniciaTaulaMillorJugadors(TipusJugador TMillorsJugadors[]);
int haMilloratPuntuacio(TipusJugador TMillorsJugadors[], int punts);
void desplacaArray(TipusJugador TMillorsJugadors[], int posicio);
void emplenaPosicioArray(TipusJugador &TMillorsJugadors, int punts);
void escriuRanking(TipusJugador TMillorsJugadors[]);

int lecturaPuntuacio(TipusJugador jugadors[]);
void deixaPuntuacio(TipusJugador jugadors[], int nJugadors);
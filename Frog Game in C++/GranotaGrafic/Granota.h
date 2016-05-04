#pragma once
#include "Area.h"
#include "lib\Grafic.h"

// nº de píxels que es desplaça la granota a cada moviment
#define DESPLACAMENT_GRANOTA  15

//Comptador per a canviar l'estat de la granota
const int TEMPS_MOVIMENT_GRANOTA = 3;

//Constanst de moviments
typedef enum{ AMUNT, AVALL, DRETA, ESQUERRA };
const int TOTAL_MOV = 4;

typedef enum {REP, MOV};
const int TOTAL_EST = 2;

class Granota
{
public:
	Granota();
	Granota(Grafic grafic[][TOTAL_EST], int posicioInicialX, int posicioInicialY);
	~Granota();
	Area getAreaOcupada();
	void dibuixa();
	void mouAmunt();
	void mouAvall();
	void mouDreta();
	void mouEsquerra();
	void mouAPosicioInicial();

private:
	Grafic m_grafic[TOTAL_MOV][TOTAL_EST];
	int m_posicioX;
	int m_posicioY;
	int m_posicioInicialX;
	int m_posicioInicialY;
	int m_moviment;
	int m_estat;
	int m_contador;
};


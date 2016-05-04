#pragma once
#include "Area.h"
#include "lib\Grafic.h"

typedef enum {MONEDA, ESCUT, ICEBERG, RELLOTGE, TORTUGA, TRESOR};
const int NUM_MAX_OBSTACLES = 6;
const int NUM_OBSTACLES = 2;

typedef enum {RES, PETITA, GRAN};
const int PUNTUACIO_RES = 0;
const int PUNTUACIO_PETITA = 100;
const int PUNTUACIO_GRAN = 500;

const int OBSTACLE_PUNTUACIO_PETITA = 0;
const int OBSTACLE_PUNTUACIO_GRAN = 5;

class Obstacle
{
public:
	Obstacle();
	Obstacle(Grafic grafic, int puntuacio, int posX, int posY);
	~Obstacle();

	void dibuixa();
	int getPuntuacio() const;
	Area getAreaOcupada();
	void setAgafat(bool agafat);
	bool getAgafat() const;

private:
	int m_puntuacio;
	int m_posX;
	int m_posY;
	bool m_agafat;
	Grafic m_grafic;
};
#pragma once
#include "Area.h"
#include "lib\Grafic.h"
#include "Cova.h"
#include "Vehicle.h"
#include "Granota.h"
#include "Carril.h"
#include "Cronometre.h"
#include "Obstacle.h"

// Inici del taulell respecte la cantonada superior esquerre
#define INICI_X  0
#define INICI_Y  0

// Fi del taulell respecte la cantonada superior esquerre
#define FI_X  600
#define FI_Y  450

// Constants relacionades amb el joc
const int NUM_VEHICLES = 5;
const int NUM_CARRILS = 5;
const int NUM_COVES = 5;

// Constants relacionades amb posicions d'objectes que mostren informació de la sessió de joc
const int MARGE_VIDES = 2;
const int MARGEX_VIDES = 5;
const int POSY_VIDES = 470;
const int POSX_NIVELL = 585;
const int POSY_NIVELL = 460;
const int POSY_PUNTS = 490;
const int POSX_TEXTNIVELL = 525;
const int POSX_TEXTPUNTS = 480;
const int POSX_TEMPSJUGAT = 420;
const int POSX_TEMPSRESTANT = 220;
const int POSX_MILERS_PUNTS = 540;
const int POSX_CENTENES_PUNTS = 555;
const int POSX_DESENES_PUNTS = 570;
const int POSX_UNITATS_PUNTS = 585;

//========================================================================
//Posició dels cronòmetres
const int RELOJ_X = FI_X - 15;
const int RELOJ_Y = FI_Y + 70;

const int RELOJ_ENRERE_X = POSX_TEMPSJUGAT - 25;
const int RELOJ_ENRERE_Y = RELOJ_Y;

const int AMPLADA_COVA = 120;

class Pantalla
{
public:
	Pantalla();
	~Pantalla();
	void inicia(int nivell);
	void dibuixa(int& t_dif, int& t_dif_enrere, int vides, int nivell, int punts);
	void mouGranota(int direccio);
	bool esGranotaDinsCova();
	void mouVehicles();
	bool haMortLaGranota();
	void iniciaPosicioGranota();
	bool nivellSuperat();
	void dibuixaNumero(int numero, int posX, int posY);
	void haAgafatObstacle(int &punts);

private:
	Grafic m_graficFons;
	Grafic m_graficCova;
	Grafic m_nivellText;
	Grafic m_puntsText;
	Grafic m_tempsRestant;
	Grafic m_tempsJugat;
	Grafic m_graficGranota[TOTAL_MOV][TOTAL_EST];
	Grafic m_graficVehicle[NUM_VEHICLES];
	Grafic m_graficNumero[TOTAL_DIGITOS];
	Grafic* m_graficObstacle;
	Obstacle* m_obstacle;
	Carril m_carril[NUM_CARRILS];
	Area m_areaTotal;
	Cova m_cova[NUM_COVES];
	Granota m_granota;
	Granota m_granotaAuxiliar;
	Cronometre m_cronometre;
	Cronometre m_cronometre_enrere;
	int m_iniciCarrilsY;
	int m_nCarrils;
	int m_nObstacles;
	bool espaiPermes(Area area);
};
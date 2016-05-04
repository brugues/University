#include "Pantalla.h"
#include <cstdlib>
#include <ctime>


/**
 * Constructor de la Pantalla.
 * Aquesta pantalla té una sola cova imaginària ja que no té parets.
 */
Pantalla::Pantalla()
{
	// Carreguem els components gràfics a fer servir.
	m_graficFons.crea("data/GraficsGranota/Fons.png");
	m_graficCova.crea("data/GraficsGranota/Cova120.png");
	m_nivellText.crea("data/text/nivell.png");
	m_puntsText.crea("data/text/punts.png");
	m_tempsJugat.crea("data/text/tempsjugat.png");
	m_tempsRestant.crea("data/text/tempsrestant.png");

	m_graficVehicle[0].crea("data/GraficsGranota/Cotxe_1.png");
	m_graficVehicle[1].crea("data/GraficsGranota/Cotxe_2.png");
	m_graficVehicle[2].crea("data/GraficsGranota/Camio.png");
	m_graficVehicle[3].crea("data/GraficsGranota/Tractor.png");
	m_graficVehicle[4].crea("data/GraficsGranota/Cotxe_3.png");

	m_graficGranota[AMUNT][REP].crea("data/GraficsGranota/Granota_Amunt_1.png");
	m_graficGranota[AMUNT][MOV].crea("data/GraficsGranota/Granota_Amunt_2.png");
	m_graficGranota[AVALL][REP].crea("data/GraficsGranota/Granota_Avall_1.png");
	m_graficGranota[AVALL][MOV].crea("data/GraficsGranota/Granota_Avall_2.png");
	m_graficGranota[ESQUERRA][REP].crea("data/GraficsGranota/Granota_Esquerra_1.png");
	m_graficGranota[ESQUERRA][MOV].crea("data/GraficsGranota/Granota_Esquerra_2.png");
	m_graficGranota[DRETA][REP].crea("data/GraficsGranota/Granota_Dreta_1.png");
	m_graficGranota[DRETA][MOV].crea("data/GraficsGranota/Granota_Dreta_2.png");

	m_graficNumero[0].crea("data/numeros/numero0000.png");
	m_graficNumero[1].crea("data/numeros/numero0001.png");
	m_graficNumero[2].crea("data/numeros/numero0002.png");
	m_graficNumero[3].crea("data/numeros/numero0003.png");
	m_graficNumero[4].crea("data/numeros/numero0004.png");
	m_graficNumero[5].crea("data/numeros/numero0005.png");
	m_graficNumero[6].crea("data/numeros/numero0006.png");
	m_graficNumero[7].crea("data/numeros/numero0007.png");
	m_graficNumero[8].crea("data/numeros/numero0008.png");
	m_graficNumero[9].crea("data/numeros/numero0009.png");


	// Inicialitzem l'area total de la pantalla, així com l'espai pels carrils, el número de carrils i instanciem els objectes granota i cova.
	m_areaTotal = Area(INICI_X, FI_X, INICI_Y, FI_Y);
	m_iniciCarrilsY = INICI_Y + m_graficCova.getScaleY();
	m_nCarrils = (((FI_Y - m_graficGranota[AMUNT][MOV].getScaleY()) - m_iniciCarrilsY) / m_graficVehicle[0].getScaleY()) - 1;
	m_granota = Granota(m_graficGranota, (FI_X - INICI_X - m_graficGranota[AMUNT][REP].getScaleX()) / 2, FI_Y-m_graficGranota[AMUNT][REP].getScaleY());// FI_Y - m_graficGranotaAmunt.getScaleY());
	m_cronometre = Cronometre(m_graficNumero, RELOJ_X, RELOJ_Y);
	m_cronometre_enrere = Cronometre(m_graficNumero, RELOJ_ENRERE_X, RELOJ_ENRERE_Y);

	m_carril[0] = Carril(m_graficVehicle[0], 1, (m_iniciCarrilsY + 15), FI_X);
	m_carril[1] = Carril(m_graficVehicle[1], 1, (m_iniciCarrilsY + 15 + (3 * m_graficVehicle[0].getScaleY() / 2)), FI_X);
	m_carril[2] = Carril(m_graficVehicle[2], 1, (m_iniciCarrilsY + 15 + (6 * m_graficVehicle[0].getScaleY() / 2)), INICI_X);
	m_carril[3] = Carril(m_graficVehicle[3], 1, (m_iniciCarrilsY + 15 + (9 * m_graficVehicle[0].getScaleY() / 2)), INICI_X);
	m_carril[4] = Carril(m_graficVehicle[4], 1, (m_iniciCarrilsY + 15 + (12 * m_graficVehicle[0].getScaleY() / 2)), INICI_X);
}


/**
 * Destructor de la classe pantalla
 */
Pantalla::~Pantalla()
{
	int i;

	m_graficFons.destrueix();
	m_graficCova.destrueix();

	for (i = 0; i < TOTAL_MOV; i++)
	{
		for (int j = 0; j < TOTAL_EST; j++)
			m_graficGranota[i][j].destrueix();
	}

	for (i = 0; i < NUM_CARRILS; i++)
		m_graficVehicle[i].destrueix();

	for (i = 0; i < TOTAL_DIGITOS; i++)
		m_graficNumero[i].destrueix();

	delete[] m_graficObstacle;
	delete[] m_obstacle;
}


/**
 * Inicia la pantalla instanciant l'objecte vehicle i colocant la granota i el vehicle a la posició inicial.
 * @param nivell Nivell de la pantalla.
 */
void Pantalla::inicia(int nivell)
{	
	int i, j = 0;
	for (i = 0; i < NUM_COVES; i++)
	{
		m_cova[i] = Cova(m_graficCova, INICI_X + i * m_graficCova.getScaleX(), INICI_Y);
	}

	iniciaPosicioGranota();
	
	m_nObstacles = nivell*NUM_OBSTACLES;
	m_graficObstacle = new Grafic[m_nObstacles];
	m_obstacle = new Obstacle[m_nObstacles];

	// De moment, el mateix gràfic per tots els obstacles
	for (i = 0; i < m_nObstacles;i++)
		m_graficObstacle[i].crea("data/obstacles/moneda.png");

	/*m_graficObstacle[0].crea("data/obstacles/moneda.png");
	m_graficObstacle[1].crea("data/obstacles/escut.png");
	m_graficObstacle[2].crea("data/obstacles/gel.png");
	m_graficObstacle[3].crea("data/obstacles/rellotge.png");
	m_graficObstacle[4].crea("data/obstacles/tortuga.png");
	m_graficObstacle[5].crea("data/obstacles/tresor.png");*/

	int aux;
	bool solapat;

	for (i = 0; i < m_nObstacles; i++)
	{
		if (i == OBSTACLE_PUNTUACIO_PETITA)
			aux = PETITA;
		else
		{
			if (i == OBSTACLE_PUNTUACIO_GRAN)
				aux = GRAN;
			else
				aux = RES;
		}
		
		solapat = true;
		m_obstacle[i] = Obstacle(m_graficObstacle[i], aux, rand() % FI_X, rand() % (FI_Y + m_iniciCarrilsY));
		
		while ((j < (m_nObstacles - 1)) && (solapat))
		{
			if (i > 0)
			{
				solapat = (m_obstacle[i].getAreaOcupada().solapa(m_obstacle[j].getAreaOcupada()));

				if (solapat)
				{
					m_obstacle[i] = Obstacle(m_graficObstacle[i], aux, rand() % FI_X,
						rand() % (FI_Y + m_iniciCarrilsY));
					j = 0;
				}
				else
					j++;
			}
			else
				solapat = false;
		}
	}
}


/**
* Mou la granota a la seva posició inicial
*/
void Pantalla::iniciaPosicioGranota()
{
	m_granota.mouAPosicioInicial();
}


/**
 * Comprova si una àrea donada es troba dins la cova.
 * @param cova la cova que es vol mirar si hi ha entrat la granota
 * @return true si l'àrea es troba dins la cova i false si no s'hi troba. 
 */
bool Pantalla::esGranotaDinsCova()
{
	bool covaOcupada = false;

	for (int i = 0; i < NUM_COVES; i++)
	{
		if (m_cova[i].granotaEsDins(m_granota.getAreaOcupada()))
		{
			m_cova[i].setOcupada();
			covaOcupada = true;
		}
	}
	return covaOcupada;
}


/**
 * Comprova si una àrea donada es troba dins l'espai permès de moviment.
 * @param area Area a comprovar si es troba dins l'espai permès de moviment.
 * @return true si l'àrea es troba dins l'espai permès de moviment i false si no és així.
 */
bool Pantalla::espaiPermes(Area area)
{
	bool esAccessible = true;
	int i = 0;

	if (m_areaTotal.inclou(area))
	{
		while (i < NUM_COVES && (esAccessible))
		{
			esAccessible = (m_cova[i].esAccessible(area));
			i++;
		}
	}
	else
		esAccessible = false;

	return esAccessible;
}


/**
 * Dibuixa tots els elements gràfics a la posició on es troben.
 * @param t_dif diferència entre el temps d'inici del joc i el temps actual
 * @param vides vides que li queden al jugador
 */
void Pantalla::dibuixa(int& t_dif, int& t_dif_enrere, int vides, int nivell, int punts)
{
	int i = 0;
	// Variables utilitzades per a la impressió dels punts per pantalla.
	int m = 0, c = 0, d = 0, u = 0;

	m_graficFons.dibuixa(INICI_X, INICI_Y);	// Dibuixa el gràfic del fons de pantalla

	for (i = 0; i < NUM_COVES; i++)	// Dibuixa una granota al centre de les coves ocupades
	{
		m_cova[i].dibuixa();
		if (m_cova[i].esOcupada())
			m_graficGranota[AMUNT][REP].dibuixa((m_graficCova.getScaleX() / 2 - m_graficGranota[AMUNT][REP].getScaleX() / 2) + 
			i*m_graficCova.getScaleX(), m_graficCova.getScaleY() - m_graficGranota[AMUNT][REP].getScaleY());
	}

	m_granota.dibuixa();	// Dibuixa la granota

	for (i = 0; i < NUM_CARRILS; i++)	// Dibuixa cada un dels vehicles
		m_carril[i].dibuixaVehicle();

	for (i = 0; i < vides; i++)	// Dibuixa les vides restants a jugador
		m_graficGranota[AMUNT][MOV].dibuixa(i*m_graficGranota[AMUNT][MOV].getScaleX() + MARGE_VIDES * i + MARGEX_VIDES, POSY_VIDES);
	

	//Dibuixen els textos indicadors d'informació
	m_nivellText.dibuixa(POSX_TEXTNIVELL, POSY_NIVELL);
	m_puntsText.dibuixa(POSX_TEXTPUNTS, POSY_PUNTS);
	m_tempsJugat.dibuixa(POSX_TEMPSJUGAT, RELOJ_Y);
	m_tempsRestant.dibuixa(POSX_TEMPSRESTANT, RELOJ_Y);

	//Es dibuixen els punts
	if (punts < 1000)
	{
		//m = punts / 1000;
		c = punts / 100;
		d = ((punts - c * 100) / 10);
		u = punts - c * 100 - d * 10;
	}

	// Dibuix dels números del marcador de punts
	// dibuixaNumero(m, POSX_MILERS_PUNTS, POSY_PUNTS);
	dibuixaNumero(c, POSX_CENTENES_PUNTS, POSY_PUNTS);
	dibuixaNumero(d, POSX_DESENES_PUNTS, POSY_PUNTS);
	dibuixaNumero(u, POSX_UNITATS_PUNTS, POSY_PUNTS);
	dibuixaNumero(nivell, POSX_NIVELL, POSY_NIVELL);

	// Dibuix dels cronòmetres
	m_cronometre.dibuixa(t_dif);	// Dibuixa el crònometre, que mostra el temps que es porta jugant
	m_cronometre_enrere.dibuixa(t_dif_enrere);	// Dibuixa el cronòmetre que mostra el temps restant que té el jugador per entrar en una de les coves

	// Dibuix dels obstacles
	for (int i = 0; i < m_nObstacles; i++)
		m_obstacle[i].dibuixa();
}


/**
* Dibuixa per pantalla un numero passat per paràmetre
* @param numero numero que es vol dibuixar per pantalla
* @param posX posicio en l'eix de les X on es vol dibuixar el número
* @param posY posicio en l'eix de les Y on es vol dibuixar el número
*/
void Pantalla::dibuixaNumero(int numero, int posX, int posY)
{
	switch (numero)
	{
	case 0:
		m_graficNumero[0].dibuixa(posX, posY);
		break;
	case 1:
		m_graficNumero[1].dibuixa(posX, posY);
		break;
	case 2:
		m_graficNumero[2].dibuixa(posX, posY);
		break;
	case 3:
		m_graficNumero[3].dibuixa(posX, posY);
		break;
	case 4:
		m_graficNumero[4].dibuixa(posX, posY);
		break;
	case 5:
		m_graficNumero[5].dibuixa(posX, posY);
		break;
	case 6:
		m_graficNumero[6].dibuixa(posX, posY);
		break;
	case 7:
		m_graficNumero[7].dibuixa(posX, posY);
		break;
	case 8:
		m_graficNumero[8].dibuixa(posX, posY);
		break;
	case 9:
		m_graficNumero[9].dibuixa(posX, posY);
		break;
	}
}


/**
 * Mou els vehicles.
 */
void Pantalla::mouVehicles()
{
	for (int i = 0; i < NUM_CARRILS; i++)
		m_carril[i].mouVehicle();
}


/**
 * Comprova si la granota ha mort.
 * @return true si la granota és morta i false si és viva.
 */
bool Pantalla::haMortLaGranota()
{
	if (m_carril[0].xoc(m_granota))
		return true;
	else
	if (m_carril[1].xoc(m_granota))
		return true;
	else
	if (m_carril[2].xoc(m_granota))
		return true;
	else
	if (m_carril[3].xoc(m_granota))
		return true;
	else
	if (m_carril[4].xoc(m_granota))
		return true;
	else
		return false;
}


/**
 * Mou la granota en la direcció donada.
 * @param direccio Direcció cap on s'ha de moure la granota. Fer servir constants AMUNT, AVALL, DRETA i ESQUERRA.
 */
void Pantalla::mouGranota(int direccio)
{
	m_granotaAuxiliar = m_granota;

	switch (direccio)
	{
	case AMUNT: 
		m_granotaAuxiliar.mouAmunt();
		if (espaiPermes(m_granotaAuxiliar.getAreaOcupada()))
			m_granota = m_granotaAuxiliar;
		break;

	case AVALL:
		m_granotaAuxiliar.mouAvall();
		if (espaiPermes(m_granotaAuxiliar.getAreaOcupada()))
			m_granota = m_granotaAuxiliar;
		break;
	
	case ESQUERRA:
		m_granotaAuxiliar.mouEsquerra();
		if (espaiPermes(m_granotaAuxiliar.getAreaOcupada()))
			m_granota = m_granotaAuxiliar;
		break;
	
	case DRETA:
		m_granotaAuxiliar.mouDreta();
		if (espaiPermes(m_granotaAuxiliar.getAreaOcupada()))
			m_granota = m_granotaAuxiliar;
		break;
	}
}


/**
* Comprova si el jugador ha superat el nivell en el que estava jugant
* @return true si ha superat el nivell i false si no ho ha fet
*/
bool Pantalla::nivellSuperat()
{
	int comptador = 0;

	for (int i = 0; i < NUM_COVES; i++)
	{
		if (m_cova[i].esOcupada())
			comptador++;
	}

	if (comptador == NUM_COVES)
		return true;
	else
		return false;
}


/**
* Permet saber si algun dels obstacles ha estat agafat pel jugador i, en cas necessari, 
actualitza els punts aconseguits pel jugador
* @param punts punts que ha aconseguit el jugador
*/
void Pantalla::haAgafatObstacle(int &punts)
{
	int i, j = 0;
	bool trobat = false;
	bool* agafats = new bool[m_nObstacles];

	for (i = 0; i < m_nObstacles; i++)
		agafats[i] = false;

	for (i = 0; i < m_nObstacles; i++)
	{
		while ((!trobat) && (j < NUM_CARRILS))
		{
			if (!m_obstacle[i].getAgafat())
				trobat = m_carril[j].haAgafatObstacle(m_obstacle[i]);

			if (!trobat)
				j++;
			else
			{
				agafats[i] = true;
				m_obstacle[i].setAgafat(true);
				trobat = false;
			}
		}
	}

	for (i = 0; i < m_nObstacles; i++)
	{
		if (agafats[i])
			punts = punts + m_obstacle[i].getPuntuacio();
	}

	delete[] agafats;
}
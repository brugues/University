#include "Obstacle.h"

/**
* Constructor per defecte de la classe Obstacle
*/
Obstacle::Obstacle()
{

}


/**
* Destructor per defecte de la classe Obstacle
*/
Obstacle::~Obstacle()
{

}


/**
* Constructor de la classse Obstacle
* @param grafic Grafic associat a l'obstacle
* @param puntuacio Puntuacio que otorga l'obstacle en cas de ser agafat
* @posX posicio X de l'obstacle respecte del fons
* @posY posicio Y de l'obstacle respecte del fons
*/
Obstacle::Obstacle(Grafic grafic, int puntuacio, int posX, int posY)
{
	m_agafat = false;
	m_grafic = grafic;
	m_posX = posX;
	m_posY = posY;

	switch (puntuacio)
	{
	case PETITA:
		m_puntuacio = PUNTUACIO_PETITA;
		break;
	case GRAN:
		m_puntuacio = PUNTUACIO_GRAN;
		break;
	default:
		m_puntuacio = PUNTUACIO_RES;
		break;
	}
}


/**
* Ens diu la quantitat de punts que otorga l'obstacle al jugador
* @return puntuacio
*/
int Obstacle::getPuntuacio() const
{
	return m_puntuacio;
}


/**
* Dibuixa el gràfic de l'obstacle en la pantalla del joc
*/
void Obstacle::dibuixa()
{
	m_grafic.dibuixa(m_posX, m_posY);
}


/**
* Retorna l'area ocupada per l'obstacle
*/
Area Obstacle::getAreaOcupada()
{
	return Area(m_posX, m_posX + m_grafic.getScaleX(), m_posY, m_posY + m_grafic.getScaleY());
}


/**
* Permet modificar l'estat d'agafat de l'objecte
* @param agafat true es vol posar com a agafat i false si es vol deixar d'estar com a agafat
*/
void Obstacle::setAgafat(bool agafat)
{
	m_agafat = agafat;
}


/**
* Permet saber si un objecte ha estat agafat
* @return true si ja ha estat agafat i false si no ho ha estat
*/
bool Obstacle::getAgafat() const
{
	return m_agafat;
}
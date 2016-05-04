#include "Vehicle.h"
#include "Pantalla.h"

/**
 * Constructor per defecte.
 */
Vehicle::Vehicle()
{
}

/**
 * Constructor del Vehicle.
 * @param grafic Grafic amb el que ilustrar el vehicle
 * @param velocitat Velocitat de moviment
 */
Vehicle::Vehicle(Grafic grafic, int velocitat, int iniciCarrilX)
{
	m_grafic = grafic;
	if (iniciCarrilX == INICI_X)
		m_velocitat = velocitat;
	else
		m_velocitat = -velocitat;
}

/**
 * Destructor per defecte.
 */
Vehicle::~Vehicle()
{
}

/**
 * Retorna l'area ocupada pel vehicle.
 */
Area Vehicle::getAreaOcupada()
{
	return Area(m_posicioX, m_posicioX + m_grafic.getScaleX(), m_posicioY, m_posicioY + m_grafic.getScaleY()); 
}

/**
 * Dibuixa el vehicle a la posició actual.
 */
void Vehicle::dibuixa()
{
	m_grafic.dibuixa(m_posicioX, m_posicioY);
}

/**
 * Mou el vehicle tenint en compte la velocitat d'aquest.
 */
void Vehicle::mou()
{
		m_posicioX = m_posicioX + m_velocitat;
}

/**
 * Mou el vehicle a l'inici d'un carril.
 * @param iniciXCarril Coordenada X inicial del carril
 * @param iniciYCarril Coordenada Y del carril
 */
void Vehicle::mouAIniciCarril(int iniciXCarril, int iniciYCarril)
{
	m_posicioY = iniciYCarril;
	if (iniciXCarril == INICI_X)
		m_posicioX = iniciXCarril;
	else
		m_posicioX = iniciXCarril - m_grafic.getScaleX();
}
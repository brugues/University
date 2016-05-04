#include "Cova.h"

/**
 * Constructor per defecte.
 */
Cova::Cova()
{
}

/**
 * Constructor de la cova.
 * @param grafic Grafic ilustrant la cova
 * @param posicioX Coordenada horitzontal de la cova
 * @param posicioY Coordenada vertical de la cova
 */
Cova::Cova(Grafic grafic, int posicioX, int posicioY)
{
	m_posicioX = posicioX;
	m_posicioY = posicioY;
	m_grafic = grafic;
	m_ocupada = false;
	m_interior = Area(m_posicioX + MARGE_COVA, m_posicioX + m_grafic.getScaleX() - MARGE_COVA, m_posicioY, m_posicioY + m_grafic.getScaleY());
	m_paretEsquerra = Area(m_posicioX, m_posicioX + MARGE_COVA, m_posicioY, m_posicioY + m_grafic.getScaleY());
	m_paretDreta = Area(m_posicioX + m_grafic.getScaleX() - MARGE_COVA, m_posicioX + m_grafic.getScaleX(), m_posicioY, m_posicioY + m_grafic.getScaleY());
	m_total = Area(m_posicioX, m_posicioX + m_grafic.getScaleX(), m_posicioY, m_posicioY + m_grafic.getScaleY());
}


/**
 * Destructor per defecte.
 */
Cova::~Cova(void)
{
}


/**
 * Dibuixa la cova a la seva posici�.
 */
void Cova::dibuixa()
{
	m_grafic.dibuixa(m_posicioX, m_posicioY);
}


/**
 * Comprova si una �rea donada no es solapa amb cap paret de la cova.
 * @param area Area a comprovar
 * @return true si l'�rea no es solapa amb cap parets de la cova.
 */
bool Cova::esAccessible(Area area)
{
	bool esAccessible = true;

	if (m_interior.solapa(area) && m_ocupada)
		esAccessible = false;

	return (esAccessible && (!area.solapa(m_paretEsquerra) && (!area.solapa(m_paretDreta))));
}


/**
 * Comprova si l'�rea es troba totalment a l'interior de la cova.
 * @param area Area a comprovar
 * @returns true si l'�rea es troba totalment dins la cova i false si no �s aix�.
 */
bool Cova::granotaEsDins(Area area)
{
	return m_interior.inclou(area);
}


/**
* Comprova si una cova est� ocupada o no
* @return false si cova est� desocupada i true si la cova est� ocupada
*/
bool Cova::esOcupada()
{
	return m_ocupada;
}


/**
* Posa una cova en l'estat d'ocupada
*/
void Cova::setOcupada()
{
	m_ocupada = true;
}

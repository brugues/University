#include "Area.h"

/**
 * Constructor per defecte.
 */
Area::Area()
{
}

/**
 * Constructor d'una àrea rectangular no inclinada.
 * @param minX Mínima coordenada horitzontal
 * @param maxX Màxima coordenada horitzontal
 * @param minY Mínima coordenada vertical
 * @param maxY Màxima coordenada vertical
 */
Area::Area(int minX, int maxX, int minY, int maxY)
{
	m_minX = minX;
	m_maxX = maxX;
	m_minY = minY;
	m_maxY = maxY;
}

/**
 * Destructor per defecte.
 */
Area::~Area()
{
}

/**
 * Obté la mínima coordenada horitzontal.
 * @return mínima coordenada horitzontal
 */
int Area::getMinX()
{
	return m_minX;
}

/**
 * Obté la màxima coordenada horitzontal.
 * @return màxima coordenada horitzontal
 */int Area::getMaxX()
{
	return m_maxX;
}

/**
 * Obté la mínima coordenada vertical.
 * @return mínima coordenada vertical
 */
int Area::getMinY()
{
	return m_minY;
}

/**
 * Obté la màxima coordenada vertical.
 * @return màxima coordenada vertical
 */
int Area::getMaxY()
{
	return m_maxY;
}

/**
 * Comprova si un punt donat pertany a l'area.
 * @param x Coordenada horitzontal del punt
 * @param y Coordenada vertical del punt
 * @return true si hi pertany i false si no hi pertany.
 */
bool Area::pertany(int x, int y)
{
	if (((x >= m_minX) && (x<=m_maxX)) && ((y>=m_minY) && (y <= m_maxY)))
		return true;
	else
		return false;
}

/**
 * Comprova si una àrea donada està inclosa dins l'àrea.
 * @param area L'àrea donada que es vol comprovar.
 * @return true si l'àrea donada està inclosa, false si no.
 */
bool Area::inclou(Area area)
{
	if (((area.getMinX()>=m_minX) && (area.getMaxX()<=m_maxX)) && ((area.getMinY()>=m_minY) && (area.getMaxY() <= m_maxY)))
		return true;
	else
		return false;

}

/**
 * Comprova si l'àrea donada es solapa amb l'àrea.
 * Nota: dues àrees se solapen si la intersecció entre elles no és buida.
 * Assumpció: El cas en què dos rectangles formen una creu no cal que el tingueu en compte, no es donarà en aquest projecte.
 * @param area L'àrea a comprovar
 * @return true si es solapen i false si no.
 */
bool Area::solapa(Area area)
{
	bool valid = false;

	if (area.pertany(m_minX, m_minY))
		valid = true;
	if (area.pertany(m_maxX, m_minY))
		valid = true;
	if (area.pertany(m_minX, m_maxY))
		valid = true;
	if (area.pertany(m_maxX, m_maxY))
		valid = true;
	if (pertany(area.getMinX(), area.getMinY()))
		valid = true;
	if (pertany(area.getMaxX(), area.getMinY()))
		valid = true;
	if (pertany(area.getMinX(), area.getMaxY()))
		valid = true;
	if (pertany(area.getMaxX(), area.getMaxY()))
		valid = true;

	return valid;
}
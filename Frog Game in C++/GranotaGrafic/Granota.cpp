#include "Granota.h"


/**
 * Constructor per defecte.
 */
Granota::Granota()
{
}


/**
 * Constructor de la Granota.
 * @param grafic Grafic amb el que ilustrar la granota
 * @param posicioInicialX Posició inicial en coordenada horitzontal
 * @param posicioInicialY Posició inicial en coordenada vertical
 */
Granota::Granota(Grafic grafic[][TOTAL_EST], int posicioInicialX, int posicioInicialY)
{
	m_posicioInicialX = posicioInicialX;
	m_posicioInicialY = posicioInicialY;

	for (int i = 0; i < TOTAL_MOV; i++)
	{
		for (int j = 0; j < TOTAL_EST; j++)
			m_grafic[i][j] = grafic[i][j];
	}

	m_moviment = AMUNT;
	m_estat = REP;
	m_contador = TEMPS_MOVIMENT_GRANOTA;
}


/**
 * Destructor per defecte.
 */
Granota::~Granota()
{
}


/**
 * Obté l'àrea ocupada per la granota.
 * @return Area ocupada
 */
Area Granota::getAreaOcupada()
{
	return Area(m_posicioX, m_posicioX + m_grafic[m_moviment][m_estat].getScaleX(), m_posicioY,
				m_posicioY + m_grafic[m_moviment][m_estat].getScaleY());
}


/**
 * Dibuixa la granota a la posició actual.
 */
void Granota::dibuixa()
{
	switch (m_moviment)
	{
	case AMUNT:
		if (m_estat)
			m_grafic[AMUNT][MOV].dibuixa(m_posicioX, m_posicioY);
		else
			m_grafic[AMUNT][REP].dibuixa(m_posicioX, m_posicioY);
		break;
	case AVALL:
		if (m_estat)
			m_grafic[AVALL][MOV].dibuixa(m_posicioX, m_posicioY);
		else
			m_grafic[AVALL][REP].dibuixa(m_posicioX, m_posicioY);
		break;
	case ESQUERRA:
		if (m_estat)
			m_grafic[ESQUERRA][MOV].dibuixa(m_posicioX, m_posicioY);
		else
			m_grafic[ESQUERRA][REP].dibuixa(m_posicioX, m_posicioY);
		break;
	case DRETA:
		if (m_estat)
			m_grafic[DRETA][MOV].dibuixa(m_posicioX, m_posicioY);
		else
			m_grafic[DRETA][REP].dibuixa(m_posicioX, m_posicioY);
		break;
	}

	if (m_contador > 0)
		m_contador--;
	else
	{
		m_contador = TEMPS_MOVIMENT_GRANOTA;
		m_estat = REP;
	}
}


/**
 * Mou la granota cap a l'esquerra.
 */
void Granota::mouEsquerra()
{
	if (!m_estat)
	{
		m_posicioX = m_posicioX - DESPLACAMENT_GRANOTA;
		m_moviment = ESQUERRA;
		m_estat = MOV;
	}
}


/**
 * Mou la granota cap a la dreta.
 */
void Granota::mouDreta()
{
	if (!m_estat)
	{
		m_posicioX = m_posicioX + DESPLACAMENT_GRANOTA;
		m_moviment = DRETA;
		m_estat= MOV;
	}
}


/**
 * Mou la granota cap amunt.
 */
void Granota::mouAmunt()
{
	if (!m_estat)
	{
		m_posicioY = m_posicioY - DESPLACAMENT_GRANOTA;
		m_moviment = AMUNT;
		m_estat = MOV;
	}
}


/**
 * Mou la granota cap avall.
 */
void Granota::mouAvall()
{
	if (!m_estat)
	{
		m_posicioY = m_posicioY + DESPLACAMENT_GRANOTA;
		m_moviment = AVALL;
		m_estat = MOV;
	}
}


/**
 * Mou la granota a la seva posició inicial.
 */
void Granota::mouAPosicioInicial()
{
	m_posicioX = m_posicioInicialX;
	m_posicioY = m_posicioInicialY;
}
#pragma once
#include "Area.h"
#include "lib\Grafic.h"

const int MARGE_COVA = 20;

class Cova
{
public:
	Cova();
	Cova(Grafic grafic, int posicioX, int posicioY);
	~Cova();
	void Cova::dibuixa();
	bool esAccessible(Area area);
	bool esOcupada();
	void setOcupada();
	bool granotaEsDins(Area area);

private:
	Grafic m_grafic;
	Area m_interior;
	Area m_paretEsquerra;
	Area m_paretDreta;
	Area m_total;
	int m_posicioX;
	int m_posicioY;
	bool m_ocupada;
};


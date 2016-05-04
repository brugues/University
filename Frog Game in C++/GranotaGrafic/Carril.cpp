#include "Carril.h"
#include <cstdlib>
#include <ctime>

/**
* Constructor de la classe Carril
*/
Carril::Carril()
{
	// Fixem l'hora actual com a llavor pel generador d'aleatoris.
	std::srand(std::time(0));
}


/**
* Constructor de la classe carril
* @param graficVehicle gràfic associat al vehicle
* @param area àrea de la zona per on es pot moure el vehicle
* @param nivell nivell en el que es troba el jugador
* @param iniciCarril indica on comença el carril del vehicle
*/
Carril::Carril(Grafic graficVehicle, int nivell, int iniciCarrilY, int iniciCarrilX)
{
	m_areaTotal = Area(INICI_X, FI_X, INICI_Y, FI_Y);
	m_iniciCarrilY = iniciCarrilY;
	m_iniciCarrilX = iniciCarrilX;
	m_grafic = graficVehicle;
	m_vehicle = Vehicle(m_grafic, nivell*DESPLACAMENT_COTXE, m_iniciCarrilX);
	m_numeroVehicles = (rand() % nivell + 1);

	
	if (m_iniciCarrilX == INICI_X)
	{
		m_vehicle.mouAIniciCarril(m_iniciCarrilX + retardSortidaX(), m_iniciCarrilY);
		m_cua.afegeix(m_vehicle);
	}
	else
	{
		m_vehicle.mouAIniciCarril(m_iniciCarrilX - retardSortidaX(), m_iniciCarrilY);
		m_cua.afegeix(m_vehicle);
	}
}


/**
* Destructor per defecte
*/
Carril::~Carril()
{

}


/**
* Aquesta funció comprova si la granota ha xocat amb el vehicle.
* @param granota es el grafic de la granota
* @return true si la granota ha mort i false si la granota no ha mort
*/
bool Carril::xoc(Granota granota)
{
	bool xoc = false;
	Iterador posicio = m_cua.getInici();

	while (!posicio.esNul() && (!xoc))
	{
		Vehicle& vehicle = posicio.getElement();
		xoc = vehicle.getAreaOcupada().solapa(granota.getAreaOcupada());
		posicio.seguent();
	}

	return xoc;
}


/**
* Mou el vehicle en la direcció desitjada. Si el vehicle arriba al final del carril, el cotxe és dibuixat al principi.
*/
void Carril::mouVehicle()
{
	Iterador posicio = m_cua.getInici();
	int aleatori = rand() % 100;
	m_vehicle.mouAIniciCarril(m_iniciCarrilX, m_iniciCarrilY);

	while (!posicio.esNul())
	{
		Vehicle& vehicle = posicio.getElement();

		if ((aleatori > 90) && (vehicle.getAreaOcupada().solapa(m_vehicle.getAreaOcupada())))
		{
			m_cua.afegeix(m_vehicle);
		}
		if (!esDinsCarril(vehicle.getAreaOcupada()))
		{
			if (posicio.getNode()->getNext() == NULL)
			{
				m_cua.treu();
				m_vehicle.mouAIniciCarril(m_iniciCarrilX, m_iniciCarrilY);
				m_cua.afegeix(m_vehicle);
			}
			else
			{
				if (aleatori > 90)
				{
					m_cua.treu();
					m_vehicle.mouAIniciCarril(m_iniciCarrilX, m_iniciCarrilY);
					m_cua.afegeix(m_vehicle);
				}
				else
					m_cua.treu();
			}
		}
		else
		{
			vehicle.mou();
		}
		posicio.seguent();
	}
}


/**
* Dibuixa el vehicle per pantalla
*/
void Carril::dibuixaVehicle()
{
	Iterador posicio = m_cua.getInici();

	while (!posicio.esNul())
	{
		Vehicle vehicle = posicio.getElement();
		if (esDinsCarril(vehicle.getAreaOcupada()))
			vehicle.dibuixa();
		posicio.seguent();
	}
}


/**
* Comprova si una certa àrea és inclosa dins de la zona de moviment dels vehicles
* @param area es l'area que es comprova si està dins de la zona de moviment dels vehicles
* @return true si l'area es troba dins la zona de moviment dels vehicles i false si no s'hi troba
*/
bool Carril::esDinsCarril(Area area)
{
	return (area.solapa(m_areaTotal));
}


/**
* Genera un nombre aleatori entre els valors de l'INICI_X i del FI_X
* @return un nombre aleatori entre 0 (INICI_X) i 600 (FI_X)
*/
int Carril::retardSortidaX()
{
	return rand() % FI_X;
}


/**
* Ens informa de si algun dels objectes ha estat agafat pel jugador
* @param obstacle és l'obstacle que volem saber si ha estat agafat
* @return true si l'objecte ha estat agafat i false si l'objecte no ha estat agafat.
*/
bool Carril::haAgafatObstacle(Obstacle obstacle)
{
	bool agafat = false;
	Iterador posicio = m_cua.getInici();

	while ((!posicio.esNul()) && (!agafat))
	{
		Vehicle& vehicle = posicio.getElement();
		agafat = vehicle.getAreaOcupada().solapa(obstacle.getAreaOcupada());
		posicio.seguent();
	}

	return agafat;
}
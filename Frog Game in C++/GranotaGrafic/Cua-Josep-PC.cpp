#include "Cua.h"


/*
* Constructor per defecte de la classe Cua
*/
Cua::Cua()
{
	m_primer = NULL;
	m_ultim = NULL;
}


/**
* Destructor per defecte de la classe Cua
*/
Cua::~Cua()
{

}


/**
* Permet saber si la cua es buida
* @return true si la cua esta buida i false si no ho està
*/
bool Cua::esBuida() const
{
	return m_primer == NULL;
}


/**
* Permet obtenir el primer element de la cua
* @return el primer element de la cua
*/
Vehicle& Cua::getPrimer() const
{
	return m_primer->getValor();
}


/**
* Permet obtenir l'ultim element de la cua
* @return l'ultim element de la cua
*/
Vehicle& Cua::getUltim() const
{
	return m_ultim->getValor();
}


/**
* Retorna la posicio del primer element de la cua
* @return l'iterador del primer element de la cua
*/
Iterador Cua::getInici() const
{
	return Iterador(m_primer);
}


/**
* Permet afegir un element a la cua
* @param vehicle vehicle que es vol afegir a la cua
*/
bool Cua::afegeix(Vehicle& vehicle)
{
	Node* aux;
	bool correcte = false;
	if ((aux = new Node) != NULL)
	{
		correcte = true;
		aux->setValor(vehicle);
		aux->setNext(NULL);
		if (esBuida())
			m_primer = aux;
		else
			m_ultim->setNext(aux);
		m_ultim = aux;
	}
	return correcte;
}


/**
* Permet treure un element de la cua
* @return l'element que es vol treue de la cua (un vehicle en aquest cas)
*/
Vehicle Cua::treu()
{
	Node* aux;
	Vehicle vehicle;

	aux = m_primer;

	if (m_primer == m_ultim)
		m_ultim = NULL;

	vehicle = aux->getValor();
	m_primer = aux->getNext();

	delete aux;

	return vehicle;
}
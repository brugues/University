#pragma once
#include "Node.h"
#include "Vehicle.h"


class Iterador
{
private:
	Node* m_posicio;

public:
	Iterador();
	Iterador(Node* posicio);
	~Iterador();

	void seguent();
	Vehicle& getElement() const;
	bool esNul() const;
	Node* getNode() const;
};
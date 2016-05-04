#pragma once
#include "Iterador.h"

class Cua
{
private:
	Node* m_primer;
	Node* m_ultim;

public:
	Cua();
	~Cua();

	bool afegeix(Vehicle& vehicle);
	Vehicle treu();
	Vehicle& getPrimer() const;
	Vehicle& getUltim() const;
	bool esBuida() const;
	Iterador getInici() const;
};
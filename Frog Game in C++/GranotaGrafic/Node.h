#pragma once
#include "Vehicle.h"

class Node
{
public:
	Vehicle& getValor();
	Node* getNext();
	void setValor(Vehicle valor);
	void setNext(Node* next);

private:
	Vehicle m_valor;
	Node* m_next;

};
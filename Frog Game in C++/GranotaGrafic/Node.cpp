#include "Node.h"

Vehicle& Node::getValor()
{
	return m_valor;
}
Node* Node::getNext()
{
	return m_next;
}
void Node::setValor(Vehicle valor)
{
	m_valor = valor;
}
void Node::setNext(Node* next)
{
	m_next = next;
}
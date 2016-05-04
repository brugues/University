# -*- coding: latin-1 -*-
# Alfonso Amayuelas  1392661
# Josep  Brugues 1392631

from LinkedList import *

class StackList(object):
    """Clase stack implementada sobre LinkedList"""
    
    def __init__(self):
        """ Crea una LinkedList vacia"""
        self.llista = LinkedList()
    
    def push(self, data):
        """ Agrega un elemento a la pila"""
        self.llista.insertBefore(data)

    def pop(self):
        """ Saca un elemento de la pila y lo retorna"""
        if self.llista.isEmpty(): raise IndexError, "La pila esta vacia"
        aux = self.llista.getHead()
        self.llista.remove()
        return aux

    def head(self):
        """ Devuelve el primer elemento que saldra de la pila, pero no lo borra """
        if self.llista.isEmpty(): raise IndexError, "La pila esta vacia"
        return self.llista.getHead()

    def purge(self):
        """ Elimina todos los elementos de la pila"""
        self.llista.clear()

    def __len__(self):
        """ Numero de elementos de la pila"""
        return self.llista.getSize()

    def __str__(self):
        """ Devuelve una cadena de caracteres """
        return str(self.llista)


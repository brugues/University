# -*- coding: latin-1 -*-
# LLenar con NIUs de los integrantes del grupo
# NIU_1: 1392661 - Alfonso Amayuelas Fernandez
# NIU_2: 1392631 - Josep Brugues Pujolras

from LinkedList import *


class QueueList(LinkedList):
    """ Cola de elementos enlazados """
    def __init__(self):
        """ Constructr de la clase QueueList. Inicializa la lista como
            una lista vacia"""
        
        LinkedList.__init__(self)
    
    def push(self, data):
        """ A�ade un elemento al final de la cola
            Par�metros:
                data: elemento que se quiere a�adir a la cola """
        
        self.current = self.tail
        self.insertAfter(data)

    def pop(self):
        """ Se elimina el primer elemento de la cola
            Return: el elemento que se ha eliminado """
        
        self.moveHead()
        aux = self.getHead()
        self.remove()
        return aux

    def queueHead(self):
        """ Retorna el primer elemento de la cola """
        return self.getHead()
            
    def purge(self):
        """ Elimina todos los elemenos de la cola """
        while not self.isEmpty():
            self.remove()
    
    
    def __len__(self):
        """ Retorna el numero de elementos que tiene la cola """
        return int(self.getSize())

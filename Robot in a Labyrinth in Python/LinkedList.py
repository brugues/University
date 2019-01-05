# Alfonso Amayuelas Fernandez 1392661
# Josep Brugues Pujolras 1392631

class LinkedList(object):
    """ Lista de nodos enlazados """
    class Node(object):
        """ Esta clase guarda los elementos de la lista en nodos"""
        def __init__(self, data, next = None):
            """ Incializa el nodo con data y la referencia al nodo siguiente (por defecto None)
                Parametros:
                data: datos que se quieren guardar en el nodo
                next: el siguiente nodo al que se enlaza, se iniciliza como None por defecto
                """
            
            self.data = data
            self.next = next
        def getData(self):
            """ Retorna el contenido del nodo """
            return self.data
        
        def getNext(self):
            """ Retorna el nodo siguiente """
            return self.next
        
        def setData(self, data):
            """ Rellena el nodo con la informacion que se pasa por parametro
                data: Contenido del nodo que se quiere guardar
                """
            self.data = data
            
        def setNext(self, next):
            """ Se enlaza el siguiente nodo
                next: Nodo que se quiere enlazar
                """
            
            self.next = next
            
        def __str__(self):
            """ Metodo para configurar la funcion print del nodo """
            return str(self.data)

    def __init__(self):
        """ Inicializa la lista como una lista vacia """
        self.head = None
        self.tail = None
        self.current = None
        self.size = 0

    def getHead(self):
        """ Retorna los datos guardados en el primer nodo de la lista """
        
        if self.isEmpty(): raise IndexError, "La lista esta vacia"
        return self.head.getData()
    
    def getTail(self):
        """ Retorna los datos guardados en el ultimo nodo de la lista """
        
        if self.isEmpty(): raise IndexError, "La lista esta vacia"
        return self.tail.getData()
    
    def getCurrent(self):
        """ Retorna los datos guardados en el nodo actual """
        
        if self.isEmpty(): raise IndexError, "La lista esta vacia"
        return self.current.getData()
    
    def moveNext(self):
        """ Mueve current al siguiente nodo si es posible """
        if self.isEmpty(): raise IndexError, "La lista esta vacia"
        if self.current == self.tail: raise IndexError, "Current apunta al ultimo elemento"
        self.current =self.current.getNext()
        
    def moveHead(self):
        """ Mueve current al primer nodo de la lista """
        
        if self.isEmpty(): raise IndexError, "La lista esta vacia"
        self.current = self.head
        
    def isEmpty(self):
        """ Comprueba si la lista esta vacia y retorna si True si lo esta """
        return self.head == None
    
    def getSize(self):
        """ Retorna el numero de elementos de la lista """
        return self.size
    
    def clear(self):
        self.head = None
        self.tail = None
        self.current = None
        self.size = 0
            
    def insertBefore(self, data):
        """ Agrega el data a un nodo antes del que senala el current """
        
        new = self.Node(data)
        if self.isEmpty():
            self.head = new
            self.tail = new
            
        elif self.current == self.head:
            new.setNext(self.head)
            self.head = new
            
        else:
            aux = self.head
            while aux.getNext() != self.current:
                aux = aux.getNext()
            new.setNext(self.current)
            aux.setNext(new)
            

        self.current = new
        self.size += 1
        
    def insertAfter(self, data):
        """ Agrega el data a un nodo despues del current, mueve el current al nuevo nodo """

        new = self.Node(data)
        if self.isEmpty():
            self.head = new
            self.tail = new
            self.current = new
        elif self.current == self.tail:
            self.current.setNext(new)
            self.tail = new
            self.current = new
        else:
            new.setNext(self.current.getNext())
            self.current.setNext(new)
            self.current = new

        self.size += 1

        
    def remove(self):
        """ Borra el nodo actual y mueve el current al nodo anterior si es posible """
        
        if self.isEmpty(): raise IndexError, "La lista esta vacia"
        if self.size == 1:
            self.current = None
            self.head = None
            self.tail = None
            
        elif self.current == self.head:
            self.moveNext()
            self.head = self.current
            
        elif self.current == self.tail:
            aux = self.head
            while aux.getNext() != self.current:
                aux = aux.getNext()
            aux.setNext(None)
            self.current = aux
            self.tail = aux
            
        else:
            aux = self.head
            while aux.getNext() != self.current:
                aux = aux.getNext()
            aux.setNext(self.current.getNext())
            self.current = aux

        self.size -= 1
            
    def __str__(self):
        """ Retorna la lista como una lista de caracteres separados por comas """
        aux = self.head
        cadena = ""
        while (aux != None):
            cadena = cadena + str(aux)
            if aux.getNext() != None: cadena = cadena + ","
            aux = aux.getNext()
        
        return cadena
        

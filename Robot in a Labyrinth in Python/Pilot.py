# Alfonso Amayuelas Fernandez 1392661
# Josep Brugues Pujolras 1392631

from QueueList import QueueList

class Pilot(object):
    """ Class Pilot to know which is the next action """
    __slots__ = ['__previous', '__sonar', '__inverse', '__culdesac']
    def __init__(self):
        """ Class constructor.
            self.__previous: Last action
            self.__sonar: Filled by booleans of possible actions
            self.__inerse: Dicionary with opposite directions
            self.__culdesac: Boolean. True if it's in a culdesac. False if not
            """
        
        self.__previous = None 
        self.__sonar = {}
        self.__inverse = {'left' : 'right', 'right' : 'left', 'up' : 'down', 'down' : 'up'}
        self.__culdesac = False
        
    def getPrevious(self):
        """ Returns previous movement """
        return self.__previous
    
    def setSonar(self, sonar):
        """ Makes a copy of the dictionary to self.__sonar """
        self.__sonar = dict(sonar) # Fa una copia del diccionari, no una referencia.
        
    def isCrossRoad(self):
        """ Checks wheter it is in Cross Road or not """
        return sum(self.__sonar.values()) > 2
    
    def getCulDeSac(self):
        """ Returns whether it is in a Cul de Sac or not """
        return self.__culdesac
    
    def setCulDeSac(self, culdesac):
        """ Sets cul de Sac to True/False """
        self.__culdesac = culdesac
        
    def moveTo(self, action):
        """ Checks it is possible to make the action given by parametre and saves it as previous"""
      
        if not action in self.__sonar: raise ValueError, """Action does not exist"""
            
        if self.__sonar[action] == False: raise ValueError, """Action not possible"""

        self.__previous = action
        return action
        
    def nextMove(self):
        """ Returns which movement should be next """
        possible = self.__sonar.copy()
        num_possible = 0

        if self.__previous != None:
            self.__previous = self.__inverse[self.__previous]
            
        possible[self.__previous] = False 
        
        for count in possible:  
            if possible[count] == True:
                num_possible += 1
                available = count 

        if num_possible == 0:
            self.__culdesac = True
            available = self.__previous
        else:
            self.__previous = available

        return available

    def possibleActions(self):
        """ Return a queue with tuples of possible following actions """
        possibilities = QueueList()
        possibilities.push((True, self.__inverse[self.getPrevious()]))
        for action in self.__sonar:
            if action != self.__inverse[self.getPrevious()] and self.__sonar[action]:
                possibilities.push((False, action))
        return possibilities
            
        
        


            
      

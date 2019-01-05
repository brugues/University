from math import *
#from StackList import * #change this to the name of the stack you implemented

import Pilot;
Pilot = reload(Pilot) #change this to the name of the pilot you implemented
import StackList
StackList = reload(StackList)

from pyrobot.brain import Brain
from pyrobot.brain import avg
import os

class WB(Brain):
    def saveMap(self,fname):
        """
        Method that stores a boolean matrix as a text file.
        :param fname: a string containing the full path to the filename
        """
        bool2str = {True:'T',False:'F'}
        rows = [''.join([bool2str[col] for col in line]) for line in self.__map]
        open(fname,'w').write('\n'.join(rows))

    def setup(self):
        "Setups de brain. Functionality for recording the  map + variable definition"
        # Adding functionality for recording the map
        self.cols = 12 #same as world cols
        self.rows = 12 #same as world rows
        self.__map = [[0 for y in range(self.cols)] for x in range(self.rows)]
        yx = self.robot.getItem('location')
        self.__map[self.rows-yx[1]][yx[0]-1] = 1

        #Variable definition
        self.stack = StackList.StackList()
        self.pilot = Pilot.Pilot()
        self.robot.move('reset')

    def step(self):
        if not(self.robot.getItem('win')):
            self.pilot.setSonar(self.robot.getItem('sonar'))
            
            
            if self.pilot.isCrossRoad():
                if len(self.stack) == 0:
                    self.pilot.setCulDeSac(False)
                        
                if self.pilot.getCulDeSac():
                    culdesac, action = self.stack.pop()
                    self.pilot.setCulDeSac(culdesac)
                else:
                    actions = self.pilot.possibleActions()
                    while actions.isEmpty() == False:
                        self.stack.push(actions.pop())
                    culdesac, action = self.stack.pop()
            else:
                action = self.pilot.nextMove()
  
            self.pilot.moveTo(action)
            ti_gold = self.robot.move(action)   
            if ti_gold == "gold":
                self.robot.move('grab')
            yx = self.robot.getItem('location')
            self.__map[self.rows-yx[1]][yx[0]-1] = 1

        else:
            self.saveMap(os.path.dirname(os.path.realpath(__file__))+'/maze_map.txt')

def INIT(engine):
    return WB('WB', engine)


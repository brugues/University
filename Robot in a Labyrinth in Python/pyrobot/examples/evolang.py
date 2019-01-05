"""
Replicating ALife Nolfi 2006.
"""

############################################################
# First, let's build a simulated world:
############################################################

from pyrobot.simulators.pysim import *
from pyrobot.geometry import distance
from pyrobot.tools.sound import SoundDevice
import time, random, math

#SimulatorClass, PioneerClass = TkSimulator, TkPioneer
SimulatorClass, PioneerClass = Simulator, Pioneer

# In pixels, (width, height), (offset x, offset y), scale:
sim = SimulatorClass((441,434), (22,420), 40.357554, run=0)  
# x1, y1, x2, y2 in meters:
sim.addBox(0, 0, 10, 10)
# (x, y) meters, brightness usually 1 (1 meter radius):
sim.addLight(2, 2, 1)
sim.addLight(7, 7, 1)
# port, name, x, y, th, bounding Xs, bounding Ys, color
sim.addRobot(60000, PioneerClass("Pioneer0",
                              1, 1, -0.86,
                              ((.225, .225, -.225, -.225),
                               (.15, -.15, -.15, .15)),
                            "red"))
sim.addRobot(60001, PioneerClass("Pioneer1",
                             8, 8, -0.86,
                             ((.225, .225, -.225, -.225),
                              (.15, -.15, -.15, .15)),
                            "blue"))
sim.addRobot(60002, PioneerClass("Pioneer2",
                              5, 1, -0.86,
                              ((.225, .225, -.225, -.225),
                               (.15, -.15, -.15, .15)),
                            "green"))
sim.addRobot(60003, PioneerClass("Pioneer3",
                             8, 1, -0.86,
                             ((.225, .225, -.225, -.225),
                              (.15, -.15, -.15, .15)),
                            "purple"))
# add some sensors:
for robot in sim.robots:
    robot.addDevice(PioneerFrontSonars())
    robot.addDevice(PioneerFrontLightSensors())

############################################################
# Now, make some client-side connections to the sim robots
############################################################

# client side:
from pyrobot.robot.symbolic import Simbot
from pyrobot.engine import Engine
clients = [Simbot(sim, ["localhost", 60000], 0),
           Simbot(sim, ["localhost", 60001], 1),
           Simbot(sim, ["localhost", 60002], 2),
           Simbot(sim, ["localhost", 60003], 3)]

engines = [Engine(), Engine(), Engine(), Engine()]

for n in range(4):
    engines[n].robot = clients[n]
    engines[n].loadBrain("NNBrain")

if 0:
    steps = 500
    start = time.time()
    for i in range(steps):
        for client in clients:
            client.update()
        for engine in engines:
            engine.brain.step()
        sim.step(run=0)
    stop = time.time()
    print "Average steps per second:", float(steps)/ (stop - start)

def myquit():
    for e in engines:
        e.shutdown()
import sys
sys.exitfunc = myquit

sim.redraw()

############################################################
# Now, let's set up the GA:
############################################################

from pyrobot.geometry import Polar
def quadNum(myangle, angle):
    """
    Given angle, return quad number
      |0|
    |3| |1|
      |2|
    """
    diff = angle - myangle
    if diff >= 0:
        if diff < math.pi/4:
            return 0
        elif diff < math.pi/4 + math.pi/2:
            return 3
        elif diff < math.pi:
            return 2
        else:
            return 1
    else:
        if diff > -math.pi/4:
            return 0
        elif diff > -math.pi/4 - math.pi/2:
            return 1
        elif diff > -math.pi:
            return 2
        else:
            return 3
def quadTest(robot = 0):
    location = [0] * 4
    for n in range(4):
        location[n] = engines[0].robot.simulation[0].getPose(n)
    myLoc = location[robot]
    return quadSound(myLoc, range(4), location)
def quadSound(myLoc, lastS, location):
    """
    Computes the sound heard for all quads.
    myLoc:    (x, y, t) of current robot; t where 0 is up
    lastS:    last sound made by robots
    location: (x, y, t) of robots; t where 0 is up
    """
    closest = [(10000, 0), (10000, 0), (10000, 0), (10000, 0)] # dist, freq
    for n in range(len(location)):
        loc = location[n]
        if loc != myLoc:
            # distance between robots:
            dist = distance(myLoc[0], myLoc[1], loc[0], loc[1])
            # global angle from one robot to another:
            angle = Polar(loc[0] - myLoc[0], loc[1] - myLoc[1], bIsPolar=0) # 0 to right, neg down (geometry-style)
            angle = angle.t # get theta
            if angle < 0:
                angle = math.pi + (math.pi + angle) # 0 to 2pi
            angle = (angle - math.pi/2) % (math.pi * 2)
            q = quadNum(myLoc[2], angle) 
            #print n, myLoc[2], angle, q
            if dist < closest[q][0]: # if shorter than previous
                closest[q] = dist, lastS[n] # new closest
    return [v[1] for v in closest] # return the sounds

from pyrobot.brain.ga import *
import operator
g = engines[0].brain.net.arrayify()
class NNGA(GA):
    def loadWeights(self, genePos):
        for n in range(len(engines)):
            engine = engines[n]
            engine.brain.net.unArrayify(self.pop.individuals[genePos].genotype)
    def randomizePositions(self):
        positions = [(100, 100)]
        for n in range(len(engines)):
            engine = engines[n]
            # Put each robot in a random location:
            x, y, t = 1 + random.random() * 7, 1 + random.random() * 7, random.random() * math.pi * 2
            minDistance = min([distance(x, y, x2, y2) for (x2,y2) in positions])
            while minDistance < 1:
                x, y, t = 1 + random.random() * 7, 1 + random.random() * 7, random.random() * math.pi * 2
                minDistance = min([distance(x, y, x2, y2) for (x2,y2) in positions])
            positions.append( (x,y) )
            engine.robot.simulation[0].setPose(n, x, y, t)
    def fitnessFunction(self, genePos):
        self.seconds = self.generation
        if genePos >= 0:
            self.loadWeights(genePos)
            self.randomizePositions()
        sim.resetPaths()
        sim.redraw()
        fitness = [0.0] * 4
        s = [0] * 4 # each robot's sound
        lastS = [0] * 4 # previous sound
        location = [(0, 0, 0) for v in range(4)] # each robot's location
        stallCount = 0
        for i in range(self.seconds * (1000/sim.timeslice)): # simulated seconds (10/sec)
            # get the locations
            for n in range(4): # number of robots
                location[n] = engines[0].robot.simulation[0].getPose(n)
            # compute the move for each robot
            for n in range(4): # number of robots
                engine = engines[n]
                engine.robot.update()
                # compute quad for this robot
                myLoc = location[n]
                quad = quadSound(myLoc, lastS, location)
                # compute output for each robot
                oTrans, oRotate, s[n] = engine.brain.propagate(quad)
                # then set the move velocities:
                engine.brain.step(oTrans, oRotate)
            # save the sounds
            for n in range(4): # number of robots
                lastS = [v for v in s]
            # make the move:
            sim.step(run=0)
            sim.update_idletasks()
            # play a sound, need to have a thread running
            if self.playSound:
                sd.playTone(int(round(engines[0].brain.net["output"].activation[-1], 1) * 2000) + 500, .1) # 500 - 2500
                # real time?
                time.sleep(.1)
            # compute fitness
            closeTo = [0, 0] # how many robots are close to which lights?
            for n in range(len(engines)):
                engine = engines[n]
                # only allow two per feeding area
                reading = max(engine.robot.light[0].values())
                if reading >= 1.0:
                    # get global coords
                    x, y, t = engine.robot.simulation[0].getPose(n)
                    # which light?
                    dists = [distance(light.x, light.y, x, y) for light in sim.lights]
                    if dists[0] < dists[1]:
                        closeTo[0] += 1
                    else:
                        closeTo[1] += 1
            for n in range(len(engines)):
                if engines[n].robot.stall: continue
                for total in closeTo:
                    if total <= 2:
                        fitness[n] += .25 * total
                    else:
                        fitness[n] -= 1.0
            # ==================================================
            # Check for all stalled:
            stalled = 0
            for n in range(4): # number of robots
                engine = engines[n]
                if engine.robot.stall: stalled += 1
            if stalled == 4:
                stallCount += 1
            else:
                stallCount = 0
            if stallCount == 10:
                break
        fit = reduce(operator.add, fitness)
        fit = max(0.01, fit)
        print "Fitness %d: %.5f" % (genePos, fit)
        return fit
    def setup(self, **args):
        if args.has_key('seconds'):
            self.seconds = args['seconds']
        else:
            # default value
            self.seconds = 20 # how much simulated real time to run, in sim seconds
        if args.has_key('playSound'):
            self.playSound = args['playSound']
        else:
            # default value
            self.playSound = 0 # sound?
    def isDone(self):
        if self.generation % 10 == 0:
            self.saveGenesToFile("gen-%05s.pop" % self.generation)
        return 0

class Experiment:
    def __init__(self, seconds, popsize, maxgen, playsound = 0):
        self.ga = NNGA(Population(popsize, Gene, size=len(g), verbose=1,
                                  imin=-1, imax=1, min=-50, max=50, maxStep = 1,
                                  elitePercent = .1),
                       mutationRate=0.05, crossoverRate=0.6,
                       maxGeneration=maxgen, verbose=1, seconds=seconds,
                       playSound=playsound)
    def evolve(self, cont = 0):
        self.ga.evolve(cont)
    def stop(self):
        for n in range(4):
            engines[n].robot.stop()
    def saveBest(self, filename):
        net = engines[0].brain.net
        net.unArrayify(self.ga.pop.bestMember.genotype)
        net.saveWeightsToFile(filename)
    def loadGenotypes(self, filename):
        engines[0].brain.net.loadWeightsFromFile(filename)
        genotype = engines[0].brain.net.arrayify()
        for p in self.ga.pop:
            for n in range(len(genotype)):
                p.genotype[n] = genotype[n]
    def loadWeights(self, filename):
        for n in range(4):
            engines[n].brain.net.loadWeightsFromFile(filename)
    def test(self, seconds):
        self.ga.seconds = seconds
        return self.ga.fitnessFunction(-1) # -1 testing

if __name__ == "__main__":
    sd = SoundDevice("/dev/dsp", async=1)
    e = Experiment(0, 20, 100, playsound = 0)
    #e.loadWeights("nolfi-100.wts")
    #e.loadGenotypes("nolfi-100.wts")
    #e.evolve()
    #e.saveBest("nolfi-200.wts")
    #e.ga.saveGenesToFile("nolfi-20-20-100.pop")

# BUG: 73.25000 for 1 in yellow for 34 seconds?

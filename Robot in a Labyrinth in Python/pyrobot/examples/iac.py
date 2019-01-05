from pyrobot.brain import Brain
from pyrobot.brain.conx import *
from pyrobot.system.log import *
from math import *
from os import system
from time import *
from random import *

"""

To test this code type:

pyrobot -s PyrobotSimulator -w RoomWithLight -r PyrobotRobot60000 -b iac


"""

def square(x):
    return x * x

def indexOfMin(ls):
    if len(ls) == 1:
        return 0
    index = 0
    for i in range(1,len(ls)):
        if ls[i] < ls[index]:
            index = i
    return index

def indexOfMax(ls):
    if len(ls) == 1:
        return 0
    index = 0
    for i in range(1,len(ls)):
        if ls[i] > ls[index]:
            index = i
    return index

class Region:
    """
    
    A region primarily consists of a list of exemplars (stored in
    self.inputs and self.targets), a list of errors (stored in
    self.errors in newest to oldest order), and an expert (stored in
    self.expert which tries to learn to predict the correct targets
    from the inputs).

    The parameters self.timeWindow and self.smoothing are used to
    calculate error progress.

    The lists self.inputTotals and self.targetTotals maintain a
    running sum of all the exemplars stored in the region to allow
    for quick calculation of their center points.

    Currently the expert is implemented as a standard three-layer
    backprop network.  This is NOT how it was done in the original
    paper.

    """
    def __init__(self, inputVectorSize, targetVectorSize, errors):
        self.inputVectorSize = inputVectorSize
        self.targetVectorSize = targetVectorSize
        self.errors = errors
        self.regionSize = 0
        self.timeWindow = 10
        self.smoothing = 20
        self.inputs = []
        self.targets = []
        self.inputTotals = [0] * self.inputVectorSize
        self.targetTotals = [0] * self.targetVectorSize
        self.expert = Network()
        self.expert.addThreeLayers(self.inputVectorSize,
                                   self.inputVectorSize / 2,
                                   self.targetVectorSize)
        self.expert.resetEpoch = 1
        self.expert.resetLimit = 1
    def __str__(self):
        result = ""
        if self.regionSize > 0:
            result += "Region: size "
            result += str(self.regionSize)
            result += ", learning progress "
            result += str(self.learningProgress())
            result += ", variance of targets "
            result += str(self.varianceOfTargets())
            result += ", center "
            result += str(self.getCenter())
        else:
            result += "Region is empty"
        return result
    def saveRegion(self, filename):
        """
        Stores the input patterns associated with the region to
        the given file name.
        """
        fp = open(filename, "w")
        for vector in self.inputs:
            for coordinate in vector:
                fp.write("%f\t" % coordinate)
            fp.write("\n")
        fp.close()
    def trainExpert(self):
        """
        Will train the expert once there are a reasonable number of
        training patterns available.
        """
        if len(self.inputs) > (self.timeWindow + self.smoothing):
            self.expert.setInputs(self.inputs)
            self.expert.setOutputs(self.targets)
            self.expert.train()
    def askExpert(self, input):
        """
        Find out what the expert predicts for the given input.
        """
        self.expert['input'].copyActivations(input)
        self.expert.propagate()
        return self.expert['output'].activation
    def storeError(self, error):
        """
        Errors are stored with the most recent at the head of the list.
        """
        self.errors.insert(0, error)
    def learningProgress(self):
        """
        Returns the learning progress which is an approximation of
        the first derivative of the error.
        """
        if len(self.errors) < (self.timeWindow + self.smoothing + 1):
            return 0
        decrease = self.meanErrorRate(0) - self.meanErrorRate(self.timeWindow)
        return -1 * decrease
    def meanErrorRate(self, start):
        """
        Returns the average error rate over self.smoothing steps
        starting from the given start index.
        """
        result = 0
        end = start + self.smoothing + 1
        if end > len(self.errors):
            return 0
        for i in range(start, end, 1):
            result += self.errors[i]
        return result / float(self.smoothing + 1)
    def addExemplar(self, input, target):
        """
        Adds the given input and target to the appropriate lists.
        Also updates the totals used for calculating the centers.
        """
        self.inputs.append(input)
        self.targets.append(target)
        self.regionSize += 1
        for i in range(self.inputVectorSize):
            self.inputTotals[i] += input[i]
        for i in range(self.targetVectorSize):
            self.targetTotals[i] += target[i]
    def varianceOfTargets(self):
        c = self.getTargetCenter()
        variances = [0] * self.targetVectorSize
        for v in self.inputs:
            for i in range(self.targetVectorSize):
                variances[i] += square(v[i] - c[i])
        total = 0
        for i in range(self.targetVectorSize):
            total += variances[i]/float(self.regionSize)
        return total
    def getTargetCenter(self):
        """
        Used to quickly calculate the variances of the target
        vectors. 
        """
        center = self.targetTotals[:]
        if self.regionSize == 0: return None
        for i in range(self.targetVectorSize):
            center[i] /= float(self.regionSize)
        return center
    def getCenter(self):
        """
        The regions are clustered based on the input vectors.
        This returns the center point of the region's cluster.
        """
        center = self.inputTotals[:]
        if self.regionSize == 0: return None
        for i in range(self.inputVectorSize):
            center[i] /= float(self.regionSize)
        return center
    def dist(self, v1, v2):
        """
        Returns the euclidean distance between two given
        vectors.
        """
        d = 0
        for i in range(self.inputVectorSize):
            d += square(v1[i] - v2[i])
        return sqrt(d)
    def distFromCenter(self, v):
        """
        Returns the distance from the region's center.
        """
        return self.dist(self.getCenter(), v)

class Memory:
    """

    A memory consists of a list of regions.  When exemplars are added,
    it determines when a region needs to be split, and then performs
    the split using a k-means analysis.  This is NOT how the split
    was done in the original paper.
    
    """
    def __init__(self, maxRegionSize, inputVectorSize, targetVectorSize):
        self.regions = [Region(inputVectorSize, targetVectorSize, [])]
        self.maxRegionSize = maxRegionSize
        self.inputVectorSize = inputVectorSize
        self.targetVectorSize = targetVectorSize
    def __str__(self):
        result = ""
        result += "Memory contains "
        result += str(len(self.regions))
        result += " region(s):\n"
        for region in self.regions:
            result += region.__str__()
            result += "\n"
        return result
    def saveCenters(self):
        fp = open("centers", "w")
        for region in self.regions:
            center = region.getCenter()
            for coordinate in center:
                fp.write("%f\t" % coordinate)
            fp.write("\n")
        fp.close()
    def saveRegions(self):
        for i in range(len(self.regions)):
            self.regions[i].saveRegion("region%d" % i)
    def splitRegion(self, r):
        """
        Randomly chooses two of the existing vectors in the region
        as the initial centers of two new regions.  Then uses the
        k-means technique to continue to re-center until the
        clusters stablize.
        """
        # only copy enough error history to allow for
        # continued calculations of learning progress
        # in the newly split regions
        numErrors = r.timeWindow + r.smoothing + 1
        while True:
            n = r.regionSize-1
            i1 = randint(0,n)
            i2 = randint(0,n)
            if i1 != i2:
                break
        center1 = r.inputs[i1]
        center2 = r.inputs[i2]
        prev1 = None
        prev2 = None
        while True:
            if prev1 == center1 and prev2 == center2:
                self.regions.append(r1)
                self.regions.append(r2)
                return
            r1 = Region(r.inputVectorSize,
                        r.targetVectorSize,
                        r.errors[:numErrors])
            r2 = Region(r.inputVectorSize,
                        r.targetVectorSize,
                        r.errors[:numErrors])
            for i in range(r.regionSize):
                if r.dist(r.inputs[i],center1) < r.dist(r.inputs[i],center2):
                    r1.addExemplar(r.inputs[i], r.targets[i])
                else:
                    r2.addExemplar(r.inputs[i], r.targets[i])
            prev1 = center1
            prev2 = center2
            center1 = r1.getCenter()
            center2 = r2.getCenter()
    def closestRegion(self, input):
        return self.regions[self.indexOfClosestRegion(input)]
    def indexOfClosestRegion(self, input):
        if len(self.regions) == 1:
            return 0
        dists = [r.distFromCenter(input) for r in self.regions]
        return indexOfMin(dists)
    def addExemplar(self, input, target, region):
        """
        Adds the given input and target exemplar to the given
        region.  If the region is now too large, it is removed
        and split into two new regions.
        """
        region.addExemplar(input, target)
        #print "Region added exemplar, size is", len(region.inputs)
        if region.regionSize > self.maxRegionSize:
            print "*** MEMORY splitting a region ***"
            index = self.regions.index(region)
            self.regions.pop(index)
            self.splitRegion(region)
            print self.__str__()

class IACBrain(Brain):
    """

    A prototype of the IAC model.  There are some key differences
    between the model described in the Oudeyer et. al. paper and this
    implementation.  This implementation uses k-means to do the
    splitting of the sensorimotor space.  It does not try to minimize
    the variance of the prediction space.  Also, each region's
    expert is a neural network.  

    Using the PyrobotSimulator with the RoomWithLight.py world.
    The robot has 3 combined sonars, 2 light sensors, and 2 motors.
    
    """
    def setup(self, **args):
        self.maxRegionSize = args['maxRegionSize']
        self.motorVectorSize = args['motorVectorSize']
        self.sensorVectorSize = args['sensorVectorSize']
        self.inputVectorSize = self.sensorVectorSize + self.motorVectorSize
        self.targetVectorSize = self.sensorVectorSize
        self.memory = Memory(self.maxRegionSize,
                             self.inputVectorSize,
                             self.targetVectorSize)
        print "MEMORY created"
        self.robot.range.units = 'SCALED'
        self.numCandidates = 3
        self.winningRegion = None
        self.prediction = None
        self.sensorimotor = None
        self.probOfRandAction = 0.35
        # Create a dictionary to count interesting states
        self.monitor = {'stall':0, 'light':0, 'blockedL':0,
                        'blockedR':0, 'blockedF':0}
        self.testEpoch = 100
        # Open file to store this data
        self.data = open("monitor.data", "w")
        self.data.write("% Columns represent: ")
        for key in self.monitor.keys():
            self.data.write("%s " % key)
        self.data.write("\n")
    def computeError(self, actual, prediction):
        error = 0
        for i in range(self.targetVectorSize):
            error += square(actual[i] - prediction[i])
        return error
    def scale(self, m):
        """
        Motor values are stored in range [0.0,1.0]
        However, the robot uses range [-1.0,1.0]
        """
        return (m * 2.0) - 1.0
    def step(self):
        """
        Implements the main action loop of the IAC model.
        """
        # Read in current sensors S(t)
        front = min([s.distance() for s in self.robot.range["front-all"]])
        left = min([s.distance() for s in self.robot.range["left"]])
        right = min([s.distance() for s in self.robot.range["right"]])
        sonars = [left, front, right]
        lights = self.robot.light[0].value
        sensors = sonars + lights
        if self.prediction != None:
            # Compute error between S(t) and prediction
            error = self.computeError(sensors, self.prediction)
            self.winningRegion.storeError(error)
            # Add the most recent exemplar to memory
            self.memory.addExemplar(self.sensorimotor,
                                    sensors,
                                    self.winningRegion)
            # Train the updated region's expert
            self.winningRegion.trainExpert()
        # Choose a motor action M(t)
        motors = self.selectAction(sensors)
        motors = map(self.scale, motors)
        # Execute the action
        self.robot.move(motors[0], motors[1])
        self.categorizeState()
    def selectAction(self, sensors):
        """
        Considers a number of candidate actions and chooses the one
        in which the maximal progress is expected (most of the time).
        With some small probability will also take random actions.
        """
        # Generate a set of candidate actions
        candidateActions = []
        for i in range(self.numCandidates):
            motors = [random() for i in range(self.motorVectorSize)]
            candidateActions.append(motors)
        progress = []
        candidateRegions = []
        # For each sensorimotor vector, find the associated region
        # and determine learning progress
        for motors in candidateActions:
            region = self.memory.closestRegion(sensors+motors)
            candidateRegions.append(region)
            progress.append(region.learningProgress())
        # Choose the action from region with maximal progress
        # most of the time
        if random() < self.probOfRandAction:
            choice = randint(0,self.numCandidates-1)
        else:
            choice = indexOfMax(progress)
        self.sensorimotor = sensors + candidateActions[choice]
        self.winningRegion = candidateRegions[choice]
        # Determine the expert's prediction of the next sensors
        self.prediction = region.askExpert(self.sensorimotor)
        return candidateActions[choice]
    def categorizeState(self):
        """
        The vector self.sensorimotor contains 7 features:
        0 left sonar
        1 front sonar
        2 right sonar
        3 left light
        4 right light
        5 translation
        6 rotation
        """
        if self.robot.stall:
            self.monitor['stall'] += 1
        if self.sensorimotor[3]+self.sensorimotor[4] > 0.9:
            self.monitor['light'] += 1
        if self.sensorimotor[0]<0.25 and self.sensorimotor[2]>0.5:
            self.monitor['blockedL'] += 1
        if self.sensorimotor[0]>0.5 and self.sensorimotor[2]<0.25:
            self.monitor['blockedR'] += 1
        if self.sensorimotor[0]>0.3 and self.sensorimotor[2]>0.3 and \
           self.sensorimotor[1]<0.2:
            self.monitor['blockedF'] += 1
        if self.stepCount % self.testEpoch == 0:
            for key in self.monitor.keys():
                self.data.write("%d " % self.monitor[key])
                self.monitor[key] = 0
            self.data.write("\n")
            self.data.flush()

def INIT(engine):
   return IACBrain('IACBrain',
                   engine,
                   maxRegionSize=75,
                   motorVectorSize=2,
                   sensorVectorSize=5)



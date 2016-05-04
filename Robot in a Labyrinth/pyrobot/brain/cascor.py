try:
    from conx import *
except:
    from pyrobot.brain.conx import *
import math
import pdb
from unittest import *

__author__="George Dahl <gdahl1@swarthmore.edu>"

## def pick(condition, first, second):
##     """
##     If condition evaluates to false, second will be returned.  Otherwise first will be
##     returned.
##     """
##     return (condition and [first] or [second])[0]

cor = Numeric.cross_correlate

def findMax(seq):
    """
    Returns the index of the maximum value in the sequence.
    """
    bestSoFar = 0
    for i in range(len(seq)-1):
        if seq[i+1] > seq[bestSoFar]:
            bestSoFar = i+1
    return bestSoFar

class CascadeCorNet(Network):
    """
    This network implements the cascade-correlation training method.
    """
    def __init__(self, inputLayerSize, outputLayerSize, patience = 12, maxOutputEpochs = 200, maxCandEpochs = 200,
                 name = 'CascadeCor Network', verbosity = 0):
        Network.__init__(self, name, verbosity)
        self.incrType = "cascade" # only "cascade" is supported at the moment
        self.setQuickprop(1)
        self.addLayers(inputLayerSize, outputLayerSize)

        #Fahlman had 1.0 and 100 for his code!  That seems insane.
        self.outputEpsilon = 0.8
        self.candEpsilon = 2.0

        #Fahlman used 2.0 and 2.0
        self.outputMu = 2.25
        self.candMu = 2.25

        #Fahlman had 0.01 and 0.03
        self.outputChangeThreshold = 0.01
        self.candChangeThreshold = 0.01

        self.outputDecay = -0.001
        self.candDecay = -0.001
        
        self.quitEpoch = patience
        self.patience = patience
                
        self.previousError = sys.maxint
        self.maxOutputEpochs = maxOutputEpochs #perhaps duplicates the purpose of a datamember that already exists?
        self.maxCandEpochs = maxCandEpochs
        #self.symmetricOffset = 0.0
        self.candreportRate = self.reportRate

        self.switchToOutputParams()
    def switchToOutputParams(self):
        self.epsilon = self.outputEpsilon
        self.mu = self.outputMu
        self.changeThreshold = self.outputChangeThreshold
        self.decay = self.outputDecay
    def switchToCandidateParams(self):
        self.epsilon = self.candEpsilon
        self.mu = self.candMu
        self.changeThreshold = self.candChangeThreshold
        self.decay = self.candDecay
    def setup(self):
        #self.setSeed(113) #FOR DEBUGGING ONLY, DISABLE WHEN DEBUGGING COMPLETE
        pass
    def actDeriv(self, x):
        """
        Only works on scalars.
        """
        def act(v):
            if   v < -15.0: return 0.0
            elif v >  15.0: return 1.0
            else: return 1.0 / (1.0 + Numeric.exp(-v))
        return (act(x) * (1.0 - act(x))) + self.sigmoid_prime_offset
    def train(self, maxHidden):
        self.maxHidden = maxHidden
        cont = 1
        while (not self.done()) and self.trainOutputs(self.maxOutputEpochs, cont): #add hidden units until we give up or win
            self.epoch = 0
            self.switchToCandidateParams()
            best = self.trainCandidates()
            self.switchToOutputParams()
            self.recruit(best)
            print len(self)-3, " Hidden nodes.\n"
        if len(self)-3 == self.maxHidden:
            self.trainOutputs(self.maxOutputEpochs, cont)
    def trainCandidates(self):
        """
        This function trains the candidate layer to maximize its correlation with the output errors.  The way this is done
        is by setting weight error derivatives for connections and layers and assuming the change_weights function will update the
        weights appropriately based on those data members.
        """

        self["output"].active = 1 #we need the output error, etc. so the output layer must be active during propagation
        self["candidate"].active = 1 #candidate should be active throughout this function

        #E_po will hold a list of errors for each pattern for each output unit, E_po[i][j] will be error
        #          of jth output on ith pattern in the load order
        #E_o_avg is the mean of E_po over the different patterns
        #outputs[i][j] is the output of the jth output unit on the ith pattern
        E_po, E_o_avg, outputs = self.computeDataFromProp()

        numPatterns = len(self.loadOrder)
        numCandidates = len(self["candidate"])
        numInputs = len(self["input"]) #DOES NOT INCLUDE BIAS
        incomingConnections = [connection for connection in self.connections if connection.toLayer.name=="candidate"]
        numOutputs = len(outputs[0])


        ep = 0
        self.quitEpoch = self.patience
        previousBest = 0 #index of best candidate correlation on last iteration
        while ep < self.maxCandEpochs and ep < self.quitEpoch:
            #V sub p on page 5 of Fahlman's paper "The Cascade-Correlation Learning Architecture (1991)"
            #will hold  a list of activations for each candidate for each training pattern, each row a
            #           different pattern, each column a different candidate
            #
            #no need to reactivate output layer here since we don't need to recompute any data about its propagation status
            V_p, netInptToCnd = self.computeChangingDataFromProp()
            V_avg = Numeric.sum(V_p)/len(V_p)
            #sigma_o[i][j] is the sign of the correlation between the ith candidate and the jth output
            sigma_o = Numeric.array([[Numeric.sign(cor(V_p[:,c], outputs[:,out]))[0] for c in range(numCandidates)] \
                                     for out in range(len(outputs[0]))])
            for c in range(numCandidates): #for every candidate unit in the layer, get ready to train the bias weight
                #recompute dSdw for the bias weight for this candidate
                dSdw_bias = Numeric.sum( [Numeric.sum([sigma_o[i][c]*(E_po[p][i] - E_o_avg[i])*self.actDeriv(netInptToCnd[p][c]) \
                                                       for p in range(numPatterns)]) for i in range(numOutputs)] )
                self.updateCandidateLayer(dSdw_bias, c)
            for conxn in incomingConnections: #for every connection going into the candidate layer, prepare to train the weights
                #dSdw[i][j] is the derivative of S for the ith, jth weight of the current connection
                dSdw = self.compute_dSdw(sigma_o, E_po, E_o_avg, netInptToCnd, conxn)
                self.updateConnection(conxn, dSdw)
            #deactivate output layer here so we don't change its weights
            self["output"].active = 0
            self.change_weights() #change incoming connection weights and bias weights for the entire candidate layer
            
            #S_c is a list of the covariances for each candidate, or
            #Fahlman's 'S' quantity, computed for each candidate unit
            #perhaps construction of uneccesary temporary lists could be avoided with
            #generator expressions, but Numeric.sum doesn't seem to
            #evaluate a generator expression
            S_c = self.computeS_c(V_p, V_avg, E_po, E_o_avg)
            best = findMax(S_c)

            #if there is an appreciable change in the error we don't need to worry about stagnation
            if abs(S_c[best] - previousBest) > previousBest*self.changeThreshold:
                previousBest = S_c[best]
                self.quitEpoch = i + self.patience

            if ep % self.candreportRate == 0: #simplified candidate epoch reporting mechanism
                print "Candidate Epoch # ", ep
            ep += 1
        
        return best #return the index of the candidate we should recruit
    def updateCandidateLayer(self, dSdw_bias, c):
        """
        Updates the information used in changing the bias weight for the cth candidate unit in the candidate layer.
        """
        #let g(x) = -f(x), dg/dx = -df/dx since we maximize correlation (S) but minimize error
        self["candidate"].wed[c] = -1.0*dSdw_bias + self["candidate"].weight[c] * self.decay
    def updateConnection(self, conxn, dSdw):
        self[conxn.fromLayer.name, conxn.toLayer.name].wed = -1.0* dSdw +conxn.weight*self.decay
    def computeDataFromProp(self):
        #problem here as of 6/1/06
        """
        Computes data based on propagation that need not be recomputed between candidate weight changes.
        """
        E_po, outputs = [], []
        for i in self.loadOrder: #for each training pattern, save all the information that will be needed later
            self.propagate(**self.getData(i))
            E_po.append(self.errorFunction(self["output"].target, self["output"].activation)) #need not be recomputed later
            outputs.append(self["output"].activation) #need not be recomputed later
        E_o_avg = [E/len(E_po) for E in Numeric.sum(E_po)] # list of the average error over all patterns for each output
        return (Numeric.array(E_po), Numeric.array(E_o_avg), Numeric.array(outputs))
    def computeChangingDataFromProp(self):
        """
        Computes data based on propagation that needs to be recomputed between candidate weight changes.
        """
        V_p, netInptToCnd = [], []
        for i in self.loadOrder:
            self.propagate(**self.getData(i))
            netInptToCnd.append(self["candidate"].netinput)
            V_p.append([neuron.activation for neuron in self["candidate"]])
        return (Numeric.array(V_p), Numeric.array(netInptToCnd))
    def computeS_c(self, V_p, V_avg, E_po, E_o_avg):
        """
        S_c is a list of the covariances for each candidate, or
        Fahlman's 'S' quantity, computed for each candidate unit
        perhaps construction of uneccesary temporary lists could be avoided with
        generator expressions, but Numeric.sum doesn't seem to
        evaluate a generator expression
        """
        return Numeric.sum(Numeric.fabs(Numeric.sum(
            [[Numeric.multiply( Numeric.subtract(V_p[i], V_avg), E_po[i][j] - E_o_avg[j])  
                for j in range(len(E_po[0])) ] for i in range(len(V_p)) ])))
    def compute_dSdw(self, sigma_o, E_po, E_o_avg, netInptToCnd, conxn):
        """
        Computes dSdW for a specific connection to the candidate layer.
        """
        numPatterns = len(self.loadOrder)
        numOutputs = len(E_po[0])
        return Numeric.array([[Numeric.sum( [Numeric.sum( \
                    [sigma_o[i][col]*(E_po[p][i] - E_o_avg[i])*self.actDeriv( netInptToCnd[p][col] )*self.getData(p)["input"][row] \
                     for p in range(numPatterns)]) for i in range(numOutputs)] ) \
                                 for col in range(len(conxn.weight[0]))] for row in range(len(conxn.weight))])
        
    def done(self):
        return len(self) >= (self.maxHidden + 3)
    def trainOutputs(self, sweeps, cont = 0):
        """
        Trains the outputs until self.patience epochs have gone by since a noticable change in the error,
        error drops below the threshold (either self.stopPercent or cross validation if self.useCrossValidationToStop
        is set), or a maximum number of training epochs have been performed.
        """
        self["candidate", "output"].active = 0 # don't let candidates affect outputs
        self["output"].active = 1 #make sure output layer is active, afterall, that is what we are training in this function
        self["candidate"].active = 0 #in fact, don't let the candidate layer do anything!  Hopefully this won't cause problems
        self.quitEpoch = self.patience

        
        # check architecture
        self.complete = 0
        self.verifyArchitecture()
        tssErr = 0.0; rmsErr = 0.0; totalCorrect = 0; totalCount = 1; totalPCorrect = {}
        if not cont: # starting afresh
            self.resetFlags()
            self.epoch = 0
            self.reportStart()
            self.resetCount = 1
            self.epoch = 1
            self.lastLowestTSSError = sys.maxint # some maximum value (not all pythons have Infinity)
            if sweeps != None:
                self.resetEpoch = sweeps
        else:
            if sweeps != None:
                self.resetEpoch = self.epoch + sweeps - 1
        while self.doWhile(totalCount, totalCorrect):
            (tssErr, totalCorrect, totalCount, totalPCorrect) = self.sweep()
            self.complete = 1
            if totalCount != 0:
                rmsErr = math.sqrt(tssErr / totalCount)
            else:
                self.Print("Warning: sweep didn't do anything!")
            if self.epoch % self.reportRate == 0:
                self.reportEpoch(self.epoch, tssErr, totalCorrect, totalCount, rmsErr, totalPCorrect)
                if len(self.crossValidationCorpus) > 0 or self.autoCrossValidation:
                    (tssCVErr, totalCVCorrect, totalCVCount, totalCVPCorrect) = self.sweepCrossValidation()
                    rmsCVErr = math.sqrt(tssCVErr / totalCVCount)
                    self.Print("CV    #%6d | TSS Error: %.4f | Correct: %.4f | RMS Error: %.4f" % \
                               (self.epoch, tssCVErr, totalCVCorrect * 1.0 / totalCVCount, rmsCVErr))
                    if self.autoSaveWeightsFile != None and tssCVErr < self.lastLowestTSSError:
                        self.lastLowestTSSError = tssCVErr
                        self.saveWeightsToFile(self.autoSaveWeightsFile)
                        self.Print("auto saving weights to '%s'..." % self.autoSaveWeightsFile)
                    if totalCVCorrect * 1.0 / totalCVCount >= self.stopPercent and self.useCrossValidationToStop:
                        self.epoch += 1
                        break
            if self.resetEpoch == self.epoch:
                self.Print("Reset limit reached; ending without reaching goal")
                self.epoch += 1
                self.complete = 0
                break
            self.epoch += 1
            ################
            #if there is an appreciable change in the error we don't need to worry about stagnation
            if abs(tssErr - self.previousError) > self.previousError*self.changeThreshold:
                self.previousError = tssErr
                self.quitEpoch = self.epoch + self.patience
            elif self.epoch == self.quitEpoch:
                break #stagnation occured, stop training the outputs
            ################
        print "----------------------------------------------------"
        if totalCount > 0:
            self.reportFinal(self.epoch, tssErr, totalCorrect, totalCount, rmsErr, totalPCorrect)
            if len(self.crossValidationCorpus) > 0 or self.autoCrossValidation:
                (tssCVErr, totalCVCorrect, totalCVCount, totalCVPCorrect) = self.sweepCrossValidation()
                rmsCVErr = math.sqrt(tssCVErr / totalCVCount)
                self.Print("CV    #%6d | TSS Error: %.4f | Correct: %.4f | RMS Error: %.4f" % \
                           (self.epoch-1, tssCVErr, totalCVCorrect * 1.0 / totalCVCount, rmsCVErr))
                if self.autoSaveWeightsFile != None and tssCVErr < self.lastLowestTSSError:
                    self.lastLowestTSSError = tssCVErr
                    self.saveWeightsToFile(self.autoSaveWeightsFile)
                    self.Print("auto saving weights to '%s'..." % self.autoSaveWeightsFile)
        else:
            print "Final: nothing done"
        print "----------------------------------------------------"
        return (totalCorrect * 1.0 / totalCount <  self.stopPercent) #true means we continue
    
    def addCandidateLayer(self, size=8):
        """
        Adds a candidate layer for recruiting the new hidden layer cascade
        node. Connect it up to all layers except outputs.
        """
        self.addLayer("candidate", size, position = -1)
        for layer in self:
            if layer.type != "Output" and layer.name != "candidate":
                self.connectAt(layer.name, "candidate", position = -1)
        for layer in self: # ghost connection
            if layer.type == "Output" and layer.name != "candidate":
                self.connectAt("candidate", layer.name, position = -1)
    def recruit(self, n):
        """
        Grab the Nth candidate node and all incoming weights and make it
        a layer unto itself. New layer is a frozen layer.
        """
        print "Recruiting candidate number %d" % n
        # first, add the new layer:
        hcount = 0
        for layer in self:
            if layer.type == "Hidden": 
                hcount += 1
        hname = "hidden%d" % hcount
        hsize = 1 # wonder what would happen if we added more than 1?
        self.addLayer(hname, hsize, position = -2)
        # copy all of the relevant data:
        for i in range(hsize):
            self[hname].dweight[i] = self["candidate"].dweight[i + n]
            self[hname].weight[i] = self["candidate"].weight[i + n]
            self[hname].wed[i] = self["candidate"].wed[i + n]
            self[hname].wedLast[i] = self["candidate"].wedLast[i + n]
        self[hname].frozen = 1 # don't change these weights/biases
        # first, connect up input
        for layer in self: 
            if layer.type == "Input" and layer.name != hname: # includes contexts
                self.connectAt(layer.name, hname, position = 1)
                self[layer.name, hname].frozen = 1 # don't change incoming weights
        # next add hidden connections
        if self.incrType == "cascade": # or parallel
            for layer in self: 
                if layer.type == "Hidden" and layer.name not in [hname, "candidate"]: 
                    self.connectAt(layer.name, hname, position = -1)
                    self[layer.name, hname].frozen = 1 # don't change incoming weights
        # and then output connections
        for layer in self: 
            if layer.type == "Output" and layer.name not in ["candidate", hname]: 
                self.connectAt(hname, layer.name, position = -1)
                # not frozen! Can change these hidden to the output
        # now, let's copy the weights, and randomize the old ones:
        for c in self.connections:
            if c.toLayer.name == "candidate":
                for i in range(hsize):
                    for j in range(c.fromLayer.size):
                        if self.isConnected(c.fromLayer.name, hname):
                            self[c.fromLayer.name, hname][j][i] = self[c.fromLayer.name, "candidate"][j][i + n]
                if self.isConnected(c.fromLayer.name, hname):
                    self[c.fromLayer.name, "candidate"].randomize(1)
            elif c.fromLayer.name == "candidate":
                for i in range(c.toLayer.size):
                    for j in range(hsize):
                        if self.isConnected(hname, c.toLayer.name):
                            self[hname, c.toLayer.name][j][i] = self["candidate", c.toLayer.name][j + n][i]
                if self.isConnected(hname, c.toLayer.name):
                    self["candidate", c.toLayer.name].randomize(1)
        self["candidate"].randomize(1)
        # finally, connect new hidden to candidate
        self.connectAt(hname, "candidate", position = -1)
        self[hname, "candidate"].frozen = 1 # don't change weights

def crashTest(seed):
    net = CascadeCorNet(2,1)
    net.addCandidateLayer(1)
    net.symmetricOffset = 0.0
    net.setInputs( [[0, 0], [0, 1], [1, 0], [1, 1]])
    net.setTargets([[0], [1], [1], [0]])
    net.mu = 1.75
    net.setSeed(seed)
    net.train(10)

class TestCascadeCorNet(TestCase):
    def setUp(self):
        net = CascadeCorNet(2,1)

if __name__=="__main__":
    #suite =makeSuite(TestCascadeCorNet)
    #TextTestRunner(verbosity=2).run(suite)
    print "started"
    net = CascadeCorNet(2,1)
    net.addCandidateLayer(8)
    net.symmetricOffset = 0.0
    net.setInputs( [[0, 0], [0, 1], [1, 0], [1, 1]])
    net.setTargets([[0], [1], [1], [0]])
    
    #print net.getData(0)

    #net.mu = 1.75

    #s = random.randint(0, 10)
    #print s
    #net.setSeed(s)
    net.train(10)
    print len(net)-3

    
    net = CascadeCorNet(3,1)
    net.addCandidateLayer(8)
    net.symmetricOffset = 0.0
    net.setInputs( [[0, 0, 0], [0, 0, 1], [0, 1, 0], [0, 1, 1], [1, 0, 0], [1, 0, 1], [1, 1, 0], [1, 1, 1]])
    net.setTargets([[1], [1], [1], [0], [0], [1], [1], [0]])
    net.train(10)
    print len(net)-3

    print "Made up function approximation."
    inputs = [[0.01*i,0.01*j] for i in range(100) for j in range(100)]
    targets = [[(math.sin(2*npt[0])+math.cos(npt[1]+npt[0]))/2.0] for npt in inputs]
    net = CascadeCorNet(2,1)
    net.addCandidateLayer(8)
    net.symmetricOffset = 0.0
    net.setInputs(inputs)
    net.setTargets(targets)
    net.sweepReportRate = 10000
    net.train(10)
    print len(net)-3
    
##     crashes = 0
##     seeds = []
##     for seed in range(100):
##         try:
##             crashTest(seed)
##         except:
##             crashes += 1
##             seeds.append(seed)
##             print "CRASHED"
##     print "Crashed ", crashes, " times."
##     print seeds
    print "all done"
    
    
##    GLOBAL_DEBUG = False
##    net = IncrementalNetwork("cascade")
##    net.addLayers(3,2)
##    net.addCandidateLayer(8)
    
    
    
##    net.setQuickprop(1)
##    net.symmetricOffset = 0.0
##    #net.setBatch(1)
##    #net.verbosity = 4
    
##    #net.setInputs( [[0, 0], [0, 1], [1, 0], [1, 1]])
##    #net.setTargets([[0], [1], [1], [0]])
    
##    net.setInputs( [[0,0,0], [0,0,1], [0,1,0], [0,1,1], [1,0,0], [1,0,1], [1,1,0], [1,1,1]])
##    net.setTargets([  [0,0],   [0,1],   [1,1],   [1,0],   [1,0],   [1,1],   [0,1],   [0,0]])
##    net.tolerance = .25
    
##    print net.getData(1)
    
##    print net.getQuickprop()
##    print "num layers? ",len(net)
    
##    net.reportRate = 100
##    cont = 0
##    while True:
##        net.train(50, cont = cont)
##        #print net.epoch, net.resetEpoch
##        #print "netinput:  "
##        #print net["candidate"].netinput
##        #print "\n"
##        if not net.complete:
##            net.recruitBest()
##            cont = 1
##        else:
##            break
        
##        print "in batch?",net.batch
##        print "num layers? ",len(net)
##        print [layer.error for layer in net.layers if layer.type == 'Output'][0]
        
    ## net2 = IncrementalNetwork("cascade")
##     net2.addLayers(2,1)
##     net2.addCandidateLayer(8)

##     for layer in net2:
##         print layer.getActive()
    
##     net2.setQuickprop(1)

##     net2.setInputs( [[0, 0], [0, 1], [1, 0], [1, 1]])
##     net2.setTargets([[0], [1], [1], [0]])
##     net2.tolerance = .25

    
##     print net2.getQuickprop()

##     net2.reportRate = 100
##     cont = 0
##     while True:
##         net2.train(25, cont = cont)
        
##         if not net2.complete:
##             input("press a key")
##             net2.recruitBest()
##             cont = 1
##         else:
##             break

##     net2["candidate"].active = 0 # make sure it is not effecting outputs
##     net2.displayConnections()
##     net2.interactive = 1
##     net2.sweep()

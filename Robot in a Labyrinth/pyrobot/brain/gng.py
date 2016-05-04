from math import *
from random import *

__author__ = "Jenny Barry"
__version__ = "$Revision: 1.3 $"

class Node:

    def __init__(self, index, modelVector):
        self.modelVector = modelVector
        self.edges = []
        self.error = 0
        self.index = index

    def __str__(self):
        result = "Node # "+str(self.index)+ \
                 "\nModel vector: "+str(self.modelVector)+"\nEdges:\n"
        for i in range(len(self.edges)):
            result+= "\t"+str(self.edges[i])+"\n"
        result+="Error: "+str(self.error)
        return result

class Edge:

    def __init__(self, node1, node2):
        self.node1 = node1
        self.node2 = node2
        self.age = 0

    def __str__(self):
        result = "Node "+str(self.node1)\
                 +" <--"+str(self.age)+"--> "\
                 +"Node "+str(self.node2)
        return result

class GNG:

    INFTY = 1.0E16

    """
    vectorSize: size of the model vectors
    epb: learning parameter for node
    epn: learning parameter for neighborhood
    alpha: decrease in error of new node when it is inserted
    max_age: maximum age of an edge before deletion
    d: error decay rate
    """

    def __init__(self, vectorSize, maxError, epb=0.2, epn=0.006, alpha=0.6, \
                 max_age=30, d=0.995, rVector0 = [], rVector1 = []):
        self.vectorSize = vectorSize
        self.maxError = maxError
        self.epb = epb
        self.epn = epn
        self.alpha = alpha
        self.max_age = max_age
        self.d = d
        self.nodes = []
        self.error = 0
        if (len(rVector1)!=vectorSize or len(rVector2)!=vectorSize):
            for i in range(2):
                self.nodes.append(self.createRandomNode(i))
        else:
            self.nodes.append(Node(0,rVector0))
            self.nodes.append(Node(1,rVector1))

    """
    All entries to this vector between 0 and 1
    """
    def createRandomNode(self, index):
        vector = []
        for i in range(self.vectorSize):
            vector.append(random())
            
        return Node(index, vector)

    def newInput(self,vector):
        [s1, s2] = self.findNearNodes(vector)
        n1 = self.nodes[s1]
        n2 = self.nodes[s2]
        for i in range(len(n1.edges)):
            n1.edges[i].age += 1
        dist = self.dist(n1.modelVector, vector)
        n1.error+=dist*dist
        #update winner
        self.updateModelVector(n1, vector, self.epb)
        #update neighborhood of winner
        edgeExists = 0
        i = 0
        #this has to be a while statement and not a for loop because
        #len(n1.edges) might change
        while i < (len(n1.edges)):
            #find which end of the edge is NOT n1
            if (n1.edges[i].node1 != n1.index):
                node = self.nodes[n1.edges[i].node1]
            else:
                node = self.nodes[n1.edges[i].node2]
                
            self.updateModelVector(node,vector, self.epn)
            if (node.index == s2):
                edgeExists = 1
                n1.edges[i].age = 0

            else:
                n1.edges[i].age += 1
                if (n1.edges[i].age > self.max_age):
                    print "deleting edge for age, i=",i,"len(edges)=",\
                          len(n1.edges)
                    self.deleteEdge(node, n1)
                    if (len(node.edges)==0):
                        self.deleteNode(node)
            i+=1
            
        if (edgeExists == 0):
            edge = Edge(s1,s2)
            n1.edges.append(edge)
            n2.edges.append(edge)
        news = []
        if (self.error > self.maxError):
            maxNode = self.findMaxErrorNode()
            maxNeighbor = self.findMaxErrorNeighbor(maxNode)
            newVector = []
            for i in range(self.vectorSize):
                newVector.append(0.5*(maxNode.modelVector[i]\
                                 +maxNeighbor.modelVector[i]))
            for i in range(len(self.nodes)):
                if (self.nodes[i].modelVector == None):
                    break
            if (i == len(self.nodes)-1 and self.nodes[i].modelVector != None):
                i = i+1
            newNode = Node(i,newVector)
            news.append(i)
            news.append(maxNode.index)
            news.append(maxNeighbor.index)
            if i == len(self.nodes):
                self.nodes.append(newNode)
            else:
                self.nodes[i] = newNode
            self.deleteEdge(maxNode, maxNeighbor)
            edge = Edge(i, maxNode.index)
            newNode.edges.append(edge)
            maxNode.edges.append(edge)
            edge = Edge(i, maxNeighbor.index)
            newNode.edges.append(edge)
            maxNeighbor.edges.append(edge)
            maxNode.error = self.alpha*maxNode.error
            maxNeighbor.error = self.alpha*maxNeighbor.error
            newNode.error = maxNode.error
            
        self.error = 0
        num = 0
        for i in range(len(self.nodes)):
            if (self.nodes[i].modelVector != None):
                self.nodes[i].error = self.d*self.nodes[i].error
                self.error += self.nodes[i].error
                num+=1
                
        self.error = self.error/num
        #news will be an empty list if a new node was not created and will be
        #[the index of the new node, the index of the closest node, the index
        #of the neighbor node]
        return [s1, news]
        
    def findMaxErrorNode(self):
        error = -1
        node = self.nodes[0]
        for i in range (len(self.nodes)):
            if (self.nodes[i].error > error \
                and self.nodes[i].modelVector != None):
                error = self.nodes[i].error
                node = self.nodes[i]
        return node

    def findMaxErrorNeighbor(self, node):
        error = -1
        maxnode = self.nodes[0]
        for i in range(len(node.edges)):
            edge = node.edges[i]
            if (edge.node1 == node.index):
                ind = edge.node2
            else:
                ind = edge.node1
            err = self.nodes[ind].error
            if (err > error):
                error = err
                maxnode = self.nodes[ind]
        return maxnode
                
    def deleteNode(self, node):
        print "***Deleting Node***",node.index
        node.modelVector = None


    def deleteEdge(self, toNode, fromNode):
        self.deleteHalfEdge(toNode, fromNode)
        self.deleteHalfEdge(fromNode, toNode)

    def deleteHalfEdge(self, toNode, fromNode):
        for i in range(len(toNode.edges)):
            if (toNode.edges[i].node1 == fromNode.index \
                or toNode.edges[i].node2 == fromNode.index):
                del(toNode.edges[i])
                break
                
    
    def updateModelVector(self,node, vector, ep):
        for i in range(len(vector)):
            node.modelVector[i] += ep*(vector[i]-node.modelVector[i])


    def findNearNodes(self,vector):
        dist1 = self.dist(self.nodes[0].modelVector, vector)
        dist2 = self.dist(self.nodes[1].modelVector, vector)
        if (dist1 > dist2):
            tmp = dist1
            dist1 = dist2
            dist2 = tmp
            s1 = 1
            s2 = 0
        else:
            s1 = 0
            s2 = 1
        
        for i in range(2,len(self.nodes)):
            dist = self.dist(self.nodes[i].modelVector, vector)
            if (dist < dist1):
                dist2 = dist1
                dist1 = dist
                s2 = s1
                s1 = i
            elif (dist < dist2):
                dist2 = dist
                s2 = i
        return [s1, s2]

    def dist(self, v1, v2):
        """
        Returns the euclidean distance between two given
        vectors.
        """
        d = 0
        if (v1 == None or v2 == None):
            return self.INFTY

        for i in range(self.vectorSize):
            d += (v1[i] - v2[i])*(v1[i] - v2[i])
        return sqrt(d)

    def __str__(self):
        result = ""
        for i in range(len(self.nodes)):
            result += str(self.nodes[i])+"\n"
        result += "Net Error: "+str(self.error)
        return result
        
if __name__ == '__main__':
    from pyrobot.gui.plot.scatter import Scatter
    sp = Scatter(connectPoints = 0, linecount=3)
    length = 2
    gng = GNG(length, .05) # make second number smaller to match better
    print gng
    print "\n------------------------------------------------\n"
    for i in range(100):
        #vector = [(1 + sin((i+n) * 2 * pi * 3.0/70.0))/2 for n in range(2)]
        vector = [random() for x in range(length)]
        sp.addPoint(vector[0], vector[1], line = 1)
        gng.newInput(vector)
        if (i%10 == 0):
            print gng
            print "\n------------------------------------------------\n"
            sp.clear(2)
            for node in gng.nodes:
                sp.addPoint(node.modelVector[0], node.modelVector[1],
                            color = "blue", size=3, line=2)
                for edge in node.edges:
                    n1 = gng.nodes[edge.node1].modelVector
                    n2 = gng.nodes[edge.node2].modelVector
                    sp.addLine(n1[0], n1[1], n2[0], n2[1], 
                               color = "black", line=2)
            raw_input("<MORE>")

#
#   Fill in your personal details
#
#   NIU1: 1392631 Name: Josep Brugués i Pujolràs
#   NIU2: 1392661 Name: Alfonso Amayuelas Fernández
#

class Graph:
    def __init__(self,adjacent=[]):
        """
        Creates a Graph.
        :param adjacent: a list of tuples where the first element is a string
        with a node name and the second a list of strings with all its neighbors.
        """
        self.adj = dict(adjacent)


    def getNodes(self):
        """
        Provides a list of strings with all the graph nodes.
        :return : A python array with all list nodes in ascending order
        """
        nodes = self.adj.keys()
        nodes.sort()
        return nodes

    def createFromBoolMatrix(self,mat):
        """
        Transforms the occupancy matrix into the adjacency list of the graph
        :param mat: occupancy matrix from which it creates the adjacency list
        """
        def pos2name(y,x):
            """
            Auxiliary functions that return a unique node name for every point in the map
            :return :string
            """
            return 'p_'+str(x)+'_'+str(y)

        self.adj={}
        neighbors = [[0,1],[1,0],[0,-1],[-1,0]]
        for y in range(len(mat)):
            for x in range(len(mat[y])):
                if mat[y][x]==True:
                    possible = []
                    for i in range(len(neighbors)):
                        cordy = y+neighbors[i][1]
                        cordx = x+neighbors[i][0]
                        if (cordx>=0)and(cordy>=0)and(cordx<len(mat[y]))and(cordy<len(mat)):
                            if mat[cordy][cordx] == True:
                                possible.append(pos2name(cordy,cordx))
                    if len(possible)!=0:
                        self.adj[pos2name(y,x)] = possible

    def loadFromBoolMatrix(self,fname):
        """
        Loads a boolean matrix from a text file and uses it to populate the graph
        :param fname: the path to an existing text file containing a boolean matrix.
        """
        mat = [[col=='T' for col in line.strip()] for line in open(fname).read().split('\n') if len(line.strip())]
        self.createFromBoolMatrix(mat)


    def getBFS(self,p1Label,p2Label):
        """
        Finds the shortest path between two nodes if it exists.
        :param p1Label: a string with the node name to start the path
        :param p2Label: a string with the node name of the end of the path
        :return : A tuple with the length (number of vertices) of the shortest path as an
        integer and the shortest path as a python array of strings.
        If there exists no path, (-1,[]) is returned.
        """
        
        level = {p1Label:0}
        parents = {p1Label:None}
        i = 1
        border = [p1Label]
        while border:
            next = []
            for node in border:
                for neigbor in self.adj[node]:
                    if neigbor not in level:
                        level[neigbor] = i
                        parents[neigbor] = node
                        next.append(neigbor)
            border = next
            i += 1

        if p2Label in level:
            cost = level[p2Label]
            current = p2Label
            path = [current]
            while current != p1Label:
                current = parents[current]
                path.append(current)
            path.reverse()
            return (cost,path)
        else:
            return (-1,[])
   

    def isConnected(self):
        """
        Checks connectivity of the Graph.
        :return : True if the Graph is connected False otherwise
        """

        lnodes = self.getNodes()
        if lnodes:
            level = {lnodes[0]:0}
            i = 1
            border = [lnodes[0]]
            while border:
                next = []
                for node in border:
                    for neigbor in self.adj[node]:
                        if neigbor not in level:
                            level[neigbor] = i
                            next.append(neigbor)
                border = next
                i += 1

            
            for node in lnodes:
                if not level.has_key(node):
                    return False
        return True


    def __repr__(self):
        """
        :return : A string containing a python expression that can build the graph.
        """
        adjList=self.adj.items()
        for a in adjList:
            a[1].sort()
        adjList.sort()
        return 'Graph('+str(adjList)+')'

    def __eq__(self, other):
        """
        :return : True if two graphs are exactly the same.
        """
        return repr(self)==repr(other)


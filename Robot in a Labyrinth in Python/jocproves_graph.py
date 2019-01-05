# -*- coding: latin-1 -*-

import py_compile
import os
import re
import sys
import StringIO
import traceback

sum_grades = 0.0

"""
--------------------------------------------------------------------------------
Set grades
--------------------------------------------------------------------------------
"""
grades = {'trFileCompile':0.0,
          'trConstructorRepr':.5,
          'trCreateBoolMatrixNoEdge':2.0,
          'trLoadGraph':3.0,
          'trBFS':3.5,
          'trConnected':1.0}

"""
--------------------------------------------------------------------------------
Print functions
--------------------------------------------------------------------------------
"""


def error_msg():
    output = StringIO.StringIO()
    traceback.print_tb(sys.exc_traceback,None,output)
    return str(output.getvalue())

def comment(s):
    """Formats strings to create VPL comments"""
    print('Comentario :=>> ' + s)


def grade(num):
    """formats a number to create a VPL grade"""
    global sum_grades
    sum_grades = sum_grades + num

def print_grade():
    """formats a number to create a VPL grade"""
    sum(grades.values())
    
    print('Points :=>> ' + str(sum_grades) + '/'+str(sum(grades.values())))


"""
--------------------------------------------------------------------------------
Check if files exists
--------------------------------------------------------------------------------
"""
filename='Graph.py'
if os.path.isfile(filename) and os.access(filename, os.R_OK):
    comment("OK -> Source file found and readable")
else:
    comment("FAIL -> File "+filename+ " no esta en esta carpeta o no tiene permisos de lectura")
    print_grade()
    exit()

"""
--------------------------------------------------------------------------------
Check syntax
--------------------------------------------------------------------------------
"""
try:
    py_compile.compile(filename, doraise=True)
    comment('OK -> Importar '+ filename)
except py_compile.PyCompileError as e:
    comment("FAIL -> Importar "+filename+ "\n " +error_msg())
    print_grade()
    exit()

niuList=list(set([niu[1:-1] for niu in re.findall('[^0-9][0-9]{7,9}[^0-9]',open(filename).read())]))
if len(niuList)==2:
    comment('OK -> Found two NIUs in the  source file : '+' , '.join(niuList))
    grade(grades['trFileCompile'])
elif len(niuList)==1:
    comment('ATTENTION -> Found only one NIU in the  source file : '+niuList[0])
    grade(grades['trFileCompile'])
elif len(niuList)>2:
    comment('ATTENTION -> Found more than two unique NIU in the  source file : '+','.join(niuList))
    grade(grades['trFileCompile'])
else:
    comment('FAIL -> No NIU found in the source file : '+','.join(niuList))
    grade(0)
    print_grade()
    exit()


"""
--------------------------------------------------------------------------------
Import Graph
--------------------------------------------------------------------------------
"""

try:
    from Graph import Graph
    comment('OK -> from Graph import Graph\n')
except ImportError as e:
    comment("FAIL -> from Graph import Graph\n" + error_msg()+'\n')
    print_grade()
    exit()



"""
--------------------------------------------------------------------------------
Check brain_4_map
--------------------------------------------------------------------------------
"""

try:
    naive_hash=[1, 9, 5, 9, 2, 8, 10, 2, 8, 9, 4, 1]
    if ([sum([(int(row[k]=='T')*k) for k  in range(len(row))])%10+1 for row in open('maze_map.txt').read().split('\n')]) ==naive_hash:
        grade(grades['trCreateBoolMatrixNoEdge'])
        comment("OK -> maze_map.txt recoreded correctly")
    else:
        comment("FAIL -> File "+filename+ " maze_map.txt found but not correct")
        grade(grades['trCreateBoolMatrixNoEdge']*.2)
except:
    comment("FAIL -> File maze_map.txt doesn't exist or can't be read")
    grade(0)


"""
--------------------------------------------------------------------------------
Sanity check Graph constructor and __repr__
--------------------------------------------------------------------------------

"""
try:
    r=repr(Graph([('p_1_0', ['p_1_1']), ('p_1_1', ['p_1_0', 'p_2_1']), ('p_1_4', ['p_1_5', 'p_2_4']), ('p_1_5', ['p_1_4', 'p_1_6']), ('p_1_6', ['p_1_5', 'p_2_6']), ('p_2_1', ['p_1_1', 'p_2_2', 'p_3_1']), ('p_2_2', ['p_2_1']), ('p_2_4', ['p_1_4', 'p_3_4']), ('p_2_6', ['p_1_6', 'p_3_6']), ('p_3_1', ['p_2_1', 'p_4_1']), ('p_3_4', ['p_2_4', 'p_4_4']), ('p_3_6', ['p_2_6', 'p_4_6']), ('p_4_1', ['p_3_1', 'p_4_2']), ('p_4_2', ['p_4_1', 'p_4_3']), ('p_4_3', ['p_4_2', 'p_4_4']), ('p_4_4', ['p_3_4', 'p_4_3']), ('p_4_6', ['p_3_6', 'p_5_6']), ('p_5_6', ['p_4_6', 'p_5_7', 'p_6_6']), ('p_5_7', ['p_5_6', 'p_6_7']), ('p_6_1', ['p_6_2']), ('p_6_2', ['p_6_1', 'p_6_3']), ('p_6_3', ['p_6_2', 'p_6_4', 'p_7_3']), ('p_6_4', ['p_6_3', 'p_6_5']), ('p_6_5', ['p_6_4', 'p_6_6']), ('p_6_6', ['p_5_6', 'p_6_5', 'p_6_7']), ('p_6_7', ['p_5_7', 'p_6_6']), ('p_7_3', ['p_6_3'])]))
    s="Graph([('p_1_0', ['p_1_1']), ('p_1_1', ['p_1_0', 'p_2_1']), ('p_1_4', ['p_1_5', 'p_2_4']), ('p_1_5', ['p_1_4', 'p_1_6']), ('p_1_6', ['p_1_5', 'p_2_6']), ('p_2_1', ['p_1_1', 'p_2_2', 'p_3_1']), ('p_2_2', ['p_2_1']), ('p_2_4', ['p_1_4', 'p_3_4']), ('p_2_6', ['p_1_6', 'p_3_6']), ('p_3_1', ['p_2_1', 'p_4_1']), ('p_3_4', ['p_2_4', 'p_4_4']), ('p_3_6', ['p_2_6', 'p_4_6']), ('p_4_1', ['p_3_1', 'p_4_2']), ('p_4_2', ['p_4_1', 'p_4_3']), ('p_4_3', ['p_4_2', 'p_4_4']), ('p_4_4', ['p_3_4', 'p_4_3']), ('p_4_6', ['p_3_6', 'p_5_6']), ('p_5_6', ['p_4_6', 'p_5_7', 'p_6_6']), ('p_5_7', ['p_5_6', 'p_6_7']), ('p_6_1', ['p_6_2']), ('p_6_2', ['p_6_1', 'p_6_3']), ('p_6_3', ['p_6_2', 'p_6_4', 'p_7_3']), ('p_6_4', ['p_6_3', 'p_6_5']), ('p_6_5', ['p_6_4', 'p_6_6']), ('p_6_6', ['p_5_6', 'p_6_5', 'p_6_7']), ('p_6_7', ['p_5_7', 'p_6_6']), ('p_7_3', ['p_6_3'])])"
    if r==s:
        comment('Ok -> Graph.__init__() and Graph.__repr__() sanity test passed\n')
        grade(grades['trConstructorRepr'])
    else:
        comment('FAIL -> Graph.__init__() and Graph.__repr__() dissagree\n')
        grade(0)
        print_grade()
        exit()
except:
    comment('FAIL -> Graph.__init__() raised exception\n'+error_msg()+'\n')
    grade(0)
    print_grade()
    exit()


"""
--------------------------------------------------------------------------------
Cheek Graph Loading
--------------------------------------------------------------------------------
"""

try:
    correctGraphs={}
    correctGraphs['maze_map_noedge.txt']=Graph([('p_1_1', ['p_2_1']), ('p_1_4', ['p_1_5', 'p_2_4']), ('p_1_5', ['p_1_4', 'p_1_6']), ('p_1_6', ['p_1_5', 'p_2_6']), ('p_2_1', ['p_1_1', 'p_2_2', 'p_3_1']), ('p_2_2', ['p_2_1']), ('p_2_4', ['p_1_4', 'p_3_4']), ('p_2_6', ['p_1_6', 'p_3_6']), ('p_3_1', ['p_2_1', 'p_4_1']), ('p_3_4', ['p_2_4', 'p_4_4']), ('p_3_6', ['p_2_6', 'p_4_6']), ('p_4_1', ['p_3_1', 'p_4_2']), ('p_4_2', ['p_4_1', 'p_4_3']), ('p_4_3', ['p_4_2', 'p_4_4']), ('p_4_4', ['p_3_4', 'p_4_3']), ('p_4_6', ['p_3_6', 'p_5_6']), ('p_5_6', ['p_4_6', 'p_6_6']), ('p_6_1', ['p_6_2']), ('p_6_2', ['p_6_1', 'p_6_3']), ('p_6_3', ['p_6_2', 'p_6_4']), ('p_6_4', ['p_6_3', 'p_6_5']), ('p_6_5', ['p_6_4', 'p_6_6']), ('p_6_6', ['p_5_6', 'p_6_5'])])
    correctGraphs['maze_map_edge.txt']=Graph([('p_1_0', ['p_1_1']), ('p_1_1', ['p_1_0', 'p_2_1']), ('p_1_4', ['p_1_5', 'p_2_4']), ('p_1_5', ['p_1_4', 'p_1_6']), ('p_1_6', ['p_1_5', 'p_2_6']), ('p_2_1', ['p_1_1', 'p_2_2', 'p_3_1']), ('p_2_2', ['p_2_1']), ('p_2_4', ['p_1_4', 'p_3_4']), ('p_2_6', ['p_1_6', 'p_3_6']), ('p_3_1', ['p_2_1', 'p_4_1']), ('p_3_4', ['p_2_4', 'p_4_4']), ('p_3_6', ['p_2_6', 'p_4_6']), ('p_4_1', ['p_3_1', 'p_4_2']), ('p_4_2', ['p_4_1', 'p_4_3']), ('p_4_3', ['p_4_2', 'p_4_4']), ('p_4_4', ['p_3_4', 'p_4_3']), ('p_4_6', ['p_3_6', 'p_5_6']), ('p_5_6', ['p_4_6', 'p_5_7', 'p_6_6']), ('p_5_7', ['p_5_6', 'p_6_7']), ('p_6_1', ['p_6_2']), ('p_6_2', ['p_6_1', 'p_6_3']), ('p_6_3', ['p_6_2', 'p_6_4', 'p_7_3']), ('p_6_4', ['p_6_3', 'p_6_5']), ('p_6_5', ['p_6_4', 'p_6_6']), ('p_6_6', ['p_5_6', 'p_6_5', 'p_6_7']), ('p_6_7', ['p_5_7', 'p_6_6']), ('p_7_3', ['p_6_3'])])
    correctGraphs['maze_map_circle.txt']=Graph([('p_0_0', ['p_0_1']), ('p_0_1', ['p_0_0', 'p_0_2']), ('p_0_2', ['p_0_1', 'p_1_2']), ('p_10_1', ['p_11_1', 'p_9_1']), ('p_10_6', ['p_10_7', 'p_9_6']), ('p_10_7', ['p_10_6', 'p_11_7']), ('p_11_1', ['p_10_1', 'p_12_1']), ('p_11_7', ['p_10_7', 'p_11_8']), ('p_11_8', ['p_11_7', 'p_12_8']), ('p_12_1', ['p_11_1', 'p_13_1']), ('p_12_3', ['p_12_4', 'p_13_3']), ('p_12_4', ['p_12_3', 'p_12_5']), ('p_12_5', ['p_12_4', 'p_13_5']), ('p_12_8', ['p_11_8', 'p_13_8']), ('p_13_1', ['p_12_1', 'p_13_2']), ('p_13_2', ['p_13_1', 'p_13_3']), ('p_13_3', ['p_12_3', 'p_13_2']), ('p_13_5', ['p_12_5', 'p_13_6']), ('p_13_6', ['p_13_5', 'p_13_7']), ('p_13_7', ['p_13_6', 'p_13_8']), ('p_13_8', ['p_12_8', 'p_13_7']), ('p_1_2', ['p_0_2', 'p_2_2']), ('p_1_6', ['p_2_6']), ('p_1_8', ['p_2_8']), ('p_2_1', ['p_2_2', 'p_3_1']), ('p_2_2', ['p_1_2', 'p_2_1']), ('p_2_6', ['p_1_6', 'p_2_7', 'p_3_6']), ('p_2_7', ['p_2_6', 'p_2_8']), ('p_2_8', ['p_1_8', 'p_2_7', 'p_3_8']), ('p_3_1', ['p_2_1', 'p_4_1']), ('p_3_6', ['p_2_6']), ('p_3_8', ['p_2_8']), ('p_4_1', ['p_3_1', 'p_5_1']), ('p_5_1', ['p_4_1', 'p_5_2', 'p_6_1']), ('p_5_2', ['p_5_1', 'p_6_2']), ('p_6_1', ['p_5_1', 'p_6_2', 'p_7_1']), ('p_6_2', ['p_5_2', 'p_6_1', 'p_6_3']), ('p_6_3', ['p_6_2', 'p_7_3']), ('p_7_1', ['p_6_1', 'p_8_1']), ('p_7_3', ['p_6_3', 'p_7_4']), ('p_7_4', ['p_7_3', 'p_8_4']), ('p_8_1', ['p_7_1', 'p_9_1']), ('p_8_4', ['p_7_4', 'p_8_5']), ('p_8_5', ['p_8_4', 'p_9_5']), ('p_9_1', ['p_10_1', 'p_8_1']), ('p_9_5', ['p_8_5', 'p_9_6']), ('p_9_6', ['p_10_6', 'p_9_5'])])
    correctGraphs['maze_map.txt']=Graph([('p_10_1', ['p_9_1']), ('p_10_10', ['p_9_10']), ('p_10_3', ['p_9_3']), ('p_10_5', ['p_10_6', 'p_9_5']), ('p_10_6', ['p_10_5', 'p_10_7']), ('p_10_7', ['p_10_6', 'p_9_7']), ('p_1_1', ['p_2_1']), ('p_1_10', ['p_2_10']), ('p_1_3', ['p_1_4', 'p_2_3']), ('p_1_4', ['p_1_3', 'p_1_5']), ('p_1_5', ['p_1_4', 'p_1_6']), ('p_1_6', ['p_1_5', 'p_1_7']), ('p_1_7', ['p_1_6', 'p_2_7']), ('p_2_1', ['p_1_1', 'p_2_2']), ('p_2_10', ['p_1_10', 'p_3_10']), ('p_2_2', ['p_2_1', 'p_2_3', 'p_3_2']), ('p_2_3', ['p_1_3', 'p_2_2']), ('p_2_7', ['p_1_7', 'p_3_7']), ('p_3_10', ['p_2_10', 'p_3_9']), ('p_3_2', ['p_2_2', 'p_4_2']), ('p_3_5', ['p_4_5']), ('p_3_7', ['p_2_7', 'p_3_8']), ('p_3_8', ['p_3_7', 'p_3_9']), ('p_3_9', ['p_3_10', 'p_3_8', 'p_4_9']), ('p_4_2', ['p_3_2', 'p_5_2']), ('p_4_4', ['p_4_5']), ('p_4_5', ['p_3_5', 'p_4_4', 'p_5_5']), ('p_4_9', ['p_3_9', 'p_5_9']), ('p_5_10', ['p_5_9', 'p_6_10']), ('p_5_2', ['p_4_2', 'p_6_2']), ('p_5_5', ['p_4_5', 'p_5_6']), ('p_5_6', ['p_5_5', 'p_6_6']), ('p_5_9', ['p_4_9', 'p_5_10']), ('p_6_1', ['p_6_2']), ('p_6_10', ['p_5_10', 'p_7_10']), ('p_6_2', ['p_5_2', 'p_6_1', 'p_6_3', 'p_7_2']), ('p_6_3', ['p_6_2', 'p_6_4']), ('p_6_4', ['p_6_3']), ('p_6_6', ['p_5_6', 'p_6_7', 'p_7_6']), ('p_6_7', ['p_6_6']), ('p_7_10', ['p_6_10', 'p_7_9']), ('p_7_2', ['p_6_2', 'p_8_2']), ('p_7_5', ['p_7_6', 'p_8_5']), ('p_7_6', ['p_6_6', 'p_7_5']), ('p_7_8', ['p_7_9', 'p_8_8']), ('p_7_9', ['p_7_10', 'p_7_8']), ('p_8_2', ['p_7_2', 'p_9_2']), ('p_8_5', ['p_7_5', 'p_9_5']), ('p_8_8', ['p_7_8', 'p_9_8']), ('p_9_1', ['p_10_1', 'p_9_2']), ('p_9_10', ['p_10_10', 'p_9_9']), ('p_9_2', ['p_8_2', 'p_9_1', 'p_9_3']), ('p_9_3', ['p_10_3', 'p_9_2']), ('p_9_5', ['p_10_5', 'p_8_5']), ('p_9_7', ['p_10_7', 'p_9_8']), ('p_9_8', ['p_8_8', 'p_9_7', 'p_9_9']), ('p_9_9', ['p_9_10', 'p_9_8'])])
    comment('OK -> Graph construction')
except:
    comment('FAIL -> Graph construction\n'+error_msg())
    grade(0)
    print_grade()
    exit()

loadScore=[0.0 for k in range(len(correctGraphs))]
counter=0
for fname in correctGraphs.keys():
    correctGraph=correctGraphs[fname]
    try:
        g=Graph();
        g.loadFromBoolMatrix(fname)
        if g==correctGraph:
            loadScore[counter]+=1
            comment('OK -> Load matrix in to graph from '+fname)
        else:
            loadScore[counter]+=.2
            comment('FAIL -> Load matrix in to graph from '+fname+' produced wrong graph')
    except:
        comment('FAIL -> Load matrix in to graph from '+fname+' threw exceprion')
    counter+=1
grade(grades['trLoadGraph']*(sum(loadScore)/len(loadScore)))
if (sum(loadScore)/len(loadScore))>=1:
    comment('OK -> Load matrix test completed successfully\n')
else:
    comment('FAIL -> Load matrix test completed with errors\n')


"""
--------------------------------------------------------------------------------
Cheek BFS length
--------------------------------------------------------------------------------
"""

bfsAnswers={('p_7_1', 'p_13_8'):(15, ['p_7_1', 'p_8_1', 'p_9_1', 'p_10_1', 'p_11_1', 'p_12_1', 'p_13_1', 'p_13_2', 'p_13_3', 'p_12_3', 'p_12_4', 'p_12_5', 'p_13_5', 'p_13_6', 'p_13_7', 'p_13_8']),
('p_6_1', 'p_13_8'):(14, ['p_6_1', 'p_6_2', 'p_6_3', 'p_7_3', 'p_7_4', 'p_8_4', 'p_8_5', 'p_9_5', 'p_9_6', 'p_10_6', 'p_10_7', 'p_11_7', 'p_11_8', 'p_12_8', 'p_13_8']),
('p_1_8', 'p_3_6'):(4, ['p_1_8', 'p_2_8', 'p_2_7', 'p_2_6', 'p_3_6']),
('p_1_8', 'p_13_1'):(-1, []),('p_1_8', 'p_1_8'):(0, ['p_1_8'])}
bfsScore=[0.0 for k in range(len(bfsAnswers))]
counter=0
try:
    g=Graph()
    g.loadFromBoolMatrix('maze_map_circle.txt')
    for nodes in bfsAnswers.keys():
        ans=bfsAnswers[nodes]
        try:
            bfs=g.getBFS(nodes[0],nodes[1])
            if bfs[0]==ans[0]:
                bfsScore[counter]+=.3
            if bfs[1]==ans[1]:
                bfsScore[counter]+=.7
            if bfs==ans:
                comment('OK -> BSM for maze_map_circle.txt failed for path from '+nodes[0]+' to '+nodes[1]+' succeded')
            else:
                comment('FAIL -> BFS for maze_map_circle.txt failed for path from '+nodes[0]+' to '+nodes[1]+' failed '+str(bfs))
        except:
            comment('FAIL BFS for maze_map_circle.txt failed for path from '+nodes[0]+' to '+nodes[1]+' raised an exception\n'+error_msg()+'\n')
        counter+=1
except:
    comment('FAIL BFS could not load maze_map_circle.txt\n'+error_msg()+'\n')

grade(grades['trBFS']*(sum(bfsScore)/len(bfsScore)))
if (sum(bfsScore)/len(bfsScore))>=1:
    comment('OK -> BFS search test completed successfully\n')
else:
    comment('FAIL -> BFS search test completed with errors\n')


"""
--------------------------------------------------------------------------------
Cheek connectivity
--------------------------------------------------------------------------------
"""
try:
    connectedAnswers={'maze_map_circle.txt':False,'maze_map_edge.txt':True,'maze_map_noedge.txt':True,'maze_map_empty.txt':True}
    connectScore=[0.0 for k in range(len(connectedAnswers))]
    counter=0
    for fname in connectedAnswers.keys():
        connected=connectedAnswers[fname]
        try:
            g=Graph()
            g.loadFromBoolMatrix(fname)
            if g.isConnected()==connected:
                connectScore[counter]+=1
        except:
            comment('FAIL -> connectivity could not load '+fname+' and check its connectivity\n'+error_msg())
        counter+=1
except:
    comment('FAIL -> connectivity could not load '+fname+' and check its connectivity\n'+error_msg())

grade(grades['trConnected']*(sum(connectScore)/len(connectScore)))
if (sum(connectScore)/len(connectScore))>=.99999999999:
    comment('OK -> connectivity test completed successfully\n')
else:
    comment('FAIL -> connectivity test completed with errors\n')



"""
--------------------------------------------------------------------------------
Print grades
--------------------------------------------------------------------------------
"""
print_grade()
print "Final points might change upon inspection of the source by the teacher and other factors."

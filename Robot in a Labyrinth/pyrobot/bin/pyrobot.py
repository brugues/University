
"""
Pyrobot - Python Robotics
(c) 2005, PyroRobotics.org. Licensed under the GNU GPL.

THIS FILE IS AUTOMATICALLY GENERATED
"""
import os, sys, posixpath

__author__ = "Douglas Blank <dblank@brynmawr.edu>"
__version__ = "$Revision: 1.3 $"

# Where are we? Compute cwd 
# ----------------------------------------------------
if os.name in ['nt', 'dos', 'os2']:
    if sys.argv[0][1] == ':' and sys.argv[0][2] == '\\':
        cwd = sys.argv[0]
    else:
        cwd = os.getcwd() + '\\' + sys.argv[0]
elif os.name in ['posix']:
    if sys.argv[0][0] == '/':
        cwd = sys.argv[0]
    else:
        cwd = os.getcwd() + '/' + sys.argv[0]
else:
    raise AttributeError, "your OS (%s) is not supported" % os.name
# ----------------------------------------------------
# Add cwd to our PYTHON search path
# ----------------------------------------------------
(binpath,spare) = os.path.split(cwd) # peel off pyrobot filename
(pyropath,spare) = os.path.split(binpath) # peel off bin dir
(path,spare) = os.path.split(pyropath) # peel off pyro dir
sys.path.insert(0, path) # put PARENT at front of list PARENT/pyro/bin/pyro
# ----------------------------------------------------
# Make sure environment is setup:
# ----------------------------------------------------
if os.name in ['nt', 'dos', 'os2']:
    os.environ['EDITOR'] = 'notepad'
    os.putenv('EDITOR', 'notepad')
    os.environ['HOME'] = 'C:\\'
    os.putenv('HOME', 'C:\\')
    os.environ['HOSTNAME'] = os.getenv('COMPUTERNAME')
    os.putenv('HOSTNAME', os.getenv('COMPUTERNAME'))
if os.environ.has_key('PYROBOT') and os.environ["PYROBOT"] != '':
    pass
else:
    if posixpath.exists(pyropath + "/plugins"):
        os.environ['PYROBOT'] = pyropath
        os.putenv('PYROBOT', pyropath )
    else:
        pyropathguess = "/usr/lib/python%s/site-packages/pyrobot" % sys.version[0:3]
        if posixpath.exists(pyropathguess):
            os.environ['PYROBOT'] = pyropathguess
            os.putenv('PYROBOT', pyropathguess )
        else:
            pyropathguess = "/usr/local/lib/python%s/site-packages/pyrobot" % sys.version[0:3]
            if posixpath.exists(pyropathguess):
                os.environ['PYROBOT'] = pyropathguess
                os.putenv('PYROBOT', pyropathguess )
            else:
                raise "Can't find pyrobot directory! Put in python%s/site-packages/ OR run pyrobot directly from the installation directory" % sys.version[0:3]
if not os.environ.has_key('HOSTNAME'):
    os.environ['HOSTNAME'] = 'computer'
    os.putenv('HOSTNAME', 'computer' )
# add PYROBOT to PYTHONPATH first
spare = ''
path = os.environ["PYROBOT"] 
while spare == '':
   (path,spare) = os.path.split(path) # peel off pyrobot dir
sys.path.insert(0, path) # add PYROBOT to PYTHON and OS search path
if "PYTHONPATH" in os.environ:
    os.environ["PYTHONPATH"] = path + ":" + os.environ["PYTHONPATH"]
else:
    os.environ["PYTHONPATH"] = path
# at end of path, in case you have others:
os.environ["PATH"] += ":%s/plugins/simulators" % os.environ["PYROBOT"] 
# ------------------------------ All done with environment business!
try:
    from pyrobot.system import share
    from pyrobot.engine import *
except ImportError:
    raise "You need to run 'make' in %s" % (os.environ["PYROBOT"],)
print "Using PYROBOT in '%s'..." % (os.environ["PYROBOT"],)
robotfile = 0
devices = 0
vars = []
brainfile = 0
window = 'TK'
pyroargs = []
simulator = 0
configfile = 0
worldfile = 0
evalcommand = ""

def basichelp():
    print "You may need to define the PYROBOT environment variable. Try:"
    print "         export PYROBOT=/usr/lib/python2.3/site-packages/pyrobot"
    print "or maybe export PYROBOT=~/pyrobot"
    print ""
    print "Also, make sure PYROBOT is in PYTHONPATH. Try:"
    print "         export PYTHONPATH=$PYTHONPATH:$PYROBOT"
    print "(if it isn't already in Python's path)"
try:
    import pyrobot
except:
    import sys
    basichelp()
    sys.exit(1)


def process_options():
    import getopt, sys, string
    global robotfile, brainfile, window, simulator, \
           pyroargs, configfile, evalcommand, worldfile, devices
    try:
        opts, args = getopt.getopt(sys.argv[1:], \
                                   "r:b:hg:s:a:i:e:w:d:c:v:", \
                                   ["robot=", "brain=", "help", \
                                    "gui=", "sim=", "args=",\
                                    "init=", "eval=", "world=",
                                    "devices=", "config=", "var="])
    except getopt.GetoptError:
        # print help information and exit:
        pyrobot.system.usage()
        sys.exit(1)

    for o, a in opts:
        if o in ("-h", "--help"):
            pyrobot.system.usage()
            sys.exit(1)
        elif o in ("-g", "--gui"):
            window = string.upper(a)
        elif o in ("-r", "--robot"):
            robotfile = a
        elif o in ("-s", "--sim"):
            simulator = a
        elif o in ("-b", "--brain"):
            brainfile = a
	elif o in ("-a", "--args"):
            pyroargs = a
	elif o in ("-i", "--init"):
            configfile = a
	elif o in ("-w", "--world", "-c", "--config"):
            worldfile = a
	elif o in ("-d", "--devices"):
            devices = a
	elif o in ("-e", "--eval"):
            evalcommand = a
	elif o in ("-v", "--var"):
            vars.append( a )

if pyrobot.startup_check():
    import pyrobot.system
    from pyrobot.system.config import Configuration
    process_options()
    c = Configuration(configfile)
    if configfile:
        c.put('config', 'file', configfile)
    if not robotfile:
        robotfile = c.get('robot', 'file')
    else:
        c.put('robot', 'file', robotfile)
    if not devices:
        devices = c.get('robot', 'devices')
    else:
        c.put('robot', 'devices', devices)
    if not simulator:
        simulator = c.get('simulator', 'file')
    else:
        c.put('simulator', 'file', simulator)
    if not brainfile:
        brainfile = c.get('brain', 'file')
    else:
        c.put('brain', 'file', brainfile)
    if not worldfile:
        worldfile = c.get('world', 'file')
    else:
        c.put('world', 'file', worldfile)
    if not pyroargs:
        pyroargs = c.get('pyrobot', 'args')
    else:
        c.put('pyrobot', 'args', pyroargs)
    c.put('pyrobot', 'gui', window)
    for var in vars:
        section, variableValue = var.split(".")
        variable, value = variableValue.split("=")
        c.put(section, variable, value)
    share.config = c
    if devices == None:
        devices = ""
    ## need to make root here, before we load brain
    ## in case brain has gui things
    if window == "TK":
        import Tkinter
        # save it, in case we need it:
        import pyrobot.system.share as share
        if not share.gui:
            try:
                share.gui = Tkinter.Tk()
                share.gui.withdraw()
            except:
                window = 'TTY'
    eng = Engine(robotfile, brainfile, simulator,
                 pyroargs, c, worldfile, devices.split(",") )
    if window == 'GL':
        from pyrobot.gui.GL import GLgui
        gui = GLgui(eng)
        gui.win.redraw = gui.redraw
    elif window == 'TK':
        from pyrobot.gui.TK import TKgui
        gui = TKgui(eng)
    elif window == 'SIMPLE':
        gui = pyrobot.gui.gui("tty gui", {}, eng)
    elif window == 'TTY':
        from pyrobot.gui.tty import TTYGui
        gui = TTYGui(engine = eng)
    elif window == 'CURSES':
        from pyrobot.gui.Curses import Curses as Curses
        gui = Curses("curses gui", {}, eng)
    if evalcommand != "":
        evalcommand = evalcommand.split(';')
    else:
        evalcommand = []
    gui.run(evalcommand)
    gui.cleanup()
else:
    basichelp()

__author__ = "Matt Fiedler"
__version__ = "$Revision: 1.4 $"

from pyrobot.brain.conx import *

from pyrobot.brain.VisConx import VisRobotConx
from pyrobot.brain.VisConx import VisSweepConx

VNetwork = VisSweepConx.VisSweepNetwork
VINetwork = VisRobotConx.VisRobotNetwork

VSRN = VisSweepConx.VisSweepSRN
VISRN = VisRobotConx.VisRobotSRN

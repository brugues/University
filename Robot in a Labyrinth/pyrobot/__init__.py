from os import getenv

__author__ = "Douglas Blank <dblank@brynmawr.edu>"
__version__ = "$Revision: 1.3 $"


def pyrobotdir():
    return getenv("PYROBOT")

def startup_check():
    return pyrobotdir() != None

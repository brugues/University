# A log class

import time, os, posixpath

class Log:
   """
   A log class to do automatically what needs to be done for each
   experiment.
   """
   def __init__(self,filename = None, name = None, robot = None, brain = None,
                echo = 1, mode = 'w'):
      """
      Pass in robot and brain so that we can query them (and maybe make
      copies and query them on occation).
      If echo is True, then it will echo the log file to the terminal
      """
      self.open = 1
      timestamp = self.timestamp()
      if filename == None:
         filename= timestamp + '.log'
         while posixpath.exists(filename):
            timestamp = self.timestamp()
            filename = timestamp + '.log'
      self.filename = filename
      self.file = open(filename, mode)
      self.echo = echo
      if mode == 'a':
         self.writeln('... Continuing log at ' + timestamp)
      else:
         self.writeln("Log opened: " + timestamp)
      if name != None:
         self.writeln('Experiment name: ' + name)
      if robot != None:
         self.writeln('Robot: ' + robot.type)
      if brain != None:
         self.writeln('Brain: ' + brain.name)
      if os.environ.has_key('HOSTNAME'):
         self.writeln('Hostname: ' + os.environ['HOSTNAME'])
      if os.environ.has_key('USER'):
         self.writeln('User: ' + os.environ['USER'])
   def timestamp(self):
      year,month,day,hour,minute,second,one,two,three=time.localtime()
      return '%4d.%02d.%02d-%02d.%02d.%02d' % (year, month, day, hour, minute, second)
   def flush(self):
      self.file.flush()

   def write(self, msg):
      """ Write a string to the log """
      if self.echo:
         print msg,
      if self.open:
         self.file.write(msg)
         self.file.flush()

   def writeln(self, msg):
      """ Write a line (with newline) to the log """
      if self.echo:
         print msg
      if self.open:
         self.file.write(msg + "\n")
         self.file.flush()

   def close(self):
      """ Close the log """
      if self.open:
         year,month,day,hour,minute,second,one,two,three=time.localtime()
         self.writeln("Log closed: " + self.timestamp())
         self.file.close()
         self.open = 0
   
if __name__ == '__main__':
   log = Log()
   log.write("testing...")
   log.write("testing...")
   log.writeln("tested!")
   log.close()
   log.write("testing...")
   log.write("testing...")
   log.writeln("tested!")
   log.close()

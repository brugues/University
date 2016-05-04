OBJS = _robocup.so

include ../../Makefile.cfg
include ../../Makefile.src

INCLUDE = -I../device/
CPPFLAGS = -Wall -Wno-unused -D_POSIX_THREADS \
	-D_POSIX_THREAD_SAFE_FUNCTIONS \
	-D_REENTRANT -DPOSIX \
	-D__x86__ -D__linux__ \
	-D__OSVERSION__=2 -frepo -DUSINGTHREADS -DLINUX -D_GNU_SOURCE \
	$(PYTHON_INCLUDE) $(INCLUDE)

LIBDIRS= 
LIBS= -lstdc++ -ldl -lpthread

../device/Device.o: ../device/Device.h ../device/Device.cpp
	cd ../device/; make

_robocup.so: robocup.o Robocup.o 
	$(CC) $(CPPFLAGS) -shared robocup.o Robocup.o ../device/Device.o $(LIBDIRS) -o $@ $(LIBS)

Robocup.o:: Robocup.cpp Robocup.h ../device/Device.o
	$(CC) $(CPPFLAGS) -o $@ -c Robocup.cpp

Robocup.cc: Robocup.i Robocup.h ../device/Device.o
	swig -python -c++ $(INCLUDE) -o Robocup.cc Robocup.i

robocup.o: Robocup.cc 
	$(CC) -c $(PYTHON_INCLUDE) $(INCLUDE) Robocup.cc -o $@

clean::
	$(RM) *~ *.so *.o Robocup.cc robocup.py



OBJS = _geometry.so

include ../../Makefile.cfg
include ../../Makefile.src

INCLUDE = 
CPPFLAGS = -O3 -Wall -Wno-unused -D_POSIX_THREADS \
	-D_POSIX_THREAD_SAFE_FUNCTIONS \
	-D_REENTRANT -DPOSIX \
	-D__x86__ -D__linux__ \
	-D__OSVERSION__=2 -frepo -DUSINGTHREADS -DLINUX -D_GNU_SOURCE \
	$(PYTHON_INCLUDE) $(INCLUDE)

LIBS= -lstdc++ -ldl -lpthread

_geometry.so: geometry.o Geometry.o
	$(CC) $(CPPFLAGS) -shared $^ $(LIBDIRS) -o $@ $(LIBS)

Geometry.o:: Geometry.cpp
	$(CC) $(CPPFLAGS) -o $@ -c $<

Geometry.cc: Geometry.i Geometry.h Geometry.cpp
	swig $(INCLUDE) -python -c++ -o $@ Geometry.i

geometry.o: Geometry.cc
	$(CC) -c $(PYTHON_INCLUDE) $(INCLUDE) $^ -o $@

clean::
	$(RM) *~ *.so *.o *.cc *.so *.pyc geometry.py


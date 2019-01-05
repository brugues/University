OBJS = _fourway.so

include ../../Makefile.cfg
include ../../Makefile.src

INCLUDE = -I../device/
CPPFLAGS = -O3 -Wall -Wno-unused -D_POSIX_THREADS \
	-D_POSIX_THREAD_SAFE_FUNCTIONS \
	-D_REENTRANT -DPOSIX \
	-D__x86__ -D__linux__ \
	-D__OSVERSION__=2 -frepo -DUSINGTHREADS -DLINUX -D_GNU_SOURCE \
	$(PYTHON_INCLUDE) $(INCLUDE)

LIBS= -lstdc++ -ldl -lpthread

../device/Device.o: ../device/Device.h ../device/Device.cpp
	cd ../device/; make

_fourway.so: fourway.o Fourway.o 
	$(CC) $(CPPFLAGS) -shared fourway.o Fourway.o ../device/Device.o -o $@ $(LIBS)

Fourway.o:: Fourway.cpp Fourway.h ../device/Device.o
	$(CC) $(CPPFLAGS) -o $@ -c Fourway.cpp

Fourway.cc: Fourway.i Fourway.h ../device/Device.o
	swig -python -c++ $(INCLUDE) -o Fourway.cc Fourway.i

fourway.o: Fourway.cc 
	$(CC) -c $(PYTHON_INCLUDE) $(INCLUDE) Fourway.cc -o $@

clean::
	$(RM) *~ *.so *.o fourway.py Fourway.cc


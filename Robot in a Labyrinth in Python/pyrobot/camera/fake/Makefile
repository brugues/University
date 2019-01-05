OBJS = _fake.so

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

_fake.so: fake.o Fake.o 
	$(CC) $(CPPFLAGS) -shared fake.o Fake.o ../device/Device.o -o $@ $(LIBS)

Fake.o:: Fake.cpp Fake.h ../device/Device.o
	$(CC) $(CPPFLAGS) -o $@ -c Fake.cpp

Fake.cc: Fake.i Fake.h ../device/Device.o
	swig -python -c++ $(INCLUDE) -o Fake.cc Fake.i

fake.o: Fake.cc 
	$(CC) -c $(PYTHON_INCLUDE) $(INCLUDE) Fake.cc -o $@

clean::
	$(RM) *~ *.so *.o fake.py Fake.cc


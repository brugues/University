OBJS = _blob.so

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

_blob.so: blob.o Blob.o 
	$(CC) $(CPPFLAGS) -shared blob.o Blob.o ../device/Device.o $(LIBDIRS) -o $@ $(LIBS)

Blob.o:: Blob.cpp Blob.h ../device/Device.o
	$(CC) $(CPPFLAGS) -o $@ -c Blob.cpp

Blob.cc: Blob.i Blob.h ../device/Device.o
	swig -python -c++ $(INCLUDE) -o Blob.cc Blob.i

blob.o: Blob.cc 
	$(CC) -c $(PYTHON_INCLUDE) $(INCLUDE) Blob.cc -o $@

clean::
	$(RM) *~ *.so *.o Blob.cc blob.py


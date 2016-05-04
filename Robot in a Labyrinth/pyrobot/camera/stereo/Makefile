OBJS = _stereo.so
#OOBJS = error.o match_scanlines.o pnmio.o postprocess.o

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

_stereo.so: stereo.o Stereo.o
	$(CC) $(CPPFLAGS) -shared stereo.o Stereo.o ../device/Device.o $(OOBJS) -o $@ $(LIBS)

Stereo.o:: Stereo.cpp Stereo.h ../device/Device.o
	$(CC) $(CPPFLAGS) -o $@ -c Stereo.cpp

Stereo.cc: Stereo.i Stereo.h ../device/Device.o
	swig -python -c++ $(INCLUDE) -o Stereo.cc Stereo.i

stereo.o: Stereo.cc 
	$(CC) -c $(PYTHON_INCLUDE) $(INCLUDE) Stereo.cc -o $@

clean::
	$(RM) *~ *.so *.o stereo.py Stereo.cc p2p

#error.o: error.c error.h
#	$(CC) -O3 $(LIBS) -c $<
#match_scanlines.o: match_scanlines.c
#	$(CC) -O3 $(LIBS) -c $<
#pnmio.o: pnmio.c pnmio.h
#	$(CC) -O3 $(LIBS) -c $<
#postprocess.o: postprocess.c
#	$(CC) -O3 $(LIBS) -c $<


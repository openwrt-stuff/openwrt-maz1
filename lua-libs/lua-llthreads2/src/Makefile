CC?=gcc
CXX?=g++
CFLAGS+=-O2 -fPIC -DVERSION="2.8.0" -DLUA_COMPAT_5_2
CXXFLAGS+=-O2 -fPIC -DVERSION="2.8.0" -DLUA_COMPAT_5_2
LIBS=l52util.o llthread.o
all:: llthreads $(LIBS)
llthreads: $(LIBS)
	$(CC) -shared -o llthreads.so $(LIBS) -lpthread
l52util.o: l52util.h

clean:
	rm -f $(LIBS) llthreads.so
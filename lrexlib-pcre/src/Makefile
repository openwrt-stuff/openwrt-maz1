CC?=gcc
CXX?=g++
CFLAGS+=-O2 -fPIC -DVERSION="2.8.0" -DLUA_COMPAT_5_2
CXXFLAGS+=-O2 -fPIC -DVERSION="2.8.0" -DLUA_COMPAT_5_2
LIBS=common.o lpcre.o lpcre_f.o 
all:: rex_pcre $(LIBS)
rex_pcre: $(LIBS)
	$(CC) -shared -o rex_pcre.so $(LIBS) -lpcre
common.o: common.h
lpcre.o: common.h algo.h
lpcre_f.o: common.h

clean:
	rm -f $(LIBS) rex_pcre.so
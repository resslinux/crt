CC ?= clang
LIBDIR ?= /usr/lib

all: crtbeginS.o crtendS.o

crtbeginS.o: 
	$(CC) $(CFLAGS) -fPIC -c "crtbegin.c" -o "crtbeginS.o"

crtendS.o: 
	$(CC) $(CFLAGS) -fPIC -c "crtend.c" -o "crtendS.o"

install: crtbeginS.o crtendS.o
	install -d $(DESTDIR)$(LIBDIR)
	install -m 0644 crtbeginS.o $(DESTDIR)$(LIBDIR)
	install -m 0644 crtendS.o $(DESTDIR)$(LIBDIR)
	
	ln -s crtbeginS.o $(DESTDIR)$(LIBDIR)/crtbegin.o
	ln -s crtbeginS.o $(DESTDIR)$(LIBDIR)/crtbeginT.o
	
	ln -s crtendS.o $(DESTDIR)$(LIBDIR)/crtend.o
	ln -s crtendS.o $(DESTDIR)$(LIBDIR)/crtendT.o

clean:
	rm crtbeginS.o crtendS.o

.PHONY: all
.PHONY: install
.PHONY: clean

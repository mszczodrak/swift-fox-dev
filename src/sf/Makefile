C=cc
LEX=lex
YACC=yacc
CFLAGS=-c -Wall 
CFLAGS+=-I$(FENNEC_FOX_LIB)/Fennec/ -DSWIFT_FOX
LDFLAGS=-ly -ll
SRCS=traverse.o utils.o sem_check.o code_gen_engine.o \
        code_gen_caches.o code_gen_modules.o code_gen_default_params.o \
        code_gen_params.o code_gen_globals.o code_gen.o

prefix=/usr/local
exec_prefix=$(prefix)
bindir=$(exec_prefix)/bin

INSTALL=cp
INSTALL_PROGRAM=$(INSTALL)
INSTALL_DATA=${INSTALL} -m 644

UNINSTALL=rm
UNINSTALL_PROGRAM=$(UNINSTALL)

all: sfc fennec 

sfc: lex.yy.o $(SRCS) sf_driver.c
	$(CC) y.tab.c lex.yy.o $(SRCS) sf_driver.c $(LDFLAGS) -o sfc

ley.yy.o: lex.yy.c
	$(CC) $(CFLAGS) lex.yy.c

#traverse.o: traverse.c
#	$(CC) $(CFLAGS) traverse.c

sem_check.o: sem_check.c sem_check.h
	$(CC) $(CFLAGS) sem_check.c

#code_gen_engine.o: code_gen_engine.c
#	$(CC) $(CFLAGS) code_gen_engine.c

#code_gen.o: code_gen.c
#	$(CC) $(CFLAGS) code_gen.c

lex.yy.c: y.tab.c sf.l
	$(LEX) sf.l

y.tab.c: sf.y sf.h
	$(YACC) -d sf.y

fennec: fennec.c
	$(CC) -Wall fennec.c -o fennec

install:
	$(INSTALL_PROGRAM) sfc $(bindir)/sfc
	$(INSTALL_PROGRAM) fennec $(bindir)/fennec

uninstall:
	$(UNINSTALL_PROGRAM) $(bindir)/sfc
	$(UNINSTALL_PROGRAM) $(bindir)/fennec

clean:
	rm -rf *o sfc fennec y.tab.c y.tab.h lex.yy.c

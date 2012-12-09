PARSER = sf.y sf.l
AM_YFLAGS = -d
BUILT_SOURCES = sf.h
AM_CFLAGS= -g -O3 -Wall

bin_PROGRAMS=sfc fennec

sfc_SOURCES=sf.h traverse.h sem_check.h code_gen.h utils.h \
	sf_driver.c traverse.c utils.c sem_check.c code_gen_engine.c \
        code_gen_caches.c code_gen_default_params.c \
        code_gen_events.c code_gen_params.c code_gen_globals.c code_gen.c

fennec_SOURCES=fennec.c


AUTOMAKE_OPTIONS = subdir-objects
bin_PROGRAMS = \
    moba-sniffer

moba_sniffer_SOURCES = \
    main.cpp \
    handler.cpp \
    s88sniffer.cpp

moba_sniffer_LDADD = \
    -lmobacommon \
    $(srcdir)/../modules/lib-cs2interface/src/moba/libcs2interface.a \
    -lz \
    -lncurses

LDFLAGS += -L/usr/local/lib

AM_CPPFLAGS = \
    -I$(srcdir)/../modules/lib-cs2interface/src \
    -g3 -ggdb -O3 -Wall

ACLOCAL_AMFLAGS = -I m4

CLEANFILES = *~

AUTOMAKE_OPTIONS = subdir-objects
bin_PROGRAMS = \
    moba-sniffer
moba_sniffer_SOURCES = \
    main.cpp \
    frmmain.cpp \
    cs2connector.cpp


moba_sniffer_LDADD = -lMoBaCommon $(GTKMM_LIBS)
LDFLAGS += -L/usr/local/lib

AM_CPPFLAGS = $(GTKMM_CFLAGS)

CLEANFILES = *~

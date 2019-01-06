AC_PREREQ([2.69])
AC_INIT([moba-sniffer], [0.1.0-0000], [pappi-@gmx.de])

AC_CONFIG_SRCDIR([src])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([foreign])

# Checks for programs.
AC_PROG_CXX

PKG_CHECK_MODULES([GTKMM], [gtkmm-3.0])

AX_CXX_COMPILE_STDCXX_11()

AC_CONFIG_FILES([
    Makefile
    src/Makefile
])

AC_OUTPUT

#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(Sigschege, 0.0, suupkopp@user.berlios.de)
AC_CONFIG_SRCDIR([src/EventList.cpp])
AM_INIT_AUTOMAKE

AM_CONFIG_HEADER([src/config.h])

# Checks for programs.
AC_PROG_LIBTOOL
AC_PROG_CXX

# Checks for libraries.

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CONFIG_FILES([Makefile src/Makefile EasyVec/Makefile EasyVec/src/Makefile])
AC_OUTPUT

#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(Sigschege, 0.0, suupkopp@user.berlios.de)
AC_CONFIG_SRCDIR([src/EventList.cpp])
AM_INIT_AUTOMAKE
AC_LANG(C++)
AC_PROG_LIBTOOL

AM_CONFIG_HEADER(src/config.h)

# Checks for programs.
#AC_PROG_LIBTOOL
AC_PROG_INSTALL
AC_PROG_CXX

AC_CHECK_PROG(WX_CONFIG,wx-config,yes)
if test "$WX_CONFIG" == ""; then
 AC_MSG_ERROR([wx-config not found]);
 exit;
fi

AC_CHECK_PROG(FREETYPE_CONFIG,freetype-config,yes)
if test "$FREETYPE_CONFIG" == ""; then
 AC_MSG_ERROR([freetype-config not found]);
 exit;
fi

AC_CHECK_PROG(DOXYGEN,doxygen,yes)
if test "$DOXYGEN" == ""; then
 AC_MSG_ERROR([doxygen not found]);
 exit;
fi

# Checks for libraries.


# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([/usr/include/python2.5/Python.h]      ,[AC_SUBST(INC_PYTHON,[/usr/include/python2.5])],[
AC_CHECK_HEADERS([/usr/include/python2.5/Python.h]      ,[AC_SUBST(INC_PYTHON,[/usr/include/python2.5])],[
AC_CHECK_HEADERS([/usr/include/python2.4/Python.h]      ,[AC_SUBST(INC_PYTHON,[/usr/include/python2.4])],[
AC_CHECK_HEADERS([/usr/include/python2.4/Python.h]      ,[AC_SUBST(INC_PYTHON,[/usr/include/python2.4])],[
AC_CHECK_HEADERS([/usr/include/Python.h]                ,[AC_SUBST(INC_PYTHON,[/usr/include])],[
AC_CHECK_HEADERS([/usr/local/include/python2.4/Python.h],[AC_SUBST(INC_PYTHON,[/usr/local/include/python2.4])],[
AC_CHECK_HEADERS([/usr/local/include/Python.h]          ,[AC_SUBST(INC_PYTHON,[/usr/local/include])],[AC_MSG_ERROR([Python.h no found!]);exit;])])])])])])])



# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CONFIG_FILES([Makefile src/Makefile YaVec/Makefile YaVec/src/Makefile])
AC_OUTPUT

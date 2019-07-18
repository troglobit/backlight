AC_INIT([backlight], [0.1], [https://github.com/troglobit/backlight/issues])

AM_INIT_AUTOMAKE([1.11 foreign])
AM_SILENT_RULES([yes])

AC_CONFIG_SRCDIR([backlight.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile])

AC_PROG_CC
AC_PROG_INSTALL

PKG_PROG_PKG_CONFIG
PKG_CHECK_VAR([UDEVDIR], [udev], [udevdir])

AC_OUTPUT

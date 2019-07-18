AC_INIT([backlight], [0.1], [https://github.com/troglobit/backlight/issues])

AM_INIT_AUTOMAKE([1.11 foreign])
AM_SILENT_RULES([yes])

AC_CONFIG_SRCDIR([backlight.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile])

AC_PROG_CC
AC_PROG_INSTALL
PKG_PROG_PKG_CONFIG

AC_ARG_WITH([udev-rules-dir],
        AS_HELP_STRING([--with-udev-rules-dir], [Directory for udev rules, default: auto]),
	[udevdir=$withval], [udevdir=auto])

AS_IF([test "x$udevdir" = "xyes" -o "x$udevdir" = "xauto"], [
	PKG_CHECK_VAR([UDEVDIR], [udev], [udevdir])
  	AS_IF([test "x$UDEVDIR" = "x"],
		AC_MSG_ERROR([pkg-config unable to find udev rules directory]),)
	UDEVDIR=$UDEVDIR/rules.d],
	[UDEVDIR=$udevdir])
AC_SUBST(UDEVDIR)

AC_OUTPUT

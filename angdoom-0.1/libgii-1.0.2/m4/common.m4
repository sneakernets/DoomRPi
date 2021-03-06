dnl ------ compiler.m4 ------
dnl Check CC specific characteristics

dnl $1 is the $CC option to check for.
dnl $2 is a boolean value (1 for true or 0 for false),
dnl    whether the option should be activated in
dnl    CFLAGS if available
dnl    Defaults to true, if not specified

AC_DEFUN([GGI_CC_CHECK4_OPTION],
[

AC_MSG_CHECKING([if $CC has -$1 option])
save_CFLAGS="$CFLAGS"

CFLAGS="$CFLAGS -$1"
AC_COMPILE_IFELSE([
	AC_LANG_PROGRAM([[#include <stdio.h>]],
			[[printf("Hello World\n");]])
	], [cc_tmp=yes],
	[cc_tmp=no])

activate=1
if test -n "$2"; then
	activate=$2
fi

if test $activate -eq 0 -o "$cc_tmp" != "yes"; then
	CFLAGS="$save_CFLAGS"
fi


AC_MSG_RESULT([$cc_tmp])

AS_VAR_SET(AS_TR_SH(m4_tolower([cc_has_$1])), $cc_tmp)

])



dnl Check if -Werror-implicit-function-declaration kills the build.

dnl AIX 4.2 is missing a prototype for (at least) snprintf.
dnl Cygwin 1.5.11 is missing a prototype for (at least) siginterrupt.
dnl HP/UX 11.11 is missing a prototype for (at least) strtoull.
dnl True64 (version?) is missing a prototype for (at least) strtoull.

AC_DEFUN([GGI_CHECK_IMPLICIT_DECLARATIONS],
[

dnl First check, if we _have_ -Werror-implicit-function-declaration
GGI_CC_CHECK4_OPTION([Werror-implicit-function-declaration], 0)

if test "$cc_has_werror_implicit_function_declaration" = "yes"; then
	ggi_test_funcs="strncasecmp snprintf siginterrupt strtoull"

	dnl Now check for some headers ...
	AC_CHECK_HEADERS([string.h strings.h signal.h])

	dnl ... for the declarations
	for func in $ggi_test_funcs; do
		AC_CHECK_DECLS($func,[],[],
			[$ac_includes_default
			 #ifdef HAVE_SIGNAL_H
			 #include <signal.h>
			 #endif])
	done

	dnl ... and for the symbols.
	AC_CHECK_FUNCS($ggi_test_funcs)

	AC_MSG_CHECKING([if the system is missing declarations])

	for func in $ggi_test_funcs; do
		decl_var=AS_TR_SH([ac_cv_have_decl_$func])
		func_var=AS_TR_SH([ac_cv_func_$func])

		if eval "test \"x\${$decl_var}\" = \"xno\" -a \
			      \"x\${$func_var}\" = \"xyes\""; then
		  cc_has_werror_implicit_function_declaration="no"
		fi
	done

	dnl When we can use -Werror-implicit-function-declaration, then
	dnl there are no declarations missing. Thus the result output
	dnl must be inverted!
	if test $cc_has_werror_implicit_function_declaration = "yes"; then
		AC_MSG_RESULT([no])
	else
		AC_MSG_RESULT([yes])
	fi
fi

])




dnl ----- dllext.m4 -----
dnl Suffix detection for runtime loadable libraries.

AC_DEFUN([GGI_DLLEXT],
[

AC_MSG_CHECKING([for shared library extension])
case "${host}" in
  *-*-mingw* | *-*-cygwin*)
	DLLEXT="dll"
        ;;
  *)
	DLLEXT="so"
        ;;
esac
AC_MSG_RESULT([$DLLEXT])

AC_SUBST(DLLEXT)

])




dnl ------ extrapaths.m4 ------
dnl Let user add extra includes and libs

AC_DEFUN([GGI_EXTRA_PATHS],
[

AC_ARG_WITH([extra-includes],
[  --with-extra-includes=DIR
                          add extra include paths (separator ':')],
  use_extra_includes="$withval",
  use_extra_includes=NO
)

if test -n "$use_extra_includes" && \
        test "$use_extra_includes" != "NO"; then
  ac_save_ifs=$IFS
  IFS=':'
  for dir in ${use_extra_includes} ; do
    if test -d "$dir" ; then
      extra_includes="$extra_includes -I$dir"
    else
      test -f "$dir" && \
        extra_includes="$extra_includes -include $dir"
    fi
  done
  IFS=$ac_save_ifs
  CPPFLAGS="$CPPFLAGS $extra_includes"
fi

AC_ARG_WITH([extra-libs],
[  --with-extra-libs=DIR   add extra library paths (separator ':')],
  use_extra_libs="$withval",
  use_extra_libs=NO
)
if test -n "$use_extra_libs" && \
        test "$use_extra_libs" != "NO"; then
   ac_save_ifs=$IFS
   IFS=':'
   for dir in $use_extra_libs; do
     if test -d "$dir" ; then
       extra_libraries="$extra_libraries -L$dir"
     else
       extra_libraries="$extra_libraries -l$dir"
     fi
   done
   IFS=$ac_save_ifs
   LDFLAGS="$LDFLAGS $extra_libraries"
fi

AC_SUBST(extra_includes)
AC_SUBST(extra_libraries)

])



dnl ------ os.m4 ------
dnl Add your OS here, if not listed

AC_DEFUN([GGI_CHECKOS],
[

case "${host_os}" in
  cygwin*)
	os="os_win32_cygwin"
	;;
  mingw*)
	os="os_win32_mingw"
	;;
  pw32*)
	os="os_win32_pw32"
	;;
  darwin* | rhapsody*)
	os="os_darwin"
        ;;
  freebsd*)
	os="os_freebsd"
	;;
  linux*)
	os="os_linux"
	;;
  netbsd*)
	os="os_netbsd"
	;;
  openbsd*)
	os="os_openbsd"
	;;
  solaris*)
	os="os_solaris"
	;;
  aix*)
	os="os_aix"
	;;
  *)
	os="os_default"
        ;;
esac

AM_CONDITIONAL(OS_WIN32, [test $os = "os_win32_cygwin" -o $os = "os_win32_mingw" -o $os = "os_win32_pw32"])
AM_CONDITIONAL(OS_WIN32_CYGWIN, test $os = "os_win32_cygwin")
AM_CONDITIONAL(OS_WIN32_MINGW, test $os = "os_win32_mingw")
AM_CONDITIONAL(OS_WIN32_PW32, test $os = "os_win32_pw32")

AM_CONDITIONAL(OS_DARWIN, test $os = "os_darwin")
AM_CONDITIONAL(OS_FREEBSD, test $os = "os_freebsd")
AM_CONDITIONAL(OS_LINUX, test $os = "os_linux")
AM_CONDITIONAL(OS_NETBSD, test $os = "os_netbsd")
AM_CONDITIONAL(OS_OPENBSD, test $os = "os_openbsd")
AM_CONDITIONAL(OS_SOLARIS, test $os = "os_solaris")
AM_CONDITIONAL(OS_AIX, test $os = "os_aix")
AM_CONDITIONAL(OS_DEFAULT, test $os = "os_default")

])




dnl ------ rellibdir.m4 -----
dnl Find a relative path that takes us from static_sysconfdir/ggi_subdir
dnl to static_libdir/ggi_subdir.

dnl This macro is easily fooled with //, /./ and /../ combinations.
dnl Also, I'm very far from a script guru. This macro can probably
dnl be written in a couple of lines if you know the right script
dnl knobs.

AC_DEFUN([GGI_SYSCONF_TO_LIB],
[
rel_ggisysconfdir="$static_sysconfdir/$ggi_subdir"
rel_ggilibdir="$static_libdir/$ggi_subdir"
again="yes"
until test "$again" = "no"; do
	again=""
	newcdir=""
	newldir=""
	as_save_IFS=$IFS
	IFS='/'
	for cdir in $rel_ggisysconfdir; do
		IFS=$as_save_IFS
		if test -n "$again"; then
			if test -n "$newcdir"; then
				newcdir="$newcdir/$cdir"
			else
				newcdir="$cdir"
			fi
			continue
		fi
		as_save_IFS=$IFS
		IFS='/'
		for ldir in $rel_ggilibdir; do
			IFS=$as_save_IFS
			if test -z "$again"; then
				if test "$ldir" = "$cdir"; then
					again="yes"
					newldir=""
					newcdir=""
				else
					again="no"
					newldir="$ldir"
					newcdir="$cdir"
				fi
				continue
			fi
			if test -n "$newldir"; then
				newldir="$newldir/$ldir"
			else
				newldir="$ldir"
			fi
		done
	done
	rel_ggisysconfdir="$newcdir"
	rel_ggilibdir="$newldir"
done
as_save_IFS=$IFS
IFS='/'
for cdir in $rel_ggisysconfdir; do
	rel_ggilibdir="../$rel_ggilibdir"
done
IFS=$as_save_IFS

ggi_sysconfdir_to_libdir="$rel_ggilibdir"
])


dnl ----- strings.m4 -----
dnl Check for safe and secure string functions

AC_DEFUN([GGI_CHECK_STRING_FUNCS],
[

dnl strings.h exists on SYSV systems
dnl and contains strcasecmp() and strncasecmp()
AC_CHECK_HEADERS(string.h strings.h)

AC_CHECK_FUNCS([strcasecmp strncasecmp \
	strncat strncpy snprintf vsnprintf \
	strlcpy strlcat asprintf \
	strtol strtoul strtoll strtoull])

])



dnl ----- checklib.m4 -----
dnl Check for libs using libtool

AC_DEFUN([GGI_CHECK_LIB],
[
   save_CC="$CC"
   CC="$SHELL ./libtool --mode=link $CC"
   AC_CHECK_LIB($1, $2, [
     CC="$save_CC"
     $3], [
     CC="$save_CC"
     $4])
])

dnl ----- checkint.m4 -----
dnl Add fallback if C99 inttypes are not there...
AC_DEFUN([GGI_NEED_INTTYPES],
[
if test "$ac_cv_header_inttypes_h" != "yes"; then
  AC_DEFINE(GG_NEED_INTTYPES, 1,
	    [Tell libgg to define integer types when building])
fi
])

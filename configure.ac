dnl-----------------------------------------------------------------------------
dnl -- Extract package info
dnl-----------------------------------------------------------------------------

dnl extract package name and version from Version.h

m4_define([m4_EBUSDK_LIBRARY_NAME],
	m4_esyscmd([(sed -n 's/^.*EBUSDK_LIBRARY_NAME[^\"]*\"\([^\"]*\)\"/\1/p' Version.h | tr -d '\n')]))
m4_define([m4_EBUSDK_VERSION_MAJOR],
	m4_esyscmd([(sed -n 's/^.*EBUSDK_VERSION_MAJOR\ *\([0-9][0-9]*\)/\1/p' Version.h | tr -d '\n')]))
m4_define([m4_EBUSDK_VERSION_MINOR],
	m4_esyscmd([(sed -n 's/^.*EBUSDK_VERSION_MINOR\ *\([0-9][0-9]*\)/\1/p' Version.h | tr -d '\n')]))
m4_define([m4_EBUSDK_VERSION_MICRO],
	m4_esyscmd([(sed -n 's/^.*EBUSDK_VERSION_MICRO\ *\([0-9][0-9]*\)/\1/p' Version.h | tr -d '\n')]))
m4_define([m4_EBUSDK_VERSION],
	m4_defn([m4_EBUSDK_VERSION_MAJOR]).m4_defn([m4_EBUSDK_VERSION_MINOR]).m4_defn([m4_EBUSDK_VERSION_MICRO]))


dnl-----------------------------------------------------------------------------
dnl -- Init
dnl-----------------------------------------------------------------------------

AC_INIT(m4_defn([m4_EBUSDK_LIBRARY_NAME]), m4_defn([m4_EBUSDK_VERSION]))
dnl AC_CONFIG_SRCDIR([src/common/BMXException.cpp])
AC_CONFIG_HEADER([config.h])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([-Wall -Werror])
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])


dnl-----------------------------------------------------------------------------
dnl -- Version
dnl-----------------------------------------------------------------------------

dnl CURRENT, REVISION, AGE
dnl - library source changed -> increment REVISION
dnl - interfaces added/removed/changed -> increment CURRENT, REVISION = 0
dnl - interfaces added -> increment AGE
dnl - interfaces removed -> AGE = 0
EBUSDK_LIBVERSION="3:0:0"
AC_SUBST(EBUSDK_LIBVERSION)


EBUSDK_MAJORMINOR=m4_defn([m4_EBUSDK_VERSION_MAJOR]).m4_defn([m4_EBUSDK_VERSION_MINOR])
AC_SUBST(EBUSDK_MAJORMINOR)


dnl-----------------------------------------------------------------------------
dnl -- Checks for programs.
dnl-----------------------------------------------------------------------------

AC_PROG_LIBTOOL
AC_PROG_CXX
AC_PROG_CC
AC_PROG_INSTALL

AC_CHECK_PROGS(MD5TOOL, [md5sum md5])
if test x"$MD5TOOL" = x"" ; then
	AC_MSG_WARN(Missing md5sum/md5 tool. Cannot make check.)
fi


dnl-----------------------------------------------------------------------------
dnl -- Checks for libraries.
dnl-----------------------------------------------------------------------------

ORIGCFLAGS=$CFLAGS
if test x"$prefix" != x"NONE"; then
	CFLAGS="${CFLAGS} -L${prefix}/lib -I${prefix}/include"
fi

dnl Check for UUID generation library
case "$host" in
	*-*-*mingw*) os=win ;;
	*-*-darwin*) os=mac ;;
esac
if test x"$os" = xwin; then
	AC_CHECK_HEADER([windows.h],
					[UUIDLIB="-lole32"],
					AC_MSG_ERROR(No windows uuid generation function))
elif test x"$os" = xmac; then
	UUIDLIB=""
else
	AC_CHECK_LIB([uuid], [uuid_generate],
			     [UUIDLIB="-luuid"],
			     AC_MSG_ERROR(No uuid generation function))
fi
AC_SUBST(UUIDLIB)

AC_CHECK_LIB(uriparser,uriParseUriA,,
	[AC_MSG_ERROR([liburiparser not found])])
if test x"$prefix" = x"NONE"; then
	LIBURIPARSER_CFLAGS=""
	LIBURIPARSER_LIBS="-luriparser"
else
	LIBURIPARSER_CFLAGS="-I${prefix}/include"
	LIBURIPARSER_LIBS="-L${prefix}/lib -luriparser"
fi
AC_SUBST(LIBURIPARSER_CFLAGS)
AC_SUBST(LIBURIPARSER_LIBS)

dnl version 0.7.2 has been tested
AC_COMPILE_IFELSE([AC_LANG_SOURCE([
#include <uriparser/Uri.h>
#if (defined(URI_VER_MAJOR) && defined(URI_VER_MINOR) && defined(URI_VER_RELEASE) \
&& ((URI_VER_MAJOR > 0) \
|| ((URI_VER_MAJOR == 0) && (URI_VER_MINOR > 7)) \
|| ((URI_VER_MAJOR == 0) && (URI_VER_MINOR == 7) && (URI_VER_RELEASE >= 2)) \
))
/* FINE */
#else
# error uriparser not recent enough
#endif
])],,[AC_MSG_ERROR([uriparser 0.7.2 or later is required, your copy is too old])])

CFLAGS=$ORIGCFLAGS


dnl-----------------------------------------------------------------------------
dnl -- Check for modules
dnl-----------------------------------------------------------------------------

LIBMXF_MAJORMINOR=1.0
LIBMXFPP_MAJORMINOR=${LIBMXF_MAJORMINOR}
BMX_MAJORMINOR=0.1
AC_SUBST(LIBMXF_MAJORMINOR)
AC_SUBST(LIBMXFPP_MAJORMINOR)
AC_SUBST(LIBBMX_MAJORMINOR)

PKG_CHECK_MODULES(LIBMXF, libMXF-${LIBMXF_MAJORMINOR} >= 1.0.3)
AC_SUBST(LIBMXF_CFLAGS)
AC_SUBST(LIBMXF_LIBS)

PKG_CHECK_MODULES(LIBMXFPP, libMXF++-${LIBMXFPP_MAJORMINOR} >= 1.0.3)
AC_SUBST(LIBMXFPP_CFLAGS)
AC_SUBST(LIBMXFPP_LIBS)

PKG_CHECK_MODULES(BMX, bmx-${BMX_MAJORMINOR} >= 0.0.0)
AC_SUBST(BMX_CFLAGS)
AC_SUBST(BMX_LIBS)


dnl-----------------------------------------------------------------------------
dnl -- Checks for header files.
dnl-----------------------------------------------------------------------------

AC_CHECK_HEADERS([inttypes.h sys/time.h sys/timeb.h unistd.h])


dnl-----------------------------------------------------------------------------
dnl -- Checks for typedefs, structures, and compiler characteristics.
dnl-----------------------------------------------------------------------------

AC_HEADER_STDBOOL
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_INT8_T
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T


dnl mingw doesn't support the 'z' printf format length modifier for size_t
case "$host" in
	*-*-*mingw32) AC_DEFINE([PRIszt], ["u"], [Define printf size_t format specifier]) ;;
			   *) AC_DEFINE([PRIszt], ["zu"], [Define printf size_t format specifier])
esac


dnl-----------------------------------------------------------------------------
dnl -- Checks for library functions
dnl-----------------------------------------------------------------------------

AC_SYS_LARGEFILE
AC_FUNC_FSEEKO


AC_CHECK_FUNCS([getcwd gettimeofday memmove memset mkdir strerror])


dnl-----------------------------------------------------------------------------
dnl -- Compiler flags etc.
dnl-----------------------------------------------------------------------------

WARN_CFLAGS=
if test x"$GCC" = xyes; then
	WARN_CFLAGS="-W -Wall"
fi
AC_SUBST(WARN_CFLAGS)

EBUSDK_CFLAGS="${WARN_CFLAGS} ${LIBMXF_CFLAGS} ${LIBMXFPP_CFLAGS} ${BMX_CFLAGS} \
	${LIBURIPARSER_CFLAGS} -I\$(top_srcdir)/CustomMetadataSupport/include -I\$(top_srcdir)/EBUCoreProcessor/include -I\$(top_srcdir)/EBUCoreProcessor/include/xsd -I\$(top_srcdir)/Analyzer/include"
AC_SUBST(EBUSDK_CFLAGS)

EBUSDK_LIBADDLIBS="${UUIDLIB} ${LIBURIPARSER_LIBS} ${LIBMXF_LIBS} ${LIBMXFPP_LIBS} ${BMX_LIBS}"
AC_SUBST(EBUSDK_LIBADDLIBS)

EBUSDK_METADATA_LIBADDLIBS="\$(top_builddir)/CustomMetadataSupport/src/libebucustommetadatasupport.la -lxerces-c"
AC_SUBST(EBUSDK_METADATA_LIBADDLIBS)

EBUSDK_EBUCORE_LIBADDLIBS="\$(top_builddir)/EBUCoreProcessor/src/libebucore.la -lxerces-c"
AC_SUBST(EBUSDK_EBUCORE_LIBADDLIBS)

EBUSDK_ANALYZER_LIBADDLIBS="\$(top_builddir)/Analyzer/src/libebumxfanalyzer.la -lxerces-c"
AC_SUBST(EBUSDK_ANALYZER_LIBADDLIBS)

EBUSDK_LDADDLIBS="${EBUSDK_LIBADDLIBS} ${EBUSDK_METADATA_LIBADDLIBS} ${EBUSDK_EBUCORE_LIBADDLIBS} ${EBUSDK_ANALYZER_LIBADDLIBS}"
AC_SUBST(EBUSDK_LDADDLIBS)


dnl-----------------------------------------------------------------------------
dnl -- Package Config
dnl-----------------------------------------------------------------------------

pkgconfigdir="\$(libdir)/pkgconfig"
AC_SUBST(pkgconfigdir)

dnl add libraries to pkg config "Libs:" for static-only builds
if test x"$enable_shared" = xyes; then
	PC_ADD_LIBS=
	PC_ADD_PRIVATE_LIBS="${UUIDLIB} ${LIBURIPARSER_LIBS}"
else
	PC_ADD_LIBS="${UUIDLIB} ${LIBURIPARSER_LIBS}"
	PC_ADD_PRIVATE_LIBS=
fi
AC_SUBST(PC_ADD_LIBS)
AC_SUBST(PC_ADD_PRIVATE_LIBS)


dnl-----------------------------------------------------------------------------
dnl -- Config files
dnl-----------------------------------------------------------------------------

AC_CONFIG_FILES([
	Makefile
	CustomMetadataSupport/Makefile
	CustomMetadataSupport/src/Makefile
	EBUCoreProcessor/Makefile
	EBUCoreProcessor/src/Makefile
	EBUCoreProcessor/apps/Makefile
	EBUCoreProcessor/apps/mxf2raw/Makefile
	EBUCoreProcessor/apps/raw2bmx/Makefile
	EBUCoreProcessor/apps/ebu2mxf/Makefile
	EBUCoreProcessor/apps/mxf2ebu/Makefile
	EBUCoreProcessor/tools/Makefile
	EBUCoreProcessor/tools/gen_ebucore_classes/Makefile
	EBUCoreProcessor/msvc_build/Makefile
	EBUCoreProcessor/msvc_build/vs8/Makefile
	Analyzer/Makefile
	Analyzer/src/Makefile
	Analyzer/apps/Makefile
	Analyzer/apps/analyzer/Makefile
    ebu-mxfsdk.pc])

AC_OUTPUT


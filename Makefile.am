SUBDIRS = CustomMetadataSupport EBUCoreProcessor Analyzer


pkgconfig_DATA = ebu-mxfsdk-$(EBUSDK_MAJORMINOR).pc

ebu-mxfsdk-$(EBUSDK_MAJORMINOR).pc: ebu-mxfsdk.pc
	cp ebu-mxfsdk.pc ebu-mxfsdk-$(EBUSDK_MAJORMINOR).pc

CLEANFILES = ebu-mxfsdk-$(EBUSDK_MAJORMINOR).pc


ACLOCAL_AMFLAGS = -I m4


BUILT_SOURCES = bmx_scm_version.h

bmx_scm_version.h:
	sh $(top_srcdir)/gen_scm_version.sh

.PHONY: bmx_scm_version.h

DISTCLEANFILES = bmx_scm_version.h


EXTRA_DIST = \
	autogen.sh \
	gen_scm_version.sh \
	bmx_scm_version.h

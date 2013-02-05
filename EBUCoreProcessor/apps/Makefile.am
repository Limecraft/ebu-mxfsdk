SUBDIRS = . raw2bmx ebu2mxf mxf2ebu


noinst_LTLIBRARIES = libapp.la

libapp_la_SOURCES = \
	AppUtils.cpp \
	AppUtils.h \
	AS11Helper.cpp \
	AS11Helper.h

libapp_la_CXXFLAGS = $(EBUSDK_CFLAGS)
libapp_la_LDFLAGS = $(EBUSDK_LIBADDLIBS)


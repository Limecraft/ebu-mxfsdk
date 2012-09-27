noinst_PROGRAMS = gen_metadata_classes

gen_metadata_classes_SOURCES = gen_metadata_classes.cpp
gen_metadata_classes_CXXFLAGS = $(LIBMXFPP_CFLAGS)
gen_metadata_classes_LDADD = $(LIBMXF_LIBS)


.PHONY: generate
generate: gen_metadata_classes
	./gen_metadata_classes generated

.PHONY: copy
copy: generate
	mkdir -p ${top_srcdir}/libMXF++/metadata/base
	cp -R generated/base/* ${top_srcdir}/libMXF++/metadata/base

.PHONY: firstcopy
firstcopy: generate
	mkdir -p ${top_srcdir}/libMXF++/metadata/base
	cp -R generated/* ${top_srcdir}/libMXF++/metadata
	cp Metadata.h ${top_srcdir}/libMXF++/metadata



EXTRA_DIST = README.txt


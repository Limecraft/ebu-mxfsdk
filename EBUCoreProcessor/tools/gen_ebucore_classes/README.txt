Run "make install" to generate and copy the base classes to 
libMXF++/metadata/base.

Run "make firstinstall" to generate and copy the derived (user editable) classes 
and base classes to libMXF++/metadata/ and libMXF++/metadata/base.



NOTES: 
- the lines "REGISTER_CLASS..." written to standard output should be added to
the HeaderMetadata implementation of the function initialiseObjectFactory().
- the generated file, tools/generated/Metadata.h, is replaced in libMXF++/metadata
with tools/Metadata.h. The tools/Metadata.h header file has the right ordering
for compilation.


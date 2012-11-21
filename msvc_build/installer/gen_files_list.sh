find ../../ebu-libmxf ../../ebu-libmxfpp ../../ebu-bmx ../../Analyzer ../../CustomMetadataSupport ../../EBUCoreProcessor ../../uriparser \
	-iname '.git' -prune -o -iname Debug -prune -o -iname Release -prune -o -iname ipch -prune -o  \
	-not -path '.git' -not -path '*Debug' -not -path '*Release' -not -path '*ipch' \
	-not -iname '*suo*' -not -iname '*sdf*' -not -iname '*opensdf' -not -iname '*.user' \
	-printf '%y|"%h/%f"\n' > files.txt
find ../../msvc_build \
	-iname '.git' -prune -o -iname installer -prune -o -iname Debug -prune -o -iname Release -prune -o -iname ipch -prune -o -iname xerces-c-3.1.1-x86-windows-vc-10.0 -prune -o -iname xsd-3.3.0-i686-windows -prune -o \
	-not -path '.git' -not -path '*Debug' -not -path '*Release' -not -path '*ipch' -not -path '*installer' \
	-not -iname '*suo*' -not -iname '*sdf*' -not -iname '*opensdf' -not -iname 'ebu-mxfsdk*.exe' \
	-printf '%y|"%h/%f"\n' >> files.txt
find ../../bin \
	-not -iname '*.pdb' \
	-printf '%y|"%h/%f"\n' >> files.txt
find ../../doc/ \
	-iname '*.pdf' \
	-printf '%y|"%h/%f"\n' >> files.txt
find ../../doc/doxygen \
	-printf '%y|"%h/%f"\n' >> files.txt

sed -e 's/^f|\(.*\)/f|\1|\1/' -e 's/^f|/File\|/' -e s/^d\ .*// -e 's/\//\\/g' files.txt | \
	awk ' BEGIN {FS="|"}; /^File/ { sub(/[.][.]\\[.][.]\\/, "/oname=", $2); print $1 " " $2 " " $3 }; /^d/ { sub(/[.][.]\\[.][.]/, "$INSTDIR", $2); print "CreateDirectory " $2 } ' > files_installer.inc
tac files.txt | sed -e 's/^f|/Delete\ /' -e 's/^d|/RMDir\ /' -e 's/\//\\/g' -e 's/[.][.]\\[.][.]/$INSTDIR/' > files_uninstaller.inc

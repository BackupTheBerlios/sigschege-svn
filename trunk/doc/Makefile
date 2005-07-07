# $Id$

all: docu sigschege-manual.dvi

sigschege-manual.dvi: sigschege-manual.tex
	latex sigschege-manual.tex

docu:
	doxygen doxygen_yavec.cfg

distclean: clean

clean:
	rm -rf html latex

maintainer-clean:
	rm -rf html latex

install:

uninstall:


.PHONY: all docu clean distclean maintainer-clean

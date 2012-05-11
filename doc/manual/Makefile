# basic tools
LATEX	= latex
BIBTEX	= bibtex
DVIPS	= dvips
PS2PDF	= ps2pdf

# sources
TEX_SRC	= manual.tex
BIB_SRC	= *.bib
FIG_SRC = fig/*.eps

# default target
all: $(TARGET)

# build
$(TARGET): $(TEX_SRC) $(BIB_SRC) $(FIG_SRC)
	# standard boilerplate (latex; bibtex; latex; latex)
	$(LATEX) $(TEX_SRC)
	$(BIBTEX) *.aux
	$(LATEX) $(TEX_SRC)
	$(LATEX) $(TEX_SRC)

	# dvi to ps
	$(DVIPS) -Ppdf *.dvi

	# ps to pdf
	$(PS2PDF) *.ps

	# cleanup
	rm -f *.aux *.bbl *.blg *.dvi *.log *.ps

# clean
clean:
	rm -f *.aux *.bbl *.blg *.dvi *.log *.ps *.pdf

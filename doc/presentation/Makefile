# basic tools
LATEX	= pdflatex

# sources
TEX_SRC	= presentation.tex
FIG_SRC = fig/*

# default target
all: $(TARGET)

# build
$(TARGET): $(TEX_SRC) $(FIG_SRC)
	# standard boilerplate
	$(LATEX) $(TEX_SRC)
	$(LATEX) $(TEX_SRC)

	# cleanup
	rm -f *.out *.vrb *.nav *.snm *.toc
	rm -f *.aux *.bbl *.blg *.dvi *.log *.ps

# clean
clean:
	rm -f *.out *.vrb *.nav *.snm *.toc
	rm -f *.aux *.bbl *.blg *.dvi *.log *.ps *.pdf

TEXs = rapport  
pdf = pdflatex
all: $(TEXs)

$(TEXs): *.tex
	$(pdf) $@ $< ;
	$(pdf) $@ $< 

veryclean: clean
	rm -f *.pdf

clean:
	rm -f *.aux
	rm -f *.log
	rm -f *.out
	rm -f *.toc
help:
	@echo "make: Compile le .tex"
	@echo "make clean: Supprime tous les .aux .log"
	@echo "make veryclean: make clean + Suppression du .pdf aussi"

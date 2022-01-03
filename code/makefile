SRCDIR=src
BINDIR=bin
INCLUDEDIR=include
TESTDIR=tests

CC = gcc
CFLAGS=-Wall -pedantic -I$(INCLUDEDIR)
EXEC= itispell

all :  $(BINDIR)/$(EXEC)


tests: $(SRCDIR)/tests.o $(SRCDIR)/mot.o $(SRCDIR)/dictionnaire.o $(SRCDIR)/correcteur.o
	gcc -o $(TESTDIR)/testUnitItispell $(SRCDIR)/tests.o $(SRCDIR)/mot.o $(SRCDIR)/dictionnaire.o $(SRCDIR)/correcteur.o  -lcunit

$(SRCDIR)/%.o : $(SRCDIR)/%.c
	$(CC) -o $@ -c $< $(CFLAGS) 



$(BINDIR)/$(EXEC) : $(SRCDIR)/main.o $(SRCDIR)/mot.o $(SRCDIR)/dictionnaire.o $(SRCDIR)/correcteur.o 
	$(CC)  -o $@ $^ 


clean :
	rm -rf $(BINDIR)/*
	rm -rf $(TESTDIR)/*
	rm -rf $(SRCDIR)/*.o

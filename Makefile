CC=		gcc
CFLAGS=		-g -gdwarf-2 -Wall -std=gnu99
LD=		gcc
LDFLAGS=	-L.
AR=		ar
ARFLAGS=	rcs
TARGETS=	search

all:		$(TARGETS)

search: main.o execute.o filter.o search.o utilities.o
	@echo "Linking $@..."
	@$(LD) $(LDFLAGS) -o search main.o execute.o filter.o search.o utilities.o -o search

main.o: main.c search.h
	@echo "Compiling $@..."
	@$(CC) $(CFLAGS) -c -o main.o main.c

execute.o: execute.c search.h
	@echo "Compiling $@..."
	@$(CC) $(CFLAGS) -c -o execute.o execute.c

filter.o: filter.c search.h
	@echo "Compiling $@..."
	@$(CC) $(CFLAGS) -c -o filter.o filter.c

search.o: search.c search.h
	@echo "Compiling $@..."
	@$(CC) $(CFLAGS) -c -o search.o search.c

utilities.o: utilities.c search.h
	@echo "Compiling $@..."
	@$(CC) $(CFLAGS) -c -o utilities.o utilities.c

test:		search test_search.sh
	@echo Testing $<...
	@./test_search.sh

clean:
	@echo Cleaning...
	@rm -f $(TARGETS) *.o *.log *.input

.PHONY:		all test benchmark clean

# TODO: Add rules for search and object files

CC = gcc
WARNFLAGS = -Wall -Wextra
DEBUGFLAGS = -g -O0

all: bcc

OBJS := BabyC.tab.o BabyC.yy.o ast.o symbolTable.o main.o

bcc: $(OBJS)
	$(CC) $(WARNFLAGS) $(DEBUGFLAGS) $(OBJS) -o $@

%.o: %.c
	$(CC) $(WARNFLAGS) $(DEBUGFLAGS) -c $<

%.yy.c: %.l
	flex -o $@ $<

%.tab.c: %.y
	bison -o $@ -d $<

clean:
	rm -f *.o *.tab.* *.yy.* bcc bcc.out

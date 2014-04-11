TARGET=PolyPlexer
CC=gcc
OBJECT= Color.o main.o
CFLAGS=-W -Wall -g
VERBOSE=no

ifeq ($(VERBOSE), yes)
        CFLAGS+= -DVERBOSE -DCOLOR
endif


$(TARGET) : $(OBJECT)
	$(CC) $(CFLAGS) $(OBJECT) -o $(TARGET)



all: $(OBJ)

verbose:
	@make clean
	@make VERBOSE=yes

gnuplot:
	@make clean
	@make GNUPLOT=yes


Color.o : Color.c Color.h
	$(CC) $(CFLAGS) -c Color.c


main.o : main.c 
	$(CC) $(CFLAGS) -c main.c

.PHONY: clean mrproper                                                                                                                        

clean:
	@rm -fv *.o

mrproper: clean

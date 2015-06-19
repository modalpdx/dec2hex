CC = clang
ARGS = -g 

all: dec2hex

dec2hex: intConvert.o main.o 
	$(CC) $(ARGS) -lm intConvert.o main.o -o dec2hex -lm

intConvert.o:
	$(CC) $(ARGS) -c intConvert.c 

main.o:
	$(CC) $(ARGS) -c main.c

clean:
	rm *.o dec2hex


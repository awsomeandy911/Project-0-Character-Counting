all: project0

.c:
    gcc -Wall $< -o $@

project0: project0.o project0.c
    gcc -o project0 project0.o

project0.o: project0.c
    gcc -I. -c project0.c

clean:
    rm -f *.o project0

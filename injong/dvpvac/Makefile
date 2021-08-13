app: m.o rwbuf.o
	gcc -lm -o app m.o rwbuf.o 

m.o:m.c rwbuf.c m.h
	gcc -c $<

clean:
	rm -f *.o app

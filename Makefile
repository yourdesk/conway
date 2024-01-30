conway: lut.o conway.o
	gcc -O3 -o conway conway.o lut.o

conway2d: lut.o conway2d.o
	gcc -O3 -o conway2d conway2d.o lut.o

lut.o: lut.c
	gcc -O3 -c -o lut.o lut.c  

conway.o: conway.c
	gcc -O3 -c -o conway.o conway.c

conway2d.o: conway2d.c
	gcc -O3 -c -o conway2d.o conway2d.c

clear:
	rm conway
	rm conway2d
	rm *.o
	rm callgrind.out.*
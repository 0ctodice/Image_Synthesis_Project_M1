CC = gcc

CFLAGS = -Wall -Wno-comment -W -std=c17
LFLAGS = $(libG3X) $(DBG_LIB)
INCLUDE = -I../INCLUDE $(incG3X)
SOURCE = src/

ALL: scene1 scene2

scene1: scene1.o sphere.o torus.o cylinder.o cone.o cube.o object.o
	$(CC) -o scene1 $^ $(LFLAGS)

scene2: scene2.o sphere.o torus.o cylinder.o cone.o cube.o object.o
	$(CC) -o scene2 $^ $(LFLAGS)

scene1.o: scene1.c
	$(CC) $(CFLAGS) $(INCLUDE) -c scene1.c

scene2.o: scene2.c
	$(CC) $(CFLAGS) $(INCLUDE) -c scene2.c

sphere.o: $(SOURCE)sphere.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $(SOURCE)sphere.c

torus.o: $(SOURCE)torus.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $(SOURCE)torus.c

cylinder.o: $(SOURCE)cylinder.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $(SOURCE)cylinder.c

cone.o: $(SOURCE)cone.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $(SOURCE)cone.c

cube.o: $(SOURCE)cube.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $(SOURCE)cube.c

object.o: $(SOURCE)object.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $(SOURCE)object.c

clean:
	rm *.o
	rm scene1 scene2



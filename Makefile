# # compiler
# CC = gcc

# DEBUG = no

# ifeq ($(DEBUG),yes)
#   CFLAGS  = -g -Wpointer-arith -Wall -std=c17
# else
#   CFLAGS  = -O2 -std=c17
# endif

# lib = $(libG3X) $(DBG_LIB)
# inc = -I./include $(incG3X)
# src = src/

# # cible pour les binaires (.a,.so)
# bin = .

# # règle générique de création de xxx.o à partir de src/xxx.c
# %.o : $(src)%.c
# 	@echo "module $@"
# 	@$(CC) $(CFLAGS) $(inc) -c $< -o $@
# 	@echo "------------------------"

# # règle générique de création de l'executable xxx à partir de src/xxx.c (1 seul module)
# % : %.o
# 	@echo "assemblage [$^]->$@"
# 	@$(CC) $^ $(lib) -o $@
# 	@echo "------------------------"

# .PHONY : clean cleanall ?

# # informations sur les paramètres de compilation
# ? :
# 	@echo "---------compilation informations----------"
# 	@echo "  processor      : $(PROCBIT)"
# 	@echo "  compiler       : $(CC)"
# 	@echo "  options        : $(CFLAGS)"
# 	@echo "  lib g3Ox/OpenGl : $(libG3X)$(COMP)"
# 	@echo "  headers        : $(incG3X)"
# clean :
# 	@rm -f *.o
# cleanall :
# 	@rm -f *.o g2x_squelette g2x_example

CC = gcc

CFLAGS = -Wall -Wno-comment -W -std=c17
LFLAGS = $(libG3X) $(DBG_LIB)
INCLUDE = $(incG3X)
SOURCE = src/

NAME = scene2

$(NAME): scene2.o sphere.o torus.o cylinder.o cone.o cube.o object.o
	$(CC) -o $(NAME) $^ $(LFLAGS)

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
	rm $(NAME)



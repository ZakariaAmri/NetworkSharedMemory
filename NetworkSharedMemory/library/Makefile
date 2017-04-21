CC =gcc
LFLAGS = -lpthread 
CFLAGS = -W

BIN =bin/
OBJ =obj/
INCLUDE =include/
LIB =lib/
SRC =src/
OBJS = $(OBJ)mpr.o $(OBJ)communication.o $(OBJ)connection.o $(OBJ)data.o $(OBJ)default.o $(OBJ)msg.o $(OBJ)request.o $(OBJ)verrou.o

all: $(STATLIB)

lib: $(OBJ)mpr$(OBJ)communication $(OBJ)connection $(OBJ)data $(OBJ)default $(OBJ)msg $(OBJ)request $(OBJ)verrou

$(STATLIB): $(
obj/%.o: src/%.c
        $(CC) $(CFLAGS) -I./include  -c -o $@ $<
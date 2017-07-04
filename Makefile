SRC_PATH=./src/
INCLUDE_PATH=./include/

LIB_OBJ=c_map.o c_list.o c_set.o system.o 
LIB_NAME=$(LIB_PATH)libutil.a
LIB_PATH=./lib/

all:$(LIB_NAME)

$(LIB_NAME):$(LIB_OBJ)
	ar rcs $(LIB_NAME) $(addprefix $(LIB_PATH), $^)

.c.o:
	gcc -I $(INCLUDE_PATH) -c -o $(LIB_PATH)$@ $^ -std=c99 -g

.PHONY:clean

vpath %.c $(SRC_PATH)
vpath %.o $(LIB_PATH)

clean:
	rm -rf ./lib/*

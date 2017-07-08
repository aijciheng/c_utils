SRC_PATH=./src/
INCLUDE_PATH=./include/

LIB_OBJ=c_map.o c_list.o c_linkedlist.o c_set.o c_iterator.o c_string.o c_sort.o system.o 
LIB_NAME=$(LIB_PATH)libcutils.a
LIB_PATH=./lib/

CMD=cmd

all:$(CMD) $(LIB_NAME)

$(CMD):
	mkdir -p $(LIB_PATH)

$(LIB_NAME):$(LIB_OBJ)
	ar rcs $(LIB_NAME) $(addprefix $(LIB_PATH), $^)

.c.o:
	gcc -I $(INCLUDE_PATH) -c -o $(LIB_PATH)$@ $^ -std=c99 -g

.PHONY:clean $(CMD)

vpath %.c $(SRC_PATH)
vpath %.o $(LIB_PATH)

clean:
	rm -rf ./lib/*

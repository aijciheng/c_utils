INCLUDE_PATH=../../include/
LIB_PATH=../../lib/
TARGET_OBJ=main.c
TARGET=test_list

$(TARGET):$(TARGET_OBJ)
	gcc -o $@ $^ -I $(INCLUDE_PATH) -L $(LIB_PATH) -lcutils -std=c99 -g

.PHONY:clean

clean:
	rm -rf $(TARGET) 

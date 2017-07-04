INCLUDE_PATH=../../include/
LIB_PATH=../../lib/
TARGET_OBJ=main.c
TARGET=test_set

$(TARGET):$(TARGET_OBJ)
	gcc -o $@ $^ -I $(INCLUDE_PATH) -L $(LIB_PATH) -lutil -std=c99 -g

.PHONY:clean

clean:
	rm -rf $(TARGET) 

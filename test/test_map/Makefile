INCLUDE_PATH=../../include/
LIB_PATH=../../lib/

test_map:main.c
	gcc -o $@ $^ -I $(INCLUDE_PATH) -L $(LIB_PATH) -lutil -std=c99 -g

.PHONY:clean

clean:
	rm -rf test_map

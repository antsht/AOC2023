BUILD_PATH=../bin/
CC=gcc
CFLAGS=-g -Wall -Wextra -Werror
EXTRAFLAGS=-fsanitize=leak -fsanitize=address -fsanitize=undefined -fsanitize=unreachable -fno-sanitize-recover -fstack-protector 

all: check rebuild

build: clean day6_1  day6_2 

rebuild: clean_all day6_1  day6_2  clean

day6_1: clean 6_1.c 
	$(CC) $(CFLAGS) 6_1.c -o  $(BUILD_PATH)6_1  -lm
	$(CC) $(CFLAGS) $(EXTRAFLAGS)  6_1.c  -o  $(BUILD_PATH)6_1_extra  -lm

day6_2: clean 6_2.c 
	$(CC) $(CFLAGS) 6_2.c -o  $(BUILD_PATH)6_2 -lm
	$(CC) $(CFLAGS) $(EXTRAFLAGS) 6_2.c  -o  $(BUILD_PATH)6_2_extra  -lm

clean_all:
	rm -rf *.o *.a *.so $(BUILD_PATH)*
	
clean:
	rm -rf *.o *.a

check:
	clang-format -n *.c
#	clang-format -n *.h
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

run:
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes $(BUILD_PATH)6_1
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes $(BUILD_PATH)6_2

run_no_valgrind:
	$(BUILD_PATH)6_1_extra
	$(BUILD_PATH)6_2_extra



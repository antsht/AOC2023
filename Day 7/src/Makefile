BUILD_PATH=../bin/
CC=gcc
CFLAGS=-g -Wall -Wextra -Werror
EXTRAFLAGS=-fsanitize=leak -fsanitize=address -fsanitize=undefined -fsanitize=unreachable -fno-sanitize-recover -fstack-protector 

all: check rebuild

build: clean day7_1  day7_2 

rebuild: clean_all day7_1  day7_2  clean

day7_1: clean 7_1.c common_7.c
	$(CC) $(CFLAGS) 7_1.c common_7.c -o  $(BUILD_PATH)7_1  -lm
	$(CC) $(CFLAGS) $(EXTRAFLAGS)  7_1.c common_7.c -o  $(BUILD_PATH)7_1_extra  -lm

day7_2: clean 7_2.c common_7.c
	$(CC) $(CFLAGS) 7_2.c common_7.c -o  $(BUILD_PATH)7_2 -lm
	$(CC) $(CFLAGS) $(EXTRAFLAGS)  7_2.c common_7.c -o  $(BUILD_PATH)7_2_extra  -lm

clean_all:
	rm -rf *.o *.a *.so $(BUILD_PATH)*
	
clean:
	rm -rf *.o *.a

check:
	clang-format -n *.c
	clang-format -n *.h
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

run:
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes $(BUILD_PATH)7_1
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes $(BUILD_PATH)7_2

run_no_valgrind:
	$(BUILD_PATH)7_1_extra
	$(BUILD_PATH)7_2_extra



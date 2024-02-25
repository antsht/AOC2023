BUILD_PATH=../bin/
CC=gcc
CFLAGS=-g -Wall -Wextra -Werror
EXTRAFLAGS=-fsanitize=leak -fsanitize=address -fsanitize=undefined -fsanitize=unreachable -fno-sanitize-recover -fstack-protector 

all: check rebuild

build: clean day5_1  day5_2 

rebuild: clean_all day5_1  day5_2  clean

day5_1: clean 5_1.c common_5.c
	$(CC) $(CFLAGS) 5_1.c common_5.c -o  $(BUILD_PATH)5_1  -lm
	$(CC) $(CFLAGS) $(EXTRAFLAGS)  5_1.c common_5.c -o  $(BUILD_PATH)5_1_extra  -lm

day5_2: clean 5_2.c common_5.c
	$(CC) $(CFLAGS) 5_2.c common_5.c -o  $(BUILD_PATH)5_2 -lm
	$(CC) $(CFLAGS) $(EXTRAFLAGS)  5_2.c common_5.c -o  $(BUILD_PATH)5_2_extra  -lm

clean_all:
	rm -rf *.o *.a *.so $(BUILD_PATH)*
	
clean:
	rm -rf *.o *.a

check:
	clang-format -n *.c
	clang-format -n *.h
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

run:
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes $(BUILD_PATH)5_1
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes $(BUILD_PATH)5_2

run_no_valgrind:
	$(BUILD_PATH)5_1_extra
	$(BUILD_PATH)5_2_extra



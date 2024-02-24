BUILD_PATH=../bin/
CC=gcc
CFLAGS=-g -Wall -Wextra -Werror
EXTRAFLAGS=-fsanitize=leak -fsanitize=address -fsanitize=undefined -fsanitize=unreachable -fno-sanitize-recover -fstack-protector 

all: check rebuild

build: clean day4_1 day4_1_extra day4_2 day4_2_extra

rebuild: clean_all day4_1 day4_1_extra day4_2 day4_2_extra clean

day4_1: clean 4_1.c
	$(CC) $(CFLAGS) 4_1.c -o  $(BUILD_PATH)4_1  -lm

day4_1_extra: clean 4_1.c
	$(CC) $(CFLAGS) $(EXTRAFLAGS)  4_1.c -o  $(BUILD_PATH)4_1_extra  -lm

day4_2: clean 4_2.c
	$(CC) $(CFLAGS) 4_2.c -o  $(BUILD_PATH)4_2 -lm

day4_2_extra: clean 4_2.c
	$(CC) $(CFLAGS) $(EXTRAFLAGS)  4_2.c -o  $(BUILD_PATH)4_2_extra  -lm

clean_all:
	rm -rf *.o *.a *.so $(BUILD_PATH)*
	
clean:
	rm -rf *.o *.a

check:
	clang-format -n *.c
#	clang-format -n *.h
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

run:
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes $(BUILD_PATH)4_1
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes $(BUILD_PATH)4_2

run_no_valgrind:
	$(BUILD_PATH)4_1_extra
	$(BUILD_PATH)4_2_extra



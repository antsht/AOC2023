BUILD_PATH=../bin/
CC=gcc
CFLAGS=-g -Wall -Wextra -Werror 
EXTRAFLAGS=-fsanitize=leak -fsanitize=address -fsanitize=undefined -fsanitize=unreachable -fno-sanitize-recover -fstack-protector 

all: check rebuild

build: clean day3_1 day3_1_extra day3_2 day3_2_extra

rebuild: clean_all day3_1 day3_1_extra day3_2 day3_2_extra clean

day3_1: clean 3_1.c
	$(CC) $(CFLAGS) 3_1.c -o  $(BUILD_PATH)3_1

day3_1_extra: clean 3_1.c
	$(CC) $(CFLAGS) $(EXTRAFLAGS)  3_1.c -o  $(BUILD_PATH)3_1_extra

day3_2: clean 3_2.c
	$(CC) $(CFLAGS) 3_2.c -o  $(BUILD_PATH)3_2

day3_2_extra: clean 3_2.c
	$(CC) $(CFLAGS) $(EXTRAFLAGS)  3_2.c -o  $(BUILD_PATH)3_2_extra

clean_all:
	rm -rf *.o *.a *.so $(BUILD_PATH)*
	
clean:
	rm -rf *.o *.a

check:
	clang-format -n *.c
#	clang-format -n *.h
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

run:
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes $(BUILD_PATH)3_1
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes $(BUILD_PATH)3_2

run_no_valgrind:
	$(BUILD_PATH)3_1_extra
	$(BUILD_PATH)3_2_extra



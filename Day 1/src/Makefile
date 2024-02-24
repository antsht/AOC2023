BUILD_PATH=../bin/
CC=gcc
CFLAGS=-g -Wall -Wextra -Werror 
EXTRAFLAGS=-fsanitize=leak -fsanitize=address -fsanitize=undefined -fsanitize=unreachable -fno-sanitize-recover -fstack-protector 

all: check rebuild

build: clean day1_1 day1_1_extra day1_2 day1_2_extra

rebuild: clean_all day1_1 day1_1_extra day1_2 day1_2_extra clean

day1_1: clean 1_1.c
	$(CC) $(CFLAGS) 1_1.c -o  $(BUILD_PATH)1_1

day1_1_extra: clean 1_1.c
	$(CC) $(CFLAGS) $(EXTRAFLAGS)  1_1.c -o  $(BUILD_PATH)1_1_extra

day1_2: clean 1_2.c
	$(CC) $(CFLAGS) 1_2.c -o  $(BUILD_PATH)1_2

day1_2_extra: clean 1_2.c
	$(CC) $(CFLAGS) $(EXTRAFLAGS)  1_2.c -o  $(BUILD_PATH)1_2_extra

clean_all:
	rm -rf *.o *.a *.so $(BUILD_PATH)*
	
clean:
	rm -rf *.o *.a

check:
	clang-format -n *.c
#	clang-format -n *.h
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

run:
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes $(BUILD_PATH)1_1
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes $(BUILD_PATH)1_2

run_no_valgrind:
	$(BUILD_PATH)1_1_extra
	$(BUILD_PATH)1_2_extra



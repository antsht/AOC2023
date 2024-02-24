BUILD_PATH=../bin/
CC=gcc
CFLAGS=-g -Wall -Wextra -Werror 
EXTRAFLAGS=-fsanitize=leak -fsanitize=address -fsanitize=undefined -fsanitize=unreachable -fno-sanitize-recover -fstack-protector 

all: check rebuild

build: clean day2_1 day2_1_extra day2_2 day2_2_extra

rebuild: clean_all day2_1 day2_1_extra day2_2 day2_2_extra clean

day2_1: clean 2_1.c
	$(CC) $(CFLAGS) 2_1.c -o  $(BUILD_PATH)2_1

day2_1_extra: clean 2_1.c
	$(CC) $(CFLAGS) $(EXTRAFLAGS)  2_1.c -o  $(BUILD_PATH)2_1_extra

day2_2: clean 2_2.c
	$(CC) $(CFLAGS) 2_2.c -o  $(BUILD_PATH)2_2

day2_2_extra: clean 2_2.c
	$(CC) $(CFLAGS) $(EXTRAFLAGS)  2_2.c -o  $(BUILD_PATH)2_2_extra

clean_all:
	rm -rf *.o *.a *.so $(BUILD_PATH)*
	
clean:
	rm -rf *.o *.a

check:
	clang-format -n *.c
#	clang-format -n *.h
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

run:
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes $(BUILD_PATH)2_1
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes $(BUILD_PATH)2_2

run_no_valgrind:
	$(BUILD_PATH)2_1_extra
	$(BUILD_PATH)2_2_extra



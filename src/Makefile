PROJECT_NAME = matrix_oop
CC = g++
CFLAGS = -Wall -Werror -Wextra -std=c++17 -g
SOURCE = $(PROJECT_NAME).cc
LIBS = -lgtest -lgtest_main -pthread
UNAME := $(shell uname -s)

ifeq ($(UNAME), Darwin)
OPEN_REPORT = open
LEAKS = CK_FORK=no leaks --atExit -- ./test
endif
ifeq ($(UNAME), Linux)
OPEN_REPORT = xdg-open
LEAKS = CK_FORK=no valgrind -s --leak-check=full --track-origins=yes ./test
endif

all : clean test matrix_oop.a gcov_report

clean : 
	rm -rf test *.gcno *.gcda *.info report *.a *.o 

test :
	$(CC) ${CFLAGS} *.cc -o $@ $(LIBS)
	./$@	

matrix_oop.a : 
	$(CC) -c $(SOURCE) $(CFLAGS)	
	ar rc $@ *.o
	ranlib $@

gcov_report: test
	$(CC) --coverage ${CFLAGS} *.cc -o $^ $(LIBS)
	./$^
	lcov -t "test" -o test.info -c -d . --no-external
	genhtml -o report test.info
	$(OPEN_REPORT) report/index.html

style:
	cp ../.clang-format ./
	clang-format -style=Google -n *.cc *.h
	rm .clang-format

check:	
	cppcheck --language=c++ *.cc *.h

leaks:	
	$(LEAKS)
CC = g++
TEST_LIBS = -lgtest -lgtest_main
ifeq ($(shell uname -s), Linux)
	TEST_LIBS += -lsubunit -lm -pthread
endif
CFLAGS = -std=c++17 -Wall -Werror -Wextra -g
SOURCES = $(wildcard *.cpp)
OBJECTS = $(patsubst %.cpp, %.o, $(SOURCES))

all: check_style test

test: clean lib_matrix_oop.a
	$(CC) $(CFLAGS) tests/*.cpp lib_matrix_oop.a -o test $(TEST_LIBS)
	./test
	rm -rf *.o tests/*.o

lib_matrix_oop.a: 
	$(CC) $(CFLAGS) -c $(SOURCES)
	ar rcs lib_matrix_oop.a $(OBJECTS)

gcov_flag:
	$(eval CFLAGS += -fprofile-arcs -ftest-coverage)

gcov_report: clean gcov_flag test
	@lcov --capture --directory . --output-file coverage.info
	@lcov --remove coverage.info '/usr/include/*' 'tests/*' --output-file coverage.info
	@genhtml coverage.info --output-directory coverage
	@rm -f *.gcno *.gcda coverage.info
	@xdg-open coverage/index.html || open coverage/index.html || \
	(echo "Could not open the report automatically. Please open file://$(CURDIR)/coverage/index.html manually" && false)
	
style:
	clang-format --style=google -i *.cpp *.h
	clang-format --style=google -i tests/*.cpp

check_style:
	clang-format --style=google -n *.cpp *.h
	clang-format --style=google -n tests/*.cpp

test_leaks: lib_matrix_oop.a
	$(CC) $(CFLAGS) tests/*.cpp lib_matrix_oop.a -o test $(TEST_LIBS)
ifeq ($(shell uname -s), Linux)
	rm -rf *.o tests/*.o
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./test
else
	leaks --atExit -- ./test
endif

clean:
	rm -rf *.a *.o tests/*.o test *.gcno *.gcda *.gcov *.info coverage* *.dSYM

.PHONY: lib_matrix_oop.a all clean test style

CC = gcc
CFLAGS = -Werror -Wall -Wextra -std=c11
TARGET = s21_math
TEST_DIR = tests
TEST_SRCS = $(TEST_DIR)/*.c
TEST_OBJS = $(TEST_SRCS:.c=.o)
TEST_FLAGS = $(shell pkg-config --libs --cflags check) 
GCOV_FLAGS = -ftest-coverage -fprofile-arcs -fPIC
OS := $(shell uname)

ifeq ($(OS), Linux)
	TEST_FLAGS += -L. -l:s21_math.a
else
	TEST_FLAGS += -lm
endif

.PHONY: all clean test build rebuild gcov_report

all: build
rebuild: clean build
build: $(TARGET).a

$(TARGET).a: $(TARGET).o
	ar -rc $(TARGET).a $(TARGET).o
$(TARGET).o:
	$(CC) $(CFLAGS) -c $(TARGET).c -o $(TARGET).o

test: rebuild
	$(CC) $(CFLAGS) $(GCOV_FLAGS) check_s21_math.c tests/*.c $(TARGET).a -o $@ $(TEST_FLAGS)
	./$@
gcov_report: test
	lcov -t test -o test.info -c -d . --no-external
	genhtml -o report test.info
	open ./report/index.html

clean:
	rm -rf *.o test *.a $(TEST_DIR)/*.o *.gcda *.gcno test.info report
## ---------
## SmartCalc
## ---------

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, obj/%.o, $(SRC))
OBJ_FILTERED := $(filter-out obj/main.o, $(OBJ))
TARGET = qt/calc.app/Contents/MacOS/calc
TARGET_H = smart_calc.h

FLAGS_ER = -Wall -Wextra -Werror -std=c11 -pedantic -fsanitize=address -lm
FLAGS_GRIND = -Wall -Wextra -Werror -std=c11 -pedantic -lm
FLAGS_COV = -lcheck -lgcov -fprofile-arcs --coverage -lm
FLAGS_CHECK = -lcheck -lgcov -lm

TMP_FILES = *.gcda *.gcno gcov_report.info *.gcda obj/*.gcno obj/*.gcda
REST_FILES = $(TARGET) report obj/*.o ./test test.dSYM _valgrind-out.txt
QT_TMP = qt/calc_autogen qt/CMakeFiles qt/cmake_install.cmake qt/CMakeCache.txt qt/Makefile
QT_APP = qt/calc.app
QT_BUILD = qt/build-calc-Desktop_x86_darwin_generic_mach_o_64bit-Release
TAR = calc.tar.gz
DOCS = doxygen/html doxygen/latex

.PHONY: all
all: $(OBJ) ## install and run program
	gcc $(OBJ) $(FLAGS_ER) $(FLAGS_CHECK) -o mai

.PHONY: clean
clean: ## remove files: cmake generated, check.h temporary files
	rm -rf $(TMP_FILES)

.PHONY: fclean
fclean: clean ## remove files: cmake generated, check.h temporary files, executables, dists, docs
	rm -rf $(QT_APP) $(TAR) $(DOCS) $(REST_FILES) $(QT_BUILD)

obj/%.o: %.c ## generate .o files
	gcc $(FLAGS_ER) $(FLAGS_COV) -c $< -o $@

.PHONY: tests
tests: $(OBJ_FILTERED) ## generate test executable
	gcc $(OBJ_FILTERED) tests/*.c $(FLAGS_ER) $(FLAGS_CHECK) -o test
	./test
	$(MAKE) clean

.PHONY: gcov_report ## generate and open gcov report with coverage
gcov_report: fclean $(OBJ)
	gcc $(OBJ_FILTERED) tests/*.c $(FLAGS_ER) $(FLAGS_CHECK) -o test
	gcc -o test $(OBJ_FILTERED) tests/*.c $(FLAGS_ER) $(FLAGS_CHECK)
	./test
	lcov -t "gcov_report" -o gcov_report.info -c -d ./obj
	genhtml -o report gcov_report.info;
	$(MAKE) clean
	open report/index.html

.PHONY: lint ## run linters
lint: $(OBJ_FILTERED)
	cppcheck --enable=all --suppress=missingIncludeSystem *.c

.PHONY: grind ## run valgrind
grind: FLAGS_ER = $(FLAGS_GRIND)
grind: fclean $(OBJ_FILTERED)
	gcc $(OBJ_FILTERED) tests/*.c $(FLAGS_CHECK) -o test
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=_valgrind-out.txt ./test
	$(MAKE) clean

.PHONY: leaks ## run leaks
leaks: FLAGS_ER = $(FLAGS_GRIND)
leaks: tests
	leaks --atExit -- ./test
	$(MAKE) clean

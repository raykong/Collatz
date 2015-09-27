CXX        := gpp-4.8
CXXFLAGS   := -pedantic -std=cpp11 -Wall
LDFLAGS    := -lgtest -lgtest_main -pthread
GCOV       := gcov-4.8
GCOVFLAGS  := -fprofile-arcs -ftest-coverage
GPROF      := gprof
GPROFFLAGS := -pg
VALGRIND   := valgrind

clean:
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.gcov
	rm -f RunCollatz
	rm -f RunCollatz.tmp
	rm -f TestCollatz
	rm -f TestCollatz.tmp

config:
	git config -l

scrub:
	make  clean
	rm -f  Collatz.log
	rm -rf collatz-tests
	rm -rf html
	rm -rf latex

status:
	make clean
	@echo
	git branch
	git remote -v
	git status

test: RunCollatz.tmp TestCollatz.tmp

RunCollatz: Collatz.h Collatz.cpp RunCollatz.cpp
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) Collatz.cpp RunCollatz.cpp -o RunCollatz

RunCollatz.tmp: RunCollatz
	./RunCollatz < RunCollatz.in > RunCollatz.tmp
	diff RunCollatz.tmp RunCollatz.out

TestCollatz: Collatz.h Collatz.cpp TestCollatz.cpp
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) Collatz.cpp TestCollatz.cpp -o TestCollatz $(LDFLAGS)

TestCollatz.tmp: TestCollatz
	$(VALGRIND) ./TestCollatz                                       >  TestCollatz.tmp 2>&1
	$(GCOV) -b Collatz.cpp     | grep -A 5 "File 'Collatz.cpp'"     >> TestCollatz.tmp
	$(GCOV) -b TestCollatz.cpp | grep -A 5 "File 'TestCollatz.cpp'" >> TestCollatz.tmp
	cat TestCollatz.tmp

CXX = g++
CXXFLAGS = -Wall -g

mytest: dtree.o utree.o mytest.cpp
	$(CXX) $(CXXFLAGS) dtree.o utree.o mytest.cpp -o mytest

dtree.o: dtree.h dtree.cpp
	$(CXX) $(CXXFLAGS) -c dtree.cpp

utree.o: utree.h utree.cpp accounts.csv
	$(CXX) $(CXXFLAGS) -c utree.cpp


clean:
	rm *.o*
	rm *~


run:
	./mytest


val:
	valgrind ./mytest

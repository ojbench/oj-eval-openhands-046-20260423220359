CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2

code: test.cpp Role.hpp
	$(CXX) $(CXXFLAGS) -o code test.cpp

clean:
	rm -f code

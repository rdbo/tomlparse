all:
	mkdir -p build
	$(CXX) -o build/libtomlparse.so -std=c++23 -g -ggdb -I include -Wall -Wextra -shared -fPIC src/tomlparse.cpp
	$(CXX) -o build/test -std=c+=23 -g -ggdb -I include -Wall -Wextra tests/test.cpp -L build -ltomlparse

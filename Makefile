all:
	mkdir -p build
	$(CXX) -o build/libtomlparse.so -g -ggdb -I include -Wall -Wextra -shared -fPIC src/tomlparse.cpp
	$(CXX) -o build/test -g -ggdb -I include -Wall -Wextra tests/test.cpp -L build -ltomlparse

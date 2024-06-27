#include <tomlparse.hpp>
#include <iostream>
#include <fstream>

int main()
{
	auto file = std::ifstream("tests/config.toml");
	tomlparse(file);
	return 0;
}

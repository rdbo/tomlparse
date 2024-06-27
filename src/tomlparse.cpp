#include <tomlparse.hpp>
#include <iostream>
#include <sstream>

using namespace tomlparse;

std::expected<Toml, Error>
tomlparse::parse(std::ifstream &file)
{
	std::stringstream ss;
	ss << file.rdbuf();

	auto content = ss.str();
	std::cout << content << std::endl;

	return std::unexpected(Error::ReadFailed);
}

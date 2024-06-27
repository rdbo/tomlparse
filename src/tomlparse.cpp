#include <tomlparse.hpp>
#include <iostream>
#include <sstream>

std::expected<Toml, TomlError>
tomlparse(std::ifstream &file)
{
	std::stringstream ss;
	ss << file.rdbuf();

	auto content = ss.str();
	std::cout << content << std::endl;

	return std::unexpected(TomlError::ReadFailed);
}

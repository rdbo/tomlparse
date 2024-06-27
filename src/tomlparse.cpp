#include <tomlparse.hpp>
#include <iostream>
#include <sstream>
#include <cctype>

using namespace tomlparse;

std::expected<Toml, Error>
parse_toml_content(std::string &content)
{
	for (auto c: content) {
		if (std::isspace(c))
			continue;
	}

	return std::unexpected(Error::MalformedContent);
}

std::expected<Toml, Error>
tomlparse::parse(std::ifstream &file)
{
	std::stringstream ss;
	ss << file.rdbuf();

	auto content = ss.str();
	std::cout << content << std::endl;

	return parse_toml_content(content);
}

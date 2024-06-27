#include <tomlparse.hpp>
#include <iostream>
#include <sstream>
#include <cctype>

using namespace tomlparse;

enum class TokenType {
	Identifier,
	Equals,
	Number,
	Dot,
	DoubleQuote,
	Quote,
	LeftBrace,
	RightBrace,
	LeftBracket,
	RightBracket,
};

struct Token {
	TokenType type;
	std::string value;
};

std::vector<Token>
tokenize_toml_content(std::string &content)
{
	std::vector<Token> tokens = {};

	for (size_t i = 0; i < content.length(); ++i) {
		auto c = content[i];
		if (std::isspace(c))
			continue;

		if (std::isdigit(c)) {
			if (!tokens.empty() && tokens.back().type == TokenType::Number) {
				tokens.back().value.push_back(c);
			} else {
				tokens.push_back(Token { type: TokenType::Number, value: std::string(1, c) });
			}
		} else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
			if (!tokens.empty() && tokens.back().type == TokenType::Identifier) {
				tokens.back().value.push_back(c);
			} else {
				tokens.push_back(Token { type: TokenType::Identifier, value: std::string(1, c) });
			}
		} else {
			TokenType tt;
			
			switch (c) {
			case '[':
				tt = TokenType::LeftBracket;
				break;
			case ']':
				tt = TokenType::RightBracket;
				break;
			case '{':
				tt = TokenType::LeftBrace;
				break;
			case '}':
				tt = TokenType::RightBrace;
				break;
			case '=':
				tt = TokenType::Equals;
				break;
			case '.':
				tt = TokenType::Dot;
				break;
			case '"':
				tt = TokenType::DoubleQuote;
				break;
			case '\'':
				tt = TokenType::Quote;
				break;
			default:
				continue;
			}

			tokens.push_back(Token { type: tt, value: std::string(1, c) });
		}
	}

	return tokens;
}

std::expected<Toml, Error>
parse_toml_tokens(std::vector<Token> &tokens)
{
	return std::unexpected(Error::UnexpectedToken);
}

std::expected<Toml, Error>
tomlparse::parse(std::ifstream &file)
{
	std::stringstream ss;
	ss << file.rdbuf();
	auto content = ss.str();

	auto tokens = tokenize_toml_content(content);
	std::cout << "Token count: " << tokens.size() << std::endl;
	for (auto &token : tokens) {
		std::cout << "Token: " << static_cast<int>(token.type) << ", " << token.value << std::endl;
	}

	return parse_toml_tokens(tokens);
}

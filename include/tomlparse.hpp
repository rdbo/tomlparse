#ifndef TOMLPARSE_HPP
#define TOMLPARSE_HPP

#include <cstdint>
#include <fstream>
#include <expected>
#include <unordered_map>
#include <variant>
#include <vector>
#include <memory>

enum class TomlError {
	ReadFailed
};

// TOML Types
class TomlTable;
typedef std::int64_t TomlInt;
typedef double       TomlFloat;
typedef bool         TomlBool;
template <typename T>
class TomlArray: public std::vector<T> {  };

class TomlEntry {
private:
	std::unique_ptr<std::variant<TomlTable, TomlInt, TomlFloat, TomlBool, TomlArray<TomlEntry>>> value;
public:
	template <typename T>
	inline T get()
	{
		return std::get<T>(*this->value.get());
	}
};

class TomlTable {
private:
	std::unordered_map<std::string, TomlEntry> entries;
public:
	template<typename T>
	inline T get(std::string name)
	{
		return this->entries[name].get<T>();
	}

	inline std::unordered_map<std::string, TomlEntry> &
	get_entries()
	{
		return this->entries;
	}
};

typedef TomlTable Toml; // A root-level toml content can be seen as just a regular table

std::expected<Toml, TomlError>
tomlparse(std::ifstream &file);

#endif

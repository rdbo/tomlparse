#ifndef TOMLPARSE_HPP
#define TOMLPARSE_HPP

#include <cstdint>
#include <fstream>
#include <expected>
#include <type_traits>
#include <unordered_map>
#include <variant>
#include <vector>

enum class TomlResult {
	Ok,
	ReadErr
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
	std::variant<TomlTable, TomlInt, TomlFloat, TomlBool, TomlArray<TomlEntry>> value;
public:
	template <typename T>
	inline T get()
	{
		return std::get<T>(this->value);
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

typedef TomlTable Toml;

std::expected<Toml, TomlResult>
tomlparse(std::ifstream &file);

#endif

#ifndef TOMLPARSE_HPP
#define TOMLPARSE_HPP

#include <cstdint>
#include <fstream>
#include <expected>
#include <unordered_map>
#include <variant>
#include <vector>
#include <memory>

namespace tomlparse {
	enum class Error {
		ReadFailed
	};

	// TOML Types
	class Table;
	typedef std::int64_t Int;
	typedef double       Float;
	typedef bool         Bool;
	template <typename T>
	class Array: public std::vector<T> {  };

	class Entry {
	private:
		std::unique_ptr<std::variant<Table, Int, Float, Bool, Array<Entry>>> value;
	public:
		template <typename T>
		inline T get()
		{
			return std::get<T>(*this->value.get());
		}
	};

	class Table {
	private:
		std::unordered_map<std::string, Entry> entries;
	public:
		template<typename T>
		inline T get(std::string name)
		{
			return this->entries[name].get<T>();
		}

		inline std::unordered_map<std::string, Entry> &
		get_entries()
		{
			return this->entries;
		}
	};

	typedef Table Toml; // A root-level toml content can be seen as just a regular table

	std::expected<Toml, Error>
	parse(std::ifstream &file);
}

#endif

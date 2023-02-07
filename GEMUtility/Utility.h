#pragma once

#include <regex>
#include <string>
#include <filesystem>



namespace _gem {

	std::regex sanitizeForRegex(std::string input) {
		std::regex specialChars{ R"([-[\]{}()*+?.,\^$|#\s])" };
		return std::regex(std::regex_replace(input, specialChars, R"(\$&)"));
	}

	void guaranteePath(std::string path) {
		//Check if path exists, otherwise create path
		namespace sf = std::filesystem;
		sf::path newPath(path);
		bool pathExists = sf::exists(newPath);
		if (!pathExists) {
			Logger::log(Logger::GEM, "Path not found: " + newPath.string() + "\n");
			sf::create_directories(newPath);
		}
	}

	template<class T>
	std::string castToString(T val) {
		std::ostringstream ss;
		ss << std::fixed << std::setprecision(std::numeric_limits<T>::digits10 + 1);
		ss << val; return ss.str();
	}


	std::string getRelativePath(std::filesystem::path path, std::filesystem::path root) {
		namespace sf = std::filesystem;

		std::string relPath = sf::relative(path, root).replace_extension("").string();
		char seperator = sf::path::preferred_separator;

		std::replace(relPath.begin(), relPath.end(), seperator, '/');
		return relPath;
	}

}
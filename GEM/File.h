#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <regex>
#include <vector>
#include <unordered_set>
#include <filesystem>

#include "Logger.h"
#include "Utility.h"
#include "Signature.h"
#include "Configuration.h"

namespace _gem {

	class File {
	public:
		File(std::filesystem::path path) :
			path(getRelativePath(path, Configuration::getSourceDirectory())),
			name(path.stem().string()),
			extension(path.extension().string())
		{
			/*
			namespace sf = std::filesystem;
			sf::path dir = std::filesystem::path(Configuration::getSourceDirectory());
			std::string fileName = sf::relative(dir, path).replace_extension("").string();
			*/
			std::ifstream file(path);
			std::ostringstream ss;
			ss << file.rdbuf();
			content = ss.str();
			file.close();

			Logger::log(Logger::GEM, "Loading file: ", path.string());

			std::unordered_set<std::string> duplicateChecker;

			std::regex macroRegex("%%\\[([a-zA-Z][a-zA-Z0-9_/-]*):?([a-zA-Z][a-zA-Z0-9_.-]*)?\\]");
			std::smatch macroMatches;
			std::string toSearchMacro = content;

			//Get all macros
			while (std::regex_search(toSearchMacro, macroMatches, macroRegex)) {
				auto pair = duplicateChecker.emplace(macroMatches[1].str());
				macros.emplace_back(macroMatches[0].str());
				if (!pair.second) {
					Logger::log(Logger::GEM, "Macro: " + macroMatches[1].str() + " duplicate found in file: " + path.string(), "...");
				}

				toSearchMacro = macroMatches.suffix().str();
			}

			duplicateChecker.clear();



			std::regex includeRegex("##\\[([a-zA-Z][a-zA-Z0-9_/-]*):?([a-zA-Z][a-zA-Z0-9_.-]*)?\\]");
			std::smatch includeMatches;
			std::string toSearchInclude = content;

			//Get all includes
			while (std::regex_search(toSearchInclude, includeMatches, includeRegex)) {
				auto pair = duplicateChecker.emplace(includeMatches[0].str());
				includes.emplace_back(includeMatches[0].str());
				if (!pair.second) {
					Logger::log(Logger::GEM, "Include: " + includeMatches[1].str() + " duplicate found in file: " + path.string(), "...");
				}
				toSearchInclude = includeMatches.suffix().str();
			}
		}



		template<class... Args>
		size_t processFile(Args... args) {
			std::vector<std::string> arguments({ castToString(args)... });
			std::string processedContent = content;

			for (size_t i = 0; i < macros.size(); i++) {

				processedContent = std::regex_replace(processedContent, sanitizeForRegex(macros[i].signature), arguments[i]);
			}

			processedContents.emplace_back(processedContent);

			return processedContents.size() - 1;
		}


		std::string content;
		std::string path;
		std::string name;
		std::string extension;
		std::vector<Signature> macros;
		std::vector<Signature> includes;
		std::vector<std::string> processedContents;
	};

}
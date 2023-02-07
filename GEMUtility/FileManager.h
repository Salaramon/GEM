#pragma once

#include <filesystem>
#include <algorithm>
#include <cctype>
#include <unordered_map>
#include <regex>
#include <string>
#include <stdlib.h>
#include <algorithm>

#include "File.h"
#include "Logger.h"

#include "Configuration.h"

namespace _gem {

	class FileManager {
	public:
		FileManager() :
			source_directory(Configuration::getSourceDirectory()),
			entry_directory(Configuration::getEntryDirectory())
		{
			namespace sf = std::filesystem;

			//Check if path exists, otherwise create path
			guaranteePath(source_directory.string());

			Logger::log(Logger::GEM, "Loading source files at ", source_directory.string());


			//Add all files to map
			auto pred = [this](const sf::path& path) {
				std::string ext = path.extension().string();
				std::string stem = path.stem().string();
				std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
				std::transform(stem.begin(), stem.end(), stem.begin(), ::tolower);
				if (ext == ".gem") {
					File file(path.string());
					std::string relativePath = getRelativePath(path, source_directory);
					files.emplace(relativePath, file);

					sf::path noFilePath = path;
					noFilePath.remove_filename();
					if (noFilePath == entry_directory) {
						entry_files.push_back(file.path);
					}
				}
			};

			using SFrdit = sf::recursive_directory_iterator;
			std::for_each(SFrdit(source_directory), SFrdit{}, pred);

			if (files.size()) {
				Logger::log(Logger::GEM, "No .gem files found under: " + source_directory.string() + "\n");
			}



		}

		std::vector<std::string> getEntryFiles() {
			return entry_files;
		}

		File& getFileByName(std::string name) {
			auto found = files.find(name);
			if (found == files.end()) {
				Logger::log(Logger::GEM, "File: " + name + " was not found.");
			}

			return found->second;
		}

		inline static Configuration config;

	private:

		std::filesystem::path entry_directory;
		std::filesystem::path source_directory;
		std::ofstream log;
		std::unordered_map<std::string, File> files;
		std::vector<std::string> entry_files;
	};

}
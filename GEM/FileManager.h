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
			directory(config.getSourceDirectory())
		{
			namespace sf = std::filesystem;

			//Check if path exists, otherwise create path
			guaranteePath(directory.string());

			Logger::log(Logger::GEM, "Loading source files at ", directory.string());


			//Add all files to map
			auto pred = [this](const sf::path& path) {
				std::string ext = path.extension().string();
				std::string stem = path.stem().string();
				std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
				std::transform(stem.begin(), stem.end(), stem.begin(), ::tolower);
				if (ext == ".gem") {
					files.emplace(getRelativePath(path, directory), File(path.string()));
				}
			};

			using SFrdit = sf::recursive_directory_iterator;
			std::for_each(SFrdit(directory), SFrdit{}, pred);

			if (files.size()) {
				Logger::log(Logger::GEM, "No .gem files found under: " + directory.string() + "\n");
			}



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

		std::filesystem::path directory;
		std::ofstream log;
		std::unordered_map<std::string, File> files;
		std::string entryFile;


	};

}
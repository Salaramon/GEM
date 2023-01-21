#pragma once


#include <toml++/toml.h>
#include <filesystem>
#include <fstream>

#include "Logger.h"

namespace _gem {

	class Configuration {
	public:
		Configuration() {
			namespace sf = std::filesystem;

			const std::string configFile = "GEM.cfg";

			sf::path localDirectory(configFile);
			if (!sf::exists(localDirectory)) {
				Logger::log(Logger::GEM, configFile + " was not found. Creating file with default values...");
				std::ofstream cfgFile(configFile);
				cfgFile
					<< "source_directory = \"src/\"\n"
					<< "build_directory = \"build/\"\n"
					<< "entry_files = []";
				cfgFile.close();
			}

			try {
				table = toml::parse_file(configFile);
			}
			catch (const toml::parse_error& err) {
				Logger::log(Logger::GEM, "Parsing of GEM.cfg was unsuccessful:\n\t", std::string(err.description()), "\n");
			}

			if (table["source_directory"].is_value()) {
				Logger::log(Logger::GEM, "Could not find source_directory, or it was not assigned in the GEM.cfg\n");
			}
			if (table["build_directory"].is_value()) {
				Logger::log(Logger::GEM, "Could not find build_directory, or it was not assigned in the GEM.cfg\n");
			}
			if (table["entry_files"].is_value()) {
				Logger::log(Logger::GEM, "Could not find entry_files, or it was not assigned in the GEM.cfg\n");
			}


		}

		static std::string getSourceDirectory() {
			return table["source_directory"].value<std::string>().value();
		}

		static std::string getBuildDirectory() {
			return table["build_directory"].value<std::string>().value();
		}

		static std::string getLinkerDirectory() {
			return table["linker_directory"].value<std::string>().value();
		}

		static std::vector<std::string> getEntryFiles() {
			std::vector<std::string> vec;
			toml::array& arr = *table.get_as<toml::array>("entry_files");
			for (size_t i = 0; i < arr.size(); i++) {
				vec.push_back(arr[i].value<std::string>().value());
			}

			return vec;
		}

		inline static toml::table table;
	};

}
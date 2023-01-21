#pragma once

#include <string>
#include <fstream>
#include <unordered_map>

class Logger {
public:
	template<class... Args>
	static void log(std::string log, Args... entry) {

		auto it = logMap.find(log);
		if (it == logMap.end()) {
			it = logMap.emplace(log, "").first;
		}
		
		it->second += (std::string(entry) + ...);

		/*
		std::vector<std::string> message({ std::string(entry)... });

		for (std::string elm : message) {
			it->second += elm;
		}
		*/
	}

	static void post(std::string log) {
		std::ofstream logFile(log + ".log");
		logFile << logMap.find(log)->second;
		logFile.close();
	}

	inline static std::string GEM = "GEM";
	inline static std::string GEMLinker = "GEMLinker";

private:
	//log name, log string
	inline static std::unordered_map<std::string, std::string> logMap;
};
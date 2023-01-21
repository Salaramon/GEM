#pragma once

#include <string>
#include <regex>

#include "FileManager.h"
#include "Logger.h"
#include "Utility.h"

template<class T>
class Shader : public T {
public:



	void compile() {
		std::string glslCode = parseTree(T::getEntry());

		guaranteePath(T::manager.config.getBuildDirectory());
		std::ofstream codeFile(T::manager.config.getBuildDirectory() + "/" + T::getEntry().name + ".glsl");
		codeFile << glslCode;
		codeFile.close();
	}

private:
	std::string parseTree(File& file) {

		std::regex includeRegex("##\\[([a-zA-Z][a-zA-Z0-9_.-]+)\\]");
		std::smatch matches;

		std::string compiledCode;
		

		for (size_t i = 0; i < file.processedContents.size(); i++) {
			compiledCode += file.processedContents[i] + "\n";
		}

		for (size_t i = 0; i < file.includes.size(); i++) {
			File& includedFile = T::manager.getFileByName(file.includes[i].parameter);
			compiledCode = std::regex_replace(compiledCode, sanitizeForRegex(file.includes[i].signature), Shader<T>::parseTree(includedFile));
		}

		return compiledCode;
	}
};
#pragma once

#include <string>
#include <regex>

#include "FileManager.h"
#include "Utility.h"

//Need to fix GEM.h so that build and entry dir belongs to each struct
//Need to fix generation of macroless includes are just automatically processed when compiled and is not accessible through GEM.h


namespace gem {

	template<class T>
	class Shader : public T {
	public:



		void compile() {
			std::string glslCode = parseTree(T::getEntry());

			_gem::guaranteePath(T::build);
			std::ofstream codeFile(std::string(T::build) + "/" + T::getEntry().name + ".glsl");
			codeFile << glslCode;
			codeFile.close();
		}

	private:
		std::string parseTree(_gem::File& file) {

			std::string compiledCode;


			for (size_t i = 0; i < file.processedContents.size(); i++) {
				compiledCode += file.processedContents[i] + "\n";
			}

			for (size_t i = 0; i < file.includes.size(); i++) {
				_gem::File& includedFile = T::manager.getFileByName(file.includes[i].parameter);
				compiledCode = std::regex_replace(compiledCode, _gem::sanitizeForRegex(file.includes[i].signature), Shader<T>::parseTree(includedFile));
			}

			return compiledCode;
		}
	};

}
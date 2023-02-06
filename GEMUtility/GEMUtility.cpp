
#include <vector>
#include <string>

#include <FileManager.h>
#include <File.h>
#include <Configuration.h>
#include <Types.h>

using namespace _gem;

FileManager manager;

std::string parse(const File& file, std::string useCase, std::string prefix) {

	//Logging parse action
	Logger::log(Logger::GEMLinker, "parsing file: ", file.name, " as part in ", prefix, "\n");

	//Invalid parameter check.
	bool validParameter = false;
	for (std::string s : includeSpecifiers) {
		if (useCase == s) {
			validParameter = true;
		}
	}
	if (!validParameter) {
		Logger::log(Logger::GEMLinker, useCase, " is an unrecognized include specifier...\n");
	}


	//Generated function start
	std::string generatedCode = "static void " + useCase + prefix + "(";

	
	//Generating function parameters from macros
	for (size_t i = 0; i < file.macros.size(); i++) {
		generatedCode += file.macros[i].type + " " + file.macros[i].parameter + ",";
	}
	if (file.macros.size() != 0) {
		generatedCode.pop_back();
	}

	//Generating function parameters as arguments to be passed
	std::string parameters;
	for (size_t i = 0; i < file.macros.size(); i++) {
		parameters += file.macros[i].parameter + ",";
	}
	if (parameters.size()) {
		parameters.pop_back();
	}

	
	//Finalizing function
	generatedCode += ") { if(manager.getFileByName(\"" + file.path + "\").processFile(" + parameters + ") && \"set\" == \"" + useCase + "\" ){ throw; } ;}\n";


	//Continuing include iteration and parsing.
	for (size_t i = 0; i < file.includes.size(); i++) {
		File includedFile = manager.getFileByName(file.includes[i].parameter);
		generatedCode += parse(includedFile, file.includes[i].type, prefix + "_" + includedFile.name);
	}

	return generatedCode;

}



int main(int argc, char* argv[]) {
	std::vector<std::string> entryFiles = manager.getEntryFiles();
	if (entryFiles.size() == 0) {
		Logger::log(Logger::GEMLinker, "No entry files found.\n");
	}

	std::string generatedCode = "#include <Shader.h>\n";
	generatedCode += "namespace gem {\n";


	for (size_t i = 0; i < entryFiles.size(); i++) {
		File file = manager.getFileByName(entryFiles[i]);

		//Logging entry points
		Logger::log(Logger::GEMLinker, "Initializing parsing of: ", file.name, " as entry point\n");

		generatedCode += "struct " + file.name + " {public:\n";
		generatedCode += parse(file, "set", file.name);
		generatedCode += "protected:\n";
		generatedCode += "inline static _gem::FileManager manager;\n";
		generatedCode += "static _gem::File& getEntry() { return manager.getFileByName(\"" + entryFiles[i] + "\");}\n";
		generatedCode += "};\n";
	}

	generatedCode += "};";

	std::ofstream codeFile(manager.config.getLinkerDirectory() + "/GEM.h");
	codeFile << generatedCode;
	codeFile.close();
	
	Logger::post(Logger::GEMLinker);
}
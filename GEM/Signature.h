#pragma once

#include <string>
#include <vector>
#include <regex>


class Signature {
public:
	/*
		
	*/

	Signature(std::string signature) : signature(signature)
	{
		std::string search = signature;
		std::regex regex("([#%][#%])[\\[]([a-zA-Z][a-zA-Z0-9_/-]*)(:?)([a-zA-Z]?[a-zA-Z0-9_.-]*)?[\\]]");
		std::smatch matches;
		
		std::regex_search(search, matches, regex);
		Signature::signature = matches[0];
		tag = matches[1];
		parameter = matches[2];
		seperator = matches[3];
		specifier = matches[4];

		if (tag == "%%") {
			type = "std::string";
		}
		if (tag == "##") {
			type = "set";
		}
		
		if (specifier != "") {
			type = specifier;
		}
	}

	std::string tag;
	std::string parameter;
	std::string seperator;
	std::string specifier;

	std::string type;

	std::string signature;

};
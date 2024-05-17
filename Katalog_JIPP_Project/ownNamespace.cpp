#include "ownNamespace.h"
#include <cctype>

namespace ownNamespace {
	std::string capitalizeFirstLetter(const std::string& str) {
		std::string result = str;
		bool capitalizeNext = true;

		for (char& c : result) {
			c = std::tolower(c);
			if (std::isspace(c)) {
				capitalizeNext = true;
			}
			else if (capitalizeNext) {
				c = std::toupper(c);
				capitalizeNext = false;
			}
		}

		return result;
	}
}
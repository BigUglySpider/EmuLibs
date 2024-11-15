#ifndef EMU_IO_ARG_PARSER_HPP_INC_
#define EMU_IO_ARG_PARSER_HPP_INC_ 1

#include <map>
#include <string>
#include <string_view>
#include <unordered_map>

#include "../EmuCore/CommonConcepts/CommonRequirements.h"
#include "../EmuCore/TMPHelpers/Values.h"

#include "_do_not_manually_include/_arg_parser/Parameter.hpp"
#include "_do_not_manually_include/_arg_parser/ParameterType.hpp"

namespace EmuIO
{
	class ArgParser
	{
	public:

	private:
		std::unordered_map<std::string, EmuIO::Parameter> parameters;
		std::unordered_map<std::string, std::string_view> alias_to_param_map;
		std::unordered_map<std::string_view, std::vector<std::string_view>> param_to_aliases_map;
	};
}

#endif

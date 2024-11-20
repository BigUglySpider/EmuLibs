#ifndef EMU_IO_ARG_PARSER_HPP_INC_
#define EMU_IO_ARG_PARSER_HPP_INC_ 1

#include <array>
#include <map>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>

#include "../EmuCore/CommonConcepts/CommonRequirements.h"
#include "../EmuCore/TMPHelpers/Values.h"
#include "../EmuCore/TMPHelpers/VariadicHelpers.h"

#include "_do_not_manually_include/_arg_parser/Parameter.hpp"
#include "_do_not_manually_include/_arg_parser/ParameterType.hpp"

namespace EmuIO
{
	class ArgParser
	{
	private:
		template<class Exception, class...StreamArgs>
		[[nodiscard]] static Exception _make_exception(StreamArgs&&...msg_args)
		{
			std::ostringstream str{};
			((str << std::forward<StreamArgs>(msg_args)), ...);
			return Exception{ str.str().c_str() };
		}

	public:
		static constexpr auto reserved_names = EmuCore::TMP::make_std_array<std::string_view>
		(
			"--help", "-h"
		);
		static constexpr std::string_view default_help_separator = "----------";

	private:
		template<std::size_t...Indices>
		[[nodiscard]] static constexpr bool _is_reserved_name(const std::string_view& name, [[maybe_unused]] std::index_sequence<Indices...>) noexcept
		{
			return (... || (name == reserved_names[Indices]));
		}

	public:
		[[nodiscard]] static constexpr bool is_reserved_name(const std::string_view& name) noexcept
		{
			return _is_reserved_name(name, std::make_index_sequence<reserved_names.size()>());
		}

		ArgParser() = delete;
		ArgParser(const ArgParser&) = delete;
		ArgParser& operator=(const ArgParser&) = delete;

		ArgParser(ArgParser&&) noexcept = default;
		ArgParser& operator=(ArgParser&&) noexcept = default;

		ArgParser(std::string program_name_, std::optional<std::string> program_desc_ = std::nullopt) :
			parameters{},
			alias_to_param_map{},
			param_to_aliases_map{},
			parameter_descriptions{},
			unnamed_arguments{},
			program_name{ std::move(program_name_) },
			program_desc{ std::move(program_desc_) }
		{
		}

		[[nodiscard]] const EmuIO::Parameter& operator[](const std::string& name_or_alias) const
		{
			const EmuIO::Parameter* param{ nullptr };
			if (!TryGet(name_or_alias, &param))
			{
				throw _make_exception<std::out_of_range>("Attempted to retrieve a parameter whose name does not exist, even as an alias (", name_or_alias, ')');
			}
			return *param;
		}

		[[nodiscard]] bool TryGet(const std::string& name_or_alias, const EmuIO::Parameter** out_param) const
		{
			auto param_it{ parameters.find(name_or_alias) };
			auto params_end{ parameters.end() };
			if (param_it != params_end)
			{
				(*out_param) = &(param_it->second);
				return true;
			}

			auto alias_it{ alias_to_param_map.find(name_or_alias) };
			if (alias_it == alias_to_param_map.end())
			{
				return false;
			}

			auto aliased_param_it{ parameters.find(alias_it->second) };
			if (aliased_param_it != params_end)
			{
				(*out_param) = &(aliased_param_it->second);
				return true;
			}
			return false;
		}

		template<EmuIO::ParameterType Type, class DefaultValue>
		requires((Type & EmuIO::ParameterType::Enum) == EmuIO::ParameterType{} && !EmuConcepts::UnqualifiedMatch<DefaultValue, std::monostate>)
		void RegisterParameter(std::string name, std::string desc, DefaultValue&& default_value)
		{
			_throw_if_invalid_new_name(name);

			param_to_aliases_map.emplace(std::make_pair(name, std::vector<std::string>{}));
			parameter_descriptions.emplace(std::make_pair(name, std::move(desc)));
			parameters.emplace(std::make_pair
			(
				std::move(name),
				EmuIO::Parameter::make<Type>(std::forward<DefaultValue>(default_value))
			));
		}

		template<EmuIO::ParameterType Type>
		requires((Type & EmuIO::ParameterType::Enum) == EmuIO::ParameterType{} && (Type & EmuIO::ParameterType::Array) == EmuIO::ParameterType::Array)
		void RegisterParameter(std::string name, std::string desc, std::monostate default_as_empty_array)
		{
			_throw_if_invalid_new_name(name);

			param_to_aliases_map.emplace(std::make_pair(name, std::vector<std::string>{}));
			parameter_descriptions.emplace(std::make_pair(name, std::move(desc)));
			parameters.emplace(std::make_pair
			(
				std::move(name),
				EmuIO::Parameter::make<Type>(std::move(default_as_empty_array))
			));
		}

		template<class ParamType, class DefaultValue>
		requires(!EmuConcepts::UnqualifiedMatch<DefaultValue, std::monostate>)
		void RegisterParameter(std::string name, std::string desc, DefaultValue&& default_value)
		{
			RegisterParameter<EmuIO::type_to_parameter_type_enum<ParamType>()>
			(
				std::move(name),
				std::move(desc),
				std::forward<DefaultValue>(default_value)
			);
		}

		template<class ParamType>
		requires(std::is_array_v<typename std::remove_cvref<ParamType>::type>)
		void RegisterParameter(std::string name, std::string desc, std::monostate default_as_empty_array)
		{
			RegisterParameter<EmuIO::type_to_parameter_type_enum<ParamType>()>
			(
				std::move(name),
				std::move(desc),
				std::move(default_as_empty_array)
			);
		}

		void AddAlias(const std::string& name, std::string alias)
		{
			_throw_if_invalid_new_name(alias);
			alias_to_param_map.emplace(std::make_pair(alias, name));
			param_to_aliases_map[name].emplace_back(std::move(alias));
		}

		template<class...AliasStrings>
		requires(sizeof...(AliasStrings) != 0 && (... && std::is_constructible_v<std::string, AliasStrings>))
		void AddAliases(const std::string& name, AliasStrings&&...aliases)
		{
			((AddAlias(name, std::string{ std::forward<AliasStrings>(aliases) })), ...);
		}

		[[nodiscard]] bool ContainsNameOrAlias(const std::string& name_or_alias) const
		{
			return parameters.contains(name_or_alias) || alias_to_param_map.contains(name_or_alias);
		}

		std::ostream& Help(std::ostream& str, std::string_view separator = default_help_separator) const
		{
			str << program_name << '\n';
			if (program_desc.has_value())
			{
				str << *program_desc << '\n';
			}
			str << separator << std::endl;

			auto alphabetical_map{ _make_alphabetical_map(parameters) };
			for (const auto& name_param_pair : alphabetical_map)
			{
				str << '[' << name_param_pair.first << "]\n";
				const std::vector<std::string>& aliases{ param_to_aliases_map.at(name_param_pair.first) };
				const std::size_t num_aliases{ aliases.size() };
				if (num_aliases > 0)
				{
					str << "\tAliases: [";
					std::vector<std::string> alphabetical_aliases{ aliases };
					std::sort(alphabetical_aliases.begin(), alphabetical_aliases.end());
					str << '"' << alphabetical_aliases[0] << '"';
					for (std::size_t i{ 1u }; i < num_aliases; ++i)
					{
						str << " | \"" << alphabetical_aliases[i] << '"';
					}
					str << "]\n";
				}
				auto desc_it{ parameter_descriptions.find(name_param_pair.first) };
				if (desc_it != parameter_descriptions.end())
				{
					str << desc_it->second << '\n';
				}
				str << '\n';

				name_param_pair.second->AppendToStream<false, true, false, true>(str) << '\n';
				if (name_param_pair.second->IsConst())
				{
					str << "Can only be set once.\n";
				}
				else if (name_param_pair.second->IsArray())
				{
					str << "Can be set multiple times, adding each new value to the back of an expanding array.\n";
				}
				else
				{
					str << "Can be set multiple times, with the most-recently set value being the used value.\n";
				}
				str << separator << std::endl;
			}
			return str;
		}

		template<bool ReturnOnError>
		std::size_t Parse(int argc, const char** argv, std::ostream& out_stream, std::ostream& err_stream)
		{
			std::size_t err_count{ 0u };
			for (int i{ 0 }; i < argc; ++i)
			{
				std::string arg{ argv[i] };
				if (arg.starts_with('-'))
				{
					std::size_t dash_count{ 1u };
					if (arg.size() == 1)
					{
						++err_count;
						err_stream << "Invalid argument at position " << i << ": Cannot provide just `-`." << std::endl;
						if constexpr (ReturnOnError) { return err_count; }
						else                         { continue; }
					}
					else if (arg.starts_with("--"))
					{
						if (arg.size() == 2)
						{
							++err_count;
							err_stream << "Invalid argument at position " << i << ": Cannot provide just `--`." << std::endl;
							if constexpr (ReturnOnError) { return err_count; }
							else                         { continue; }
						}
						else if (arg.starts_with("---"))
						{
							++err_count;
							err_stream << "Invalid argument at position " << i << " (" << arg << "): Cannot provide just more than 2 dashes as prefixes." << std::endl;
							if constexpr (ReturnOnError) { return err_count; }
							else                         { continue; }
						}
						else
						{
							++dash_count;
						}
					}

					EmuIO::Parameter* param{ nullptr };
					if (!_try_get(arg, &param))
					{
						if (arg == "--help" || arg == "-h")
						{
							Help(out_stream);
						}
						else
						{
							++err_count;
							err_stream << "Invalid argument at position " << i << " (" << arg << "): It is not registered as a valid parameter." << std::endl;
							if constexpr (ReturnOnError) { return err_count; }
							else { continue; }
						}
					}
					else
					{
						const int next_i{ i + 1 };
						if (next_i < argc)
						{
							std::string next_arg{ argv[next_i] };
							if (next_arg.starts_with('-'))
							{
								if ((param->GetType() & ParameterType::Bool) == ParameterType::Bool)
								{
									std::optional<std::string> append_err{ param->AppendInput("true") };
									if (append_err.has_value())
									{
										++err_count;
										err_stream << "Invalid argument at position " << i << " (" << arg << "): " << *append_err << std::endl;
										if constexpr (ReturnOnError) { return err_count; }
										else                         { continue; }
									}
								}
								else
								{
									++err_count;
									err_stream << "Invalid argument at position " << i << " (" << arg
											   << "): It is not followed by a value at position " << next_i << " (which is instead a different parameter) and thus does not have a paired value. This is valid for parameters with boolean values, but this is a "
											   << EmuIO::arg_param_type_to_string(param->GetType()) << " parameter." << std::endl;
									if constexpr (ReturnOnError) { return err_count; }
									else                         { continue; }
								}
							}
							else
							{
								++i; // Skip next regardless of outcome since we're considering it paired with the current argument
								std::optional<std::string> append_err{ param->AppendInput(next_arg) };
								if (append_err.has_value())
								{
									++err_count;
									err_stream << "Invalid argument pair at position " << (i - 1) << ", " << next_i << " (" << arg << ", " << next_arg << "): " << *append_err << std::endl;
									if constexpr (ReturnOnError) { return err_count; }
									else { continue; }
								}
							}
						}
						else
						{
							if ((param->GetType() & ParameterType::Bool) == ParameterType::Bool)
							{
								std::optional<std::string> append_err{ param->AppendInput("true") };
								if (append_err.has_value())
								{
									++err_count;
									err_stream << "Invalid argument at position " << i << " (" << arg << "): " << *append_err << std::endl;
									if constexpr (ReturnOnError) { return err_count; }
						            else                         { continue; }
								}
							}
							else
							{
								++err_count;
								err_stream << "Invalid argument at position " << i << " (" << arg
									       << "): It is the final argument and thus does not have a paired value. This is valid for parameters with boolean values, but this is a "
									       << EmuIO::arg_param_type_to_string(param->GetType()) << " parameter." << std::endl;
								if constexpr (ReturnOnError) { return err_count; }
						        else                         { continue; }
							}
						}
					}
				}
				else
				{
					unnamed_arguments.emplace_back(std::move(arg));
				}
			}
			return err_count;
		}

	private:
		template<class T>
		[[nodiscard]] static std::map<std::string, const T*> _make_alphabetical_map(const std::unordered_map<std::string, T>& in_map)
		{
			std::map<std::string, const T*> out_map{};
			for (const auto& name_param_pair : in_map)
			{
				out_map.emplace(std::make_pair(name_param_pair.first, &(name_param_pair.second)));
			}
			return out_map;
		}

		void _throw_if_invalid_new_name(const std::string& name) const
		{
			if (ContainsNameOrAlias(name))
			{
				throw _make_exception<std::invalid_argument>("Attempted to add a parameter with the name `", name, "`, but that name is already in use.");
			}

			if (is_reserved_name(name))
			{
				throw _make_exception<std::invalid_argument>("Attempted to add a parameter with the reserved name `", name, "`.");
			}

			if (!name.starts_with('-'))
			{
				throw _make_exception<std::invalid_argument>("Attempted to add a parameter whose name does not start with `-` (`", name, "`). This character is required to differentiate `-` args from `- - ` args.");
			}

			if (name.size() == 1)
			{
				throw _make_exception<std::invalid_argument>("Attempted to add a parameter whose name is only `-`. Dashes (or dash pairs) must be followed with at least one character.");
			}

			if (name.starts_with("--"))
			{
				if (name.size() == 2)
				{
					throw _make_exception<std::invalid_argument>("Attempted to add a parameter whose name is only `--`. Dash pairs must be followed with at least one character.");
				}

				if (name.starts_with("---"))
				{
					throw _make_exception<std::invalid_argument>("Attempted to add a parameter whose name starts with more than 2 dashes (`", name, "`). A name must start with 1 (`-`) or 2 (`- - `) dashes.");
				}
			}

			if (std::any_of(name.begin(), name.end(), [](const char char_) { return std::isspace(char_); }))
			{
				throw _make_exception<std::invalid_argument>("Attempted to add a parameter whose name contains whitespace (`", name, "`). Parameter names must contain no whitespace; use tokens such as dashes and underscores(`-` or `_`) instead of whitespace.");
			}
		}

		[[nodiscard]] bool _try_get(const std::string& name_or_alias, EmuIO::Parameter** out_param)
		{
			auto param_it{ parameters.find(name_or_alias) };
			auto params_end{ parameters.end() };
			if (param_it != params_end)
			{
				(*out_param) = &(param_it->second);
				return true;
			}

			auto alias_it{ alias_to_param_map.find(name_or_alias) };
			if (alias_it == alias_to_param_map.end())
			{
				return false;
			}

			auto aliased_param_it{ parameters.find(alias_it->second) };
			if (aliased_param_it != params_end)
			{
				(*out_param) = &(aliased_param_it->second);
				return true;
			}
			return false;
		}

		std::unordered_map<std::string, EmuIO::Parameter> parameters;
		std::unordered_map<std::string, std::string> alias_to_param_map;
		std::unordered_map<std::string, std::vector<std::string>> param_to_aliases_map;
		std::unordered_map<std::string, std::string> parameter_descriptions;
		std::vector<std::string> unnamed_arguments;
		std::string program_name;
		std::optional<std::string> program_desc;
	};
}

#endif

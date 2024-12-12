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
		/*
		* @brief Names reserved by the ArgParser which may not be used to name/alias parameters as they have predefined responses.
		*        `"--help" | "-h"`: Outputs help information based on the parser's current context to the provided output stream (NOT the error stream).
		*/
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
		enum class AccessPresenceFlag : std::uint16_t
		{
			Unknown          = 0x00,
			BaseParam        = 0x01,
			Alias            = 0x02,
			BaseParamOrAlias = 0x04 | BaseParam | Alias,
			AliasOrBaseParam = 0x08 | BaseParam | Alias
		};

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

		/*
		* @brief Shorthand for `Get(const std::string&)`.
		*        See said function for a clearer description on how the access works.
		* @returns Constant reference to the parameter referenced by the input `name_or_alias`.
		*/
		template<AccessPresenceFlag PresenceFlag = AccessPresenceFlag::Unknown>
		[[nodiscard]] const EmuIO::Parameter& operator[](const std::string& name_or_alias) const
		{
			if constexpr (PresenceFlag == AccessPresenceFlag::Unknown)
			{
				const EmuIO::Parameter* param{ nullptr };
				if (!TryGet(name_or_alias, &param))
				{
					throw _make_exception<std::out_of_range>("Attempted to retrieve a parameter whose name does not exist, even as an alias (", name_or_alias, ')');
				}
				return *param;
			}
			else if constexpr (PresenceFlag == AccessPresenceFlag::BaseParam)
			{
				return parameters.at(name_or_alias);
			}
			else if constexpr (PresenceFlag == AccessPresenceFlag::Alias)
			{
				return parameters.at(alias_to_param_map.at(name_or_alias));
			}
			else if constexpr (PresenceFlag == AccessPresenceFlag::BaseParamOrAlias)
			{
				auto it{ parameters.find(name_or_alias) };
				return (it != parameters.end()) ? it->second : parameters.at(alias_to_param_map.at(name_or_alias));
			}
			else if constexpr (PresenceFlag == AccessPresenceFlag::AliasOrBaseParam)
			{
				auto it{ alias_to_param_map.find(name_or_alias) };
				return (it != alias_to_param_map.end()) ? parameters.at(it->second) : parameters.at(name_or_alias);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<PresenceFlag>(), "Invalid `PresenceFlag` passed to access a parameter inside of an arg parser.");
				throw _make_exception<std::out_of_range>("Invalid `PresenceFlag`"); // Never called due to static_assert
			}
		}

		/*
		* @brief Returns a constant reference to the parameter with the given name or alias.
		* @param name_or_alias Name (or alias) of the parameter to retrieve.
		* @param PresenceFlag Access hint which can be used to optimise the access with guarantees from the caller.
		*                     This must not be changed from `Unknown` unless you can fully guarantee that the input exists as a name or alias.
		*					  Possible values include:
		*                     - `Unknown` (default): No guarantees; the parser will safely throw an exception if the input name or alias does not exist.
		*                     - `BaseParam`: The input `name_or_alias` is guaranteed to be the exact name used by a registered parameter; NOT an alias.
		*                     - `Alias`: The input `name_or_alias` is guaranteed to be an exact alias for a registered parameter; NOT the base name of a parameter.
		*                     - `BaseParamOrAlias`: The input `name_or_alias` is guaranteed to be the exact name or alias used by a registered parameter; could be either, but most likely the base param name.
		*                     - `AliasOrBaseParam`: The input `name_or_alias` is guaranteed to be the exact name or alias used by a registered parameter; could be either, but most likely an alias
		*                     NOTE: `BaseParamOrAlias` and `AliasOrBaseParam` are functionally identical, but may implement optimisations to target access for the more-likely option first.
		*                           There is no necessary advantage to choosing one over the other if it is unknown which is more likely.
		* @returns Constant reference to the parameter referenced by the input `name_or_alias`.
		*/
		template<AccessPresenceFlag PresenceFlag = AccessPresenceFlag::Unknown>
		[[nodiscard]] const EmuIO::Parameter& Get(const std::string& name_or_alias) const
		{
			return this->operator[]<PresenceFlag>(name_or_alias);
		}

		/*
		* @brief Tries to retrieve a parameter by the given name or alias, outputting a constant pointer to it at the pointer pointed to by `out_param`.
		* @param name_or_alias Name or alias of the parameter to try and retrieve.
		* @param out_param Pointer to a constant Parameter pointer which will be output to if the target parameter is found.
		*                  This will not be modified if the target parameter is not found; test the return value of this function to determine success.
		* @returns `true` if the target parameter was found and the output pointer written to; otherwise `false`.
		*/
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

		// Register basic parameter
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

		template<EmuIO::ParameterType Type, class DefaultValue, EmuConcepts::CanExplicitlyConstruct<std::string>...Aliases>
		requires((Type & EmuIO::ParameterType::Enum) == EmuIO::ParameterType{} && !EmuConcepts::UnqualifiedMatch<DefaultValue, std::monostate> && sizeof...(Aliases) != 0)
		void RegisterParameter(std::string name, std::string desc, DefaultValue&& default_value, Aliases&&...aliases)
		{
			RegisterParameter<Type>(name, std::move(desc), std::forward<DefaultValue>(default_value));
			AddAliases(std::move(name), std::forward<Aliases>(aliases)...);
		}

		// Register basic array parameter defaulting to empty
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

		template<EmuIO::ParameterType Type, EmuConcepts::CanExplicitlyConstruct<std::string>...Aliases>
		requires((Type & EmuIO::ParameterType::Enum) == EmuIO::ParameterType{} && (Type & EmuIO::ParameterType::Array) == EmuIO::ParameterType::Array && sizeof...(Aliases) != 0)
		void RegisterParameter(std::string name, std::string desc, std::monostate default_as_empty_array, Aliases&&...aliases)
		{
			RegisterParameter<Type>(name, std::move(desc), std::move(default_as_empty_array));
			AddAliases(std::move(name), std::forward<Aliases>(aliases)...);
		}

		// Register basic parameter with `Type` enum determined by the input `ParamType`
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

		template<class ParamType, class DefaultValue, EmuConcepts::CanExplicitlyConstruct<std::string>...Aliases>
		requires(!EmuConcepts::UnqualifiedMatch<DefaultValue, std::monostate> && sizeof...(Aliases) != 0)
		void RegisterParameter(std::string name, std::string desc, DefaultValue&& default_value, Aliases&&...aliases)
		{
			RegisterParameter<EmuIO::type_to_parameter_type_enum<ParamType>()>
			(
				name,
				std::move(desc),
				std::forward<DefaultValue>(default_value)
			);
			AddAliases(std::move(name), std::forward<Aliases>(aliases)...);
		}

		// Register basic array parameter with `Type` enum determined by the input `ParamType` defaulting to empty
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

		template<class ParamType, EmuConcepts::CanExplicitlyConstruct<std::string>...Aliases>
		requires(std::is_array_v<typename std::remove_cvref<ParamType>::type>)
		void RegisterParameter(std::string name, std::string desc, std::monostate default_as_empty_array, Aliases&&...aliases)
		{
			RegisterParameter<EmuIO::type_to_parameter_type_enum<ParamType>()>
			(
				name,
				std::move(desc),
				std::move(default_as_empty_array)
			);
			AddAliases(std::move(name), std::forward<Aliases>(aliases)...);
		}

		// Register enum parameter with info types
		template<ParameterType Type, EmuConcepts::CanExplicitlyConstruct<typename EmuIO::parameter_enum_builder_arg<Type | ParameterType::Enum>::type>...EnumInfos>
		requires(sizeof...(EnumInfos) != 0)
		void RegisterEnumParameter(std::string name, std::string desc, std::string default_enum, EnumInfos&&...enum_infos)
		{
			_throw_if_invalid_new_name(name);

			param_to_aliases_map.emplace(std::make_pair(name, std::vector<std::string>{}));
			parameter_descriptions.emplace(std::make_pair(name, std::move(desc)));
			parameters.emplace(std::make_pair
			(
				std::move(name),
				EmuIO::Parameter::make<Type | ParameterType::Enum>(std::move(default_enum), std::forward<EnumInfos>(enum_infos)...)
			));
		}

		// Register enum array parameter with info types, defaulting to empty array
		template<ParameterType Type, EmuConcepts::CanExplicitlyConstruct<typename EmuIO::parameter_enum_builder_arg<Type | ParameterType::Enum>::type>...EnumInfos>
		requires(sizeof...(EnumInfos) != 0 && (Type & ParameterType::Array) == ParameterType::Array)
		void RegisterEnumParameter(std::string name, std::string desc, std::monostate default_empty_array, EnumInfos&&...enum_infos)
		{
			_throw_if_invalid_new_name(name);

			param_to_aliases_map.emplace(std::make_pair(name, std::vector<std::string>{}));
			parameter_descriptions.emplace(std::make_pair(name, std::move(desc)));
			parameters.emplace(std::make_pair
			(
				std::move(name),
				EmuIO::Parameter::make<Type | ParameterType::Enum>(std::move(default_empty_array), std::forward<EnumInfos>(enum_infos)...)
			));
		}

		// Register enum parameter with inline arguments to form info pairs - only used for non-string-valued enums
		template<ParameterType Type, class...NameValueArgSequenceForEnumInfos>
		requires((Type & ParameterType::String) != ParameterType::String && valid_scalar_args_for_enum_builder_arg<Type | ParameterType::Enum, NameValueArgSequenceForEnumInfos...>::value)
		void RegisterEnumParameter(std::string name, std::string desc, std::string default_enum, NameValueArgSequenceForEnumInfos&&...enum_infos_name_value_sequence)
		{
			_throw_if_invalid_new_name(name);

			param_to_aliases_map.emplace(std::make_pair(name, std::vector<std::string>{}));
			parameter_descriptions.emplace(std::make_pair(name, std::move(desc)));
			parameters.emplace(std::make_pair
			(
				std::move(name),
				EmuIO::Parameter::make<Type | ParameterType::Enum>(std::move(default_enum), std::forward<NameValueArgSequenceForEnumInfos>(enum_infos_name_value_sequence)...)
			));
		}

		// Register enum array parameter with inline arguments to form info pairs, defaulting to empty array - only used for non-string-valued enums
		template<ParameterType Type, class...NameValueArgSequenceForEnumInfos>
		requires((Type & ParameterType::String) != ParameterType::String && (Type & ParameterType::Array) == ParameterType::Array && valid_scalar_args_for_enum_builder_arg<Type | ParameterType::Enum, NameValueArgSequenceForEnumInfos...>::value)
		void RegisterEnumParameter(std::string name, std::string desc, std::monostate default_empty_array, NameValueArgSequenceForEnumInfos&&...enum_infos_name_value_sequence)
		{
			_throw_if_invalid_new_name(name);

			param_to_aliases_map.emplace(std::make_pair(name, std::vector<std::string>{}));
			parameter_descriptions.emplace(std::make_pair(name, std::move(desc)));
			parameters.emplace(std::make_pair
			(
				std::move(name),
				EmuIO::Parameter::make<Type | ParameterType::Enum>(std::move(default_empty_array), std::forward<NameValueArgSequenceForEnumInfos>(enum_infos_name_value_sequence)...)
			));
		}

		// Register enum parameter with info types
		// --- Additionally determines `Type` enum from the input `ParamType`
		template<class ParamType, EmuConcepts::CanExplicitlyConstruct<typename EmuIO::parameter_enum_builder_arg<EmuIO::type_to_parameter_type_enum<ParamType>() | ParameterType::Enum>::type>...EnumInfos>
		requires(sizeof...(EnumInfos) != 0)
		void RegisterEnumParameter(std::string name, std::string desc, std::string default_enum, EnumInfos&&...enum_infos)
		{
			RegisterEnumParameter<EmuIO::type_to_parameter_type_enum<ParamType>()>
			(
				std::move(name),
				std::move(desc),
				std::move(default_enum),
				std::forward<EnumInfos>(enum_infos)...
			);
		}

		// Register enum array parameter with info types, defaulting to empty array
		// --- Additionally determines `Type` enum from the input `ParamType`
		template<class ParamType, EmuConcepts::CanExplicitlyConstruct<typename EmuIO::parameter_enum_builder_arg<EmuIO::type_to_parameter_type_enum<ParamType>() | ParameterType::Enum>::type>...EnumInfos>
		requires(sizeof...(EnumInfos) != 0 && std::is_array_v<ParamType>)
		void RegisterEnumParameter(std::string name, std::string desc, std::monostate default_empty_array, EnumInfos&&...enum_infos)
		{
			RegisterEnumParameter<EmuIO::type_to_parameter_type_enum<ParamType>()>
			(
				std::move(name),
				std::move(desc),
				std::move(default_empty_array),
				std::forward<EnumInfos>(enum_infos)...
			);
		}

		// Register enum parameter with inline arguments to form info pairs - only used for non-string-valued enums
		// --- Additionally determines `Type` enum from the input `ParamType`
		template<class ParamType, class...NameValueArgSequenceForEnumInfos>
		requires((EmuIO::type_to_parameter_type_enum<ParamType>() & ParameterType::String) != ParameterType::String && valid_scalar_args_for_enum_builder_arg<EmuIO::type_to_parameter_type_enum<ParamType>() | ParameterType::Enum, NameValueArgSequenceForEnumInfos...>::value)
		void RegisterEnumParameter(std::string name, std::string desc, std::string default_enum, NameValueArgSequenceForEnumInfos&&...enum_infos_name_value_sequence)
		{
			RegisterEnumParameter<EmuIO::type_to_parameter_type_enum<ParamType>()>
			(
				std::move(name),
				std::move(desc),
				std::move(default_enum),
				std::forward<NameValueArgSequenceForEnumInfos>(enum_infos_name_value_sequence)...
			);
		}

		// Register enum array parameter with inline arguments to form info pairs, defaulting to empty array - only used for non-string-valued enums
		// --- Additionally determines `Type` enum from the input `ParamType`
		template<class ParamType, class...NameValueArgSequenceForEnumInfos>
		requires((EmuIO::type_to_parameter_type_enum<ParamType>() & ParameterType::String) != ParameterType::String && std::is_array_v<ParamType> && valid_scalar_args_for_enum_builder_arg<EmuIO::type_to_parameter_type_enum<ParamType>() | ParameterType::Enum, NameValueArgSequenceForEnumInfos...>::value)
		void RegisterEnumParameter(std::string name, std::string desc, std::monostate default_empty_array, NameValueArgSequenceForEnumInfos&&...enum_infos_name_value_sequence)
		{
			RegisterEnumParameter<EmuIO::type_to_parameter_type_enum<ParamType>()>
			(
				std::move(name),
				std::move(desc),
				std::move(default_empty_array),
				std::forward<NameValueArgSequenceForEnumInfos>(enum_infos_name_value_sequence)...
			);
		}

		/*
		* @param Adds an alias for the parameter registered with the given `name`.
		*        Said parameter may be referenced with `alias` after this call, both in-program and by an end-user.
		*        For example, for a `--config` command, you can pass an alias `-c` to give the end-user a shorthand `-c` to refer to that parameter in the command line.
		* @param name Registered name of the parameter to reference. Must not be an alias to said parameter.
		* @param alias New alias for the target parameter.
		*              Must follow the usual naming rules of parameters.
		*              Cannot conflict with any other names or aliases.
		*/
		void AddAlias(const std::string& name, std::string alias)
		{
			_throw_if_invalid_new_name(alias);
			alias_to_param_map.emplace(std::make_pair(alias, name));
			param_to_aliases_map[name].emplace_back(std::move(alias));
		}

		/*
		* @param Adds 1 or more alias for the parameter registered with the given `name`.
		*        Said parameter may be referenced with any of the input aliases after this call, both in-program and by an end-user.
		*        For example, for a `--config` command, you can pass an alias `-c` to give the end-user a shorthand `-c` to refer to that parameter in the command line.
		* @param name Registered name of the parameter to reference. Must not be an alias to said parameter.
		* @param aliases 1 or more values which each represent a new alias for the target parameter.
		*                Must follow the usual naming rules of parameters.
		*                Cannot conflict with any other names or aliases.
		*                May be any type, but each input type must be valid for explicitly constructing a `std::string` with curly-brace syntax.
		*/
		template<EmuConcepts::CanExplicitlyConstruct<std::string>...AliasStrings>
		requires(sizeof...(AliasStrings) >= 1)
		void AddAliases(const std::string& name, AliasStrings&&...aliases)
		{
			((AddAlias(name, std::string{ std::forward<AliasStrings>(aliases) })), ...);
		}

		/*
		* @brief Checks if the input string exists as either a registered parameter name or an alias to a parameter.
		* @param name_or_alias Name or alias to search for.
		* @returns `true` if `name_or_alias` exists as a parameter (or an alias to one) in this parser; otherwise `false`.
		*/
		[[nodiscard]] bool ContainsNameOrAlias(const std::string& name_or_alias) const
		{
			return parameters.contains(name_or_alias) || alias_to_param_map.contains(name_or_alias);
		}

		/*
		* @brief Appends help information regarding this program and its registered parameters to the input `str`.
		* @param str Any type which can have information appended to it as per a `std::ostream`.
		*            This is a templatised type to support input of wrappers around `std::ostream` instances.
		* @param separator Separator to split sections of the output help.
		*                  Defaults to `ArgParser::default_help_separator`.
		*                  Will always be immediately followed by `std::endl`.
		*/
		template<class Str>
		void Help(Str&& str, std::string_view separator = default_help_separator) const
		{
			str << separator << std::endl;
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

				name_param_pair.second->AppendToStream<true, false, true, false, true>(str) << '\n';
				if (name_param_pair.second->IsConst())
				{
					str << "Can only be set once (excluding the default value).\n";
				}
				else if (name_param_pair.second->IsArray())
				{
					str << "Can be set multiple times, adding each new value to the back of an expanding array (the default array will be cleared when adding the first custom value).\n";
				}
				else
				{
					str << "Can be set multiple times, with the most-recently set value being the used value (which overwrites the previous).\n";
				}
				if (name_param_pair.second->IsArray())
				{
					str << "\tCan set multiple values in one argument by passing in the format \"[arg0, arg1, arg2, ..., argN]\".\n";
					if (name_param_pair.second->IsConst())
					{
						str << "\tThis is the only way to provide input for a constant array with size > 1.\n";
					}
				}
				str << separator << std::endl;
			}
		}

		/*
		* @brief Parses the input command line arguments `argv[0:argc]` under the constraints of this parser's current context.
		*        Outputs information via the provided streams.
		*        Certain arguments will trigger predefined responses. See `ArgParser::reserved_names` for information on these responses.
		* @param argc Number of command line arguments. Expected to be `argc` as passed to `main`.
		* @param argv Array of C-strings representing individual command line arguments. Expected to be `argv` as passed to `main`.
		* @param out_stream Stream to output general info to (e.g. help if the `argv` contains `--help` or `-h`).
		* @param err_stream Stream to output errors to (e.g. invalid arguments).
		* @param ReturnOnError If `true`, parsing will be cancelled and this function will return immediately as soon as an error is encountered and logged to `err_stream`.
		*                      If `false`, parsing will skip to the next argument if an invalid argument is detected.
		* @returns The total number of errors encountered during parsing.
		*          `0` indicates a total success in parsing.
		*/
		template<bool ReturnOnError, class OutStream, class ErrStream>
		std::size_t Parse(int argc, const char** argv, OutStream&& out_stream, ErrStream&& err_stream)
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
							Help(std::forward<OutStream>(out_stream));
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

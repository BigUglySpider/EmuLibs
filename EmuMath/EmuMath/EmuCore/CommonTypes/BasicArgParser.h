#ifndef EMU_CORE_BASIC_ARG_PARSER_H_INC_
#define EMU_CORE_BASIC_ARG_PARSER_H_INC_ 1

#include "../CommonConcepts/Arithmetic.h"
#include "../CommonConcepts/CommonRequirements.h"
#include "../Functors/Convertors.h"
#include "../TMPHelpers/OperatorChecks.h"
#include "../TMPHelpers/TypeComparators.h"
#include "../TMPHelpers/TypeConvertors.h"
#include "../TMPHelpers/Values.h"

#include <deque>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

namespace EmuCore
{
	namespace TMP
	{
		template<class T_>
		struct is_emu_basic_arg_parser_supported_string
		{
			static constexpr bool value = EmuCore::TMP::is_instance_of_typeparams_only_v<T_, std::basic_string>;
		};
	}

	template<class StringType_>
	requires(EmuCore::TMP::is_emu_basic_arg_parser_supported_string<StringType_>::value)
	struct BasicArgParser
	{
	public:
		/// <summary> String type used by this parser. Same as the template argument type, but with ref/constant/volatile qualification removed. </summary>
		using string_type = typename std::remove_cvref<StringType_>::type;
		/// <summary> Character type used by this parser's `string_type`. </summary>
		using char_type = string_type::value_type;
		using config_args_map_type = std::map<string_type, string_type>;
		using switch_to_full_name_map_type = std::map<char_type, string_type>;

#pragma region PRIVATE_STATIC_HELPER_TYPES
	private:
		template<class ArgsCollection_>
		struct _is_compatible_args_collection
		{
		private:
			[[nodiscard]] static constexpr inline bool _get()
			{
				if constexpr (std::is_same_v<ArgsCollection_, typename std::remove_cvref<ArgsCollection_>::type>)
				{
					return false;
				}
				else
				{
					return _is_compatible_args_collection<typename std::remove_cvref<ArgsCollection_>::type>::value;
				}
			}

		public:
			static constexpr bool value = _get();
		};

		template<class ArrayValue_, std::size_t ArraySize_>
		struct _is_compatible_args_collection<std::array<ArrayValue_, ArraySize_>>
		{
			static constexpr bool value = std::is_constructible_v<string_type, ArrayValue_>;
		};

		template<class VectorValue_, class Allocator_>
		struct _is_compatible_args_collection<std::vector<VectorValue_, Allocator_>>
		{
			static constexpr bool value = std::is_constructible_v<string_type, VectorValue_>;
		};

		template<class DequeValue_, class Allocator_>
		struct _is_compatible_args_collection<std::deque<DequeValue_, Allocator_>>
		{
			static constexpr bool value = std::is_constructible_v<string_type, DequeValue_>;
		};
#pragma endregion

#pragma region PUBLIC_STATIC_HELPERS
	public:
		/// <summary>
		/// <para> Returns the default value ("true") used when arguments are not provided anything other than their name. </para>
		/// <para> Provides support to construct any of the built-in character type strings directly as that type of string. </para>
		/// <para> If the character type of the string is not `char`, `unsigned char`, `signed char`, `char8_t`, `char16_t`, `char32_t` or `wchar_t`, `string_type` must be constructible with an argument of `"true"`. </para>
		/// <para> Note that if you fall back to the final use of this string, it is likely to output garbage if the target string's encoding does not match up with ASCII's a-z range (or at least, those characters used to spell true). </para>
		/// </summary>
		/// <returns>String "true" as this parser's `string_type`, which is used by default if a custom value is not provided for arguments that are only provided as names with no matching value argument.</returns>
		static inline string_type make_default_value_if_name_only()
		{
			using _char_type_uq = typename std::remove_cvref<char_type>::type;
			if constexpr (EmuCore::TMP::is_any_comparison_true<std::is_same, _char_type_uq, char, unsigned char, signed char>::value)
			{
				return string_type("true");
			}
			else if constexpr (std::is_same_v<_char_type_uq, char8_t>)
			{
				return string_type(u8"true");
			}
			else if constexpr (std::is_same_v<_char_type_uq, char16_t>)
			{
				return string_type(u"true");
			}
			else if constexpr (std::is_same_v<_char_type_uq, char32_t>)
			{
				return string_type(U"true");
			}
			else if constexpr (std::is_same_v<_char_type_uq, wchar_t>)
			{
				return string_type(L"true");
			}
			else
			{
				if constexpr (std::is_constructible_v<string_type, decltype("true")>)
				{
					return string_type("true");
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<_char_type_uq>(),
						"Unable to create default value-if-name-only for a BasicStringParser as its `char_type` is not recognised as a supported type to safely form a literal. Supported types for this are: `char`, 'unsigned char', 'signed char', `char8_t`, `char16_t`, `char32_t`, and their unsigned variants. Alternatively, the string_type may be anything constructible via \"true\"."
					);
				}
			}
		}

		/// <summary>
		/// <para> Converts `argc` and `argv` into a more concise vector. </para>
		/// <para> If `Stringify_` is true: `argv` occurrences will be translated into this item's `string_type`. </para>
		/// <para> If `Stringify_` is false: `argv` occurrences will not be translated, and the output vector will simply contain each individual `char*` within `argv`. </para>
		/// </summary>
		/// <param name="argc">Number of arguments passed.</param>
		/// <param name="argv">Array of C-string arguments.</param>
		/// <returns>Input command-line (-style) arguments converted into a vector, with stringification if `Stringify_` is true.</returns>
		template<bool Stringify_>
		static inline auto make_vector_from_main_args(int argc, char** argv)
			-> typename std::conditional<Stringify_, std::vector<string_type>, std::vector<char*>>::type
		{
			std::vector<typename std::conditional<Stringify_, string_type, char*>::type> args_vector;
			const std::size_t argc_as_size = static_cast<std::size_t>(argc);
			args_vector.reserve(argc_as_size);
			for (std::size_t i = 0; i < argc_as_size; ++i)
			{
				if constexpr (Stringify_)
				{
					args_vector.emplace_back(string_type{ argv[i] });
				}
				else
				{
					args_vector.emplace_back(argv[i]);
				}
			}
			return args_vector;
		}

		/// <summary>
		/// <para> Returns true if the passed type is compatible to be used as an arguments collection when using this parser's parsing utilities. </para>
		/// <para> In general, requires that the collection contains types that may be used to construct this parser's `string_type`. </para>
		/// </summary>
		/// <returns>True if `ArgsCollection_` is compatible with this parser's parsing utilities; otherwise false.</returns>
		template<class ArgsCollection_>
		[[nodiscard]] static constexpr inline bool is_compatible_args_collection()
		{
			return _is_compatible_args_collection<ArgsCollection_>::value;
		}
#pragma endregion

#pragma region CONSTRUCTORS
	public:
		/// <summary>
		/// <para> Constructs an empty BasicArgParser. </para>
		/// </summary>
		inline BasicArgParser() : 
			all_parsed_args(),
			default_config_args(),
			parsed_config_args(),
			parsed_non_config_args(),
			switch_to_full_name_map()
		{
		}

		/// <summary>
		/// <para> Constructs a BasicArgParser from the passed command-line (-style) arguments, with everything else set to its default state. </para>
		/// <para> The passed arguments will be parsed immediately upon construction as if calling ParseConfigArgs, with replacement allowed. </para>
		/// </summary>
		/// <param name="argc">Number of arguments passed.</param>
		/// <param name="argv">Array of C-string arguments.</param>
		inline BasicArgParser(int argc, char** argv) : 
			BasicArgParser(make_vector_from_main_args<false>(argc, argv))
		{
		}

		/// <summary>
		/// <para> Constructs a BasicArgParser from the passed command-line (-style) arguments, providing it a custom map of default arguments and a custom map of switch-to-full-name translations. </para>
		/// <para> The passed arguments will be parsed immediately upon construction as if calling ParseConfigArgs, with replacement allowed. </para>
		/// </summary>
		/// <param name="argc">Number of arguments passed.</param>
		/// <param name="argv">Array of C-string arguments.</param>
		/// <param name="config_name_only_value_">String value to apply to items if they are provided as a config argument but not given any value. For example, "true" for boolean switches.</param>
		/// <param name="default_config_args_">
		///		Default arguments applied to config options. These will be fallen back to when querying this parser if the argument has not been parsed. 
		///		Must be of this parser's `config_args_map_type` type, but may have any qualification and reference status.
		/// </param>
		/// <param name="switch_to_full_name_map_">
		///		Translations from single-character switches to full name arguments, used for translating character siwtches to their full names when querying this parser with switches or asking for translations. 
		///		Must be of this parser's `switch_to_full_name_map_type` type, but may have any qualification and reference status.
		/// </param>
		template<EmuConcepts::UnqualifiedMatch<config_args_map_type> DefaultConfigArgs_, EmuConcepts::UnqualifiedMatch<switch_to_full_name_map_type> SwitchToFullNameMap_>
		inline BasicArgParser(int argc, char** argv, string_type config_name_only_value_, DefaultConfigArgs_&& default_config_args_, SwitchToFullNameMap_&& switch_to_full_name_map_) :
			BasicArgParser
			(
				make_vector_from_main_args<false>(argc, argv),
				make_default_value_if_name_only(),
				std::forward<DefaultConfigArgs_>(default_config_args_),
				std::forward<SwitchToFullNameMap_>(switch_to_full_name_map_)
			)
		{
		}

		/// <summary>
		/// <para> Constructs a BasicArgParser from the passed collection of arguments, with everything else set to its default state. </para>
		/// <para> The passed arguments will be parsed immediately upon construction as if calling ParseConfigArgs, with replacement allowed. </para>
		/// </summary>
		/// <param name="args_collection_">
		///		Collection of arguments to be parsed. Can be any collection type, as long as it returns true from `is_compatible_args_collection`, 
		///		which generally requires a collection which contains a type that is the same as (or can be used to construct) this parser's `string_type`.
		/// </param>
		template<class ArgsCollection_>
		requires((is_compatible_args_collection<ArgsCollection_>()))
		inline BasicArgParser(ArgsCollection_&& args_collection_) :
			BasicArgParser(std::forward<ArgsCollection_>(args_collection_), make_default_value_if_name_only(), config_args_map_type(), switch_to_full_name_map_type())
		{
		}

		/// <summary>
		/// <para> Constructs a BasicArgParser from the passed collection of arguments, providing it a custom map of default arguments and a custom map of switch-to-full-name translations. </para>
		/// <para> The passed arguments will be parsed immediately upon construction as if calling ParseConfigArgs, with replacement allowed. </para>
		/// </summary>
		/// <param name="args_collection_">
		///		Collection of arguments to be parsed. Can be any collection type, as long as it returns true from `is_compatible_args_collection`, 
		///		which generally requires a collection which contains a type that is the same as (or can be used to construct) this parser's `string_type`.
		/// </param>
		/// <param name="config_name_only_value_">String value to apply to items if they are provided as a config argument but not given any value. For example, "true" for boolean switches.</param>
		/// <param name="default_config_args_">
		///		Default arguments applied to config options. These will be fallen back to when querying this parser if the argument has not been parsed. 
		///		Must be of this parser's `config_args_map_type` type, but may have any qualification and reference status.
		/// </param>
		/// <param name="switch_to_full_name_map_">
		///		Translations from single-character switches to full name arguments, used for translating character siwtches to their full names when querying this parser with switches or asking for translations. 
		///		Must be of this parser's `switch_to_full_name_map_type` type, but may have any qualification and reference status.
		/// </param>
		template<class ArgsCollection_, EmuConcepts::UnqualifiedMatch<config_args_map_type> DefaultConfigArgsMap_, EmuConcepts::UnqualifiedMatch<switch_to_full_name_map_type> SwitchToFullNameMap_>
		requires((is_compatible_args_collection<ArgsCollection_>()))
		BasicArgParser
		(
			ArgsCollection_&& args_collection_,
			const string_type& config_name_only_value_,
			DefaultConfigArgsMap_&& default_config_args_,
			SwitchToFullNameMap_&& switch_to_full_name_map_
		) : default_config_args(std::forward<DefaultConfigArgsMap_>(default_config_args_)),
			switch_to_full_name_map(std::forward<SwitchToFullNameMap_>(switch_to_full_name_map_)),
			all_parsed_args(),
			parsed_config_args(),
			parsed_non_config_args()
		{
			constexpr bool can_replace_repeated_args = true;
			ParseConfigArgs<can_replace_repeated_args>(std::forward<ArgsCollection_>(args_collection_), config_name_only_value_);
		}
#pragma endregion

#pragma region PARSING_FUNCS
		template<bool CanReplace_>
		inline void ParseConfigArgs(int argc, char** argv)
		{
			ParseConfigArgs<CanReplace_>(make_vector_from_main_args<false>(argc, argv), make_default_value_if_name_only());
		}

		template<bool CanReplace_>
		inline void ParseConfigArgs(int argc, char** argv, const string_type& config_name_only_value_)
		{
			ParseConfigArgs<CanReplace_>(make_vector_from_main_args<false>(argc, argv), config_name_only_value_);
		}

		template<bool CanReplace_, class ArgsCollection_>
		inline void ParseConfigArgs(ArgsCollection_&& args_collection_)
		{
			ParseConfigArgs<CanReplace_>(std::forward<ArgsCollection_>(args_collection_), make_default_value_if_name_only());
		}

		template<bool CanReplace_, class ArgsCollection_>
		void ParseConfigArgs(ArgsCollection_&& args_collection_, const string_type& config_name_only_value_)
		{
			constexpr bool can_move = !std::is_lvalue_reference_v<ArgsCollection_>;
			auto& args_collection_ref = EmuCore::TMP::lval_ref_cast<ArgsCollection_>(std::forward<ArgsCollection_>(args_collection_));
			bool is_full_name_config_arg = false;
			bool is_switch_config_arg = false;
			auto current_config_arg_name = string_type();
			const std::size_t input_arg_count = _get_args_collection_size(args_collection_ref);
			for (std::size_t i = 0; i < input_arg_count; ++i)
			{
				string_type arg_string = string_type(_get_arg_from_collection<can_move>(args_collection_ref, i));
				all_parsed_args.emplace_back(arg_string);
				if (is_full_name_config_arg)
				{
					if (arg_string.size() == 0)
					{
						// Empty argument, so just set to the default and move on
						this->SetConfigValue<CanReplace_>(std::move(current_config_arg_name), config_name_only_value_);
					}
					else if (_is_likely_config_name_string<true>(arg_string))
					{
						// We've moved on to a different config argument, so set the previous to the default and then determine what we're working with for next iteration
						this->SetConfigValue<CanReplace_>(std::move(current_config_arg_name), config_name_only_value_);
						EMU_CORE_PUSH_WARNING_STACK
						EMU_CORE_MSVC_DISABLE_WARNING(26800)
						if (this->_determine_config_arg_type(arg_string, current_config_arg_name, is_switch_config_arg, is_full_name_config_arg))
						{
							this->_set_config_args_if_no_more_input<CanReplace_>(i, input_arg_count, is_switch_config_arg, is_full_name_config_arg, current_config_arg_name, config_name_only_value_);
						}
						EMU_CORE_POP_WARNING_STACK
					}
					else
					{
						this->SetConfigValue<CanReplace_>(std::move(current_config_arg_name), std::move(arg_string));
						is_full_name_config_arg = false;
					}
				}
				else if(is_switch_config_arg)
				{
					if (arg_string.size() == 0)
					{
						// Empty argument, so just set to the default and move on
						this->SetMultipleSwitchValues<CanReplace_>(current_config_arg_name, config_name_only_value_);
					}
					else if (_is_likely_config_name_string<true>(arg_string))
					{
						// We've moved on to a different config argument, so set the previous to the default and then determine what we're working with for next iteration
						this->SetMultipleSwitchValues<CanReplace_>(current_config_arg_name, config_name_only_value_);
						if (this->_determine_config_arg_type(arg_string, current_config_arg_name, is_switch_config_arg, is_full_name_config_arg))
						{
							this->_set_config_args_if_no_more_input<CanReplace_>(i, input_arg_count, is_switch_config_arg, is_full_name_config_arg, current_config_arg_name, config_name_only_value_);
						}
					}
					else
					{
						this->SetMultipleSwitchValues<CanReplace_>(current_config_arg_name, arg_string);
						is_switch_config_arg = false;
					}
				}
				else
				{
					if (arg_string.size() == 0)
					{
						// Random empty spot considered an arg for some reason; skip
						continue;
					}
					else if (_is_likely_config_name_string<false>(arg_string))
					{
						this->_determine_config_arg_type(arg_string, current_config_arg_name, is_switch_config_arg, is_full_name_config_arg);
						this->_set_config_args_if_no_more_input<CanReplace_>(i, input_arg_count, is_switch_config_arg, is_full_name_config_arg, current_config_arg_name, config_name_only_value_);
					}
					else
					{
						parsed_non_config_args.push_back(&(this->all_parsed_args.back()));
					}
				}
			}
		}
#pragma endregion

#pragma region ACCESS_OPERATORS
		/// <summary>
		/// <para> Shorthand for `GetConfigArg` with the same arguments. </para>
		/// </summary>
		[[nodiscard]] inline const string_type& operator[](const string_type& config_name_) const
		{
			return GetConfigArg(config_name_);
		}

		/// <summary>
		/// <para> Shorthand for `GetConfigArg` with the same arguments. </para>
		/// </summary>
		[[nodiscard]] inline const string_type& operator[](const char_type& config_switch_char_) const
		{
			return GetConfigArg(config_switch_char_);
		}

		/// <summary>
		/// <para> Shorthand for `TryGetConfigArg` with the same arguments. </para>
		/// </summary>
		[[nodiscard]] inline bool operator()(const string_type& config_name_, const string_type** pp_out_string_) const
		{
			return TryGetConfigArg(config_name_, pp_out_string_);
		}

		/// <summary>
		/// <para> Shorthand for `TryGetConfigArg` with the same arguments. </para>
		/// </summary>
		[[nodiscard]] inline bool operator()(const char_type& config_switch_char_, const string_type** pp_out_string_) const
		{
			return TryGetConfigArg(config_switch_char_, pp_out_string_);
		}

		/// <summary>
		/// <para> Shorthand for `TryGetConfigArg` with the same arguments. </para>
		/// </summary>
		[[nodiscard]] inline bool operator()(const string_type& config_name_, std::reference_wrapper<const string_type>& out_string_) const
		{
			return TryGetConfigArg(config_name_, out_string_);
		}

		/// <summary>
		/// <para> Shorthand for `TryGetConfigArg` with the same arguments. </para>
		/// </summary>
		[[nodiscard]] inline bool operator()(const char_type& config_switch_char_, std::reference_wrapper<const string_type>& out_string_) const
		{
			return TryGetConfigArg(config_switch_char_, out_string_);
		}

		/// <summary>
		/// <para> Shorthand for `TryGetConfigArg` with the same arguments. </para>
		/// </summary>
		[[nodiscard]] inline bool operator()(const string_type& config_name_, string_type& out_string_) const
		{
			return TryGetConfigArg(config_name_, out_string_);
		}

		/// <summary>
		/// <para> Shorthand for `TryGetConfigArg` with the same arguments. </para>
		/// </summary>
		[[nodiscard]] inline bool operator()(const char_type& config_switch_char_, string_type& out_string_) const
		{
			return TryGetConfigArg(config_switch_char_, out_string_);
		}
#pragma endregion

#pragma region EXCEPTING_ACCESS_FUNCS
		/// <summary>
		/// <para> Retrieves a constant reference to the value of the specified config argument. </para>
		/// <para> If the passed argument has not been parsed, this will return the argument's default value. </para>
		/// <para> If the passed argument has not been parsed and there is no default value for it, this will throw a standard out_of_range exception. </para>
		/// <para> 
		///		If `CanViewSingleCharStringAsSwitch_` is true, this will convert a single-character string to a switch and translate it if possible before throwing an exception. 
		///		This conversion will only be performed after all other avenues have failed to find a result.
		/// </para>
		/// <para> By default, `CanViewSingleCharStringAsSwitch_` is `false`. </para>
		/// </summary>
		/// <param name="config_name_">Full name of the config argument to retrieve the value of.</param>
		/// <returns>Constant reference to the value for the specified config argument.</returns>
		template<bool CanViewSingleCharStringAsSwitch_ = false>
		[[nodiscard]] const string_type& GetConfigArg(const string_type& config_name_) const
		{
			auto it = parsed_config_args.find(config_name_);
			if (it != parsed_config_args.end())
			{
				return it->second;
			}
			else
			{
				it = default_config_args.find(config_name_);
				if (it != default_config_args.end())
				{
					return it->second;
				}
				else
				{
					if constexpr (CanViewSingleCharStringAsSwitch_)
					{
						if (config_name_.size() == 1)
						{
							return GetConfigArg(config_name_[0]);
						}
						else
						{
							throw std::out_of_range("Invalid config name provided to retrieve from a parser - it has neither been parsed nor provided a default value, and it cannot be translated as a switch as it contains more than 1 character.");
						}
					}
					else
					{
						throw std::out_of_range("Invalid config name provided to retrieve from a parser - it has neither been parsed nor provided a default value.");
					}
				}
			}
		}

		/// <summary>
		/// <para> Retrieves a constant reference to the value of the specified config argument switch. </para>
		/// <para> The passed switch will be automatically translated to its full name. </para>
		/// <para> If the passed argument has not been parsed, this will return the argument's default value. </para>
		/// <para> If the passed argument has not been parsed and there is no default value for it, this will throw a standard out_of_range exception. </para>
		/// </summary>
		/// <param name="config_switch_char_">Character switch for the config argument to retrieve the value of.</param>
		/// <returns>Constant reference to the value for the config argument specified by the passed switch character.</returns>
		[[nodiscard]] inline const string_type& GetConfigArg(const char_type& config_switch_char_) const
		{
			return GetConfigArg<false>(this->TranslateSwitch(config_switch_char_));
		}
#pragma endregion

#pragma region TRY_ACCESS_FUNCS
		/// <summary>
		/// <para> Tries to output a read-only pointer to the value of the specified config argument, returning a boolean which indicates if the operation was a success. </para>
		/// <para> If the passed argument has not been parsed, this will output a pointer to the argument's default value. </para>
		/// <para> If the passed argument has not been parsed and there is no default value for it, this will output a nullptr and return false. </para>
		/// </summary>
		/// <param name="config_name_">Full name of the config argument to output the value of.</param>
		/// <param name="pp_out_string_">Pointer to the string pointer to update with the specified config value (if it can be found).</param>
		/// <returns>True if the operation is successful; otherwise false.</returns>
		[[nodiscard]] bool TryGetConfigArg(const string_type& config_name_, const string_type** pp_out_string_) const
		{
			auto it = parsed_config_args.find(config_name_);
			if (it != parsed_config_args.end())
			{
				*pp_out_string_ = &(it->second);
				return true;
			}
			else
			{
				it = default_config_args.find(config_name_);
				if (it != default_config_args.end())
				{
					*pp_out_string_ = &(it->second);
					return true;
				}
				else
				{
					*pp_out_string_ = nullptr;
					return false;
				}
			}
		}

		/// <summary>
		/// <para> Tries to output a read-only pointer to the value of the specified config argument switch, returning a boolean which indicates if the operation was a success. </para>
		/// <para> The passed switch will be automatically translated to its full name. </para>
		/// <para> If the passed argument has not been parsed, this will output a pointer to the argument's default value. </para>
		/// <para> If the passed argument has not been parsed and there is no default value for it, this will output a nullptr and return false. </para>
		/// </summary>
		/// <param name="config_switch_char_">Character switch for the config argument to output the value of.</param>
		/// <param name="pp_out_string_">Pointer to the string pointer to update with the specified config value (if it can be found).</param>
		/// <returns>True if the operation is successful; otherwise false.</returns>
		[[nodiscard]] inline bool TryGetConfigArg(const char_type& config_switch_char_, const string_type** pp_out_string_) const
		{
			return TryGetConfigArg(this->TranslateSwitch(config_switch_char_), pp_out_string_);
		}

		/// <summary>
		/// <para> Tries to output a read-only reference to the value of the specified config argument, returning a boolean which indicates if the operation was a success. </para>
		/// <para> If the passed argument has not been parsed, this will output a constant reference to the argument's default value. </para>
		/// <para> If the passed argument has not been parsed and there is no default value for it, this will not modify the output parameter. </para>
		/// </summary>
		/// <param name="config_name_">Full name of the config argument to output the value of.</param>
		/// <param name="out_string_">Reference wrapper to output a constant reference to the specified config value via (if it can be found).</param>
		/// <returns>True if the operation is successful; otherwise false.</returns>
		[[nodiscard]] bool TryGetConfigArg(const string_type& config_name_, std::reference_wrapper<const string_type>& out_string_) const
		{
			auto it = parsed_config_args.find(config_name_);
			if (it != parsed_config_args.end())
			{
				out_string_ = std::reference_wrapper<const string_type>(it->second);
				return true;
			}
			else
			{
				it = default_config_args.find(config_name_);
				if (it != default_config_args.end())
				{
					out_string_ = std::reference_wrapper<const string_type>(it->second);
					return true;
				}
				else
				{
					return false;
				}
			}
		}

		/// <summary>
		/// <para> Tries to output a read-only reference to the value of the specified config argument switch, returning a boolean which indicates if the operation was a success. </para>
		/// <para> The passed switch will be automatically translated to its full name. </para>
		/// <para> If the passed argument has not been parsed, this will output a constant reference to the argument's default value. </para>
		/// <para> If the passed argument has not been parsed and there is no default value for it, this will not modify the output parameter. </para>
		/// </summary>
		/// <param name="config_switch_char_">Character switch for the config argument to output the value of.</param>
		/// <param name="out_string_">Reference to output a copy of the specified config value via (if it can be found).</param>
		/// <returns>True if the operation is successful; otherwise false.</returns>
		[[nodiscard]] inline bool TryGetConfigArg(const char_type& config_switch_char_, std::reference_wrapper<const string_type>& out_string_) const
		{
			return TryGetConfigArg(this->TranslateSwitch(config_switch_char_), out_string_);
		}

		/// <summary>
		/// <para> Tries to output a copy of the value of the specified config argument, returning a boolean which indicates if the operation was a success. </para>
		/// <para> The passed switch will be automatically translated to its full name. </para>
		/// <para> If the passed argument has not been parsed, this will output a copy of the argument's default value. </para>
		/// <para> If the passed argument has not been parsed and there is no default value for it, this will not modify the output parameter. </para>
		/// </summary>
		/// <param name="config_name_">Full name of the config argument to output the value of.</param>
		/// <param name="out_string_">Reference to output a copy of the specified config value via (if it can be found).</param>
		/// <returns>True if the operation is successful; otherwise false.</returns>
		[[nodiscard]] bool TryGetConfigArg(const string_type& config_name_, string_type& out_string_) const
		{
			auto it = parsed_config_args.find(config_name_);
			if (it != parsed_config_args.end())
			{
				out_string_ = it->second;
				return true;
			}
			else
			{
				it = default_config_args.find(config_name_);
				if (it != default_config_args.end())
				{
					out_string_ = it->second;
					return true;
				}
				else
				{
					return false;
				}
			}
		}

		/// <summary>
		/// <para> Tries to output a copy of the value of the specified config argument switch, returning a boolean which indicates if the operation was a success. </para>
		/// <para> The passed switch will be automatically translated to its full name. </para>
		/// <para> If the passed argument has not been parsed, this will output a copy of the argument's default value. </para>
		/// <para> If the passed argument has not been parsed and there is no default value for it, this will not modify the output parameter. </para>
		/// </summary>
		/// <param name="config_switch_char_">Character switch for the config argument to output the value of.</param>
		/// <param name="out_string_">Reference wrapper to output a constant reference to the specified config value via (if it can be found).></param>
		/// <returns>True if the operation is successful; otherwise false.</returns>
		[[nodiscard]] inline bool TryGetConfigArg(const char_type& config_switch_char_, string_type& out_string_) const
		{
			return TryGetConfigArg(this->TranslateSwitch(config_switch_char_), out_string_);
		}
#pragma endregion

#pragma region VALUE_SETTERS
		/// <summary>
		/// <para> Sets the config argument of the specified name to the passed value. </para>
		/// <para> If `CanReplace_` is true, this will always set the value for the specified name and always return true. </para>
		/// <para> If `CanReplace_` is false, this will only set the value if one does not already exist for the specified name. </para>
		/// </summary>
		/// <param name="config_name_">Name of the config argument to set.</param>
		/// <param name="value_">Item of any type that may be used to construct this parser's `string_type`, which will be used as the value for the specified config argument.</param>
		/// <returns>False if the set is cancelled to prevent a replacement; otherwise false.</returns>
		template<bool CanReplace_, EmuConcepts::UnqualifiedMatch<string_type> ConfigName_, class Value_>
		requires(std::is_constructible_v<string_type, Value_&&>)
		bool SetConfigValue(ConfigName_&& config_name_, Value_&& value_)
		{
			if constexpr (CanReplace_)
			{
				parsed_config_args[std::forward<ConfigName_>(config_name_)] = string_type(std::forward<Value_>(value_));
				return true;
			}
			else
			{
				string_type config_name = std::forward<ConfigName_>(config_name_);
				auto map_it = parsed_config_args.find(config_name);
				if (map_it == parsed_config_args.end())
				{
					parsed_config_args.emplace(std::make_pair(std::move(config_name), std::forward<Value_>(value_)));
					return true;
				}
				else
				{
					return false;
				}
			}
		}

		/// <summary>
		/// <para> Sets the config argument of the specified switches to the passed value. </para>
		/// <para> Each character in the passed string will be considered an individual switch. </para>
		/// <para> Each switch will automatically be translated to its full name. </para>
		/// <para> </para>
		/// <para> If `CanReplace_` is true, this will always set the value for the specified items. </para>
		/// <para> If `CanReplace_` is false, this will only set the values for switches where a value does not already exist. </para>
		/// </summary>
		/// <param name="switch_chars_array_">String to interpret as an array of switches.</param>
		/// <param name="value_">String of this parser's `string_type` to set the values of all specified switches to.</param>
		template<bool CanReplace_>
		inline void SetMultipleSwitchValues(const string_type& switch_chars_array_, const string_type& value_)
		{
			for (const auto& switch_char : switch_chars_array_)
			{
				this->SetConfigValue<CanReplace_>(this->TranslateSwitch(switch_char), value_);
			}
		}
#pragma endregion

#pragma region TRANSLATION_FUNCS
		/// <summary>
		/// <para> Translates the input switch into its full nane string translation. </para>
		/// </summary>
		/// <param name="switch_char">Switch character to translate into its full name string.</param>
		/// <returns>Full name translation for the passed switch. If it does not have a translation, this will simply be the character as a string.</returns>
		[[nodiscard]] inline string_type TranslateSwitch(const char_type switch_char) const
		{
			auto map_it = switch_to_full_name_map.find(switch_char);
			if (map_it != switch_to_full_name_map.end())
			{
				return map_it->second;
			}
			else
			{
				return string_type(1, switch_char);
			}
		}

		/// <summary>
		/// <para> Checks if this parser contains a translation for the given switch character into a full name. </para>
		/// </summary>
		/// <param name="switch_char_">Switch character to search for the translation of.</param>
		/// <returns>True if a full-name translation exists for the passed switch character; otherwise false.</returns>
		[[nodiscard]] inline bool ContainsSwitchTranslation(const char_type& switch_char_) const
		{
			return this->switch_to_full_name_map.find(switch_char_) == this->switch_to_full_name_map.end();
		}

		/// <summary>
		/// <para> Replaces the current switch-to-full-name translation map with the passed one. </para>
		/// <para> All current translations which are not within the passed map will be lost. </para>
		/// </summary>
		/// <param name="new_switch_to_full_name_map_">Switch-to-full-name translation map to replace this parser's current map with.</param>
		template<EmuConcepts::UnqualifiedMatch<switch_to_full_name_map_type> SwitchToFullNameMap_>
		inline void SetSwitchToFullNameMap(SwitchToFullNameMap_&& new_switch_to_full_name_map_)
		{
			this->switch_to_full_name_map = std::forward<SwitchToFullNameMap_>(new_switch_to_full_name_map_);
		}

		/// <summary>
		/// <para> Sets the full-name translation for the passed switch character to the passed full name. </para>
		/// <para> If `CanReplace_` is true, this will always set the translation even if one already exists, and will always return true. </para>
		/// <para> If `CanReplace_` is false, this will cancel the setting operation if a translation already exists. In the case of cancellation, this will return false. </para>
		/// </summary>
		/// <param name="switch_char_">Character to set the translation for.</param>
		/// <param name="full_name_">Full name to translate the passed switch character to. This can be any type that may be used to construct this parser's `string_type`.</param>
		/// <returns>False if the setting operation is cancelled; otherwise true.</returns>
		template<bool CanReplace_ = true, class FullName_>
		requires(std::is_constructible_v<string_type, FullName_&&>)
		inline bool SetSwitchToFullNameTranslation(const char_type& switch_char_, FullName_&& full_name_)
		{
			if constexpr (CanReplace_)
			{
				this->switch_to_full_name_map[switch_char_] = std::forward<FullName_>(full_name_);
				return true;
			}
			else
			{
				if (this->ContainsSwitchTranslation(switch_char_))
					return false;

				this->switch_to_full_name_map.emplace(std::make_pair(switch_char_, std::forward<FullName_>(full_name_)));
				return true;
			}
		}
#pragma endregion

#pragma region BUILT_IN_CONVERSION_FUNCS
		/// <summary>
		/// <para> Converts the specified config arg to an integer. </para>
		/// <para> If `GetConfigArg` is an unsuccessful operation, this will throw an exception. </para>
		/// <para> Subject to usual string-to-integer conversion exceptions where applicable. </para>
		/// </summary>
		/// <param name="config_name_">Name of the config argument to parse into an integer.</param>
		/// <returns>Specified config argument parsed into an integer.</returns>
		template<EmuConcepts::Integer OutInt_>
		[[nodiscard]] inline auto ToInt(const string_type& config_name_) const
			-> typename std::remove_cvref<OutInt_>::type
		{
			const string_type& arg_value = this->GetConfigArg(config_name_);
			return _built_in_cvt_arg_to_int<OutInt_>(arg_value);
		}

		/// <summary>
		/// <para> Converts the specified config switch to an integer. </para>
		/// <para> The passed switch will be automatically translated to its full name. </para>
		/// <para> If `GetConfigArg` is an unsuccessful operation, this will throw an exception. </para>
		/// <para> Subject to usual string-to-integer conversion exceptions where applicable. </para>
		/// </summary>
		/// <param name="config_switch_char_">Switch for the config argument to parse into an integer.</param>
		/// <returns>Specified config argument parsed into an integer.</returns>
		template<EmuConcepts::Integer OutInt_>
		[[nodiscard]] inline auto ToInt(const char_type& config_switch_char_) const
			-> typename std::remove_cvref<OutInt_>::type
		{
			return ToInt<OutInt_>(this->TranslateSwitch(config_switch_char_));
		}

		/// <summary>
		/// <para> Converts the specified config arg to an integer, if it can be found. </para>
		/// <para> Subject to usual string-to-integer conversion exceptions where applicable. </para>
		/// </summary>
		/// <param name="config_name_">Name of the config argument to parse into an integer.</param>
		/// <returns>Specified config argument parsed into an integer if the specified config arg can be found; otherwise a default, unqualified `OutInt_`.</returns>
		template<EmuConcepts::Integer OutInt_>
		[[nodiscard]] inline auto TryToInt(const string_type& config_name_) const
			-> typename std::remove_cvref<OutInt_>::type
		{
			const string_type* p_arg_value;
			if (this->TryGetConfigArg(config_name_, &p_arg_value))
			{
				return _built_in_cvt_arg_to_int<OutInt_>(*p_arg_value);
			}
			else
			{
				return typename std::remove_cvref<OutInt_>::type();
			}
		}

		/// <summary>
		/// <para> Converts the specified config switch to an integer, if it can be found. </para>
		/// <para> The passed switch will be automatically translated to its full name. </para>
		/// <para> Subject to usual string-to-integer conversion exceptions where applicable. </para>
		/// </summary>
		/// <param name="config_switch_char_">Switch for the config argument to parse into an integer.</param>
		/// <returns>Specified config argument parsed into an integer if the specified config arg can be found; otherwise a default, unqualified `OutInt_`.</returns>
		template<EmuConcepts::Integer OutInt_>
		[[nodiscard]] inline auto TryToInt(const char_type& config_switch_char_) const
			-> typename std::remove_cvref<OutInt_>::type
		{
			return TryToInt<OutInt_>(this->TranslateSwitch(config_switch_char_));
		}

		/// <summary>
		/// <para> Converts the specified config arg to an integer, if it can be found. </para>
		/// <para> Subject to usual string-to-integer conversion exceptions where applicable. </para>
		/// </summary>
		/// <param name="config_name_">Name of the config argument to parse into an integer.</param>
		/// <param name="out_if_not_found_">Default output value if the specified config arg cannot be found.</param>
		/// <returns>Specified config argument parsed into an integer if the specified config arg can be found; otherwise the passed `out_if_not_found_` value converted to an unqualified `OutInt_`.</returns>
		template<EmuConcepts::Integer OutInt_, EmuConcepts::Integer OutIfNotFound_>
		requires(EmuCore::TMP::is_static_castable_v<OutIfNotFound_&&, typename std::remove_cvref<OutInt_>::type>)
		[[nodiscard]] inline auto TryToInt(const string_type& config_name_, OutIfNotFound_&& out_if_not_found_) const
			-> typename std::remove_cvref<OutInt_>::type
		{
			const string_type* p_arg_value;
			if (this->TryGetConfigArg(config_name_, &p_arg_value))
			{
				return _built_in_cvt_arg_to_int<OutInt_>(*p_arg_value);
			}
			else
			{
				return static_cast<typename std::remove_cvref<OutInt_>::type>(std::forward<OutIfNotFound_>(out_if_not_found_));
			}
		}

		/// <summary>
		/// <para> Converts the specified config switch to an integer, if it can be found. </para>
		/// <para> The passed switch will be automatically translated to its full name. </para>
		/// <para> Subject to usual string-to-integer conversion exceptions where applicable. </para>
		/// </summary>
		/// <param name="config_switch_char_">Switch for the config argument to parse into an integer.</param>
		/// <param name="out_if_not_found_">Default output value if the specified config arg cannot be found.</param>
		/// <returns>Specified config argument parsed into an integer if the specified config arg can be found; otherwise the passed `out_if_not_found_` value converted to an unqualified `OutInt_`.</returns>
		template<EmuConcepts::Integer OutInt_, EmuConcepts::Integer OutIfNotFound_>
		requires(EmuCore::TMP::is_static_castable_v<OutIfNotFound_&&, typename std::remove_cvref<OutInt_>::type>)
		[[nodiscard]] inline auto TryToInt(const char_type& config_switch_char_, OutIfNotFound_&& out_if_not_found_) const
			-> typename std::remove_cvref<OutInt_>::type
		{
			return TryToInt<OutInt_>(this->TranslateSwitch(config_switch_char_), std::forward<OutIfNotFound_>(out_if_not_found_));
		}

		/// <summary>
		/// <para> Converts the specified config arg to a floating-point. </para>
		/// <para> If `GetConfigArg` is an unsuccessful operation, this will throw an exception. </para>
		/// <para> Subject to usual string-to-floating-point conversion exceptions where applicable. </para>
		/// </summary>
		/// <param name="config_name_">Name of the config argument to parse into a floating-point.</param>
		/// <returns>Specified config argument parsed into a floating-point.</returns>
		template<EmuConcepts::FloatingPoint OutFP_>
		[[nodiscard]] inline auto ToFloatingPoint(const string_type& config_name_) const
			-> typename std::remove_cvref<OutFP_>::type
		{
			const string_type& config_string = this->GetConfigArg(config_name_);
			return _built_in_cvt_arg_to_fp<OutFP_>(config_name_);
		}

		/// <summary>
		/// <para> Converts the specified config switch to a floating-point. </para>
		/// <para> The passed switch will be automatically translated to its full name. </para>
		/// <para> If `GetConfigArg` is an unsuccessful operation, this will throw an exception. </para>
		/// <para> Subject to usual string-to-floating-point conversion exceptions where applicable. </para>
		/// </summary>
		/// <param name="config_switch_char_">Switch for the config argument to parse into a floating-point.</param>
		/// <returns>Specified config argument parsed into a floating-point.</returns>
		template<EmuConcepts::FloatingPoint OutFP_>
		[[nodiscard]] inline auto ToFloatingPoint(const char_type& config_switch_char_) const
			-> typename std::remove_cvref<OutFP_>::type
		{
			return ToFloatingPoint<OutFP_>(this->TranslateSwitch(config_switch_char_));
		}

		/// <summary>
		/// <para> Converts the specified config arg to a floating-point, if it can be found. </para>
		/// <para> Subject to usual string-to-floating-point conversion exceptions where applicable. </para>
		/// </summary>
		/// <param name="config_name_">Name of the config argument to parse into a floating-point.</param>
		/// <returns>Specified config argument parsed into a floating-point if the specified config arg can be found; otherwise a default, unqualified `OutFP_`.</returns>
		template<EmuConcepts::FloatingPoint OutFP_>
		[[nodiscard]] inline auto TryToFloatingPoint(const string_type& config_name_) const
			-> typename std::remove_cvref<OutFP_>::type
		{
			const string_type* p_arg_value;
			if (this->TryGetConfigArg(config_name_, &p_arg_value))
			{
				return _built_in_cvt_arg_to_fp<OutFP_>(*p_arg_value);
			}
			else
			{
				return typename std::remove_cvref<OutFP_>::type();
			}
		}

		/// <summary>
		/// <para> Converts the specified config switch to a floating-point, if it can be found. </para>
		/// <para> The passed switch will be automatically translated to its full name. </para>
		/// <para> Subject to usual string-to-floating-point conversion exceptions where applicable. </para>
		/// </summary>
		/// <param name="config_switch_char_">Switch for the config argument to parse into a floating-point.</param>
		/// <returns>Specified config argument parsed into a floating-point if the specified config arg can be found; otherwise a default, unqualified `OutFP_`.</returns>
		template<EmuConcepts::FloatingPoint OutFP_>
		[[nodiscard]] inline auto TryToFloatingPoint(const char_type& config_switch_char_) const
			-> typename std::remove_cvref<OutFP_>::type
		{
			return TryToFloatingPoint<OutFP_>(this->TranslateSwitch(config_switch_char_));
		}

		/// <summary>
		/// <para> Converts the specified config arg to a floating-point, if it can be found. </para>
		/// <para> Subject to usual string-to-floating-point conversion exceptions where applicable. </para>
		/// </summary>
		/// <param name="config_name_">Name of the config argument to parse into a floating-point.</param>
		/// <param name="out_if_not_found_">Default output value if the specified config arg cannot be found.</param>
		/// <returns>Specified config argument parsed into a floating-point if the specified config arg can be found; otherwise the passed `out_if_not_found_` value converted to an unqualified `OutFP_`.</returns>
		template<EmuConcepts::FloatingPoint OutFP_, EmuConcepts::FloatingPoint OutIfNotFound_>
		requires(EmuCore::TMP::is_static_castable_v<OutIfNotFound_&&, typename std::remove_cvref<OutFP_>::type>)
		[[nodiscard]] inline auto TryToFloatingPoint(const string_type& config_name_, OutIfNotFound_&& out_if_not_found_) const
			-> typename std::remove_cvref<OutFP_>::type
		{
			const string_type* p_arg_value;
			if (this->TryGetConfigArg(config_name_, &p_arg_value))
			{
				return _built_in_cvt_arg_to_fp<OutFP_>(*p_arg_value);
			}
			else
			{
				return static_cast<typename std::remove_cvref<OutFP_>::type>(std::forward<OutIfNotFound_>(out_if_not_found_));
			}
		}

		/// <summary>
		/// <para> Converts the specified config switch to a floating-point, if it can be found. </para>
		/// <para> The passed switch will be automatically translated to its full name. </para>
		/// <para> Subject to usual string-to-floating-point conversion exceptions where applicable. </para>
		/// </summary>
		/// <param name="config_switch_char_">Switch for the config argument to parse into a floating-point.</param>
		/// <param name="out_if_not_found_">Default output value if the specified config arg cannot be found.</param>
		/// <returns>Specified config argument parsed into a floating-point if the specified config arg can be found; otherwise the passed `out_if_not_found_` value converted to an unqualified `OutFP_`.</returns>
		template<EmuConcepts::FloatingPoint OutFP_, EmuConcepts::FloatingPoint OutIfNotFound_>
		requires(EmuCore::TMP::is_static_castable_v<OutIfNotFound_&&, typename std::remove_cvref<OutFP_>::type>)
		[[nodiscard]] inline auto TryToFloatingPoint(const char_type& config_switch_char_, OutIfNotFound_&& out_if_not_found_) const
			-> typename std::remove_cvref<OutFP_>::type
		{
			return TryToFloatingPoint<OutFP_>(this->TranslateSwitch(config_switch_char_), std::forward<OutIfNotFound_>(out_if_not_found_));
		}

		/// <summary>
		/// <para> Converts the specified config switch to a boolean. </para>
		/// <para> If `GetConfigArg` is an unsuccessful operation, this will throw an exception. </para>
		/// </summary>
		/// <param name="config_switch_char_">Switch for the config argument to parse into a boolean.</param>
		/// <returns>Specified config argument parsed into a boolean.</returns>
		[[nodiscard]] inline bool ToBool(const string_type& config_name_) const
		{
			const string_type& config_string = this->GetConfigArg(config_name_);
			return EmuCore::string_to_bool<string_type>()(config_string);
		}

		/// <summary>
		/// <para> Converts the specified config switch to a boolean. </para>
		/// <para> The passed switch will be automatically translated to its full name. </para>
		/// <para> If `GetConfigArg` is an unsuccessful operation, this will throw an exception. </para>
		/// </summary>
		/// <param name="config_switch_char_">Switch for the config argument to parse into a boolean.</param>
		/// <returns>Specified config argument parsed into a boolean.</returns>
		[[nodiscard]] inline bool ToBool(const char_type& config_switch_char_) const
		{
			return ToBool(this->TranslateSwitch(config_switch_char_));
		}

		/// <summary>
		/// <para> Converts the specified config arg to a boolean, if it can be found. </para>
		/// </summary>
		/// <param name="config_name_">Name of the config argument to parse into a boolean.</param>
		/// <returns>Specified config argument parsed into a boolean if the specified config arg can be found; otherwise `false`.</returns>
		[[nodiscard]] inline bool TryToBool(const string_type& config_name_) const
		{
			const string_type* p_arg_value;
			if (this->TryGetConfigArg(config_name_, &p_arg_value))
			{
				return EmuCore::string_to_bool<string_type>()(*p_arg_value);
			}
			else
			{
				return false;
			}
		}

		/// <summary>
		/// <para> Converts the specified config switch to a boolean, if it can be found. </para>
		/// </summary>
		/// <param name="config_switch_char_">Switch for the config argument to parse into a boolean.</param>
		/// <param name="out_if_not_found_">Default output value if the specified config arg cannot be found.</param>
		/// <returns>Specified config argument parsed into a boolean if the specified config arg can be found; otherwise `false`.</returns>
		[[nodiscard]] inline bool TryToBool(const char_type& config_switch_char_) const
		{
			return TryToBool(this->TranslateSwitch(config_switch_char_));
		}

		/// <summary>
		/// <para> Converts the specified config arg to a boolean, if it can be found. </para>
		/// </summary>
		/// <param name="config_name_">Name of the config argument to parse into a boolean.</param>
		/// <param name="out_if_not_found_">Default output value if the specified config arg cannot be found.</param>
		/// <returns>Specified config argument parsed into a boolean if the specified config arg can be found; otherwise the passed `out_if_not_found_`.</returns>
		[[nodiscard]] inline bool TryToBool(const string_type& config_name_, bool out_if_not_found_) const
		{
			const string_type* p_arg_value;
			if (this->TryGetConfigArg(config_name_, &p_arg_value))
			{
				return EmuCore::string_to_bool<string_type>()(*p_arg_value);
			}
			else
			{
				return out_if_not_found_;
			}
		}

		/// <summary>
		/// <para> Converts the specified config switch to a boolean, if it can be found. </para>
		/// </summary>
		/// <param name="config_switch_char_">Switch for the config argument to parse into a boolean.</param>
		/// <param name="out_if_not_found_">Default output value if the specified config arg cannot be found.</param>
		/// <returns>Specified config argument parsed into a boolean if the specified config arg can be found; otherwise the passed `out_if_not_found_`.</returns>
		[[nodiscard]] inline bool TryToBool(const char_type& config_switch_char_, bool out_if_not_found_) const
		{
			return TryToBool(this->TranslateSwitch(config_switch_char_), out_if_not_found_);
		}
#pragma endregion

#pragma region CUSTOM_CONVERSION_FUNCS
		/// <summary>
		/// <para> Converts the specified config arg via the provided custom conversion function. </para>
		/// <para> The conversion function must be invocable with a constant reference to this parser's string_type, however it does not have any return requirements. </para>
		/// <para> If `GetConfigArg` is an unsuccessful operation, this will throw an exception. </para>
		/// </summary>
		/// <param name="config_name_">Name of the config argument to parse via the custom conversion function.</param>
		/// <param name="conversion_func_">Function which is invocable when passed a constant reference to this parser's string_type. May return anything.</param>
		/// <returns>Result of the passed conversion function when invoked with the specified config argument.</returns>
		template<class ConversionFunc_>
		requires(std::is_invocable_v<ConversionFunc_, const string_type&>)
		[[nodiscard]] inline decltype(auto) Convert(const string_type& config_name_, ConversionFunc_&& conversion_func_) const
		{
			const string_type& config_string = this->GetConfigArg(config_name_);
			return std::forward<ConversionFunc_>(conversion_func_)(config_string);
		}

		/// <summary>
		/// <para> Converts the specified config switch via the provided custom conversion function. </para>
		/// <para> The passed switch will be automatically translated to its full name. </para>
		/// <para> The conversion function must be invocable with a constant reference to this parser's string_type, however it does not have any return requirements. </para>
		/// <para> If `GetConfigArg` is an unsuccessful operation, this will throw an exception. </para>
		/// </summary>
		/// <param name="config_switch_char_">Switch for the config argument to parse via the custom conversion function.</param>
		/// <param name="conversion_func_">Function which is invocable when passed a constant reference to this parser's string_type. May return anything.</param>
		/// <returns>Result of the passed conversion function when invoked with the specified config argument.</returns>
		template<class ConversionFunc_>
		requires(std::is_invocable_v<ConversionFunc_, const string_type&>)
		[[nodiscard]] inline decltype(auto) Convert(const char_type& config_switch_char_, ConversionFunc_&& conversion_func_) const
		{
			return Convert(this->TranslateSwitch(config_switch_char_), std::forward<conversion_func_>(conversion_func_));
		}

		/// <summary>
		/// <para> Converts the specified config arg via the provided custom conversion function. </para>
		/// <para>
		///		The conversion function must be invocable with a constant reference to this parser's string_type and also invocable with no arguments, but it does not have any return requirements. 
		///		However, both required signatures must return the same type.
		/// </para>
		/// <para> If `GetConfigArg` is an unsuccessful operation, this will throw an exception. </para>
		/// </summary>
		/// <param name="config_name_">Name of the config argument to parse via the custom conversion function.</param>
		/// <param name="conversion_func_">
		///		Function which is invocable when passed a constant reference to this parser's string_type and also when passed nothing. 
		///		May return anything, but both required signatures must return the same type.
		/// </param>
		/// <returns>Result of the passed conversion function when invoked with the specified config argument if it can be found, or when invoked with no arguments otherwise.</returns>
		template<class ConversionFunc_>
		requires(std::is_invocable_v<ConversionFunc_&&, const string_type&> && std::is_invocable_v<ConversionFunc_&&>)
		[[nodiscard]] inline decltype(auto) TryConvert(const string_type& config_name_, ConversionFunc_&& conversion_func_) const
		{
			const string_type* p_arg_value;
			if (this->TryGetConfigArg(config_name_, &p_arg_value))
			{
				return std::forward<ConversionFunc_>(conversion_func_)(*p_arg_value);
			}
			else
			{
				return std::forward<ConversionFunc_>(conversion_func_)();
			}
		}

		/// <summary>
		/// <para> Converts the specified config switch via the provided custom conversion function. </para>
		/// <para> The passed switch will be automatically translated to its full name. </para>
		/// <para>
		///		The conversion function must be invocable with a constant reference to this parser's string_type and also invocable with no arguments, but it does not have any return requirements. 
		///		However, both required signatures must return the same type.
		/// </para>
		/// <para> If `GetConfigArg` is an unsuccessful operation, this will throw an exception. </para>
		/// </summary>
		/// <param name="config_switch_char_">Switch for the config argument to parse via the custom conversion function.</param>
		/// <param name="conversion_func_">
		///		Function which is invocable when passed a constant reference to this parser's string_type and also when passed nothing. 
		///		May return anything, but both required signatures must return the same type.
		/// </param>
		/// <returns>Result of the passed conversion function when invoked with the specified config argument if it can be found, or when invoked with no arguments otherwise.</returns>
		template<class ConversionFunc_>
		requires(std::is_invocable_v<ConversionFunc_, const string_type&>)
		[[nodiscard]] inline decltype(auto) TryConvert(const char_type& config_switch_char_, ConversionFunc_&& conversion_func_) const
		{
			return TryConvert(this->TranslateSwitch(config_switch_char_), std::forward<conversion_func_>(conversion_func_));
		}
#pragma endregion

#pragma region VALIDATION_FUNCS
		/// <summary>
		/// <para>
		///		Validates the parsed config arguments within this parser, 
		///		updating them via the passed validation function and removing them if the validation function suggests to.
		/// </para>
		/// <para>
		///		The passed function must return a boolean-evaluable value when invoked with (`const string_type reference`, `string_type reference`), 
		///		being the config arg name and the value of the arg respectively.
		/// </para>
		/// <para> The function may freely write different data to the value reference. </para>
		/// <para> If the function returns false, the config arg will be flagged for removal. All removals will be performed after validation process is complete. </para>
		/// </summary>
		/// <param name="validation_func_">Validation function which meets the stated constraints within the main body of this function. Called once for each parsed config argument.</param>
		/// <param name="removed_count_hint_">
		///		Optional hint for the amount of values to expect to be removed. This allows for some optimisation for heap allocation used to defer removal until after the main operation. 
		///		Defaults to 0 (i.e. no space pre-allocated), but heap allocation will always be performed with or without a hint.
		/// </param>
		template<class ValidationFunc_>
		requires(std::is_invocable_r_v<bool, typename std::remove_reference<ValidationFunc_>::type&, const string_type&, string_type&>)
		void ValidateParsedConfigArgs(ValidationFunc_&& validation_func_, const std::size_t removed_count_hint_ = 0)
		{
			auto keys_to_remove = std::vector<const string_type*>();
			keys_to_remove.reserve(removed_count_hint_);
			auto& validation_func_ref = EmuCore::TMP::lval_ref_cast<ValidationFunc_>(std::forward<ValidationFunc_>(validation_func_));
			for (auto& key_value_pair : this->parsed_config_args)
			{
				if (!validation_func_ref(key_value_pair.first, key_value_pair.second))
				{
					keys_to_remove.push_back(&key_value_pair.first);
				}
			}
		}
#pragma endregion

#pragma region STREAM_APPENDING_FUNCS
		template<bool IncludeDefaults_ = true, bool IncludeSwitchTranslations_ = false>
		std::ostream& AppendToStream(std::ostream& str_) const
		{
			const string_type group_opener = ": {\n";
			const string_type group_closer = "\n}";
			const string_type single_indent = "    ";

			str_ << "Basic arguments";
			str_ << group_opener;
			AppendNonConfigArgsToStream(str_, single_indent);
			str_ << group_closer;

			str_ << "\nConfig arguments";
			str_ << group_opener;
			AppendConfigArgsToStream(str_, single_indent);
			str_ << group_closer;

			if constexpr (IncludeDefaults_)
			{
				str_ << "\nDefault arguments";
				str_ << group_opener;
				AppendDefaultArgsToStream(str_, single_indent);
				str_ << group_closer;
			}

			if constexpr (IncludeSwitchTranslations_)
			{
				str_ << "\nSwitches";
				str_ << group_opener;
				AppendSwitchNameTranslationsToStream(str_, single_indent);
				str_ << group_closer;
			}

			return str_;
		}

		inline std::ostream& AppendNonConfigArgsToStream(std::ostream& str_) const
		{
			return _append_basic_collection_to_stream(str_, parsed_non_config_args, _underlying_no_indent());
		}

		template<class Indent_>
		inline std::ostream& AppendNonConfigArgsToStream(std::ostream& str_, const Indent_& indent_) const
		{
			return _append_basic_collection_to_stream(str_, parsed_non_config_args, indent_);
		}

		inline std::ostream& AppendConfigArgsToStream(std::ostream& str_) const
		{
			return _append_map_to_stream(str_, parsed_config_args, _underlying_no_indent());
		}

		template<class Indent_>
		inline std::ostream& AppendConfigArgsToStream(std::ostream& str_, const Indent_& indent_) const
		{
			return _append_map_to_stream(str_, parsed_config_args, indent_);
		}

		inline std::ostream& AppendDefaultArgsToStream(std::ostream& str_) const
		{
			return _append_map_to_stream(str_, default_config_args, _underlying_no_indent());
		}

		template<class Indent_>
		inline std::ostream& AppendDefaultArgsToStream(std::ostream& str_, const Indent_& indent_) const
		{
			return _append_map_to_stream(str_, default_config_args, indent_);
		}

		inline std::ostream& AppendSwitchNameTranslationsToStream(std::ostream& str_) const
		{
			return _append_map_to_stream(str_, switch_to_full_name_map, _underlying_no_indent());
		}

		template<class Indent_>
		inline std::ostream& AppendSwitchNameTranslationsToStream(std::ostream& str_, const Indent_& indent_) const
		{
			return _append_map_to_stream(str_, switch_to_full_name_map, indent_);
		}
#pragma endregion

	private:
		/// <summary> Meta-type used as an indentation argument to perform no indentation in functions that may provide indents, allowing to avoid empty stream appends when not wanted. </summary>
		struct _underlying_no_indent {};

		template<bool AllowNegativeNumbers_>
		[[nodiscard]] static inline bool _is_likely_config_name_string(const string_type& str_)
		{
			if constexpr (AllowNegativeNumbers_)
			{
				if (str_[0] == '-')
				{
					return !(str_.size() >= 2 && isdigit(str_[1]));
				}
				else
				{
					return false;
				}
			}
			else
			{
				return str_[0] == '-';
			}
		}

		static inline void _trim_keys(const std::vector<const string_type*>& keys_to_remove_, config_args_map_type& map_to_trim_)
		{
			for (const string_type* p_config_key : keys_to_remove_)
			{
				map_to_trim_.erase(*p_config_key);
			}
		}

		template<EmuConcepts::Integer OutInt_>
		[[nodiscard]] static inline auto _built_in_cvt_arg_to_int(const string_type& arg_value_)
		{
			constexpr bool is_signed = std::is_signed_v<typename std::remove_cvref<OutInt_>::type>;
			constexpr std::size_t num_bytes = sizeof(typename std::remove_cvref<OutInt_>::type);
			if constexpr (num_bytes <= sizeof(int))
			{
				return static_cast<typename std::remove_cvref<OutInt_>::type>(std::stoi(arg_value_));
			}
			else if constexpr (num_bytes <= sizeof(long))
			{
				if constexpr (is_signed)
				{
					return static_cast<typename std::remove_cvref<OutInt_>::type>(std::stol(arg_value_));
				}
				else
				{
					return static_cast<typename std::remove_cvref<OutInt_>::type>(std::stoul(arg_value_));
				}
			}
			else
			{
				if constexpr (is_signed)
				{
					return static_cast<typename std::remove_cvref<OutInt_>::type>(std::stoll(arg_value_));
				}
				else
				{
					return static_cast<typename std::remove_cvref<OutInt_>::type>(std::stoull(arg_value_));
				}
			}
		}

		template<EmuConcepts::FloatingPoint OutFP_>
		[[nodiscard]] static inline auto _built_in_cvt_arg_to_fp(const string_type& arg_value_)
		{
			constexpr std::size_t num_bytes = sizeof(typename std::remove_cvref<OutFP_>::type);
			if constexpr (num_bytes <= sizeof(float))
			{
				return static_cast<typename std::remove_cvref<OutFP_>::type>(std::stof(arg_value_));
			}
			else if constexpr (num_bytes <= sizeof(double))
			{
				return static_cast<typename std::remove_cvref<OutFP_>::type>(std::stod(arg_value_));
			}
			else
			{
				return static_cast<typename std::remove_cvref<OutFP_>::type>(std::stold(arg_value_));
			}
		}

		template<class Indent_, class Key_, class Value_, class Pr_, class Allocator_>
		static std::ostream& _append_map_to_stream(std::ostream& str_, const std::map<Key_, Value_, Pr_, Allocator_>& config_map_, const Indent_& indent_)
		{
			auto it = config_map_.begin();
			auto end = config_map_.end();
			if (it != end)
			{
				_append_indent(str_, indent_);
				str_ << EmuCore::TMP::do_dereference(it->first);
				str_ << '=';
				str_ << EmuCore::TMP::do_dereference(it->second);
				++it;
				while (it != end)
				{
					str_ << '\n';
					_append_indent(str_, indent_);
					str_ << EmuCore::TMP::do_dereference(it->first);
					str_ << '=';
					str_ << EmuCore::TMP::do_dereference(it->second);
					++it;
				}
			}
			return str_;
		}

		template<class Indent_, class Collection_>
		static std::ostream& _append_basic_collection_to_stream(std::ostream& str_, const Collection_& basic_collection_, const Indent_& indent_)
		{
			auto it = basic_collection_.begin();
			auto end = basic_collection_.end();
			if (it != end)
			{
				_append_indent(str_, indent_);
				str_ << EmuCore::TMP::do_dereference(*it);
				++it;
				while (it != end)
				{
					str_ << '\n';
					_append_indent(str_, indent_);
					str_ << EmuCore::TMP::do_dereference(*it);
					++it;
				}
			}
			return str_;
		}

		template<class Indent_>
		static inline void _append_indent(std::ostream& str_, const Indent_& indent_)
		{
			if constexpr (!std::is_same_v<Indent_, typename std::remove_cvref<_underlying_no_indent>::type>)
			{
				str_ << indent_;
			}
		}

		/// <summary>
		/// <para> Suitably sets config arg(s) to the passed `value_` if the passed index is the final argument index. </para>
		/// <para> Does nothing if more indices remain after the current one. </para>
		/// </summary>
		/// <param name="arg_index_">Index of the current argument.</param>
		/// <param name="arg_index_">Total number of input arguments.</param>
		/// <param name="is_switch_config_arg_">True if setting a series of switches representing different config args, otherwise false.</param>
		/// <param name="is_full_name_config_arg_">True if setting a single full name config arg, otherwise false.</param>
		/// <param name="current_config_arg_name">Reference to either the full name of the current arg or a string to use as an array of characters indicating individual switches, based on which of the passed bools is true.</param>
		/// <param name="value_">Value to set config arg(s) to.</param>
		template<bool CanReplace_>
		inline void _set_config_args_if_no_more_input
		(
			const std::size_t arg_index_,
			const std::size_t num_args_,
			const bool is_switch_config_arg_,
			const bool is_full_name_config_arg_,
			string_type& current_config_arg_name,
			const string_type& value_
		)
		{
			if ((arg_index_ + 1) >= num_args_)
			{
				if (is_full_name_config_arg_)
				{
					this->SetConfigValue<CanReplace_>(std::move(current_config_arg_name), value_);
				}
				else if(is_switch_config_arg_)
				{
					this->SetMultipleSwitchValues<CanReplace_>(current_config_arg_name, value_);
				}
			}
		}

		static inline bool _determine_config_arg_type(const string_type& arg_string_, string_type& out_current_config_arg_name_, bool& is_switch_config_arg_, bool& is_full_name_config_arg_)
		{
			// Do not accept just `-`; it should be discarded
			if (arg_string_.size() > 1)
			{
				if (arg_string_[1] == '-')
				{
					// Do not accept just "--"; it should be discarded
					if (arg_string_.size() > 2)
					{
						// We have a valid full name arg
						out_current_config_arg_name_ = arg_string_.substr(2);
						is_full_name_config_arg_ = true;
						is_switch_config_arg_ = false;
						return true;
					}
				}
				else
				{
					// We have a valid switch arg - store all switches in the current name; in this case, it is considered an array of switches
					out_current_config_arg_name_ = arg_string_.substr(1);
					is_full_name_config_arg_ = false;
					is_switch_config_arg_ = true;
					return true;
				}
			}
			return false;
		}

		template<class ArgsCollection_>
		[[nodiscard]] static constexpr inline std::size_t _get_args_collection_size(const ArgsCollection_& args_collection_)
		{
			return args_collection_.size();
		}

		template<bool CanMove_, class ArgsCollection_>
		[[nodiscard]] static constexpr inline decltype(auto) _get_arg_from_collection(ArgsCollection_&& args_collection_, std::size_t index_)
		{
			if constexpr (CanMove_)
			{
				return std::move(std::forward<ArgsCollection_>(args_collection_)[index_]);
			}
			else
			{
				return std::forward<ArgsCollection_>(args_collection_)[index_];
			}
		}

#pragma region DATA
		/// <summary> Collection of all arguments that have been parsed by this parser. Does NOT include values set manually via this parser's functions (such as SetConfigValue). </summary>
		std::deque<string_type> all_parsed_args;
		/// <summary> All config args with default values, mapped to their default value. This map will be used when a config arg has not been used to populate `parsed_config_args`. </summary>
		config_args_map_type default_config_args;
		/// <summary> All config args that have been parsed, mapped to their value. </summary>
		config_args_map_type parsed_config_args;
		/// <summary> Collection of non-config args that have been parsed. These are pointers to certain strings within `all_parsed_args`. </summary>
		std::vector<const string_type*> parsed_non_config_args;
		/// <summary> Map used to translate switch characters to their full-name strings. </summary>
		switch_to_full_name_map_type switch_to_full_name_map;
#pragma endregion
	};
}

#endif

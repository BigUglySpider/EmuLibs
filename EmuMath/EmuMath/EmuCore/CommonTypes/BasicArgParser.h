#ifndef EMU_CORE_BASIC_ARG_PARSER_H_INC_
#define EMU_CORE_BASIC_ARG_PARSER_H_INC_ 1

#include "../CommonConcepts/Arithmetic.h"
#include "../CommonConcepts/CommonRequirements.h"
#include "../TMPHelpers/OperatorChecks.h"
#include "../TMPHelpers/TypeConvertors.h"

#include <map>
#include <stdexcept>
#include <string>
#include <vector>

namespace EmuCore
{
	struct BasicArgParser
	{
	public:
		using string_type = std::string;
		using char_type = string_type::value_type;
		using string_view_type = std::string_view;
		using config_args_map_type = std::map<string_type, string_type>;
		using switch_to_full_name_map_type = std::map<char_type, string_type>;
		static constexpr string_view_type default_config_name_only_value{ "true" };

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

		template<class VectorValue_>
		struct _is_compatible_args_collection<std::vector<VectorValue_>>
		{
			static constexpr bool value = std::is_constructible_v<string_type, VectorValue_>;
		};

		template<class ArgsCollection_>
		[[nodiscard]] static constexpr inline std::size_t _get_args_collection_size(const ArgsCollection_& args_collection_)
		{
			return args_collection_.size();
		}

		template<bool CanMove_, class ArgsCollection_>
		[[nodiscard]] static constexpr inline string_type _get_arg_from_collection(ArgsCollection_&& args_collection_, std::size_t index_)
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

	public:
		static inline std::vector<string_type> make_vector_from_main_args(int argc, char** argv)
		{
			std::vector<string_type> args_vector;
			const std::size_t argc_as_size = static_cast<std::size_t>(argc);
			args_vector.reserve(argc_as_size);
			for (std::size_t i = 0; i < argc_as_size; ++i)
			{
				args_vector.emplace_back(string_type{ argv[i] });
			}
			return args_vector;
		}

		template<class ArgsCollection_>
		[[nodiscard]] static constexpr inline bool is_compatible_args_collection()
		{
			return _is_compatible_args_collection<ArgsCollection_>::value;
		}

		inline BasicArgParser(int argc, char** argv) : 
			BasicArgParser(make_vector_from_main_args(argc, argv), string_type(default_config_name_only_value), config_args_map_type(), switch_to_full_name_map_type())
		{
		}

		inline BasicArgParser(int argc, char** argv, string_type config_name_only_value_, config_args_map_type&& default_config_args_, switch_to_full_name_map_type&& switch_to_full_name_map_) :
			BasicArgParser(make_vector_from_main_args(argc, argv), std::move(config_name_only_value_), std::move(default_config_args_), std::move(switch_to_full_name_map_))
		{
		}

		template<class ArgsCollection_>
		requires((is_compatible_args_collection<ArgsCollection_>()))
		BasicArgParser
		(
			ArgsCollection_&& args_collection_,
			string_type config_name_only_value_,
			config_args_map_type&& default_config_args_,
			switch_to_full_name_map_type&& switch_to_full_name_map_
		) : default_config_args(default_config_args_),
			switch_to_full_name_map(switch_to_full_name_map_),
			parsed_config_args()
		{
			constexpr bool can_move = !std::is_lvalue_reference_v<ArgsCollection_>;
			auto& args_collection_ref = EmuCore::TMP::lval_ref_cast<ArgsCollection_>(std::forward<ArgsCollection_>(args_collection_));
			bool is_full_name_config_arg = false;
			bool is_switch_config_arg = false;
			std::string current_config_arg_name = "";
			const std::size_t input_arg_count = _get_args_collection_size(args_collection_ref);
			for (std::size_t i = 0; i < input_arg_count; ++i)
			{
				string_type arg_string = _get_arg_from_collection<can_move>(args_collection_ref, i);
				parsed_non_config_args.emplace_back(arg_string);
				if (is_full_name_config_arg)
				{
					if (arg_string.size() == 0)
					{
						// Empty argument, so just set to the default and move on
						this->set_config_value<true>(std::move(current_config_arg_name), config_name_only_value_);
					}
					else if (arg_string[0] == '-')
					{
						// We've moved on to a different config argument, so set the previous to the default and then determine what we're working with for next iteration
						this->set_config_value<true>(std::move(current_config_arg_name), config_name_only_value_);
						EMU_CORE_PUSH_WARNING_STACK
						EMU_CORE_MSVC_DISABLE_WARNING(26800)
						if (this->_determine_config_arg_type(arg_string, current_config_arg_name, is_switch_config_arg, is_full_name_config_arg))
						{
							this->_set_config_args_if_no_more_input(i, input_arg_count, is_switch_config_arg, is_full_name_config_arg, current_config_arg_name, config_name_only_value_);
						}
						EMU_CORE_POP_WARNING_STACK
					}
					else
					{
						this->set_config_value<true>(std::move(current_config_arg_name), std::move(arg_string));
						is_full_name_config_arg = false;
					}
				}
				else if(is_switch_config_arg)
				{
					if (arg_string.size() == 0)
					{
						// Empty argument, so just set to the default and move on
						this->_set_multiple_switch_args(current_config_arg_name, config_name_only_value_);
					}
					else if (arg_string[0] == '-')
					{
						// We've moved on to a different config argument, so set the previous to the default and then determine what we're working with for next iteration
						this->_set_multiple_switch_args(current_config_arg_name, config_name_only_value_);
						if (this->_determine_config_arg_type(arg_string, current_config_arg_name, is_switch_config_arg, is_full_name_config_arg))
						{
							this->_set_config_args_if_no_more_input(i, input_arg_count, is_switch_config_arg, is_full_name_config_arg, current_config_arg_name, config_name_only_value_);
						}
					}
					else
					{
						this->_set_multiple_switch_args(current_config_arg_name, arg_string);
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
					else if (arg_string[0] == '-')
					{
						this->_determine_config_arg_type(arg_string, current_config_arg_name, is_switch_config_arg, is_full_name_config_arg);
						this->_set_config_args_if_no_more_input(i, input_arg_count, is_switch_config_arg, is_full_name_config_arg, current_config_arg_name, config_name_only_value_);
					}
				}
			}
		}

		/// <summary>
		/// <para> Shorthand for `get_config_arg` with the same arguments. </para>
		/// </summary>
		[[nodiscard]] inline const string_type& operator[](const string_type& config_name_) const
		{
			return get_config_arg(config_name_);
		}

		/// <summary>
		/// <para> Shorthand for `get_config_arg` with the same arguments. </para>
		/// </summary>
		[[nodiscard]] inline const string_type& operator[](const char_type& config_switch_char_) const
		{
			return get_config_arg(config_switch_char_);
		}

		/// <summary>
		/// <para> Shorthand for `try_get_config_arg` with the same arguments. </para>
		/// </summary>
		[[nodiscard]] inline bool operator()(const string_type& config_name_, const string_type** pp_out_string_) const
		{
			return try_get_config_arg(config_name_, pp_out_string_);
		}

		/// <summary>
		/// <para> Shorthand for `try_get_config_arg` with the same arguments. </para>
		/// </summary>
		[[nodiscard]] inline bool operator()(const char_type& config_switch_char_, const string_type** pp_out_string_) const
		{
			return try_get_config_arg(config_switch_char_, pp_out_string_);
		}

		/// <summary>
		/// <para> Shorthand for `try_get_config_arg` with the same arguments. </para>
		/// </summary>
		[[nodiscard]] inline bool operator()(const string_type& config_name_, std::reference_wrapper<const string_type>& out_string_) const
		{
			return try_get_config_arg(config_name_, out_string_);
		}

		/// <summary>
		/// <para> Shorthand for `try_get_config_arg` with the same arguments. </para>
		/// </summary>
		[[nodiscard]] inline bool operator()(const char_type& config_switch_char_, std::reference_wrapper<const string_type>& out_string_) const
		{
			return try_get_config_arg(config_switch_char_, out_string_);
		}

		/// <summary>
		/// <para> Shorthand for `try_get_config_arg` with the same arguments. </para>
		/// </summary>
		[[nodiscard]] inline bool operator()(const string_type& config_name_, string_type& out_string_) const
		{
			return try_get_config_arg(config_name_, out_string_);
		}

		/// <summary>
		/// <para> Shorthand for `try_get_config_arg` with the same arguments. </para>
		/// </summary>
		[[nodiscard]] inline bool operator()(const char_type& config_switch_char_, string_type& out_string_) const
		{
			return try_get_config_arg(config_switch_char_, out_string_);
		}

		/// <summary>
		/// <para> Retrieves a constant reference to the value of the specified config argument. </para>
		/// <para> If the passed argument has not been parsed, this will return the argument's default value. </para>
		/// <para> If the passed argument has not been parsed and there is no default value for it, this will throw a standard out_of_range exception. </para>
		/// </summary>
		/// <param name="config_name_">Full name of the config argument to retrieve the value of.</param>
		/// <returns>Constant reference to the value for the specified config argument.</returns>
		[[nodiscard]] inline const string_type& get_config_arg(const string_type& config_name_) const
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
					throw std::out_of_range("Invalid config name provided to retrieve from a parser - it has neither been parsed nor provided a default value.");
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
		[[nodiscard]] inline const string_type& get_config_arg(const char_type& config_switch_char_) const
		{
			return get_config_arg(this->translate_switch_to_full_name(config_switch_char_));
		}

		/// <summary>
		/// <para> Tries to output a read-only pointer to the value of the specified config argument, returning a boolean which indicates if the operation was a success. </para>
		/// <para> If the passed argument has not been parsed, this will output a pointer to the argument's default value. </para>
		/// <para> If the passed argument has not been parsed and there is no default value for it, this will output a nullptr and return false. </para>
		/// </summary>
		/// <param name="config_name_">Full name of the config argument to output the value of.</param>
		/// <param name="pp_out_string_">Pointer to the string pointer to update with the specified config value (if it can be found).</param>
		/// <returns>True if the operation is successful; otherwise false.</returns>
		[[nodiscard]] inline bool try_get_config_arg(const string_type& config_name_, const string_type** pp_out_string_) const
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
		[[nodiscard]] inline bool try_get_config_arg(const char_type& config_switch_char_, const string_type** pp_out_string_) const
		{
			return try_get_config_arg(this->translate_switch_to_full_name(config_switch_char_), pp_out_string_);
		}

		/// <summary>
		/// <para> Tries to output a read-only reference to the value of the specified config argument, returning a boolean which indicates if the operation was a success. </para>
		/// <para> If the passed argument has not been parsed, this will output a constant reference to the argument's default value. </para>
		/// <para> If the passed argument has not been parsed and there is no default value for it, this will not modify the output parameter. </para>
		/// </summary>
		/// <param name="config_name_">Full name of the config argument to output the value of.</param>
		/// <param name="out_string_">Reference wrapper to output a constant reference to the specified config value via (if it can be found).</param>
		/// <returns>True if the operation is successful; otherwise false.</returns>
		[[nodiscard]] inline bool try_get_config_arg(const string_type& config_name_, std::reference_wrapper<const string_type>& out_string_) const
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
		[[nodiscard]] inline bool try_get_config_arg(const char_type& config_switch_char_, std::reference_wrapper<const string_type>& out_string_) const
		{
			return try_get_config_arg(this->translate_switch_to_full_name(config_switch_char_), out_string_);
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
		[[nodiscard]] inline bool try_get_config_arg(const string_type& config_name_, string_type& out_string_) const
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
		[[nodiscard]] inline bool try_get_config_arg(const char_type& config_switch_char_, string_type& out_string_) const
		{
			return try_get_config_arg(this->translate_switch_to_full_name(config_switch_char_), out_string_);
		}

		template<bool ReplaceAllowed_, EmuConcepts::UnqualifiedMatch<string_type> ConfigName_, EmuConcepts::UnqualifiedMatch<string_type> Value_>
		inline bool set_config_value(ConfigName_&& config_name_, Value_&& value_)
		{
			if constexpr (ReplaceAllowed_)
			{
				parsed_config_args[std::forward<ConfigName_>(config_name_)] = std::forward<Value_>(value_);
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

		[[nodiscard]] inline std::string translate_switch_to_full_name(const char_type switch_char) const
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
		/// <para> Converts the specified config arg to an integer. </para>
		/// <para> If `get_config_arg` is an unsuccessful operation, this will throw an exception. </para>
		/// <para> Subject to usual string-to-integer conversion exceptions where applicable. </para>
		/// </summary>
		/// <param name="config_name_">Name of the config argument to parse into an integer.</param>
		/// <returns>Specified config argument parsed into an integer.</returns>
		template<EmuConcepts::Integer OutInt_>
		[[nodiscard]] inline auto ToInt(const string_type& config_name_) const
			-> typename std::remove_cvref<OutInt_>::type
		{
			const string_type& arg_value = this->get_config_arg(config_name_);
			return _built_in_cvt_arg_to_int<OutInt_>(arg_value);
		}

		/// <summary>
		/// <para> Converts the specified config switch to an integer. </para>
		/// <para> The passed switch will be automatically translated to its full name. </para>
		/// <para> If `get_config_arg` is an unsuccessful operation, this will throw an exception. </para>
		/// <para> Subject to usual string-to-integer conversion exceptions where applicable. </para>
		/// </summary>
		/// <param name="config_switch_char_">Switch for the config argument to parse into an integer.</param>
		/// <returns>Specified config argument parsed into an integer.</returns>
		template<EmuConcepts::Integer OutInt_>
		[[nodiscard]] inline auto ToInt(const char_type& config_switch_char_) const
			-> typename std::remove_cvref<OutInt_>::type
		{
			return ToInt<OutInt_>(this->translate_switch_to_full_name(config_switch_char_));
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
			if (this->try_get_config_arg(config_name_, &p_arg_value))
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
			return TryToInt<OutInt_>(this->translate_switch_to_full_name(config_switch_char_));
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
			if (this->try_get_config_arg(config_name_, &p_arg_value))
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
			return TryToInt<OutInt_>(this->translate_switch_to_full_name(config_switch_char_), std::forward<OutIfNotFound_>(out_if_not_found_));
		}

		/// <summary>
		/// <para> Converts the specified config arg to a floating-point. </para>
		/// <para> If `get_config_arg` is an unsuccessful operation, this will throw an exception. </para>
		/// <para> Subject to usual string-to-floating-point conversion exceptions where applicable. </para>
		/// </summary>
		/// <param name="config_name_">Name of the config argument to parse into a floating-point.</param>
		/// <returns>Specified config argument parsed into a floating-point.</returns>
		template<EmuConcepts::FloatingPoint OutFP_>
		[[nodiscard]] inline auto ToFloatingPoint(const string_type& config_name_) const
			-> typename std::remove_cvref<OutFP_>::type
		{
			const string_type& config_string = this->get_config_arg(config_name_);
			return _built_in_cvt_arg_to_fp<OutFP_>(config_name_);
		}

		/// <summary>
		/// <para> Converts the specified config switch to a floating-point. </para>
		/// <para> The passed switch will be automatically translated to its full name. </para>
		/// <para> If `get_config_arg` is an unsuccessful operation, this will throw an exception. </para>
		/// <para> Subject to usual string-to-floating-point conversion exceptions where applicable. </para>
		/// </summary>
		/// <param name="config_switch_char_">Switch for the config argument to parse into a floating-point.</param>
		/// <returns>Specified config argument parsed into a floating-point.</returns>
		template<EmuConcepts::FloatingPoint OutFP_>
		[[nodiscard]] inline auto ToFloatingPoint(const char_type& config_switch_char_) const
			-> typename std::remove_cvref<OutFP_>::type
		{
			return ToFloatingPoint<OutFP_>(this->translate_switch_to_full_name(config_switch_char_));
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
			if (this->try_get_config_arg(config_name_, &p_arg_value))
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
			return TryToFloatingPoint<OutFP_>(this->translate_switch_to_full_name(config_switch_char_));
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
			if (this->try_get_config_arg(config_name_, &p_arg_value))
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
			return TryToFloatingPoint<OutFP_>(this->translate_switch_to_full_name(config_switch_char_), std::forward<OutIfNotFound_>(out_if_not_found_));
		}

		/// <summary>
		/// <para> Converts the specified config arg via the provided custom conversion function. </para>
		/// <para> The conversion function must be invocable with a constant reference to this parser's string_type, however it does not have any return requirements. </para>
		/// <para> If `get_config_arg` is an unsuccessful operation, this will throw an exception. </para>
		/// </summary>
		/// <param name="config_name_">Name of the config argument to parse via the custom conversion function.</param>
		/// <param name="conversion_func_">Function which is invocable when passed a constant reference to this parser's string_type. May return anything.</param>
		/// <returns>Result of the passed conversion function when invoked with the specified config argument.</returns>
		template<class ConversionFunc_>
		requires(std::is_invocable_v<ConversionFunc_, const string_type&>)
		[[nodiscard]] inline decltype(auto) Convert(const string_type& config_name_, ConversionFunc_&& conversion_func_) const
		{
			const string_type& config_string = this->get_config_arg(config_name_);
			return std::forward<ConversionFunc_>(conversion_func_)(config_string);
		}

		/// <summary>
		/// <para> Converts the specified config switch via the provided custom conversion function. </para>
		/// <para> The passed switch will be automatically translated to its full name. </para>
		/// <para> The conversion function must be invocable with a constant reference to this parser's string_type, however it does not have any return requirements. </para>
		/// <para> If `get_config_arg` is an unsuccessful operation, this will throw an exception. </para>
		/// </summary>
		/// <param name="config_switch_char_">Switch for the config argument to parse via the custom conversion function.</param>
		/// <param name="conversion_func_">Function which is invocable when passed a constant reference to this parser's string_type. May return anything.</param>
		/// <returns>Result of the passed conversion function when invoked with the specified config argument.</returns>
		template<class ConversionFunc_>
		requires(std::is_invocable_v<ConversionFunc_, const string_type&>)
		[[nodiscard]] inline decltype(auto) Convert(const char_type& config_switch_char_, ConversionFunc_&& conversion_func_) const
		{
			return Convert(this->translate_switch_to_full_name(config_switch_char_), std::forward<conversion_func_>(conversion_func_));
		}

		/// <summary>
		/// <para> Converts the specified config arg via the provided custom conversion function. </para>
		/// <para>
		///		The conversion function must be invocable with a constant reference to this parser's string_type and also invocable with no arguments, but it does not have any return requirements. 
		///		However, both required signatures must return the same type.
		/// </para>
		/// <para> If `get_config_arg` is an unsuccessful operation, this will throw an exception. </para>
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
			if (this->try_get_config_arg(config_name_, &p_arg_value))
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
		/// <para> If `get_config_arg` is an unsuccessful operation, this will throw an exception. </para>
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
			return TryConvert(this->translate_switch_to_full_name(config_switch_char_), std::forward<conversion_func_>(conversion_func_));
		}

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
		inline void ValidateParsedConfigArgs(ValidationFunc_&& validation_func_, const std::size_t removed_count_hint_ = 0)
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

		template<bool IncludeDefaults_ = true>
		inline std::ostream& append_to_stream(std::ostream& str_) const
		{
			const string_type group_opener = ": {\n";
			const string_type group_closer = "\n}\n";
			const string_type single_indent = "    ";

			str_ << "Basic arguments";
			str_ << group_opener;
			append_non_config_args_to_stream(str_, single_indent);
			str_ << group_closer;

			str_ << "Config arguments";
			str_ << group_opener;
			append_config_args_to_stream(str_, single_indent);
			str_ << group_closer;

			if constexpr (IncludeDefaults_)
			{
				str_ << "Default arguments";
				str_ << group_opener;
				append_default_args_to_stream(str_, single_indent);
				str_ << group_closer;
			}

			return str_;
		}

		inline std::ostream& append_non_config_args_to_stream(std::ostream& str_) const
		{
			return _append_basic_collection_to_stream(str_, parsed_non_config_args, _underlying_no_indent());
		}

		template<class Indent_>
		inline std::ostream& append_non_config_args_to_stream(std::ostream& str_, const Indent_& indent_) const
		{
			return _append_basic_collection_to_stream(str_, parsed_non_config_args, indent_);
		}

		inline std::ostream& append_config_args_to_stream(std::ostream& str_) const
		{
			return _append_config_map_to_stream(str_, parsed_config_args, _underlying_no_indent());
		}

		template<class Indent_>
		inline std::ostream& append_config_args_to_stream(std::ostream& str_, const Indent_& indent_) const
		{
			return _append_config_map_to_stream(str_, parsed_config_args, indent_);
		}

		inline std::ostream& append_default_args_to_stream(std::ostream& str_) const
		{
			return _append_config_map_to_stream(str_, default_config_args, _underlying_no_indent());
		}

		template<class Indent_>
		inline std::ostream& append_default_args_to_stream(std::ostream& str_, const Indent_& indent_) const
		{
			return _append_config_map_to_stream(str_, default_config_args, indent_);
		}

	private:
		struct _underlying_no_indent {};

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

		template<class Indent_>
		static inline std::ostream& _append_config_map_to_stream(std::ostream& str_, const config_args_map_type& config_map_, const Indent_& indent_)
		{
			auto it = config_map_.begin();
			auto end = config_map_.end();
			if (it != end)
			{
				_append_indent(str_, indent_);
				str_ << it->first;
				str_ << '=';
				str_ << it->second;
				++it;
				while (it != end)
				{
					str_ << '\n';
					_append_indent(str_, indent_);
					str_ << it->first;
					str_ << '=';
					str_ << it->second;
					++it;
				}
			}
			return str_;
		}

		template<class Indent_, class Collection_>
		static inline std::ostream& _append_basic_collection_to_stream(std::ostream& str_, const Collection_& basic_collection_, const Indent_& indent_)
		{
			auto it = basic_collection_.begin();
			auto end = basic_collection_.end();
			if (it != end)
			{
				_append_indent(str_, indent_);
				str_ << (*it);
				++it;
				while (it != end)
				{
					str_ << '\n';
					_append_indent(str_, indent_);
					str_ << (*it);
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
					this->set_config_value<true>(std::move(current_config_arg_name), value_);
				}
				else if(is_switch_config_arg_)
				{
					this->_set_multiple_switch_args(current_config_arg_name, value_);
				}
			}
		}

		inline void _set_multiple_switch_args(const string_type& switch_chars_array_, const std::string& value_)
		{
			for (const auto& switch_char : switch_chars_array_)
			{
				this->set_config_value<true>(this->translate_switch_to_full_name(switch_char), value_);
			}
		}

		static inline bool _determine_config_arg_type(const std::string& arg_string_, std::string& out_current_config_arg_name_, bool& is_switch_config_arg_, bool& is_full_name_config_arg_)
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

		config_args_map_type parsed_config_args;
		const config_args_map_type default_config_args;
		switch_to_full_name_map_type switch_to_full_name_map;
		std::vector<std::string> parsed_non_config_args;
	};
}

#endif

#ifndef EMU_MATH_NEW_VECTOR_SET_UNDERLYING_H_INC_
#define EMU_MATH_NEW_VECTOR_SET_UNDERLYING_H_INC_ 1

#include "_vector_tmp.h"
#include "_vector_get_underlying.h"

namespace EmuMath::Helpers::_vector_underlying
{
	template<std::size_t Index_, typename...Args_, std::size_t Size_, typename T_>
	constexpr inline void _vector_set_scalar(EmuMath::NewVector<Size_, T_>& out_vector_, Args_&&...args_)
	{
		out_vector_.template Set<Index_, Args_...>(std::forward<Args_>(args_)...);
	}

	template<std::size_t Index_, std::size_t End_, class Arg_, std::size_t Size_, typename T_>
	constexpr inline void _vector_set_all_execution(EmuMath::NewVector<Size_, T_>& out_vector_, Arg_& arg_)
	{
		using lhs_vector_type = EmuMath::NewVector<Size_, T_>;
		if constexpr (Index_ < End_)
		{
			_vector_set_scalar<Index_, Arg_&>(out_vector_, arg_);
			_vector_set_all_execution<Index_ + 1, End_, Arg_>(out_vector_, arg_);
		}
	}

	template<std::size_t BeginIndex_, std::size_t EndIndex_, class Arg_, std::size_t Size_, typename T_>
	constexpr inline void _vector_set_all(EmuMath::NewVector<Size_, T_>& out_vector_, Arg_&& arg_)
	{
		using lhs_vector_type = EmuMath::NewVector<Size_, T_>;

		if constexpr (BeginIndex_ < lhs_vector_type::size)
		{
			// Clamp into a valid range to allow easy default arguments
			constexpr std::size_t to_index_ = (EndIndex_ >= lhs_vector_type::size) ? lhs_vector_type::size : EndIndex_;
			if constexpr (BeginIndex_ <= to_index_)
			{
				if constexpr (lhs_vector_type::contains_ref)
				{
					if constexpr (std::is_rvalue_reference_v<Arg_> || !std::is_reference_v<Arg_>)
					{
						static_assert(false, "Attempted to set all elements in a specified range within a reference-containing EmuMath Vector via an rvalue-reference (e.g. Arg_&&), which will result in a dangling reference; as such, this behaviour is prohibited.");
					}
					else
					{
						if constexpr (!lhs_vector_type::contains_const_ref)
						{
							if constexpr (std::is_const_v<Arg_>)
							{
								static_assert(false, "Attempted to set all elements in a specified range within a const-reference-containing EmuMath Vector via a constant arg_. To maintain const-safety, this behaviour is prohibited.");
							}
							else
							{
								_vector_set_all_execution<BeginIndex_, to_index_>(out_vector_, arg_);
							}
						}
						else
						{
							_vector_set_all_execution<BeginIndex_, to_index_>(out_vector_, arg_);
						}
					}
				}
				else
				{
					using lhs_stored_type = typename lhs_vector_type::stored_type;
					if constexpr (std::is_assignable_v<lhs_stored_type, Arg_>)
					{
						_vector_set_all_execution<BeginIndex_, to_index_>(out_vector_, arg_);
					}
					else if constexpr (std::is_convertible_v<Arg_, lhs_stored_type>)
					{
						lhs_stored_type converted_arg_ = static_cast<lhs_stored_type>(std::forward<Arg_>(arg_));
						_vector_set_all_execution<BeginIndex_, to_index_>(out_vector_, converted_arg_);
					}
					else if constexpr (std::is_constructible_v<lhs_stored_type, Arg_>)
					{
						lhs_stored_type constucted_arg_(std::forward<Arg_>(arg_));
						_vector_set_all_execution<BeginIndex_, to_index_>(out_vector_, constucted_arg_);
					}
					else
					{
						static_assert(false, "Attempted to set all elements in a specified range within an EmuMath Vector via a single argument, but the Vector's stored_type cannot be assigned, constructed, or converted-to from the provided arg_ type.");
					}
				}
			}
			else
			{
				static_assert(false, "Attempted to set all elements in a specified range within an EmuMath Vector via a single argument, but the provided BeginIndex_ exceeds the provided EndIndex_.");
			}
		}
	}

	template<std::size_t Index_, std::size_t EndIndex_, class VectorArg_, std::size_t Size_, typename T_>
	constexpr inline void _vector_set_vector_move(EmuMath::NewVector<Size_, T_>& out_vector_, VectorArg_&& in_vector_arg_)
	{
		using lhs_vector_type = EmuMath::NewVector<Size_, T_>;
		if constexpr (Index_ < EndIndex_)
		{
			using rhs_vector_type = EmuCore::TMP::remove_ref_cv_t<VectorArg_>;
			if constexpr (Index_ < rhs_vector_type::size)
			{
				_vector_set_scalar<Index_>(out_vector_, std::move(_vector_get<Index_>(in_vector_arg_)));
				_vector_set_vector_move<Index_ + 1, EndIndex_>(out_vector_, std::move(in_vector_arg_));
			}
			else
			{
				auto empty_value_ = _vector_get_non_contained_value<rhs_vector_type>();
				_vector_set_all_execution<Index_, EndIndex_>(out_vector_, empty_value_);
			}
		}
	}

	template<std::size_t Index_, std::size_t EndIndex_, class VectorArg_, std::size_t Size_, typename T_>
	constexpr inline void _vector_set_vector_copy(EmuMath::NewVector<Size_, T_>& out_vector_, VectorArg_& in_vector_arg_)
	{
		using lhs_vector_type = EmuMath::NewVector<Size_, T_>;
		if constexpr (Index_ < EndIndex_)
		{
			using rhs_vector_type = EmuCore::TMP::remove_ref_cv_t<VectorArg_>;
			if constexpr (Index_ < rhs_vector_type::size)
			{
				_vector_set_scalar<Index_>(out_vector_, _vector_get<Index_>(in_vector_arg_));
				_vector_set_vector_copy<Index_ + 1, EndIndex_>(out_vector_, in_vector_arg_);
			}
			else
			{
				auto empty_value_ = _vector_get_non_contained_value<rhs_vector_type>();
				_vector_set_all_execution<Index_, EndIndex_>(out_vector_, empty_value_);
			}
		}
	}

	template<bool SetAll_, class VectorArg_, std::size_t Size_, typename T_>
	constexpr inline void _vector_set_vector(EmuMath::NewVector<Size_, T_>& out_vector_, VectorArg_& vector_arg_)
	{
		if constexpr (EmuMath::TMP::is_emu_new_vector_v<VectorArg_>)
		{
			using lhs_vector_type = EmuMath::NewVector<Size_, T_>;
			using rhs_vector_type = EmuCore::TMP::remove_ref_cv_t<VectorArg_>;

			// Set all indices in out_vector_ if SetAll_ is true, otherwise only go up to the lowest end index.
			constexpr std::size_t end_index_ = SetAll_ ? lhs_vector_type::size : EmuMath::TMP::smallest_vector_t<lhs_vector_type, rhs_vector_type>::size;

			if constexpr (lhs_vector_type::contains_ref)
			{
				if constexpr (lhs_vector_type::size > rhs_vector_type::size)
				{
					static_assert(false, "Attempted to set an EmuMath Vector containing references via a Vector containing less elements than itself. This behaviour will result in dangling references, and as such is prohibited.");
				}
				else
				{
					if constexpr (!lhs_vector_type::contains_const_ref)
					{
						if constexpr (std::is_const_v<VectorArg_> || std::is_const_v<typename rhs_vector_type::value_type>)
						{
							static_assert(false, "Attempted to set an EmuMath Vector containing non-const references via a constant Vector or a Vector with a constant value_type.");
						}
						else
						{
							_vector_set_vector_copy<0, end_index_, VectorArg_>(out_vector_, vector_arg_);
						}
					}
					else
					{
						// Contains const refs, so non-const will be implicitly cast to const
						_vector_set_vector_copy<0, end_index_, VectorArg_>(out_vector_, vector_arg_);
					}
				}
			}
			else
			{
				_vector_set_vector_copy<0, end_index_, VectorArg_>(out_vector_, vector_arg_);
			}
		}
		else
		{
			static_assert(false, "Attempted to set an EmuMath Vector via another Vector, but the provided vector_arg_ was not an EmuMath Vector.");
		}
	}

	template<bool SetAll_, class VectorArg_, std::size_t Size_, typename T_>
	constexpr inline void _vector_set_vector(EmuMath::NewVector<Size_, T_>& out_vector_, VectorArg_&& vector_arg_)
	{
		if constexpr (EmuMath::TMP::is_emu_new_vector_v<VectorArg_>)
		{
			using lhs_vector_type = EmuMath::NewVector<Size_, T_>;
			using rhs_vector_type = EmuCore::TMP::remove_ref_cv_t<VectorArg_>;

			// Set all indices in out_vector_ if SetAll_ is true, otherwise only go up to the lowest end index.
			constexpr std::size_t end_index_ = SetAll_ ? lhs_vector_type::size : EmuMath::TMP::smallest_vector_t<lhs_vector_type, rhs_vector_type>::size;

			using vector_arg_no_ref = std::remove_reference_t<VectorArg_>;
			if constexpr (lhs_vector_type::contains_ref)
			{
				// Ref vectors require additional checks to prevent dangling references
				if constexpr ((!VectorArg_::contains_ref) && (std::is_rvalue_reference_v<VectorArg_> || !std::is_reference_v<VectorArg_>))
				{
					static_assert(false, "Attempted to set an EmuMath Vector containing references via an rvalue-referenced Vector (e.g. Vector&&) which does not contain references. This will result in dangling references, and is prohibited as a result.");
				}
				else
				{
					if constexpr (lhs_vector_type::size > VectorArg_::size)
					{
						static_assert(false, "Attempted to set an EmuMath Vector containing references via a Vector containing less elements than itself. This behaviour will result in dangling references, and as such is prohibited.");
					}
					else
					{
						if constexpr (!lhs_vector_type::contains_const_ref)
						{
							if constexpr (std::is_const_v<VectorArg_> || std::is_const_v<typename VectorArg_::value_type>)
							{
								static_assert(false, "Attempted to set an EmuMath Vector containing non-const references via a constant Vector or a Vector with a constant value_type.");
							}
							else
							{
								// No more checks, safe to take in what we have stored
								if constexpr (std::is_rvalue_reference_v<VectorArg_> || !std::is_reference_v<VectorArg_>)
								{
									_vector_set_vector_move<0, end_index_>(out_vector_, std::forward<vector_arg_no_ref>(vector_arg_));
								}
								else
								{
									_vector_set_vector_copy<0, end_index_>(out_vector_, vector_arg_);
								}
							}
						}
						else
						{
							// Const-containing vector means we can take anything in, since non-const is implicitly cast to const
							if constexpr (std::is_rvalue_reference_v<VectorArg_> || !std::is_reference_v<VectorArg_>)
							{
								_vector_set_vector_move<0, end_index_>(out_vector_, std::forward<vector_arg_no_ref>(vector_arg_));
							}
							else
							{
								_vector_set_vector_copy<0, end_index_>(out_vector_, vector_arg_);
							}
						}
					}
				}
			}
			else
			{
				// No additional checks needed for non-ref vectors.
				if constexpr (std::is_rvalue_reference_v<VectorArg_> || !std::is_reference_v<VectorArg_>)
				{
					_vector_set_vector_move<0, end_index_>(out_vector_, std::forward<vector_arg_no_ref>(vector_arg_));
				}
				else
				{
					_vector_set_vector_copy<0, end_index_>(out_vector_, vector_arg_);
				}
			}
		}
		else
		{
			static_assert(false, "Attempted to set an EmuMath Vector via another Vector, but the provided vector_arg_ was not an EmuMath Vector.");
		}
	}
}

#endif

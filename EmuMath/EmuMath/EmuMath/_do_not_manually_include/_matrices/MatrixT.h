#ifndef EMU_MATH_MATRIX_T_H_INC_
#define EMU_MATH_MATRIX_T_H_INC_

#include "../../Vector.h"

namespace EmuMath
{
	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_ = true>
	struct Matrix
	{
	public:
		static constexpr std::size_t num_columns = NumColumns_;
		static constexpr std::size_t num_rows = NumRows_;
		static constexpr bool is_column_major = ColumnMajor_;
		static constexpr bool is_row_major = !is_column_major;

		static constexpr std::size_t num_major_elements = is_column_major ? num_columns : num_rows;
		static constexpr std::size_t num_non_major_elements = is_column_major ? num_rows : num_columns;

		/// <summary> The type contained within this matrix. </summary>
		using contained_type = T_;
		/// <summary> Boolean indicating if this matrix contains reference wrapping types. </summary>
		static constexpr bool contains_reference_wrappers = EmuCore::TMPHelpers::is_reference_wrapper<contained_type>::value;
		/// <summary> The raw value_type within this matrix before its const qualifier is forcibly removed. </summary>
		using raw_value_type = typename EmuCore::TMPHelpers::get_reference_wrapper_contained_type<contained_type>::type;
		/// <summary> Value type of the items stored within this matrix, without const qualifiers where applicable. </summary>
		using value_type = std::remove_const_t<raw_value_type>;
		/// <summary> The preferred floating point type for this matrix. Float if this matrix contains non-floating-point types, otherwise matches value_type. </summary>
		using preferred_floating_point = EmuCore::TMPHelpers::first_floating_point_t<value_type, float>;
		/// <summary> Boolean indicating if the reference wrappers within this matrix contain constant references. Always false if contains_reference_wrappers is false. </summary>
		static constexpr bool contains_const_reference_wrappers = std::is_const_v<raw_value_type> && contains_reference_wrappers;
		/// <summary> Boolean indicating if the reference wrappers within this matrix contain non-constant references. Always false if contains_reference_wrappers is false. </summary>
		static constexpr bool contains_non_const_reference_wrappers = contains_reference_wrappers && !contains_const_reference_wrappers;

		/// <summary> Boolean indcating if this matrix's values are integral. </summary>
		static constexpr bool has_integral_elements = std::is_integral_v<std::remove_cv_t<value_type>>;
		/// <summary> Boolean indcating if this matrix's values are floating-points. </summary>
		static constexpr bool has_floating_point_elements = std::is_floating_point_v<std::remove_cv_t<value_type>>;
		/// <summary> Boolean indicating if this matrix's values are constant. </summary>
		static constexpr bool has_const_values = std::is_const_v<raw_value_type>;

		using data_storage_type = EmuMath::Vector<num_major_elements, EmuMath::Vector<num_non_major_elements, contained_type>>;
		using random_access_vector_contained_type = std::conditional_t<contains_reference_wrappers, contained_type, EmuMath::InternalVectorReference<contained_type>>;
		using const_random_access_vector_contained_type = std::conditional_t
		<
			contains_reference_wrappers,
			std::conditional_t<contains_const_reference_wrappers, contained_type, EmuMath::InternalVectorReference<const value_type>>, 
			EmuMath::InternalVectorReference<const contained_type>
		>;

		using random_access_row = EmuMath::Vector<num_columns, random_access_vector_contained_type>;
		using random_access_column = EmuMath::Vector<num_rows, random_access_vector_contained_type>;
		using const_random_access_row = EmuMath::Vector<num_columns, const_random_access_vector_contained_type>;
		using const_random_access_column = EmuMath::Vector<num_rows, const_random_access_vector_contained_type>;

#pragma region CONSTRUCTORS
		constexpr Matrix() : data_()
		{
		}
		constexpr Matrix(data_storage_type& toCopy_) : data_(toCopy_)
		{
		}
		constexpr Matrix(const data_storage_type& toCopy_) : data_(toCopy_)
		{
		}
		template<typename...Vectors_, typename RequiresNumMajorArgs_ = std::enable_if_t<sizeof...(Vectors_) == num_major_elements>>
		constexpr Matrix(Vectors_&&...major_vectors_) : data_(std::forward<Vectors_>(major_vectors_)...)
		{
			static_assert(std::is_constructible_v<data_storage_type, Vectors_...>, "Attempted to construct an EmuMath matrix via a template constructors, using Vector data which cannot be used to construct the matrix's underlying data.");
		}
#pragma endregion

#pragma region RANDOM_ACCESS
		template<std::size_t RowIndex_>
		constexpr inline random_access_row GetRow()
		{
			if constexpr (RowIndex_ < num_rows)
			{
				if constexpr (is_row_major)
				{
					return random_access_row(data_[RowIndex_]);
				}
				else
				{
					const_random_access_row out_ = const_random_access_row();
					_assign_non_major_reference<RowIndex_, 0, const_random_access_row>(out_);
					return out_;
				}
			}
			else
			{
				static_assert(false, "Attempted to access a row within an EmuMath matrix, but an invalid row index was provided.");
			}
		}
		template<std::size_t RowIndex_>
		constexpr inline const_random_access_row GetRow() const
		{
			return this->template GetRowConst<RowIndex_>();
		}
		template<std::size_t RowIndex_>
		constexpr inline const_random_access_row GetRowConst() const
		{
			if constexpr (RowIndex_ < num_rows)
			{
				if constexpr (is_row_major)
				{
					return const_random_access_row(data_[RowIndex_]);
				}
				else
				{
					const_random_access_row out_ = const_random_access_row();
					_assign_non_major_reference<RowIndex_, 0, const_random_access_row>(out_);
					return out_;
				}
			}
			else
			{
				static_assert(false, "Attempted to access a row within an EmuMath matrix, but an invalid row index was provided.");
			}
		}

		template<std::size_t ColumnIndex_>
		constexpr inline const_random_access_column GetColumn()
		{
			if constexpr (ColumnIndex_ < num_rows)
			{
				if constexpr (is_column_major)
				{
					return random_access_row(data_[ColumnIndex_]);
				}
				else
				{
					const_random_access_row out_ = const_random_access_row();
					_assign_non_major_reference<ColumnIndex_, 0, const_random_access_row>(out_);
					return out_;
				}
			}
			else
			{
				static_assert(false, "Attempted to access a column within an EmuMath matrix, but an invalid column index was provided.");
			}
		}
		template<std::size_t ColumnIndex_>
		constexpr inline const_random_access_column GetColumn() const
		{
			return this->template GetColumnConst<ColumnIndex_>();
		}
		template<std::size_t ColumnIndex_>
		constexpr inline const_random_access_column GetColumnConst() const
		{
			if constexpr (ColumnIndex_ < num_rows)
			{
				if constexpr (is_column_major)
				{
					return const_random_access_column(data_[ColumnIndex_]);
				}
				else
				{
					const_random_access_column out_ = const_random_access_column();
					_assign_non_major_reference<ColumnIndex_, 0, const_random_access_column>(out_);
					return out_;
				}
			}
			else
			{
				static_assert(false, "Attempted to access a column within an EmuMath matrix, but an invalid column index was provided.");
			}
		}
#pragma endregion

		data_storage_type data_;

	private:
		template<std::size_t NonMajorIndex_, std::size_t MajorIndex_, typename Out_>
		constexpr inline void _assign_non_major_reference(Out_& out_)
		{
			if constexpr (MajorIndex_ < num_major_elements)
			{
				out_.template Set<MajorIndex_>(data_.template at<MajorIndex_>().template at<NonMajorIndex_>());
				_assign_non_major_reference<NonMajorIndex_, MajorIndex_ + 1, Out_>(out_);
			}
		}
		template<std::size_t NonMajorIndex_, std::size_t MajorIndex_, typename Out_>
		constexpr inline void _assign_non_major_reference(Out_& out_) const
		{
			if constexpr (MajorIndex_ < num_major_elements)
			{
				out_.template Set<MajorIndex_>(data_.template at<MajorIndex_>().template at<NonMajorIndex_>());
				_assign_non_major_reference<NonMajorIndex_, MajorIndex_ + 1, Out_>(out_);
			}
		}
	};
}

template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_, std::size_t Index_ = 0>
inline std::ostream& operator<<(std::ostream& str_, const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
{
	if constexpr (Index_ < EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::num_rows)
	{
		str_ << matrix_.GetRowConst<Index_>();
		if constexpr ((Index_ + 1) < EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::num_rows)
		{
			str_ << "\n";
			return operator<<<NumColumns_, NumRows_, T_, ColumnMajor_, Index_ + 1>(str_, matrix_);
		}
		else
		{
			return str_;
		}
	}
	else
	{
		return str_;
	}
}

#endif

#ifndef EMU_MATH_FAST_MATRIX_ROTATION_3D_H_INC_
#define EMU_MATH_FAST_MATRIX_ROTATION_3D_H_INC_ 1

#include "_common_fast_matrix_helper_includes.h"

namespace EmuMath::Helpers
{
	template
	<
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_,
		bool OutColumnMajor_ = true, std::size_t OutRegisterWidth_ = 128, EmuConcepts::Arithmetic QuaternionT_
	>
	[[nodiscard]] constexpr inline auto fast_matrix_make_rotation_3d(const EmuMath::Quaternion<QuaternionT_>& rotation_)
		-> EmuMath::FastMatrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, OutRegisterWidth_>
	{
		return _fast_matrix_underlying::_make_matrix_rotate_3d_quat<EmuMath::FastMatrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, OutRegisterWidth_>>
		(
			rotation_
		);
	}

	template<typename OutT_, bool OutColumnMajor_ = true, std::size_t OutRegisterWidth_ = 128, EmuConcepts::Arithmetic QuaternionT_>
	[[nodiscard]] constexpr inline auto fast_matrix_make_rotation_3d(const EmuMath::Quaternion<QuaternionT_>& rotation_)
		-> EmuMath::FastMatrix<4, 4, OutT_, OutColumnMajor_, OutRegisterWidth_>
	{
		return _fast_matrix_underlying::_make_matrix_rotate_3d_quat<EmuMath::FastMatrix<4, 4, OutT_, OutColumnMajor_, OutRegisterWidth_>>
		(
			rotation_
		);
	}

	template
	<
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_,
		bool OutColumnMajor_ = true, std::size_t OutRegisterWidth_ = 128, EmuConcepts::EmuFastQuaternion FastQuaternion_
	>
	[[nodiscard]] constexpr inline auto fast_matrix_make_rotation_3d(FastQuaternion_&& rotation_)
		-> EmuMath::FastMatrix<4, 4, OutT_, OutColumnMajor_, OutRegisterWidth_>
	{
		return _fast_matrix_underlying::_make_matrix_rotate_3d_quat<EmuMath::FastMatrix<4, 4, OutT_, OutColumnMajor_, OutRegisterWidth_>>
		(
			std::forward<FastQuaternion_>(rotation_)
		);
	}

	template<typename OutT_, bool OutColumnMajor_ = true, std::size_t OutRegisterWidth_ = 128, EmuConcepts::EmuFastQuaternion FastQuaternion_>
	[[nodiscard]] constexpr inline auto fast_matrix_make_rotation_3d(FastQuaternion_&& rotation_)
		-> EmuMath::FastMatrix<4, 4, OutT_, OutColumnMajor_, OutRegisterWidth_>
	{
		return _fast_matrix_underlying::_make_matrix_rotate_3d_fast_quat<EmuMath::FastMatrix<4, 4, OutT_, OutColumnMajor_, OutRegisterWidth_>>
		(
			std::forward<FastQuaternion_>(rotation_)
		);
	}
}

#endif

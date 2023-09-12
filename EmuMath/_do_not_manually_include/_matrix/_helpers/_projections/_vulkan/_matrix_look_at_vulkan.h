#ifndef EMU_MATH_MATRIX_PROJECTIONS_LOOK_AT_VK_H_INC_
#define EMU_MATH_MATRIX_PROJECTIONS_LOOK_AT_VK_H_INC_ 1

#include "../../_common_matrix_helper_includes.h"

namespace EmuMath::Helpers
{
	/// <summary>
	/// <para> Creates a view matrix representing a camera looking at a position from a different position. </para>
	/// <para> The size of the output Matrix may be omitted, in which case it will default to 4x4. </para>
	/// <para> The Matrix will be designed for a left-hand coordinate system. For a right-hand coordinate system, use `matrix_look_at_rh_vk`. </para>
	/// </summary>
	/// <param name="from_">Vector representing a point in 3D space from which the viewer is looking (e.g. the camera position).</param>
	/// <param name="to_">Vector representing a point in 3D space at which the viewer is looking (e.g. the target position).</param>
	/// <param name="up_">Vector representing the direction of the transformed up Vector (e.g. where the top of the camera is pointing).</param>
	/// <returns>View Matrix of the specified type intended for use with Vulkan using a left-hand coordinate system.</returns>
	template
	<
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_ = true,
		std::size_t FromSize_, typename FromT_, std::size_t ToSize_, typename ToT_, std::size_t UpSize_, typename UpT_
	>
	[[nodiscard]] constexpr inline auto matrix_look_at_lh_vk
	(
		const EmuMath::Vector<FromSize_, FromT_>& from_,
		const EmuMath::Vector<ToSize_, ToT_>& to_,
		const EmuMath::Vector<UpSize_, UpT_>& up_
	) -> EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
	{
		return _matrix_underlying::_make_look_at_vk<EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>, false, true>
		(
			from_,
			to_,
			up_
		);
	}

	template<typename OutT_, bool OutColumnMajor_ = true, std::size_t FromSize_, typename FromT_, std::size_t ToSize_, typename ToT_, std::size_t UpSize_, typename UpT_>
	[[nodiscard]] constexpr inline auto matrix_look_at_lh_vk
	(
		const EmuMath::Vector<FromSize_, FromT_>& from_,
		const EmuMath::Vector<ToSize_, ToT_>& to_,
		const EmuMath::Vector<UpSize_, UpT_>& up_
	)
		-> EmuMath::Matrix<4, 4, OutT_, OutColumnMajor_>
	{
		return _matrix_underlying::_make_look_at_vk<EmuMath::Matrix<4, 4, OutT_, OutColumnMajor_>, false, true>
		(
			from_,
			to_,
			up_
		);
	}

	/// <summary>
	/// <para> Creates a view matrix representing a camera looking at a position from a different position. </para>
	/// <para> The size of the output Matrix may be omitted, in which case it will default to 4x4. </para>
	/// <para> The Matrix will be designed for a right-hand coordinate system. For a left-hand coordinate system, use `matrix_look_at_lh_vk`. </para>
	/// </summary>
	/// <param name="from_">Vector representing a point in 3D space from which the viewer is looking (e.g. the camera position).</param>
	/// <param name="to_">Vector representing a point in 3D space at which the viewer is looking (e.g. the target position).</param>
	/// <param name="up_">Vector representing the direction of the transformed up Vector (e.g. where the top of the camera is pointing).</param>
	/// <returns>View Matrix of the specified type intended for use with Vulkan using a right-hand coordinate system.</returns>
	template
	<
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_ = true,
		std::size_t FromSize_, typename FromT_, std::size_t ToSize_, typename ToT_, std::size_t UpSize_, typename UpT_
	>
	[[nodiscard]] constexpr inline auto matrix_look_at_rh_vk
	(
		const EmuMath::Vector<FromSize_, FromT_>& from_,
		const EmuMath::Vector<ToSize_, ToT_>& to_,
		const EmuMath::Vector<UpSize_, UpT_>& up_
	) -> EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
	{
		return _matrix_underlying::_make_look_at_vk<EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>, false, false>
		(
			from_,
			to_,
			up_
		);
	}

	template<typename OutT_, bool OutColumnMajor_ = true, std::size_t FromSize_, typename FromT_, std::size_t ToSize_, typename ToT_, std::size_t UpSize_, typename UpT_>
	[[nodiscard]] constexpr inline auto matrix_look_at_rh_vk
	(
		const EmuMath::Vector<FromSize_, FromT_>& from_,
		const EmuMath::Vector<ToSize_, ToT_>& to_,
		const EmuMath::Vector<UpSize_, UpT_>& up_
	)
		-> EmuMath::Matrix<4, 4, OutT_, OutColumnMajor_>
	{
		return _matrix_underlying::_make_look_at_vk<EmuMath::Matrix<4, 4, OutT_, OutColumnMajor_>, false, false>
		(
			from_,
			to_,
			up_
		);
	}
}

#endif

#ifndef EMU_CORE_VARIADIC_HELPERS_H_INC_
#define EMU_CORE_VARIADIC_HELPERS_H_INC_ 1

#include <utility>

namespace EmuCore::TMP
{
	template<std::size_t Offset_, std::size_t Size_>
	struct offset_index_sequence_maker
	{
	private:
		template<std::size_t Remaining_, std::size_t Current_, typename Previous_>
		struct _maker
		{
			using type = void;
		};
		template<std::size_t Remaining_, std::size_t Current_, std::size_t...PreviousIndices_>
		struct _maker<Remaining_, Current_, std::index_sequence<PreviousIndices_...>>
		{
			using type = typename _maker<Remaining_ - 1, Current_ + 1, std::index_sequence<PreviousIndices_..., Current_>>::type;
		};
		template<std::size_t Current_, std::size_t...PreviousIndices_>
		struct _maker<0, Current_, std::index_sequence<PreviousIndices_...>>
		{
			using type = std::index_sequence<PreviousIndices_...>;
		};

	public:
		using type = typename _maker<Size_, Offset_, std::index_sequence<>>::type;
	};

	template<std::size_t Offset_, std::size_t Size_>
	using make_offset_index_sequence = typename offset_index_sequence_maker<Offset_, Size_>::type;
}

#endif

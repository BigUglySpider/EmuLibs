#ifndef EMU_CORE_RING_BUFFER_H_INC_
#define EMU_CORE_RING_BUFFER_H_INC_ 1

#include <array>
#include <stdexcept>
#include <vector>

#include "../ArithmeticHelpers/BitHelpers.h"
#include "../CommonConcepts/CommonRequirements.h"
#include "../TMPHelpers/Values.h"

namespace EmuCore
{
	/// <summary>
	/// <para> Contiguous buffer which may be pushed to indefinitely, looping back to its contiguous start every time it passes the final index. </para>
	/// <para> The provided size is the number of physical elements that the buffer stores and will write to before looping back to index 0. </para>
	/// <para> If `UsesHeap_` is true, this will allocate storage on the heap. Otherwise, storage will be within the object itself. </para>
	/// </summary>
	template<std::size_t BufferSize_, typename T_, bool UsesHeap_ = false>
	class RingBuffer
	{
#pragma region STATIC_INFO_AND_ALIASES
	public:
		using this_type = RingBuffer<BufferSize_, T_, UsesHeap_>;
		using value_type = T_;
		/// <summary>
		/// <para> The number of unique items contained within this Ring Buffer type. </para>
		/// </summary>
		static constexpr std::size_t size = BufferSize_;
		/// <summary>
		/// <para> If true, this Ring Buffer's data is always stored on the heap; otherwise it is stored directly within this Ring Buffer type. </para>
		/// </summary>
		static constexpr bool uses_heap = UsesHeap_;
		/// <summary>
		/// <para> 
		///		True if the size of this Ring Buffer is a power of 2. 
		///		Being a size that is a power of 2 allows certain optimisations to be performed for index manipulation.
		/// </para>
		/// </summary>
		static constexpr bool size_is_power_of_2 = EmuCore::ArithmeticHelpers::is_integral_power_of_2(size);
		/// <summary>
		/// <para> The largest index that can be used to access this Ring Buffer's data. </para>
		/// </summary>
		static constexpr std::size_t final_index = size - 1;

	private:
		using storage_type = typename std::conditional<uses_heap, std::vector<T_>, std::array<T_, BufferSize_>>::type;
		[[nodiscard]] static constexpr inline storage_type _make_data()
		{
			if constexpr (uses_heap)
			{
				return storage_type(size);
			}
			else
			{
				return storage_type();
			}
		}

	public:
		using iterator = typename storage_type::iterator;
		using const_iterator = typename storage_type::const_iterator;
		using reverse_iterator = typename storage_type::reverse_iterator;
		using const_reverse_iterator = typename storage_type::const_reverse_iterator;
#pragma endregion

#pragma region CONSTRUCTORS
	public:
		/// <summary>
		/// <para> Constructs this Ring Buffer with its data defaulted, and pointing the next index to write to at the first contiguous item. </para>
		/// </summary>
		constexpr RingBuffer() noexcept(!uses_heap) :
			_next_index(0),
			_data(_make_data())
		{
		};
		/// <summary>
		/// <para> Copies the data of the passed Ring Buffer into a new Ring Buffer. </para>
		/// </summary>
		constexpr RingBuffer(const RingBuffer<BufferSize_, T_, UsesHeap_>&) noexcept(!uses_heap) = default;

		/// <summary>
		/// <para> Moves the data of the passed Ring Buffer into a new Ring Buffer. </para>
		/// </summary>
		constexpr RingBuffer(RingBuffer<BufferSize_, T_, UsesHeap_>&&) noexcept = default;
#pragma endregion

#pragma region ASSIGNMENT_AND_INSERTION
	public:
		constexpr RingBuffer<BufferSize_, T_, UsesHeap_>& operator=(const RingBuffer<BufferSize_, T_, UsesHeap_>&) noexcept(!uses_heap) = default;
		constexpr RingBuffer<BufferSize_, T_, UsesHeap_>& operator=(RingBuffer<BufferSize_, T_, UsesHeap_>&&) noexcept = default;

		/// <summary>
		/// <para> Assigns the passed instance of this Ring Buffer's contained type directly to the next item to be written to. </para>
		/// </summary>
		/// <param name="to_push_">Instance of this Ring Buffer's contained type (of any const/reference qualification) to assign to the next item to be written to.</param>
		template<EmuConcepts::UnqualifiedMatch<T_> TArg_>
		constexpr inline void Push(TArg_&& to_push_) noexcept(std::is_nothrow_assignable_v<T_, TArg_&&>)
		{
			_data[_next_index] = std::forward<TArg_>(to_push_);
			Increment();
		}

		/// <summary>
		/// <para> Constructs an instance of this Ring Buffer's contained type and assigns the next item to be written to, using a new item of the type constructed from the passed arguments. </para>
		/// </summary>
		/// <param name="args_for_t_">Arguments used to construct an instance of this Ring Buffer's contained type.</param>
		template<class...ArgsForT_>
		requires(std::is_constructible_v<T_, ArgsForT_&&...>)
		constexpr inline void Emplace(ArgsForT_&&...args_for_t_) noexcept(std::is_nothrow_constructible_v<T_, ArgsForT_&&...> && std::is_nothrow_assignable_v<T_, T_&&>)
		{
			_data[_next_index] = T_(std::forward<ArgsForT_>(args_for_t_)...);
			Increment();
		}
#pragma endregion

#pragma region INDICES
	public:
		/// <summary>
		/// <para> Increments the passed `index_` value as if it is an index used for access within this Ring Buffer. </para>
		/// <para> This is a static function and does not affect an instance of `RingBuffer` directly. </para>
		/// </summary>
		/// <param name="index_">Index to increment.</param>
		/// <returns>`index_ + 1` if it does not exceed the range of this `RingBuffer`; otherwise 0.</returns>
		static constexpr inline std::size_t Increment(std::size_t index_) noexcept
		{
			if constexpr (size_is_power_of_2)
			{
				// Can optimise to a simple add-then-mask op if size is x^2
				// --- Possible as final_index will be all 1 for all valid used bits, and all 0 for invalid bits
				return (index_ + 1) & final_index;
			}
			else
			{
				// Still perform a branchless increment when not x^2, but instead of a single mask we have to compare and multiply the result bool
				return (index_ + 1) * static_cast<std::size_t>(index_ < final_index);
			}
		}

		/// <summary>
		/// <para> Increments the internal index of this Ring Buffer, skipping insertion into the usual element. </para>
		/// <para> In all cases, this Ring Buffer will behave as if it wrote to the skipped index. </para>
		/// </summary>
		constexpr inline void Increment()
		{
			_next_index = Increment(_next_index);
		}

		/// <summary>
		/// <para> Get the index that will be written to next. </para>
		/// </summary>
		/// <returns>Index of the item that will be written to next.</returns>
		[[nodiscard]] constexpr inline std::size_t GetNextIndex() const noexcept
		{
			return _next_index;
		}

		/// <summary>
		/// <para> Get the index that was most recently written to. </para>
		/// </summary>
		/// <returns>Index of the item most recently written to.</returns>
		[[nodiscard]] constexpr inline std::size_t GetMostRecentIndex() const noexcept
		{
			return (_next_index == 0) ? (size - 1) : (_next_index - 1);
		}
#pragma endregion

#pragma region ACCESS
	public:
		/// <summary>
		/// <para> Retrieves a reference to the item at the given index. </para>
		/// <para> No bounds checks are performed by this function. </para>
		/// </summary>
		/// <param name="index_">Index to access.</param>
		/// <returns>Reference to the item at the specified index.</returns>
		[[nodiscard]] constexpr inline value_type& operator[](const std::size_t index_)
		{
			return _data[index_];
		}

		/// <summary>
		/// <para> Retrieves a constant reference to the item at the given index. </para>
		/// <para> No bounds checks are performed by this function. </para>
		/// </summary>
		/// <param name="index_">Index to access.</param>
		/// <returns>Const-qualified reference to the item at the specified index.</returns>
		[[nodiscard]] constexpr inline const value_type& operator[](const std::size_t index_) const
		{
			return _data[index_];
		}

		/// <summary>
		/// <para> Retrieves a reference to the item at the given index. </para>
		/// <para> Throw a `std::out_of_range` exception if the passed index exceeds the greatest index within this buffer. </para>
		/// </summary>
		/// <param name="index_">Index to access.</param>
		/// <returns>Reference to the item at the specified index.</returns>
		[[nodiscard]] constexpr inline value_type& Get(const std::size_t index_)
		{
			if (index_ >= size)
			{
				throw std::out_of_range("Out-of-range index passed to EmuCore::RingBuffer::Get.");
			}
			return _data[index_];
		}

		/// <summary>
		/// <para> Retrieves a constant reference to the item at the given index. </para>
		/// <para> Throw a `std::out_of_range` exception if the passed index exceeds the greatest index within this buffer. </para>
		/// </summary>
		/// <param name="index_">Index to access.</param>
		/// <returns>Const-qualified reference to the item at the specified index.</returns>
		[[nodiscard]] constexpr inline const value_type& Get(const std::size_t index_) const
		{
			return const_cast<this_type*>(this)->Get(index_);
		}

		/// <summary>
		/// <para> Retrieves a reference to the item at the given index. </para>
		/// <para> Triggers a static assertion if the passed index exceeds the greatest index within this buffer. </para>
		/// </summary>
		/// <returns>Reference to the item at the specified index.</returns>
		template<std::size_t Index_>
		[[nodiscard]] constexpr inline value_type& Get() noexcept
		{
			if constexpr (Index_ < size)
			{
				return _data[Index_];
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<std::size_t, Index_>(), "Out-of-range Index passed to EmuCore::RingBuffer::Get<Index_>.");
			}
		}

		/// <summary>
		/// <para> Retrieves a constant reference to the item at the given index. </para>
		/// <para> Triggers a static assertion if the passed index exceeds the greatest index within this buffer. </para>
		/// </summary>
		/// <returns>Const-qualified reference to the item at the specified index.</returns>
		template<std::size_t Index_>
		[[nodiscard]] constexpr inline const value_type& Get() noexcept
		{
			return const_cast<this_type*>(this)->template Get<Index_>();
		}

		/// <summary>
		/// <para> Retrieves a reference to the item which is next-in-line to be written to. </para>
		/// <para> If the item has never been written to, there are no guarantees regarding what the data will be. </para>
		/// </summary>
		/// <returns>Reference to the item next-in-line to be written to.</returns>
		[[nodiscard]] constexpr inline value_type& GetNext() noexcept
		{
			return _data[_next_index];
		}

		/// <summary>
		/// <para> Retrieves a constant reference to the item which is next-in-line to be written to. </para>
		/// <para> If the item has never been written to, there are no guarantees regarding what the data will be. </para>
		/// </summary>
		/// <returns>Const-qualified reference to the item next-in-line to be written to.</returns>
		[[nodiscard]] constexpr inline const value_type& GetNext() const noexcept
		{
			return _data[_next_index];
		}

		/// <summary>
		/// <para> Retrieves a reference to the most recently written to item. </para>
		/// <para> Note that skipped items are considered written to for the purposes of selecting most recent items. </para>
		/// <para> If this buffer has never been written to, there are no guarantees regarding what the data will be. </para>
		/// </summary>
		/// <returns>Reference to the item most recently written to.</returns>
		[[nodiscard]] constexpr inline value_type& GetMostRecent() noexcept
		{
			return _data[GetMostRecentIndex()];
		}

		/// <summary>
		/// <para> Retrieves a constant reference to the most recently written to item. </para>
		/// <para> Note that skipped items are considered written to for the purposes of selecting most recent items. </para>
		/// <para> If this buffer has never been written to, there are no guarantees regarding what the data will be. </para>
		/// </summary>
		/// <returns>Const-qualified reference to the item most recently written to.</returns>
		[[nodiscard]] constexpr inline const value_type& GetMostRecent() const noexcept
		{
			return _data[GetMostRecentIndex()];
		}
#pragma endregion

#pragma region STL_ACCESS
	public:
		[[nodiscard]] constexpr inline iterator begin() noexcept
		{
			return _data.begin();
		}

		[[nodiscard]] constexpr inline const_iterator begin() const noexcept
		{
			return _data.cbegin();
		}

		[[nodiscard]] constexpr inline iterator end() noexcept
		{
			return _data.end();
		}

		[[nodiscard]] constexpr inline const_iterator end() const noexcept
		{
			return _data.cend();
		}

		[[nodiscard]] constexpr inline reverse_iterator rbegin() noexcept
		{
			return _data.rbegin();
		}
		
		[[nodiscard]] constexpr inline const_reverse_iterator rbegin() const noexcept
		{
			return _data.crbegin();
		}

		[[nodiscard]] constexpr inline reverse_iterator rend() noexcept
		{
			return _data.rend();
		}

		[[nodiscard]] constexpr inline const_reverse_iterator rend() const noexcept
		{
			return _data.crend();
		}

		[[nodiscard]] constexpr inline const_iterator cbegin() const noexcept
		{
			return _data.cbegin();
		}

		[[nodiscard]] constexpr inline const_iterator cend() const noexcept
		{
			return _data.cend();
		}

		[[nodiscard]] constexpr inline const_reverse_iterator crbegin() const noexcept
		{
			return _data.crbegin();
		}

		[[nodiscard]] constexpr inline const_reverse_iterator crend() const noexcept
		{
			return _data.crend();
		}

		[[nodiscard]] constexpr inline value_type* data() noexcept
		{
			return _data.data();
		}

		[[nodiscard]] constexpr inline const value_type* data() const noexcept
		{
			return _data.data();
		}
#pragma endregion

#pragma region DATA
	private:
		std::size_t _next_index;
		storage_type _data;
#pragma endregion
	};
}

#endif

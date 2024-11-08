#ifndef EMU_IO_P_OPEN_HPP_INC_
#define EMU_IO_P_OPEN_HPP_INC_ 1

#include <array>
#include <cstdint>
#include <cstdio>
#include <iterator>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>
#include <vector>

#include "../EmuCore/CommonPreprocessor/Compiler.h"

namespace EmuIO
{
	/*
	* @brief Determines the type of iterator that will be input to raw processor functions for a call to 
	*		 `POpen::ProcessRaw` with the passed template parameters to customise the buffer.
	*/
	template<bool UsesHeap, std::size_t BufferLength>
	using popen_raw_iterator_type = typename std::conditional
	<
		UsesHeap,
		std::vector<char>::const_iterator,
		typename std::array<char, (BufferLength <= 2) ? 2 : BufferLength>::const_iterator
	>::type;

	/*
	* @brief Constraint applied to functions input to `POpen::ProcessLines`.
	*        Requires that the type `T` can be invoked when input a reference to a `std::string` (does not have to be constant).
	*/
	template<class T>
	concept POpenLineProcessor = requires(typename std::remove_reference<T>::type& processor, std::string& line)
	{
		{ processor(line) };
	};

	/*
	* @brief Constraint applied to functions input to `POpen::ProcessRaw`.
	*        Requires that the type `T` can be invoked when input two iterators representing the `begin` and `end` (respectively) of the current chunk of raw data.
	*        The iterator types used as input will be identical to `popen_raw_iterator_type<UsesHeap, BufferLength>`.
	*/
	template<class T, bool UsesHeap, std::size_t BufferLength>
	concept POpenRawProcessor = requires(typename std::remove_reference<T>::type& processor, popen_raw_iterator_type<UsesHeap, BufferLength> begin, popen_raw_iterator_type<UsesHeap, BufferLength> end)
	{
		{ processor(begin, end) };
	};

	/*
	* @brief Basic processor that can be passed to any `POpen` processing function to pump output straight into a given stream.
	*        The underlying stream is the only contained member, and may be accessed directly.
	* @param Stream Exact stream type to be used by this processor.
	*               Set this to a reference to reference an existing stream.
	*               Stream will be automatically deduced if inputting a non-const stream reference to a naked form of this type's constructor.
	*               As such, input for complex or ambiguous references can be left to compiler deduction, such as with `basic_popen_processor(std::cout)`.
	*/
	template<class Stream>
	struct basic_popen_processor
	{
		basic_popen_processor()
		requires(std::is_default_constructible_v<Stream>) :
			stream{}
		{
		}

		constexpr basic_popen_processor(const basic_popen_processor<Stream>& to_copy) noexcept
		requires(std::is_copy_constructible_v<Stream>) :
			stream{ to_copy.stream }
		{
		}

		constexpr basic_popen_processor(basic_popen_processor<Stream>&& to_move) noexcept
		requires(!std::is_reference_v<Stream>) :
			stream{ std::move(to_move.stream) }
		{
		}
		
		constexpr basic_popen_processor(basic_popen_processor<Stream>&& to_move) noexcept
		requires(std::is_reference_v<Stream>) :
			stream{ to_move.stream }
		{
		}

		template<class...StreamConstructionArgs>
		requires(std::is_constructible_v<Stream, StreamConstructionArgs...>)
		constexpr basic_popen_processor(StreamConstructionArgs&&...stream_construction_args) noexcept(std::is_nothrow_constructible_v<Stream, StreamConstructionArgs...>) :
			stream{ std::forward<StreamConstructionArgs>(stream_construction_args)... }
		{
		}

		basic_popen_processor<Stream>& operator=(basic_popen_processor<Stream>& to_copy) noexcept(std::is_nothrow_copy_assignable_v<Stream&>)
		requires(!std::is_reference_v<Stream> && std::is_copy_assignable_v<Stream&>)
		{
			stream = to_copy.stream;
			return *this;
		}

		basic_popen_processor<Stream>& operator=(basic_popen_processor<Stream>&& to_move) noexcept
		requires(!std::is_reference_v<Stream> && std::is_move_assignable_v<Stream&>)
		{
			stream = std::move(to_move.stream);
			return *this;
		}

		constexpr void operator()(const std::string& line)
		{
			stream << line;
		}

		constexpr void operator()(auto begin, auto end)
		{
			std::copy(begin, end, std::ostreambuf_iterator(stream));
		}

		template<class T>
		constexpr basic_popen_processor<Stream>& operator<<(T&& to_append)
		{
			stream << std::forward<T>(to_append);
			return *this;
		}

		Stream stream;
	};
	template<class Stream>
	requires(!std::is_const_v<Stream>)
	basic_popen_processor(Stream&) -> basic_popen_processor<Stream&>;

	/*
	* @brief Helper which wraps usage of `popen` and makes its use operating system agnostic.
	*        Provides RAII-style acquisition-and-release of the underlying handle, allowing commands to correctly close upon destruction.
	*        Can be tested as a boolean just like the underlying handle type to indicate if it currently owns a handle.
	*        Allows the output of the command produced through `popen`ing to be custom-processed line-by-line or as raw bytes.
	*        Also provides the result returned from the command when finished processing or when directly closing.
	*/
	class POpen
	{
	public:
		/*
		* @brief The type used by this wrapper to hold the handle of an open process.
		*/
		using handle_type = FILE*;

		static constexpr std::size_t min_buffer_size{ 2u }; // Minimum size of 2 for 1 character and 1 null-terminator
		static constexpr std::size_t default_buffer_size{ 128u };
		static constexpr std::size_t default_max_buffer_size_for_stack{ 1024u };

		static constexpr bool defaults_to_heap(const std::size_t buffer_size) noexcept
		{
			return buffer_size > default_max_buffer_size_for_stack;
		}

		static constexpr std::size_t clamp_buffer_size(const std::size_t input_size) noexcept
		{
			return (input_size <= min_buffer_size) ? min_buffer_size : input_size;
		}

		POpen(const POpen&) = delete;
		POpen& operator=(const POpen&) = delete;

		/*
		* @brief Creates a wrapper with no handle.
		*        No process will be immediately opened, and will need to be manually started via means such as the `Open` member function.
		*/
		constexpr POpen() noexcept = default;

		/*
		* @brief Moves ownership of the input wrapper's handle to a newly-constructed wrapper.
		* @param to_move Wrapper to move the handle of. Will be updated to be recognised as no longer owning a handle.
		*                If this does not hold a handle at the time of input, this will simply result in the new wrapper having no handle.
		*/
		constexpr POpen(POpen&& to_move) noexcept :
			_handle{ _safely_move_handle(to_move._handle) }
		{
		}

		/*
		* @brief Opens a process using the provided command input to `popen`, setting the new wrapper as the owner of the resulting handle.
		*        The process will be opened directly as a part of the new wrapper's initialisation.
		* @param cmd Command to use for opening a process via `popen`.
		*/
		POpen(const char* cmd) :
			_handle{ _agnostic_popen(cmd) }
		{
		}

		/*
		* @brief Opens a process using the provided command input to `popen`, setting the new wrapper as the owner of the resulting handle.
		*        The process will be opened directly as a part of the new wrapper's initialisation.
		* @param cmd Command to use for opening a process via `popen`.
		*/
		POpen(const std::string& cmd) :
			_handle{ _agnostic_popen(cmd.c_str()) }
		{
		}

		/*
		* @brief Opens a process using the provided command input to `popen`, setting the new wrapper as the owner of the resulting handle.
		*        The process will be opened directly as a part of the new wrapper's initialisation.
		* @param cmd Command to use for opening a process via `popen`.
		*/
		POpen(const std::string_view& cmd) :
			_handle{ _agnostic_popen(cmd.data()) }
		{
		}

		POpen& operator=(POpen&& to_move) noexcept
		{
			// Reset before moving the moved handle to avoid ending up with a dangling handle if something goes horribly wrong in pclose
			_reset(nullptr);
			_handle = _safely_move_handle(to_move._handle);
			return *this;
		}

		/*
		* @brief Shorthand for `Open` with the same argument.
		* @returns Reference to this wrapper. If the return value from `Open` is required, you will need to use `Open` directly.
		*/
		POpen& operator=(const char* cmd)
		{
			Open(cmd);
			return *this;
		}

		/*
		* @brief Shorthand for `Open` with the same argument.
		* @returns Reference to this wrapper. If the return value from `Open` is required, you will need to use `Open` directly.
		*/
		POpen& operator=(const std::string& cmd)
		{
			Open(cmd);
			return *this;
		}

		/*
		* @brief Shorthand for `Open` with the same argument.
		* @returns Reference to this wrapper. If the return value from `Open` is required, you will need to use `Open` directly.
		*/
		POpen& operator=(const std::string_view& cmd)
		{
			Open(cmd);
			return *this;
		}

		/*
		* @brief Destructor which will automatically close its owned open handle if it owns one.
		*        As a precaution, upon closing the handle will also be updated for this wrapper to identify as not owning a handle,
		*        although it's highly unlikely for a single instance of this wrapper to be used across multiple threads.
		*/
		~POpen() noexcept
		{
			_reset(nullptr);
		}

		/*
		* @brief Returns a boolean identifying if this wrapper currently owns a handle.
		*        Allows for this wrapper to be tested similarly to the `if(ptr)` idiom that would normally be used with its underlying handle.
		* @returns `true` if this wrapper currently owns a handle; otherwise `false`.
		*/
		[[nodiscard]] constexpr operator bool() const noexcept
		{
			return _handle != nullptr;
		}

		/*
		* @brief Returns a boolean identifying if this wrapper currently owns a handle.
		* @returns `true` if this wrapper currently owns a handle; otherwise `false`.
		*/
		[[nodiscard]] constexpr bool HasHandle() const noexcept
		{
			return _handle != nullptr;
		}

		/*
		* @brief Opens a process using the provided command input to `popen`, and sets this wrapper as the owner of the resulting handle.
		*        If this wrapper currently holds a handle, it will be closed and the result of that close will be returned.
		* @param cmd The command to initiate via `popen`.
		* @returns The result of closing the existing handle before opening the new command. If this wrapper has no handle, guaranteed to be `0`.
		*/
		int Open(const char* cmd)
		{
			const int result{ _reset(nullptr) };
			_handle = _agnostic_popen(cmd);
			return result;
		}

		/*
		* @brief Opens a process using the provided command input to `popen`, and sets this wrapper as the owner of the resulting handle.
		*        If this wrapper currently holds a handle, it will be closed and the result of that close will be returned.
		* @param cmd The command to initiate via `popen`.
		* @returns The result of closing the existing handle before opening the new command. If this wrapper has no handle, guaranteed to be `0`.
		*/
		int Open(const std::string& cmd)
		{
			return Open(cmd.c_str());
		}

		/*
		* @brief Opens a process using the provided command input to `popen`, and sets this wrapper as the owner of the resulting handle.
		*        If this wrapper currently holds a handle, it will be closed and the result of that close will be returned.
		* @param cmd The command to initiate via `popen`.
		* @returns The result of closing the existing handle before opening the new command. If this wrapper has no handle, guaranteed to be `0`.
		*/
		int Open(const std::string_view& cmd)
		{
			return Open(cmd.data());
		}

		/*
		* @brief Closes this wrapper's current handle and returns the result of the close.
		* @returns Value returned from closing this wrapper's handle. If this wrapper has no handle, guaranteed to be `0`.
		*/
		int Close()
		{
			return _reset(nullptr);
		}

		/*
		* @brief Releases ownership of this wrapper's handle, and returns the handle for the caller to take care of.
		* @returns The handle that this wrapper previously held. `nullptr` if it does not hold a handle.
		*/
		[[nodiscard]] handle_type Release() noexcept
		{
			return _safely_move_handle(_handle);
		}

		/*
		* @brief Grants this wrapper ownership of the input handle.
		*        You must only input a handle that has been generated via `popen` or the `EmuIO::POpen` wrapper.
		*        This will additionally close the existing handle if this wrapper currently owns a handle.
		* @param new_handle Handle generated via `popen` or the `EmuIO::POpen` wrapper to grant this wrapper ownership of.
		* @returns The result of closing the existing handle before opening the new command. If this wrapper has no handle, guaranteed to be `0`.
		*/
		int GrantOwnership(handle_type new_handle)
		{
			const int result{ _reset(nullptr) };
			_handle = std::move(new_handle); // No need for the safe move since `new_handle` itself will never be used again directly
			return result;
		}

		/*
		* @brief Pipes the output from the wrapped command handle line-by-line through the input `line_processor_func`.
		*        Automatically closes the handle whose input is being processed once processing is complete.
		*        Assumes that this wrapper holds a valid handle. If uncertain, it is the caller's responsibility to test beforehand.
		* @param line_processor_func Function through which to process individual lines.
		*                            Must satisfy the `POpenLineProcessor` concept.
		* @param IncludeLineFeeds `true` to include line feeds at the end of lines passed to the processor; `false` to omit the line feeds.
		*                         Defaults to `true`.
		* @param BufferSize Size to use for the buffer when reading the output of the command handle.
		*                   Does not affect the size of line strings input to `line_processor_func`.
		*                   Will be clamped via `clamp_buffer_size`.
		*                   Defaults to `default_buffer_size`.
		* @param BufferUsesHeap `true` to use a buffer allocated to the heap, `false` to use a stack-allocated buffer.
		*                       Does not affect the allocation of the line strings input to `line_processor_func`.
		*                       Defaults to `defaults_to_heap(BufferSize)`
		* @returns The value returned after closing the handle once processing is complete.
		*/
		template<bool IncludeLineFeeds = true, std::size_t BufferSize = default_buffer_size, bool BufferUsesHeap = defaults_to_heap(BufferSize), POpenLineProcessor Func>
		int ProcessLines(Func line_processor_func)
		{
			constexpr std::size_t clamped_size{ clamp_buffer_size(BufferSize) };
			auto buffer{ _make_buffer<clamped_size, BufferUsesHeap>() };
			auto buffer_begin{ buffer.begin() };
			auto buffer_end{ buffer.end() };
			std::string line{};

			while (fgets(buffer.data(), clamped_size, _handle))
			{
				auto it{ buffer_begin };
				bool found_line{ false };
				do
				{
					const char current_char{ *it };
					if (current_char == 0)
					{
						break;
					}
					else if (current_char == '\n')
					{
						if constexpr (IncludeLineFeeds)
						{
							++it; // Increment iterator so that range will include this feed
						}
						found_line = true;
						break;
					}
				} while ((++it) != buffer_end);

				std::copy(buffer_begin, it, std::back_inserter(line));
				if (found_line)
				{
					line_processor_func(line);
					line.clear();
				}
			}

			// Unlikely, but there is a chance that we may not get a line feed at the end of output and have a dangling ending
			if (!line.empty())
			{
				if constexpr (IncludeLineFeeds)
				{
					// We wouldn't have hit this branch if we had a line feed, so just immediately append one without a test
					line += '\n';
				}
				line_processor_func(line);
			}

			return _reset(nullptr);
		}

		/*
		* @brief Pipes the output from the wrapped command handle through the input `line_processor_func`.
		*        Automatically closes the handle whose input is being processed once processing is complete.
		*        Assumes that this wrapper holds a valid handle. If uncertain, it is the caller's responsibility to test beforehand.
		* @param raw_processor_func Function through which to process individual lines.
		*                           Must satisfy the `POpenRawProcessor` concept when supplied with the input `BufferUsesHeap` and `BufferSize`.
		* @param IncludeLineFeeds `true` to include line feeds at the end of lines passed to the processor; `false` to omit the line feeds.
		*                         Defaults to `true`.
		* @param BufferSize Size to use for the buffer when reading the output of the command handle.
		*                   The size of ranges input to `raw_processor_func` will be constrained by this value.
		*                   Will be clamped via `clamp_buffer_size`.
		*					Affects the type of iterator input to `raw_processor_func` only if `BufferUsesHeap == false`.
		*                   Defaults to `default_buffer_size`.
		* @param BufferUsesHeap `true` to use a buffer allocated to the heap, `false` to use a stack-allocated buffer.
		*                       Affects the type of iterator input to `raw_processor_func`.
		*                       Defaults to `defaults_to_heap(BufferSize)`.
		* @returns The value returned after closing the handle once processing is complete.
		*/
		template<bool IncludeLineFeeds = true, std::size_t BufferSize = default_buffer_size, bool BufferUsesHeap = defaults_to_heap(BufferSize), POpenRawProcessor<BufferUsesHeap, BufferSize> Func>
		int ProcessRaw(Func raw_processor_func)
		{
			constexpr std::size_t clamped_size{ clamp_buffer_size(BufferSize) };
			auto buffer{ _make_buffer<clamped_size, BufferUsesHeap>() };
			auto buffer_begin{ buffer.begin() };
			auto buffer_end{ buffer.end() };

			while (fgets(buffer.data(), clamped_size, _handle))
			{
				auto it{ buffer_begin };
				do
				{
					const char current_char{ *it };
					if (current_char == 0)
					{
						break;
					}
					else if (current_char == '\n')
					{
						if constexpr (IncludeLineFeeds)
						{
							++it; // Increment iterator so that range will include this feed
						}
						break;
					}
				} while ((++it) != buffer_end);

				raw_processor_func(buffer_begin, it);
			}

			// Unlike `ProcessLines`, this pumps data directly into the processor func until we run out of data from the command
			// --- As a result there's no chance of anything being missing by the end of the main loop; so nothing left to do except close

			return _reset(nullptr);
		}

	private:
		// Produces a buffer of the specified size either on the stack or on the heap
		// --- If on the heap, returns a vector allocated with `BufferSize` elements set to `0`.
		// --- If on the stack, returns a default-constructed `std::array` of `BufferSize` elements.
		// --- In either case, the contained elements are `char`.
		// --- `BufferSize` is considered valid in these notes, but will be clamped to a valid size before sizing the buffers.
		// ------ i.e. if `BufferSize < min_buffer_size`, `BufferSize` will be treated as `min_buffer_size`.
		template<std::size_t BufferSize, bool BufferUsesHeap>
		[[nodiscard]] static constexpr decltype(auto) _make_buffer() noexcept(!BufferUsesHeap)
		{
			constexpr std::size_t clamped_size{ clamp_buffer_size(BufferSize) };
			if constexpr (BufferUsesHeap)
			{
				return std::vector<char>(clamped_size, 0);
			}
			else
			{
				return std::array<char, clamped_size>{};
			}
		}

		// Wrapper function to allow a single point to call `popen` regardless of OS
		[[nodiscard]] static handle_type _agnostic_popen(const char* cmd)
		{
#if EMU_CORE_IS_MSVC
			return _popen(cmd, "r");
#else
			return popen(cmd, "r");
#endif
		}

		// Wrapper function to allow a single point to call `pclose` regardless of OS, and update the underlying handle to a new one.
		int _reset(handle_type new_handle)
		{
			int result;
			if (_handle)
			{
#if EMU_CORE_IS_MSVC
				result = _pclose(_handle);
#else
				result = pclose(handle);
#endif
			}
			else
			{
				result = 0;
			}
			_handle = std::move(new_handle);
			return result;
		}

		// Moves the input handle into a new variable and sets the input handle to correctly identify as no-handle-held.
		[[nodiscard]] static constexpr handle_type _safely_move_handle(handle_type& handle_ref) noexcept
		{
			handle_type out_handle{ std::move(handle_ref) };
			handle_ref = nullptr;
			return out_handle;
		}

		handle_type _handle{ nullptr };
	};
}

#endif

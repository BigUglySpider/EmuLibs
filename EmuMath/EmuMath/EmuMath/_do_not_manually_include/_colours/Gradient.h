#ifndef EMU_MATH_GRADIENT_H_INC_
#define EMU_MATH_GRADIENT_H_INC_ 1

#include "ColourT.h"
#include "ColourArithmeticFunctors.h"
#include <algorithm>
#include <map>
#include <ostream>

namespace EmuMath
{
	template<class Channel_>
	class Gradient
	{
	public:
		using channel_type = Channel_;
		using colour_type = EmuMath::ColourRGB<channel_type>;
		using anchor_type = float;

	private:
		using colour_map = std::map<anchor_type, colour_type>;
		using alpha_map = std::map<anchor_type, channel_type>;

	public:
		/// <summary> The minimum value that all anchors will be clamped to. </summary>
		static constexpr anchor_type min_anchor = anchor_type(0);
		/// <summary> The maximum value that all anchors will be clamped to. </summary>
		static constexpr anchor_type max_anchor = anchor_type(1);

		/// <summary> Used to clamp an anchor value into its valid range of min_anchor:max_anchor. </summary>
		[[nodiscard]] static constexpr inline anchor_type clamp_anchor(const anchor_type anchor_)
		{
			return (anchor_ <= min_anchor) ? min_anchor : (anchor_ >= max_anchor) ? max_anchor : anchor_;
		}
		[[nodiscard]] static constexpr inline channel_type clamp_alpha(const channel_type alpha_)
		{
			return EmuMath::Helpers::clamp_colour_channel<channel_type, channel_type>(alpha_);
		}
		[[nodiscard]] static constexpr inline anchor_type wrap_anchor(anchor_type anchor_)
		{
			// We know we're wrapping a 0:1 range, so just defer to this.
			return EmuCore::do_normalised_wrap<anchor_type, true>()(anchor_);
		}

		Gradient() : colours(_make_empty_colours()), alphas(_make_empty_alphas())
		{
		}

		inline std::size_t AddColourAnchor(anchor_type anchor_, colour_type colour_)
		{
			anchor_ = clamp_anchor(anchor_);
			auto it_ = colours.find(anchor_);
			if (it_ != colours.end())
			{
				it_->second = colour_.Clamped();
			}
			else
			{
				it_ = colours.insert(std::pair<anchor_type, colour_type>(anchor_, colour_.Clamped())).first;
			}
			return _find_iterator_index(it_, colours);
		}

		inline std::size_t AddAlphaAnchor(anchor_type anchor_, channel_type alpha_)
		{
			anchor_ = clamp_anchor(anchor_);
			auto it_ = alphas.find(anchor_);
			if (it_ != alphas.end())
			{
				it_->second = clamp_alpha(alpha_);
			}
			else
			{
				it_ = alphas.insert(std::pair<anchor_type, channel_type>(anchor_, clamp_alpha(alpha_))).first;
			}
			return _find_iterator_index(it_, alphas);
		}

		[[nodiscard]] inline std::size_t NumColours() const
		{
			return colours.size();
		}
		[[nodiscard]] inline std::size_t NumAlphas() const
		{
			return alphas.size();
		}

		[[nodiscard]] inline colour_type GetColour(anchor_type anchor_point_) const
		{
			return _find_item<colour_type>(clamp_anchor(anchor_point_), colours);
		}
		[[nodiscard]] inline colour_type GetColourWrapped(anchor_type anchor_point_) const
		{
			return _find_item<colour_type>(wrap_anchor(anchor_point_), colours);
		}

		[[nodiscard]] inline channel_type GetAlpha(anchor_type anchor_point_) const
		{
			return _find_item<channel_type>(clamp_anchor(anchor_point_), alphas);
		}
		[[nodiscard]] inline channel_type GetAlphaWrapped(anchor_type anchor_point_) const
		{
			return _find_item<channel_type>(wrap_anchor(anchor_point_), alphas);
		}

		[[nodiscard]] inline EmuMath::ColourRGBA<channel_type> Get(anchor_type anchor_point_) const
		{
			anchor_point_ = clamp_anchor(anchor_point_);
			return EmuMath::ColourRGBA<channel_type>
			(
				_find_item<colour_type>(anchor_point_, colours),
				_find_item<channel_type>(anchor_point_, alphas)
			);
		}
		[[nodiscard]] inline EmuMath::ColourRGBA<channel_type> GetWrapped(anchor_type anchor_point_) const
		{
			anchor_point_ = wrap_anchor(anchor_point_);
			return EmuMath::ColourRGBA<channel_type>
			(
				_find_item<colour_type>(anchor_point_, colours),
				_find_item<channel_type>(anchor_point_, alphas)
			);
		}

#pragma region STREAM_FUNCTIONS
		std::ostream& AppendColoursToStream(std::ostream& str_) const
		{
			return _do_stream_append<false>(str_, colours);
		}
		std::wostream& AppendColoursToStream(std::wostream& str_) const
		{
			return _do_stream_append<true>(str_, colours);
		}

		std::ostream& AppendAlphasToStream(std::ostream& str_) const
		{
			return _do_stream_append<false>(str_, alphas);
		}
		std::wostream& AppendAlphasToStream(std::wostream& str_) const
		{
			return _do_stream_append<true>(str_, alphas);
		}
#pragma endregion

	private:
		template<class Out_, class Container_>
		[[nodiscard]] static inline Out_ _find_item(anchor_type anchor_, Container_& container_)
		{
			using Lerp_ = EmuCore::do_lerp<Out_, Out_, anchor_type>;

			std::size_t index_ = 0;
			auto right_it_ = _find_first_index_greater_equal_to_anchor(anchor_, index_, container_);

			// If the index_ is 0, we have nothing to the left of our right item, which means we are fully the found item.
			if ((index_ != 0))
			{
				auto left_it_ = right_it_;
				--left_it_;

				anchor_ -= left_it_->first;
				anchor_type anchor_diff_ = right_it_->first - left_it_->first;
				return Lerp_()(left_it_->second, right_it_->second, anchor_ / anchor_diff_);
			}
			else
			{
				// Reached end, so return this item in its entirety
				return right_it_->second;
			}
		}
		template<class Container_>
		[[nodiscard]] static inline auto _find_first_index_greater_equal_to_anchor(const anchor_type anchor_, std::size_t& out_index_, Container_& container_)
		{
			out_index_ = 0;
			auto it_ = container_.begin();
			if (it_->first >= anchor_)
			{
				return it_;
			}
			else
			{
				auto end_ = container_.end();
				auto next_it_ = it_;
				++next_it_;
				while (next_it_ != end_)
				{
					++out_index_;
					it_ = next_it_;
					if (it_->first >= anchor_)
					{
						return it_;
					}
					else
					{
						++next_it_;
					}

				}
				return it_;
			}
		}

		template<bool IsWide_, bool IncludeNewline_, class Stream_, class It_>
		static inline void _append_it_to_stream(Stream_& str_, It_& it_)
		{
			if constexpr (IncludeNewline_)
			{

				if constexpr (IsWide_)
				{
					str_ << L"\n[" << it_->first << L"]: " << it_->second;
				}
				else
				{
					str_ << "\n[" << it_->first << "]: " << it_->second;
				}
			}
			else
			{
				if constexpr (IsWide_)
				{
					str_ << L"[" << it_->first << L"]: " << it_->second;
				}
				else
				{
					str_ << "[" << it_->first << "]: " << it_->second;
				}
			}
		}

		template<bool IsWide_, class Stream_, class Container_>
		static inline Stream_& _do_stream_append(Stream_& str_, Container_& container_)
		{
			auto it_ = container_.begin();
			auto end_ = container_.end();
			if (it_ != end_)
			{
				_append_it_to_stream<IsWide_, false>(str_, it_);
				++it_;
				while (it_ != end_)
				{
					_append_it_to_stream<IsWide_, true>(str_, it_);
					++it_;
				}
			}
			return str_;
		}

		/// <summary>
		/// <para> Finds the integral index of the iterator to_find_ before the end of the passed container_. </para>
		/// <para> If the passed iterator cannot be found, this will return the size of the container (i.e. maximum valid index + 1). </para>
		/// </summary>
		/// <param name="to_find_">Iterator to find the index of.</param>
		/// <param name="container_">Container to search.</param>
		/// <returns>Index at which the iterator was found within the provided container, or the container's size if it cannot be found.</returns>
		template<typename ItToFind_, class Container_>
		[[nodiscard]] static inline std::size_t _find_iterator_index(ItToFind_ to_find_, Container_& container_)
		{
			auto it_ = container_.begin();
			auto end_ = container_.end();
			std::size_t count_ = 0;
			while (it_ != end_)
			{
				if (it_ == to_find_)
				{
					return count_;
				}
				else
				{
					++count_;
					++it_;
				}
			}
			return container_.size();
		}

		[[nodiscard]] static inline colour_map _make_empty_colours()
		{
			colour_map out_ = colour_map();
			out_.insert(std::pair<anchor_type, colour_type>(min_anchor, colour_type()));
			return out_;
		}
		[[nodiscard]] static inline alpha_map _make_empty_alphas()
		{
			alpha_map out_ = alpha_map();
			out_.insert(std::pair<anchor_type, channel_type>(min_anchor, colour_type::max_intensity));
			return out_;
		}

		inline void _validate_colours()
		{
			if (colours.size() == 0)
			{
				colours = _make_empty_colours();
			}
		}
		inline void _validate_alphas()
		{
			if (alphas.size() == 0)
			{
				alphas = _make_empty_alphas();
			}
		}

		colour_map colours;
		alpha_map alphas;
	};
}

template<class Channel_>
inline std::ostream& operator<<(std::ostream& str_, const EmuMath::Gradient<Channel_>& gradient_)
{
	str_ << "Colours:\n";
	gradient_.AppendColoursToStream(str_);
	str_ << "\nAlphas:\n";
	gradient_.AppendAlphasToStream(str_);
	return str_;
}

template<class Channel_>
inline std::wostream& operator<<(std::wostream& str_, const EmuMath::Gradient<Channel_>& gradient_)
{
	str_ << L"Colours:\n";
	gradient_.AppendColoursToStream(str_);
	str_ << L"\nAlphas:\n";
	gradient_.AppendAlphasToStream(str_);
	return str_;
}

#endif

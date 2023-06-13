#ifndef EMU_MATH_NOISE_SAMPLE_PROCESSOR_ANALYTICS_H_INC_
#define EMU_MATH_NOISE_SAMPLE_PROCESSOR_ANALYTICS_H_INC_

#include "../../../EmuCore/TMPHelpers/Values.h"
#include <tuple>

namespace EmuMath::Functors
{
	template<class Processor_, class...AnalyticFunctors_>
	struct noise_sample_processor_with_analytics
	{
	public:
		using analytic_tuple = std::tuple<AnalyticFunctors_...>;
		using processor_type = Processor_;
		static constexpr std::size_t num_analytics = sizeof...(AnalyticFunctors_);

		template<typename...ProcessorConstructionArgs_, typename = std::enable_if_t<std::is_constructible_v<processor_type, ProcessorConstructionArgs_...>>>
		constexpr noise_sample_processor_with_analytics(ProcessorConstructionArgs_&&...underlying_processor_construction_args_) :
			underlying_processor(underlying_processor_construction_args_...),
			analytics()
		{
		}

		template<typename...ProcessorConstructionArgs_, typename = std::enable_if_t<std::is_constructible_v<processor_type, ProcessorConstructionArgs_...>>>
		constexpr noise_sample_processor_with_analytics
		(
			const analytic_tuple& analytics_,
			ProcessorConstructionArgs_&&...underlying_processor_construction_args_
		) :
			underlying_processor(underlying_processor_construction_args_...),
			analytics(analytics_)
		{
		}

		template<typename...ProcessorConstructionArgs_, typename = std::enable_if_t<std::is_constructible_v<processor_type, ProcessorConstructionArgs_...>>>
		constexpr noise_sample_processor_with_analytics
		(
			analytic_tuple&& analytics_,
			ProcessorConstructionArgs_&&...underlying_processor_construction_args_
		) :
			underlying_processor(underlying_processor_construction_args_...),
			analytics(analytics_)
		{
		}

		/// <summary> Accesses the analytic at the provided index. </summary>
		/// <returns>Reference to the analytic at the provided index.</returns>
		template<std::size_t Index_>
		[[nodiscard]] constexpr inline typename std::tuple_element<Index_, analytic_tuple>::type& at() noexcept
		{
			if constexpr (Index_ < num_analytics)
			{
				using std::get;
				return get<Index_>(analytics);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<std::size_t, Index_>(), "Attempted to get an analytic component of a noise_sample_processor_with_analytics, but the provided Index_ exceeded the valid idnex range.");
			}
		}
		/// <summary> Accesses the analytic at the provided index. </summary>
		/// <returns>Constant reference to the analytic at the provided index.</returns>
		template<std::size_t Index_>
		[[nodiscard]] constexpr inline const typename std::tuple_element<Index_, analytic_tuple>::type& at() const noexcept
		{
			if constexpr (Index_ < num_analytics)
			{
				using std::get;
				return get<Index_>(analytics);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<std::size_t, Index_>(), "Attempted to get an analytic component of a noise_sample_processor_with_analytics, but the provided Index_ exceeded the valid idnex range.");
			}
		}

		template<typename Sample_>
		[[nodiscard]] constexpr inline Sample_ operator()(Sample_ sample_)
		{
			sample_ = underlying_processor(sample_);
			_do_analysis<0, Sample_>(sample_);
			return sample_;
		}

		processor_type underlying_processor;
		analytic_tuple analytics;

	private:
		template<std::size_t Index_, typename Sample_>
		inline void _do_analysis(const Sample_& processed_sample_)
		{
			if constexpr (Index_ < num_analytics)
			{
				using std::get;
				get<Index_>(analytics)(processed_sample_);
				_do_analysis<Index_ + 1, Sample_>(processed_sample_);
			}
		}
	};
}

#endif

#ifndef EMU_SIMD_HELPERS_TEMPLATE_STREAMS_H_INC_
#define EMU_SIMD_HELPERS_TEMPLATE_STREAMS_H_INC_ 1

#include "_underlying_template_helpers/_common_underlying_simd_template_helper_includes.h"
#include "_underlying_template_helpers/_simd_helpers_underlying_stream.h"
#include <ostream>

namespace EmuSIMD
{
	/// <summary>
	/// <para> Appends the passed SIMD vector's data to the passed output stream, in the format "{ elements... }". </para>
	/// <para> OutputWidthIfInt_ determines the number of bits used to interpret each element if an integral register is passed. It defaults to 32 bits. </para>
	/// <para> OutputSignedIfInt_ determines if elements should be interpreted with a sign bit. It defaults to true. </para>
	/// <para> Both OutputWidthIfInt_ and OutputSignedIfInt_ will not be used if the input register is a floating-point register. </para>
	/// </summary>
	/// <typeparam name="Register_">Type of SIMD register to append to the stream.</typeparam>
	/// <param name="str_">Output stream to append to.</param>
	/// <param name="vec_">SIMD register representing a vector to append to the passed stream.</param>
	/// <returns>Reference to the passed str_.</returns>
	template<std::size_t OutputWidthIfInt_ = 32, bool OutputSignedIfInt_ = true, class Register_>
	inline std::ostream& append_simd_vector_to_stream(std::ostream& str_, Register_ vec_)
	{
		return _underlying_simd_helpers::_append_to_stream<false, OutputWidthIfInt_, OutputSignedIfInt_>(str_, vec_);
	}

	/// <summary>
	/// <para> Appends the passed SIMD vector's data to the passed wide output stream, in the format "{ elements... }". </para>
	/// <para> OutputWidthIfInt_ determines the number of bits used to interpret each element if an integral register is passed. It defaults to 32 bits. </para>
	/// <para> OutputSignedIfInt_ determines if elements should be interpreted with a sign bit. It defaults to true. </para>
	/// <para> Both OutputWidthIfInt_ and OutputSignedIfInt_ will not be used if the input register is a floating-point register. </para>
	/// </summary>
	/// <typeparam name="Register_">Type of SIMD register to append to the stream.</typeparam>
	/// <param name="str_">Wide output stream to append to.</param>
	/// <param name="vec_">SIMD register representing a vector to append to the passed stream.</param>
	/// <returns>Reference to the passed str_.</returns>
	template<std::size_t OutputWidthIfInt_ = 32, bool OutputSignedIfInt_ = true, class Register_>
	inline std::wostream& append_simd_vector_to_stream(std::wostream& str_, Register_ vec_)
	{
		return _underlying_simd_helpers::_append_to_stream<true, OutputWidthIfInt_, OutputSignedIfInt_>(str_, vec_);
	}
}

#endif

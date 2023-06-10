#ifndef EMU_CORE_COMMON_PREPROCESSOR_WARNING_H_INC_
#define EMU_CORE_COMMON_PREPROCESSOR_WARNING_H_INC_ 1

#include "Compiler.h"

// These preprocessor directives are designed to allow generic disabling of warnings regardless of compiler.
// --- Currently, only support for MSVC disabling is provided

#if EMU_CORE_IS_MSVC
	// Specific warning macros

	/// <summary> Helper macro to safely disable a warning specific to MSVC within a passed code block, regardless of actual compiler. </summary>
	#define EMU_CORE_MSVC_DISABLE_WARNING_FOR_CODE_BLOCK(warning_code, code_block)\
		__pragma(warning(push))\
		__pragma(warning(disable: warning_code))\
		code_block\
		__pragma(warning(pop))

	/// <summary> Helper macro to safely push the MSVC warning stack, regardless of actual compiler. </summary>
	#define EMU_CORE_MSVC_PUSH_WARNING_STACK __pragma(warning(push))
	/// <summary> Helper macro to safely pop the MSVC warning stack, regardless of actual compiler. </summary>
	#define EMU_CORE_MSVC_POP_WARNING_STACK __pragma(warning(pop))
	/// <summary> Helper macro to safely disable a warning specific to MSVC, regardless of actual compiler. </summary>
	#define EMU_CORE_MSVC_DISABLE_WARNING(warning_code) __pragma(warning(disable: warning_code))

	// Generic warning macros

	/// <summary> Helper macro to safely push the warning stack, regardless of actual compiler. </summary>
	#define EMU_CORE_PUSH_WARNING_STACK EMU_CORE_MSVC_PUSH_WARNING_STACK
	/// <summary> Helper macro to safely pop the warning stack, regardless of actual compiler. </summary>
	#define EMU_CORE_POP_WARNING_STACK EMU_CORE_MSVC_POP_WARNING_STACK
	/// <summary> Helper macro to safely disable a warning by its ID, regardless of actual compiler. </summary>
	#define EMU_CORE_DISABLE_WARNING(warning_code) EMU_CORE_MSVC_DISABLE_WARNING(warning_code)

	// Warnings

	/// <summary> Compiler-agnostic ID used for a warning when only a typename is provided in code where a declaration is expected. </summary>
	#define EMU_CORE_WARNING_TYPENAME_ONLY 4091
	/// <summary> Compiler-agnostic ID used for a warning when a moved-from object continues to be used. </summary>
	#define EMU_CORE_WARNING_BAD_MOVE 26800
#else
	// Warning macros

	/// <summary> Helper macro to safely disable a warning specific to MSVC within a passed code block, regardless of actual compiler. </summary>
	#define EMU_CORE_MSVC_DISABLE_WARNING_FOR_CODE_BLOCK(warning_code, code_block) 
	/// <summary> Helper macro to safely push the MSVC warning stack, regardless of actual compiler. </summary>
	#define EMU_CORE_MSVC_PUSH_WARNING_STACK 
	/// <summary> Helper macro to safely pop the MSVC warning stack, regardless of actual compiler. </summary>
	#define EMU_CORE_MSVC_POP_WARNING_STACK 
	/// <summary> Helper macro to safely disable a warning specific to MSVC, regardless of actual compiler. </summary>
	#define EMU_CORE_MSVC_DISABLE_WARNING(warning_code) 

	// Generic warning macros

	/// <summary> Helper macro to safely push the warning stack, regardless of actual compiler. </summary>
	#define EMU_CORE_PUSH_WARNING_STACK	
	/// <summary> Helper macro to safely pop the warning stack, regardless of actual compiler. </summary>
	#define EMU_CORE_POP_WARNING_STACK 
	/// <summary> Helper macro to safely disable a warning by its ID, regardless of actual compiler. </summary>
	#define EMU_CORE_DISABLE_WARNING(warning_code) 

	// Warnings

	/// <summary> Compiler-agnostic ID used for a warning when only a typename is provided in code where a declaration is expected. </summary>
	#define EMU_CORE_WARNING_TYPENAME_ONLY 
	/// <summary> Compiler-agnostic ID used for a warning when a moved-from object continues to be used. </summary>
	#define EMU_CORE_WARNING_BAD_MOVE 
#endif

#endif

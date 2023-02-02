#ifndef EMU_CORE_COMMON_PREPROCESSOR_WARNING_H_INC_
#define EMU_CORE_COMMON_PREPROCESSOR_WARNING_H_INC_ 1

#include "Compiler.h"

// These preprocessor directives are designed to allow generic disabling of warnings regardless of compiler.
// --- Currently, only support for MSVC disabling is provided

#if EMU_CORE_IS_MSVC
	// Specific warning macros

	#define EMU_CORE_MSVC_DISABLE_WARNING_FOR_CODE_BLOCK(warning_code, code_block)\
		__pragma(warning(push))\
		__pragma(warning(disable: warning_code))\
		code_block\
		__pragma(warning(pop))

	#define EMU_CORE_MSVC_PUSH_WARNING_STACK __pragma(warning(push))
	#define EMU_CORE_MSVC_POP_WARNING_STACK __pragma(warning(pop))
	#define EMU_CORE_MSVC_DISABLE_WARNING(warning_code) __pragma(warning(disable: warning_code))

	// Generic warning macros

	#define EMU_CORE_PUSH_WARNING_STACK EMU_CORE_MSVC_PUSH_WARNING_STACK
	#define EMU_CORE_POP_WARNING_STACK EMU_CORE_MSVC_POP_WARNING_STACK
	#define EMU_CORE_DISABLE_WARNING(warning_code) EMU_CORE_MSVC_DISABLE_WARNING(warning_code)

	// Warnings

	#define EMU_CORE_WARNING_TYPENAME_ONLY 4091
	#define EMU_CORE_WARNING_BAD_MOVE 26800
#else
	// Warning macros

	#define EMU_CORE_MSVC_DISABLE_WARNING_FOR_CODE_BLOCK(warning_code, code_block) ;
	#define EMU_CORE_MSVC_PUSH_WARNING_STACK ;
	#define EMU_CORE_MSVC_POP_WARNING_STACK ;
	#define EMU_CORE_MSVC_DISABLE_WARNING(warning_code) ;

	// Generic warning macros

	#define EMU_CORE_PUSH_WARNING_STACK	;
	#define EMU_CORE_POP_WARNING_STACK ;
	#define EMU_CORE_DISABLE_WARNING(warning_code) ;

	// Warnings

	#define EMU_CORE_WARNING_TYPENAME_ONLY ;
	#define EMU_CORE_WARNING_BAD_MOVE ;
#endif

#endif

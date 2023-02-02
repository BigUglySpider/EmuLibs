#ifndef EMU_CORE_COMMON_PREPROCESSOR_COMPILER_H_INC_
#define EMU_CORE_COMMON_PREPROCESSOR_COMPILER_H_INC_ 1

// All EMU_CORE_IS_[COMPILER] macros are defined to a boolean of either 1 or 0. Only one macro will ever be defined as 1.
// --- All macros will always be present; this is to allow for `if constexpr(EMU_CORE_IS_[COMPILER])` checks where preprocessor #if blocks are not required.
// --- Checks are performed in a hierarchical order based on which platforms could create other platform defines
// ------ For example, Clang may define __GNUC__ or _MSC_VER, so we check for Clang before either of them

#if defined(__clang__) || defined(__clang_major__) || defined(__clang_minor__) || defined(__clang_patchlevel__)
	#define EMU_CORE_IS_CLANG 1	// EmuCore has determined that this project is compiling under Clang
	#define EMU_CORE_IS_GCC 0
	#define EMU_CORE_IS_MSVC 0
	#define EMU_CORE_IS_UNKNOWN_COMPILER 0
#else
	#define EMU_CORE_IS_CLANG 0
	#if defined(_MSC_VER) || defined(_MSC_FULL_VER) || defined(_MSC_BUILD)
		#define EMU_CORE_IS_MSVC 1
		#define EMU_CORE_IS_GCC 0
		#define EMU_CORE_IS_UNKNOWN_COMPILER 0
	#else
		#define EMU_CORE_IS_CLANG 0
		#if defined(__GNUC__) || defined(__GNUC_MINOR__) || defined(__GNUC_PATCHLEVEL__)
			#define EMU_CORE_IS_GCC 1 // EmuCore has determined that this project is compiling under MSVC
			#define EMU_CORE_IS_UNKNOWN_COMPILER 0
		#else
			#define EMU_CORE_IS_GCC 0
			#define EMU_CORE_IS_UNKNOWN_COMPILER 1	// EmuCore was unable to determine which compiler this project is compiling under. Some features may be unavailable.
		#endif
	#endif
#endif

#endif

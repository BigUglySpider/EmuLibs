#ifndef EMU_CORE_COMMON_PREPROCESSOR_ARCHITECTURE_H_INC_
#define EMU_CORE_COMMON_PREPROCESSOR_ARCHITECTURE_H_INC_ 1

#if defined(__amd64__) || defined(_M_AMD64) || defined(_M_X64)
#define EMU_CORE_AMD64 1
#else
#define EMU_CORE_AMD64 0
#endif

#if defined(i386) || defined(__i386) || defined(__i386__) || defined(__i486__) || defined(__i586__) || defined(__i686__) || defined(__IA32__) || defined(_M_I86) || defined(_M_IX86) || defined(__X86__) || defined(_X86_) || defined(__THW_INTEL__) || defined(__I86__) || defined(__INTEL__) || defined(__386)
#define EMU_CORE_INTEL 1
#else
#define EMU_CORE_INTEL_X86 0
#endif

#if defined(__arm__) || defined(__thumb__) || defined(__TARGET_ARCH_ARM) || defined(__TARGET_ARCH_THUMB) || defined(_ARM) || defined(_M_ARM) || defined(_M_ARMT) || defined(__aarch64__)
#define EMU_CORE_ARM 1
#else
#define EMU_CORE_ARM 0
#endif

#if EMU_CORE_INTEL_X86 || EMU_CORE_AMD64
#define EMU_CORE_X86_X64 1
#else
#define EMU_CORE_X86_X64 0
#endif

#endif

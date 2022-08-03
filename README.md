# EmuMath Dedicated Docs
EmuMath now has a [dedicated documentation page](https://biguglyspider.github.io/math)! You should use this for all up-to-date information regarding EmuMath.

Bear in mind, it's still under construction, so a lot is likely missing!

## EmuMath
A collection of different mathematical types and functionalities with a focus on making use of template metaprogramming.

### Dependencies
- EmuCore: A core library for all Emu-prefixed repositories
- EmuSIMD: Library used for templatised usage of `__m128`, `__m256` and `__m512` intrinsics, used for Emu-prefixed repositories which make explicit use of SIMD.
- EmuThreads: Library used for simplifying thread usage, such as through the creation of thread pools.
   - Not currently in use, but is here for experimenting with certain optimisations when creating fast types (such as with noise tables).

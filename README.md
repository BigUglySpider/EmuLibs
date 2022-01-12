# EmuMath
A collection of different mathematical types and functionalities with a focus on making use of template metaprogramming.

## Dependencies
- EmuCore: A core library for all Emu-prefixed repositories
- EmuSIMD: Library used for templatised usage of `__m128`, `__m256` and `__m512` intrinsics, used for Emu-prefixed repositories which make explicit use of SIMD.
- EmuThreads: Library used for simplifying thread usage, such as through the creation of thread pools.
   - Not currently in use, but is here for experimenting with certain optimisations when creating fast types (such as with noise tables).

## Current Features
### Colour
Implements a templatised type that can be used to describe a colour with its channels stored as a desired arithmetic type.
   - If the type is floating-point, channels will be considered in the range 0:1 for min:max intensity.
   - If the type is integral, channels will be considered in the range 0:`std::numeric_limits<T>::max()` for min:max intensity.
   - Colours may be constructed of other types, and will interact on a per-colour basis for determining intensity
      - e.g. If setting a `Colour<float>` via `Colour<std::uint8_t>`, the resulting colour will have each channel set to the result of `(in.r / 255, in.g / 255, in.b / 255, in.a / 255)` (simplified).
   - Some wrapped types have been implemented to automatically wrap or clamp these colours, but an unmanaged form of the colour is available too.
      - It is your responsibility to ensure that the channels of an unmanaged colour remain valid when needed.

### Noise
Implements multiple functors to generate noise samples using value, smooth value, or perlin noise (more noise types may be available at a later point).
Additionally provides a NoiseTable type to produce contiguous noise samples in a desired range, using a desired functor.
   - Noise may be 1D, 2D, or 3D
   - SIMD variants of functors are also available, making use of `__m128` intrinsics.
   - SIMD variants of the NoiseTable are also available, which allow large chunks of SIMD processing to be executed at once.
      - 3D Perlin SIMD variant has a ~3x (rounded down) speed increase on testing hardware. Returns diminish as sample calculation complexity goes down, but SIMD remains faster for all (again, on test hardware).

### Random
Provides simple wrappers for `std::mt19937` and `std::mt19937_64`, via the template `RngWrapper` type.

### Vector
Provides a templatised mathematical Vector type which can contain any number of elements (within the constraints of `std::size_t`) of and one specified type.
Behaviour makes heavy use of templates, and for high-performance software is intended as a storage type (similar to `DirectX::XMFLOATX` and `DirectX::XMVECTOR`).
Contains a lot of helpers under the `EmuMath::Helpers` namespace, and encapsulates them in member functions for Vector instances (this allows both C-style and Object-oriented-style use of Vector functions).
   - Provides all basic arithmetic and bitwise operators, plus function variants
   - Every Vector, despite contained elements, is treated as an infinitely-sized Vector, where elements that are not physically contained are considered implied-zeroes.
      - Invoking functions allow users to choose an output size, which is the scenario in which these indices are used.
      - Access treats the Vector as its contained size unless the caller explicitly uses a `Theoretical` version of an access function, although there is no way to force non-theoretical use of indices with functions other than access.
   - Provides a selection of common Vector functionalities, but by no means all of them.
      - The list includes (but is not limited to) cross product, dot product, normalisation, magnitude calculation, and reflection via a normal describing a surface.
   - Any Vector type can be cast to another Vector type if the contained type is compatible.
   - A Vector can contain references (e.g. `Vector<float&>`); these references may be updated to reference something else, but this functionality is not set in stone.
      - Allowing Vectors of references *is* set in stone, however.

## In-progress Features
### Matrix
A mathematical type which aims to encapsulate matrix behaviour the same way that Vector does. The underlying structure may be considered an `EmuMath::Vector` of `EmuMath::Vector`s. Allows customisation of major-memory storage (i.e. data may be contiguously stored in column-major order (default) or row-major order). Note that this does not modify the common interface for these matrices, which will always take the order of `column, row`.

## Planned Features
### FastVector
A form of the Vector which makes use of SIMD intrinsics. This will be more specialised than the `Vector` template, but it would be nice to be templatised to some degree.
Would like to follow a similar usage to `DirectXMath` Vectors and their SIMD variants.
Nothing set in stone.

### FastMatrix
Same as `FastVector`, but for matrices.

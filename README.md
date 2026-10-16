# go-cpp

A console Go game using C++23 named modules.

## Build

Use CMake 4.3 or newer and Ninja 1.11 or newer, with a compiler and standard
library that provide `import std`. The build checks for that support at configure
time. CI uses MSVC on Windows and LLVM 21 with libc++ on Linux and macOS.

Set `VCPKG_ROOT` to your vcpkg checkout. On Windows, run these commands in an
MSVC developer shell:

```powershell
cmake --preset debug
cmake --build --preset debug
ctest --preset debug --output-on-failure
```

The `release` and `release_dd` presets are also available. Dynamic debugging
(`release_dd`) requires MSVC with Dynamic Debugging support.

For Linux with LLVM 21 and libc++, select the matching dependency triplet so
Catch2 uses the same standard library as the application:

```sh
export CC=clang-21 CXX=clang++-21 CXXFLAGS=-stdlib=libc++
cmake --preset debug -DVCPKG_TARGET_TRIPLET=x64-linux-libcxx
cmake --build --preset debug
ctest --preset debug --output-on-failure
```

The development container provides this compiler and standard library; select
the triplet as above when configuring. On Intel macOS, use Homebrew LLVM 21 and
`x64-osx-libcxx`, with Homebrew's LLVM `bin` directory on `PATH` and its `lib/c++`
directory on the linker/runtime library search path. These overlay triplets
target x64.

## Module interface

Both executables use:

```cpp
import std;
import goimpl;
```

`source/goimpl.ixx` is the single public interface for the `Go` types: stones,
points, boards, chains, players, the controller, console UI, and logging. These
closely related types share one module rather than exposing the former header
dependency graph as partitions. Stream operators live in `Go` so that template
consumers can find them through argument-dependent lookup.

The `.cpp` library sources are implementation units (`module goimpl;`).
`Player.tpp` supplies template definitions within the interface so importers can
instantiate `Player` with their own UI types. Only macro facilities such as
`assert` and the private logging helpers still use textual includes; macros are
not part of the module API.

CMake publishes the interface in a public `CXX_MODULES` file set and supplies
module build ordering to targets that link `goimpl`. Installation includes the
library, executables, and module source with its textual dependencies under
`include/goimpl`. The old header API is replaced, not maintained alongside the
module. Build the installed interface with the same compiler, configuration,
and standard-library settings as the library; compiled module interfaces are
not portable distribution artifacts.

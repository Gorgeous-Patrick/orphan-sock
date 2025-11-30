# Build Workflow keeping artifacts in build/ (2 ways)

## 1. With presets
Use CMake presets to keep generated files inside `build/` and to make clean
targets consistent across Linux and macOS.

### Configure

```sh
cmake --preset dev
```

This creates (or refreshes) the `build/` directory with the Unix Makefiles
generator. Run it again whenever you change `CMakeLists.txt`.

### Build

```sh
cmake --build --preset dev
```

Targets such as `orphansock_server` end up in `build/bin/` and libraries in
`build/lib/`.

### Clean

```sh
cmake --build --preset dev --target clean
```

This runs the normal `make clean` inside `build/`. If you want to wipe the
entire build tree (equivalent to a distclean), remove the directory directly:

```sh
cmake -E rm -rf build
```

### Migrating from in-source builds

If you previously ran `cmake -S . -B .`, delete the generated files at the
repository root (`CMakeCache.txt`, `CMakeFiles/`, root `Makefile`, etc.) so the
new out-of-source configuration is the only one in use. (Unless using option 2)

## 2. Without presets
mkdir -p build

### Configure
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug

### Build
cmake --build build -j

Artifacts:
+ build/bin/orphan_sockd
+ build/lib/liborphan_sock_proto.*
+ build/lib/liborphan_sock_server_impl.*

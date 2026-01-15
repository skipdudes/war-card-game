# War Card Game
A simple console-based implementation of the classic card game **War**, written in C.
The project focuses on clean game logic, correct card handling, and memory-safe code.

[![language C99][shield-c]](https://github.com/skipdudes/war-card-game)
[![build CMake][shield-cmake]](https://github.com/skipdudes/war-card-game)
[![platform Windows Linux macOS][shield-platform]](https://github.com/skipdudes/war-card-game)
[![release 1.0.0][shield-release]](https://github.com/skipdudes/war-card-game/releases)

## 🛠 Requirements
- **Language:** C (C99)
- **Build system:** CMake ≥ 3.10
- **Compiler:** GCC, Clang, or MSVC
> **Note for Windows:** The project requires a toolchain using the **Universal C Runtime (UCRT)** (e.g. MSVC or MinGW-w64 UCRT via MSYS2).
> Older MinGW toolchains based on MSVCRT are not supported.

## ⚙️ Building
Clone the repository and build the project using CMake:
```bash
git clone https://github.com/skipdudes/war-card-game.git
cd war-card-game
cmake -S . -B build
cmake --build build
```

## ▶ Running
#### 🪟 Windows (MSVC)
After building, run the executable from the configuration directory:
```bash
build\Debug\war.exe
```
(or `build\Release\war.exe` if you built the Release configuration)
#### 🪟 Windows (MinGW)
```bash
build\war.exe
```
#### 🐧 Linux / 🍎 macOS (Makefiles or Ninja)
```bash
./build/war
```

## 📜 License
This project is licensed under the [MIT](LICENSE) license.

## 👤 Author
Copyright &copy; 2019 Marcin Chętnik

[shield-c]: https://img.shields.io/badge/language-C99-blue.svg
[shield-cmake]: https://img.shields.io/badge/build-CMake-green.svg
[shield-platform]: https://img.shields.io/badge/platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey.svg
[shield-release]: https://img.shields.io/badge/release-1.0.0-blueviolet.svg

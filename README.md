# Tetrisphere

A 100% source-complete byte-matching decompilation of Tetrisphere (USA) for the
Nintendo 64, done with the aid of Fable 5 and GPT-6 Astra.

Work toward full semantic recovery and improved readability is ongoing.

## Building from scratch

### 1. Install prerequisites

**macOS:** with [Homebrew](https://brew.sh) installed, install the Xcode Command
Line Tools (if needed) and build dependencies:

```sh
xcode-select --install
brew install git make mips-linux-gnu-binutils python
```

Ensure Homebrew's binaries are on your `PATH`.

**Ubuntu / Debian** (including WSL on Windows):

```sh
sudo apt-get update
sudo apt-get install git build-essential binutils-mips-linux-gnu python3 curl
```

### 2. Clone the repository

```sh
git clone https://github.com/jnmartin84/tetrisphere.git
cd tetrisphere
```

### 3. Supply the original ROM

Place your original big-endian USA ROM in the repository root as
`tetrisphere.z64`. The ROM is not included or downloaded.

- Size: **8,388,608 bytes**
- SHA-256: `f7cbc93ac273488bfb89955ab6ae9b60c730907872107a67a56b945e8579ef87`

### 4. Build

```sh
make tools
make -j4
```

`make tools` detects your operating system and architecture, downloads and verifies
the appropriate IDO compiler, and builds the host tools. It supports macOS on
Intel and Apple Silicon, and Linux on x86-64 and ARM64.

The build extracts the required assets from your ROM, compiles and links the
source, and verifies every byte of the result, including the ROM header. A
successful build reports `FULL ROM MATCH`.

The rebuilt ROM is **`build/tetrisphere.us.z64`**.

Use `make clean` to remove build outputs, or `make distclean` to also remove
extracted assets. Both preserve your original ROM.

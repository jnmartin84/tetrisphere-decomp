# Tetrisphere (USA)

Byte-matching N64 decompilation with semantic function names. Game source is
imported exactly from semantic commit `490402d76f15dc7d4774c15dde72e868b3f15fcf`:
26 identified functions, with every other source byte preserved from the
completed decompilation. See [semantic findings](analysis/semantic/README.md).

## Build

Install host prerequisites:

```sh
# macOS (Homebrew, plus Xcode Command Line Tools)
brew install make mips-linux-gnu-binutils python

# Ubuntu / Debian
sudo apt-get install build-essential binutils-mips-linux-gnu python3 curl
```

Place your original big-endian USA ROM at `tetrisphere.z64` in this folder.
Expected size: 8,388,608 bytes. SHA-256:
`f7cbc93ac273488bfb89955ab6ae9b60c730907872107a67a56b945e8579ef87`.
The ROM is never downloaded by these tools.

```sh
make tools        # download and verify the host's IDO 5.3; build host CRC tool
make -j4          # extract local assets, compile, link, verify every ROM byte
```

The default build also runs tool setup automatically. Success ends with
`FULL ROM MATCH: 8,388,608 bytes including header`.
Output: `build/tetrisphere.us.z64`. `./build-portable.sh -j4` is equivalent.
Use `make clean` to remove outputs; `make distclean` also removes extracted
binary assets. Neither command removes the reference ROM or checked-in assembly.
`make extract` regenerates only the two binary assets from the verified ROM.

[Official IDO v1.2](https://github.com/decompals/ido-static-recomp/releases/tag/v1.2)
is pinned for reproducibility. Setup detects Linux x86-64, Linux ARM64, or
macOS Intel/Apple Silicon (universal binary), verifies the archive SHA-256,
and installs under ignored `tools/ido5.3/v1.2/<host>/`. It validates cached
files before reusing them. Once tools are cached, builds need no network.
For an offline setup, use `python3 tools/setup_ido.py --archive /path/to/the-official-host-archive.tar.gz`.
The same checksum is required. The standalone installer also recognizes
Windows x86-64; use WSL for the full Unix-based build. Native Windows and
Linux x86-64 full builds have not been validated here.

Native macOS ARM64 and Linux ARM64 verification results are recorded in
[evidence/PUBLICATION.json](evidence/PUBLICATION.json).

## Source-only repository

No ROM, extracted binary assets, compiler binaries, host executables, screenshots,
or archives belong in Git. Generated assembly, linker inputs, C sources and SDK
headers are included as text. The two raw assets are reconstructed locally from
ROM ranges 0x40..0x1000 and 0xCD3F0..0x800000; no splat setup is needed.
A fresh clone plus your ROM and the host prerequisites is sufficient.

Before committing, run `python3 tools/audit_git.py` to scan every staged file's
content and path. `.gitignore` excludes binary artifacts and `.gitattributes`
disables checkout newline conversion. `python3 check-package.py` verifies the
source distribution manifest; after editing, the baseline manifest will correctly
report the changed files. `python3 check-package.py --rom` checks the full ROM.

Preserve game source formatting, types, expressions and physical line grouping.
IDO code generation depends on source shape. Semantic changes so far alter only
identifier spellings; tooling changes are documented separately.

See [build details](docs/BUILD.md), [asset research](docs/ASSETS.md), and
[publication provenance](evidence/PUBLICATION.json). The original portable snapshot
manifest and evidence remain historical records in `evidence/`. Semantic batch
ledgers describe the old branch's original baseline; they are historical evidence,
not instructions to apply its Git-baseline validator to this new root history.

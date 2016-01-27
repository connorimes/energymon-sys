# EnergyMon Rust Bindings

The `energymon-odroid-sys` crate provides declarations and linkage for the
`energymon-odroid` C library.
Following the *-sys package conventions, this crate does not define
higher-level abstractions over the native library functions.

The latest `energymon` C libraries can be found at
[https://github.com/energymon/energymon](https://github.com/energymon/energymon).

## Dependencies

In order to use this crate, you should have the `energymon` libraries
installed to the system where they can be found by `pkg-config`.

If the libraries are not found, the build process will try to compile them.

## Usage
Add `energymon-odroid-sys` as a dependency in `Cargo.toml`:

```toml
[dependencies.energymon-odroid-sys]
git = "https://github.com/energymon/energymon-sys.git"
```

[![Build Status](https://github.com/pqrs-org/cpp-osx-application/workflows/CI/badge.svg)](https://github.com/pqrs-org/cpp-osx-application/actions)
[![License](https://img.shields.io/badge/license-Boost%20Software%20License-blue.svg)](https://github.com/pqrs-org/cpp-osx-application/blob/main/LICENSE.md)

# cpp-osx-application

Utilities of macOS application APIs.

## Install

Copy `include/pqrs` and `vendor/vendor/include` directories into your include directory.

And then configure your project as follows:

- `src/pqrs/osx/application/*.swift`
- `include/pqrs/osx/application/impl/Bridging-Header.h` as Bridging Header

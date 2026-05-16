# Contributing to pulsar-client-phpcpp

Thank you for your interest in contributing! This document provides
guidelines and information for contributors.

## Code of Conduct

This project follows the
[Apache Software Foundation Code of Conduct](https://www.apache.org/foundation/policies/conduct.html).
Please be respectful and constructive in all interactions.

## Getting Started

1. Fork and clone the repository.
2. Build the project using one of the provided Dockerfiles (see README.md).
3. Make your changes on a feature branch.
4. Submit a pull request.

## Development Setup

The fastest way to get a working development environment:

```bash
docker build -f Dockerfile-83 -t pulsar-dev:8.3 .
docker run -it --rm -v $(pwd):/src pulsar-dev:8.3 bash
cd /src && make clean && make
```

## Code Style

- C++ source follows the LLVM style with 4-space indentation (see `.clang-format`).
- All comments in source code must be in **English**.
- Use Doxygen-style doc comments (`/** @brief ... */`) for public API methods.
- Header files use `#ifndef` / `#define` include guards (not `#pragma once`).

## Pull Request Checklist

Before submitting a PR, please ensure:

- [ ] Code compiles cleanly with `-Wall` and no new warnings.
- [ ] Any new PHP-facing methods are registered in the appropriate
      `register*()` function and documented in `README.md`.
- [ ] Existing Dockerfiles still build successfully.
- [ ] If adding a new PHP class, add corresponding header and
      implementation files, and register the class in `Pulsar.cpp`.
- [ ] The PR description explains *why* the change is needed.

## Reporting Issues

Please use GitHub Issues to report bugs or request features. Include:

- PHP version and OS
- Apache Pulsar C++ client version
- Steps to reproduce

## Contributor License Agreement (CLA)

If this project is submitted to the Apache Software Foundation in the
future, contributors may be asked to sign the
[Apache ICLA](https://www.apache.org/licenses/icla.pdf). Contributions
made now under the Apache License 2.0 are compatible with this process.

## License

By contributing, you agree that your contributions will be licensed
under the [Apache License 2.0](LICENSE).

# chipcraft  

> A CHIP-8 emulator written in C using modern practises.

![GitHub top language](https://img.shields.io/github/languages/top/TheCatster/chipcraft)
![](https://img.shields.io/github/actions/workflow/status/TheCatster/chipcraft/cmake-single-platform.yml)

## Setup
- To install, clone this project and run `cmake -S . -B build` followed by `cmake --build build`.
- Inside the `build` directory, you will find the executable, named `chipcraft`.

## Usage

For now, `chipcraft` is run from the terminal, and only has one option. Usage is as follows:
```bash
chipcraft <file_name>
```

## Specification
Currently only the basic CHIP-8 is supported. Support for SUPER-CHIP and XO-CHIP is planned, as well as stepping and debugging. A better GUI for the emulator is also in the works!

## Tests
A better test suite is in progress so that opcodes can be accurately checked.

## License
Daniil Rose – daniil.rose@posteo.org

Distributed under the GNUv3 license. See LICENSE for more information.

https://github.com/TheCatster/

## Contributing
- Fork (`https://github.com/TheCatster/chipcraft/fork`)
- Create your feature branch (`git checkout -b branch_name`)
- Commit your changes (`git commit -am 'Commit message'`)
- Push to the branch (`git push origin branch_name`)
- Create a new PR

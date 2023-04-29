# Sorting Ciphertext Demo

<p align="center">
  <a href="https://www.privasea.ai"><img src="https://github.com/Privasea/Miscellaneous/blob/3be7ff3c2d9f7e955e80f6637b5098fdb4583e3a/Figures/Logo/Privasea-Logo.jpg" width=40%  /></a>
</p>

<p align="center">
  <a href="https://github.com/Privasea"><img src="https://img.shields.io/badge/Playground-Privasea_Technology-brightgreen?logo=Parity%20Substrate" /></a>
  <a href="https://www.privasea.ai"><img src="https://img.shields.io/badge/made%20by-Privasea%20Tech-blue.svg?style=flat-square" /></a>
  <a href="https://github.com/Privasea/dinn_demo"><img src="https://img.shields.io/badge/project-dinn_demo-yellow.svg?style=flat-square" /></a>
</p>


# Table of Contents

- [Introduction](#introduction)
- [Running](#running)
- [Remark](#remark)

## Introduction

This is a demonstration of ciphertext sorting using the [HESEA library](https://github.com/Privasea/HESEA_Lib). In this demo program, you need to enter the sequence of plaintexts you want to be sorted. Then, the program encrypts the plaintext sequence into the corresponding ciphertext sequence, and sorts the sequence by comparing ciphertext sequence. Then decrypt the ciphertext sequence and output the sorted plaintext sequence.


# Running

Dependencies:

[HESEA](https://github.com/Privasea/HESEA_Lib)

after installed the HESEA lib, run with the command:

```
gcc -xc++ -lstdc++ -shared-libgcc compare.cpp -o compare_demo -I /usr/local/include/hesea  -L /usr/local/lib -libHESEApke.so

./compare_demo
```

or you can build this demo by camke as follow

```shell
mkdir build
cd build
cmake ..
make
./compare_demo
```

# Remark


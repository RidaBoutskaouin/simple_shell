# Simple Shell - A Basic Unix Shell Implementation

**Simple Shell** is a minimalist implementation of a Unix shell, aiming to provide a foundational understanding of how shell environments function. This repository contains a basic version of a shell written in C. Please note that this implementation might contain some issues and is intended for educational purposes.

## Table of Contents

- [Introduction](#introduction)

- [Features](#features)

- [Getting Started](#getting-started)

- [Clone the Repository](#clone-the-repository)

- [Compilation](#compilation)

- [Usage](#usage)

	- [Interactive Mode](#interactive-mode)

	- [Non-Interactive Mode](#non-interactive-mode)

- [Contributors](#contributors)

## Introduction

A shell is a command-line interface that allows users to interact with an operating system. It takes commands from the user, interprets them, and then executes those commands by communicating with the operating system. **Simple Shell** provides a simplified version of this functionality, helping users grasp the fundamentals of shell programming.

## Features

- Command execution

- Handling of basic built-in commands like `exit`

- Single command execution with arguments

- non-interactive mode execution.

## Getting Started

To use and test **Simple Shell**, follow these steps:

### Clone the Repository

```bash

git clone https://github.com/ridaboutskaouin/simple_shell.git

```

### Compilation

Navigate to the repository's directory and compile the source code:

```bash

cd simple_shell

gcc -Wall -Werror -Wextra -pedantic *.c -o simple_shell

```

### Usage

##### Interactive Mode

Run the compiled shell in interactive mode:

```bash

./simple_shell

````

You will be greeted by the shell prompt where you can type commands and get responses.

##### Non-Interactive Mode

You can also run the shell in non-interactive mode by providing commands through pipes:

```bash

echo "ls /var" | ./simple_shell

```

Where echo "ls /var" generates the command that you want to execute, and the output will be displayed accordingly.

### Contributors

This repository is contributed to and maintained by the following individuals:

- [Rida Boutskaouin](https://github.com/RidaBoutskaouin)

- [Lkoustim Mohamed](https://github.com/kostum-kirakos)

---

**Disclaimer:** This shell implementation is for educational purposes only. It might not cover all features and edge cases of a fully-fledged Unix shell. Use it as a learning tool and refer to official documentation for production environments.

# ft_printf

`ft_printf` is a custom reimplementation of the standard `printf()` function from the C standard library. The purpose of this project is to deepen the understanding of variadic functions, which allow handling a variable number of arguments—a core feature in C programming. This project mimics the behavior of `printf()` by supporting a variety of format specifiers and ensuring efficient memory management.

## Features

### Supported Format Specifiers:
- `%c`: Prints a single character.
- `%s`: Prints a string.
- `%p`: Prints a pointer in hexadecimal format.
- `%d`: Prints a decimal (base 10) number.
- `%i`: Prints an integer (base 10).
- `%u`: Prints an unsigned decimal (base 10) number.
- `%x`: Prints a number in lowercase hexadecimal format.
- `%X`: Prints a number in uppercase hexadecimal format.
- `%%`: Prints a percent sign.

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/luis-ffe/ft_printf.git
2. Navigate to the project directory:
   ```bash
   cd ft_printf
   ```
3. Compile the library:
   ```bash
   make
   ```

## Usage
To use `ft_printf` in your project, simply include it after compiling the library:
```c
#include "ft_printf.h"
```
Then, call `ft_printf` as you would with the standard `printf`:
```c
ft_printf("Hello %s, your score is %d!\n", "world", 100);
```

## Requirements
- The project is written in C.
- Adheres to strict memory management (no leaks).

## External Functions Used
- `malloc`, `free`, `write`
- Variadic functions: `va_start`, `va_arg`, `va_copy`, `va_end`

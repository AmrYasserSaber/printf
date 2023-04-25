# printf

This is a C language implementation of the `printf` function. It provides functionality for formatting and printing output to the console or file, using a format string and variable arguments. The implementation consists of the following 15 files:

- `README.md`: This file you are currently reading.
- `printf.c`: The main implementation of the `printf` function.
- `functions.c`, `functions1.c`, `functions2.c`: Helper functions for handling different conversion specifiers, such as integers, strings, and characters.
- `get_size.c`, `get_precision.c`, `get_flags.c`, `get_width.c`: Functions for parsing and extracting information from the format string.
- `handle_print.c`: A function for handling the actual printing of formatted output.
- `utils.c`: Utility functions used by other parts of the implementation.
- `write_handlers.c`: Functions for writing different types of data to the console or file.
- `main.h`: Header file defining function prototypes and some global constants.

## Usage

To use the `printf` function, include the `main.h` header file and call the `printf` function with a format string and any required arguments. For example:

```c
#include "main.h"

int main() {
    printf("Hello, %s!\n", "world");
    return 0;
}
```

This will output `Hello, world!` to the console.

## Compilation

To compile the `printf` function, simply include all of the source files in your build process. For example:

```sh
    gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o my_program
```

This will create an executable program called `my_program` that can be run from the command line.

## Contributing

Contributions to this project are welcome! Please create a pull request with any changes or additions you would like to make.

MIT Licence.


---
# Resource

- [Secrets of “printf ”](Resource_one.pdf)
- [open Genus](https://iq.opengenus.org/how-printf-and-scanf-function-works-in-c-internally/);
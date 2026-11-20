*This project has been created as part of the 42 curriculum by thdeglos.*

# get_next_line

## Description

**get_next_line** is a C function that returns, on each call, **the next line** from a file descriptor (a file or standard input), including the trailing `\n` when there is one.

```c
char *get_next_line(int fd);
```

| Return value | Meaning |
|---|---|
| an allocated string | the line that was read (must be freed with `free`) |
| `NULL` | end of file, or an error (invalid fd, `read` or `malloc` failure) |

The project is an opportunity to work on:
- **static variables** (keeping state between two calls),
- the **`read`** system call and file descriptors,
- **memory management** (no leaks, including on error paths),
- robustness against any `BUFFER_SIZE` value.

## Algorithm

`read` fetches a fixed number of bytes (`BUFFER_SIZE`) that almost never matches a line boundary. Whatever was read beyond the current line must therefore be kept between calls, in a static variable called the **stash**.

Each call goes through three steps:

1. **`read_to_stash`**: reads blocks of `BUFFER_SIZE` bytes and appends them to the stash until it contains a `\n` or the end of the file is reached.
2. **`extract_line`**: copies the beginning of the stash, up to and including the `\n` (or the whole stash if there is none), into a new string.
3. **`clean_stash`**: replaces the stash with whatever follows the `\n` and frees the old one. If nothing is left, the stash becomes `NULL`.

Example with `"ab\ncd\nef"` and `BUFFER_SIZE = 4`:

| Call | Stash after reading | Returned | Stash after |
|---|---|---|---|
| 1 | `"ab\nc"` | `"ab\n"` | `"c"` |
| 2 | `"cd\nef"` | `"cd\n"` | `"ef"` |
| 3 | `"ef"` | `"ef"` | `NULL` |
| 4 | `""` | `NULL` | `NULL` |

## Project structure

```
.
├── get_next_line.c
├── get_next_line_utils.c
├── get_next_line.h
├── get_next_line_bonus.c
├── get_next_line_utils_bonus.c
└── get_next_line_bonus.h
```

## Instructions

### Compilation

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
   get_next_line.c get_next_line_utils.c main.c -o gnl
```

`BUFFER_SIZE` is set at compile time with `-D`. If the option is omitted, the header provides a default value.

### Usage

```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int main(void)
{
	int		fd;
	char	*line;

	fd = open("file.txt", O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
```

### Testing

It is recommended to test with several `BUFFER_SIZE` values (`1`, `2`, `42`, `9999`, `10000000`) and several kinds of input: empty file, single line, no trailing `\n`, empty lines, very long line, standard input, invalid fd.

```bash
valgrind --leak-check=full ./gnl
```

## Bonus part

- **A single static variable**: `static char *stash[FD_MAX];` (one array, therefore one variable).
- **Multiple file descriptors at the same time**: each fd has its own stash, so reads can be interleaved (fd 3, then 4, then 5, then 3 again...) without losing the reading state of any of them.
- The `fd >= FD_MAX` check protects against an out-of-bounds access in the array.

Bonus compilation:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
   get_next_line_bonus.c get_next_line_utils_bonus.c main_bonus.c -o gnl_bonus
```

## Resources

- `man 2 read`, `man 2 open`, `man 3 malloc`, `man 3 free`
- Valgrind documentation: https://valgrind.org/docs/manual/
- 42 Norm (Norminette)

### AI usage

AI (Claude) was used to review my code, prepare test files and write this README. The project code was written and understood by the author.

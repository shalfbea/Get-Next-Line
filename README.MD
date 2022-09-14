# GetNextLine

Function, that reads from file descriptor till the end

## About

This project is part of program in [School 21](https://21-school.ru/) ([Ecole 42](42.fr)).

## Requirements

- GNU GCC

## Installation and usage

1. Download/Clone this repo

   > git clone https://github.com/shalfbea/Get-Next-Line/

2. Compiling:
	> gcc -Wall -Werror -Wextra -D BUFFER_SIZE=<Put your value> *.c

Don't forget to include get_next_line.h in your project

## Technical task

The full task can be found here: [gnl_subject](https://github.com/shalfbea/Get-Next-Line/blob/main/gnl_subject.pdf)

### Quick summary:

- Only using c language is allowed
- Code-style should respect the [The Norm](https://github.com/MagicHatJo/-42-Norm/blob/master/norme.en.pdf)
- No memory leaks, segmentation faults, undefined behavior
- Only allowed functions: read, malloc, free

### Bonus:

- Manage multiple file descriptors
- Use only a single static variable

### Evaluation result:
<img width="2003" alt="Screen Shot 2022-09-14 at 18 06 29" src="https://user-images.githubusercontent.com/92727363/190192498-ea1605a9-8966-4a56-ac30-a416195737f3.png">

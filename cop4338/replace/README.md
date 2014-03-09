Replace
==========

In this programming assignment, students will...

* Use Makefile to automate the build process.
* Get familiar with developing C programs in the Unix environment.
* Learn how to use pointers and strings.
* Learn basic memory allocation and deallocation.
* Receive parameters from the command line    
* Learn how to read from a file and write to a file.

Your program must take at least four command-line arguments: `string_a`, `string_b`, `input_file`, and `output_file`.

The program will:

1. Print how many times `string_a` occurs in `input file`
2. Replace all the occurrences of `string_a` in the given file with `string_b`
3. Print the result of the above in the standard output and write it to a file. 

Here are some more specifics:

* The program needs to provide sanity-check for command line arguments. For example, there should be a correct number of arguments; string_a can't be empty; the  input file must exist and be opened and read without problem, etc.
* The program will read and process one line of the file at a time. You can assume that each line in the given file is no longer than 1024 characters (including the terminating null character). However, you CANNOT assume that the new line (after the replacement) will not be longer than 1024 characters. You need to calculate the maximum possible length of the new line and dynamically allocate buffer of sufficient size. After the program is finished, you should reclaim the buffer.
* You can use string functions in <string.h>.

Here is an example to show what your program should be able to do:

```bash
$ cat mytest.txt

Shall I compare thee to a summer\'s day?
Thou art more lovely and more temperate.
Rough winds do shake the darling buds of May,
And summer\'s lease hath all too short a date.

$ ./replace ay ing mytest.txt output.txt

2

Shall I compare thee to a summer\'s ding?
Thou art more lovely and more temperate.
Rough winds do shake the darling buds of Ming,
And summer\'s lease hath all too short a date.


% cat output.txt

Shall I compare thee to a summer\'s ding?
Thou art more lovely and more temperate.
Rough winds do shake the darling buds of Ming,
And summer\'s lease hath all too short a date.
```
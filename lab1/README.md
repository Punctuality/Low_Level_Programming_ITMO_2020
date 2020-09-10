## Lab work #1

An implementation of BASIC **I/O** library using **NASM**

Library functions:

| **FUNCTION**  | **DEFINITION** |
| ------------  | ---------------|
| *GENERAL*     | *General functions* |
| exit          | Accepts an exit code and terminates the process |
| string_lenght | Accepts a pointer to a string and returns its lenght |
| *OUTPUT*      | *Output functions* |
| print_string  | Accepts a point to a null-terminated string and prints it to ```stdout``` |
| print_char    | Accepts a character code directly as its first argument and prints it to ```stdout``` |
| print_newline | Prints a character with code ```0xA``` |
| print_uint    | Prints an unsigned 8-byte integer in decimal format |
| print_int     | Prints a signed 8-byte integer in decimal format |
| *Input*       | *Input functions* |
| read_char     | Read one character from ```stdin``` and **return** it. If end of input stream occurs, return 0 |
| read_word     | Accepts a buffer address and size as arguments. Reads next word from ```stdin```. Returns 0 if word id too big for the buffer specified, otherwise returns a buffer address |
| *Processing*  | *Processing functions* |
| parse_uint    | Accepts a null-terminated string and tries to parse an unsigned number from its start. Returns number in ```rax```, characters count in ```rdx``` |
| parse_int     | Accepts a null-terminated string and tries to parse a signed number from its start. Returns number in ```rax```, characters count in ```rdx``` (including possible sign) |
| string_equals | Accepts two pointers to strings and compares them. Returns 1 if they are quals, 0 otherwise. |
| string_copy   | Accepts a pointer to a string, a pointer to a buffer, and buffer's lenght. Copies string to the destination. The destination address is returned if the string fits the buffer, 0 otherwise |

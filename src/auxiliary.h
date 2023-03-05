#include <stdbool.h>
#include <stdio.h>

/*
 * Throws an error
 *
 * message: char* = Error message
 *
 * Pre: message != NULL
 * Post: Exits program with code 1 (failure)
 * Return: None
 */
void throw_error (char* const message);
/*
 * Allocates memory
 * Wraps malloc () with error handling
 *
 * size: size_t = Size of data to allocate
 *
 * Pre: None
 * Post: None
 * Return: Address of allocated memory
 */
void* allocate (size_t size);
/*
 * Reads user input (integer)
 * Loops until input starts with an integer and is within bounds
 *
 * stream: FILE* = Filestream to read
 * message: char* = Prompt message
 * lower: int = Lower bound (inclusive) for input
 * upper: int = Upper bound (inclusive) for input
 *
 * Pre: stream == stdin || ! is_standard_stream (stream), message != NULL
 * Post: None
 * Return: input integer
 */
int read_int (FILE* const stream, char* const message, int lower, int upper);
/*
 * Reads user input (string)
 *
 * stream: FILE* = Filestream to read
 * message: char* = Prompt message
 * upper: int = Upper bound (inclusive) on number of characters for input
 *
 * Pre: stream == stdin || ! is_standard_stream (stream), message != NULL
 * Post: None
 * Return: input string
 */
char* read_string (FILE* const stream, char* const message, int upper);
/*
 * Checks if filestream is standard (stdin, stdout, stderr)
 *
 * stream: FILE* = Filestream to check
 *
 * Pre: stream != NULL
 * Post: None
 * Return: true if filestream is standard, false otherwise
 */
bool is_standard_stream (FILE* const stream);

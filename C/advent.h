#ifndef ADVENT_H
#define ADVENT_H

#define SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

/**
 * Performs Python-like stripping of whitespace on a string
 * @param str String to strip
 * @return In-place stripped string
 */
char *strip(char *str);

/**
 * Perform Python-like string splitting
 * @param str String to split
 * @param delim Delimiting substring
 * @param len Number of elements in returned list
 * @return List of split substrings
 */
char **split(const char *str, const char *delim, size_t *len);

/**
 * Reads the lines of a binary
 * @param fp File pointer
 * @param len number of elements in returned list
 * @return List of lines found in file
 */
char **readlines(FILE *fp, size_t *len);

/**
 * Finds the index of a substring in a string
 * @param str String
 * @param chr Character to index
 * @return index if found, else -1
 */
int indexOf(const char *str, char chr);

/**
 * In-place reversal of an array
 * @param arr Array to reverse
 * @param len Size of array
 * @return Array post-reversal
 */
int *rev(int *arr, size_t len);

/**
 * Replaces every instance of a char with another
 * @param s String to perform replacement
 * @param a Character to replace
 * @param b Character replacing
 * @return Copy of string with characters replaced
 */
char *replace(const char *s, char a, char b);

/**
 * Gets the GCD of two numbers
 * @param a First long
 * @param b Second long
 * @return gcd(a, b) -> long
 */
long gcd(long a, long b);

/**
 * Gets the LCM of an array of numbers
 * @param a Array of numbers
 * @param n Size of the array
 * @return LCM of the array -> long
 */
long lcm(const long a[], size_t n);

#endif // ADVENT_H
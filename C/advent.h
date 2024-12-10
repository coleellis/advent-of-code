#ifndef ADVENT_H
#define ADVENT_H

#include "common.h"

/**
 * The only function that needs to be called by the user
 * is get_data. Call get_data with the day and year and
 * you will receive the data from the API.
 */

// Used to get input from string
struct Memory {
    char *response;
    size_t size;
};

/**
 * Get the input data for a year.
 */
char *get_data(int day, int year);

/**
 * Get session token to pull data from URL.
 * Token can either be stored:
 * (1) in an AOCD_TOKEN environment variable
 * (2) In ~/.config/aocd/token
 * This token is return as a string.
 */
char *get_token(void);

/**
 * Make the cURL request to AOC to get the data.
 * This requires a token and the URL, both
 * are generated inside get_data.
 */
char *curl_request(char *url, char *token);

#endif // ADVENT_H

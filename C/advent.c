#include "advent.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>


char *get_token(void)
{
    // Get realpath
    char *home = getenv("HOME");
    if (!home)
    {
        fprintf(stderr, "HOME environment variable not set.\n");
        exit(EXIT_FAILURE);
    }

    // Full pathname
    char rpath[1024];
    snprintf(rpath, sizeof(rpath), "%s/.config/aocd/token", home);

    char *token;
    // Pass 1: ~/.config/aocd/token
    FILE *fp = fopen(rpath, "r");
    if (fp)
    {
        size_t len;
        getline(&token, &len, fp);
        token[strcspn(token, "\n")] = '\0';
        fclose(fp);
    }
    // Pass 2: AOCD_TOKEN env
    else
    {
        token = getenv("AOCD_TOKEN");
    }

    // Validate we got a token
    if (!token || !strlen(token))
    {
        fprintf(stderr, "get_data: No AOCD_TOKEN found. Please add an AOCD_TOKEN environment "
                        "variable or add the token inside ~/.config/aocd/token.\n");
        exit(EXIT_FAILURE);
    }

    return token;
}

char *get_data(int day, int year)
{
    char *token = get_token();
    char *data, url[256];

    // Validate date input
    if (year < 2015)
    {
        fprintf(stderr, "AOC started in 2015!\n");
        exit(EXIT_FAILURE);
    }
    if (day < 0 || day > 25)
    {
        fprintf(stderr, "AOC only runs until Christmas!\n");
        exit(EXIT_FAILURE);
    }

    // Get URL
    snprintf(url, sizeof(url), "https://adventofcode.com/%d/day/%d/input", year, day);

    // Make request
    data = curl_request(url, token);

    // free(token);
    return data;
}

size_t callback_write(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t total_size = size * nmemb;
    struct Memory *mem = (struct Memory *)userp;

    char *ptr = realloc(mem->response, mem->size + total_size + 1);
    if (ptr == NULL)
    {
        perror("realloc");
        return 0;
    }

    mem->response = ptr;
    memcpy(&(mem->response[mem->size]), contents, total_size);
    mem->size += total_size;
    mem->response[mem->size] = 0;

    return total_size;
}

char *curl_request(char *url, char *token)
{
    CURL *curl;
    CURLcode res;

    struct Memory chunk = { 0 };
    struct curl_slist *headers = NULL;

    curl = curl_easy_init();
    if (curl)
    {
        // URL
        curl_easy_setopt(curl, CURLOPT_URL, url);

        // Authorization header
        char auth[256];
        snprintf(auth, sizeof(auth), "Cookie: session=%s", token);
        headers = curl_slist_append(headers, auth);

        // Options
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback_write);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);

        // CURL
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        // Cleanup
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        return chunk.response;
    }
    return NULL;
}

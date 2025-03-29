#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINE_LEN 20

struct ConnectionParams {
    char PTY_T[11];
    char PTY_R[11];
};

struct Record {
    int n;
    double ts;
    float val1;
    float val2;
};

struct ConnectionParams get_devices() {
    FILE *fptr;
    struct ConnectionParams params;

    fptr = fopen("../../connection_params.txt", "r");
    if (fptr == NULL){
        perror("File is not opened");
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LEN];
    while (fgets(line, MAX_LINE_LEN, fptr) != NULL) {  // Read line by line
        if (line[4] == 'T'){
            strncpy(params.PTY_T, &line[6], 10);
            params.PTY_T[10] = '\0';
        } else if (line[4] == 'R') {
            strncpy(params.PTY_R, &line[6], 10);
            params.PTY_R[10] = '\0';
        }
    }

    // Close the file
    fclose(fptr);
    printf("Connection params:\n");
    printf("%s\n", params.PTY_T);
    printf("%s\n", params.PTY_R);
    return params;
}

double get_time() {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    
    double time_ms = ts.tv_sec * 1000L + ts.tv_nsec / 1000000;
    double time_s = time_ms / 1000;
    return time_s;
}

float get_random_float() {
    float rand_raw = rand();
    return rand_raw / 1000;
}

struct Record create_record() {
    struct Record new_record;
    new_record.ts = get_time();
    new_record.val1 = get_random_float();
    new_record.val2 = get_random_float();
    return new_record;
}

#endif

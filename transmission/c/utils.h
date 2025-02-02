#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ConnectionParams{
    char PTY_T[11];
    char PTY_R[11];
};

struct ConnectionParams get_devices(){
    FILE *fptr;
    struct ConnectionParams params;

    fptr = fopen("../../connection_params.txt", "r");
    if (fptr == NULL){
        perror("File is not opened");
        exit(EXIT_FAILURE);
    }

    int max_line_len = 20;
    char line[max_line_len];
    while (fgets(line, max_line_len, fptr) != NULL) {  // Read line by line
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


float get_random_float(){
    float rand_raw = rand();
    return rand_raw / 1000;
}

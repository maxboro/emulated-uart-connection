#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>

#include "utils.h"

int serial_port = -1;

void handle_sigint(int sig) {
    printf("\nCaught signal %d (SIGINT). Exiting safely...\n", sig);
    if (serial_port >= 0) {
        close(serial_port);
    }
    exit(0);
}

// Parse message into elements of record and compose record
struct Record parse_record(char msg[]) {
    struct Record new_record;

    char* token = strtok(msg, " ");
    new_record.n = atoi(token);

    token = strtok(NULL, " ");
    new_record.ts = atof(token);

    token = strtok(NULL, " ");
    new_record.val1 = atof(token);

    token = strtok(NULL, " ");
    new_record.val2 = atof(token);

    return new_record;
}

bool open_port(int* serial_port, struct ConnectionParams* params){
    *serial_port = open(params->PTY_R, O_RDONLY);
    if (*serial_port < 0) {
        perror("Error opening serial port.\n");
        return false;
    }
    return true;
}

void print_stats(int first_n_received, int last_n_received, int n_received){
    if (n_received == 0 || first_n_received < 0 || last_n_received < 0){
        printf("Nothing seems to be received.\n");
        return;
    }

    int packs_sent = last_n_received - first_n_received + 1;
    printf("Packs sent %d, packs received %d.\n", packs_sent, n_received);
    float success_rate = 100 * (float)n_received / (float) packs_sent;
    printf("Receiving success rate: %.1f\n", success_rate);
}

int main() {
    // Register the signal handler
    signal(SIGINT, handle_sigint);

    int first_n_received = -1;
    int last_n_received = -1;
    int n_received = 0;
    
    struct ConnectionParams params = get_devices();
    printf("main PTY_T: %s\n", params.PTY_T);
    printf("main PTY_R: %s\n", params.PTY_R);

    bool opened = open_port(&serial_port, &params);
    if (!opened)
        return -1;

    bool proceed_receiving = true;
    while (proceed_receiving) {
        char buffer[256];
        int bytes_read = read(serial_port, buffer, sizeof(buffer) - 1);

        // Check for end of transmission signal
        for (int i = 0; i < bytes_read; i++){
            if (buffer[i] == 3) {
                printf("Received end of transmission signal\n");
                proceed_receiving = false;
                break;
            }
        }
        
        struct Record record;
        // Print message received
        if (bytes_read > 0 && proceed_receiving) {
            buffer[bytes_read] = '\0';
            printf("Received: %s\n", buffer);
            record = parse_record(buffer);
            float val_sum = record.val1 + record.val2;
            printf("Val sum: %f\n", val_sum);
            n_received++;
        }

        
        if (first_n_received < 0)
            first_n_received = record.n;
        last_n_received = record.n;
    }

    close(serial_port);
    print_stats(first_n_received, last_n_received, n_received);
    return 0;
}

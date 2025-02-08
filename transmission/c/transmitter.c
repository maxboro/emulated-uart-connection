#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <unistd.h>
#include "utils.h"

int serial_port = -1;

void handle_sigint(int sig) {
    printf("\nCaught signal %d (SIGINT). Exiting safely...\n", sig);
    if (serial_port >= 0) {
        close(serial_port);
    }
    exit(0);
}

// Send end of transmission signal
void end_of_transmission(int serial_port) {
    char end_of_transmission_char = 3;
    char end_of_transmission_message[] = {end_of_transmission_char , '\0'};

    write(serial_port, end_of_transmission_message, strlen(end_of_transmission_message));
    printf("End of transmission signal is sent.\n");
    fflush(stdout);
    close(serial_port);
}

int main() {
    // Register the signal handler
    signal(SIGINT, handle_sigint);

    struct ConnectionParams params = get_devices();
    printf("main PTY_T: %s\n", params.PTY_T);
    printf("main PTY_R: %s\n", params.PTY_R);

    serial_port = open(params.PTY_T, O_WRONLY);
    if (serial_port < 0){
        perror("Error opening serial port");
        return 1;
    }

    for (int n_msg = 0; n_msg < 10; n_msg++) {
        struct Record new_record = create_record();
        new_record.n = n_msg;
        char message[50];
        sprintf(message, "%d %lf %f %f", new_record.n, new_record.ts, new_record.val1, new_record.val2);
        write(serial_port, message, strlen(message));
        printf("Msg '%s' is sent.\n", message);
        fflush(stdout);
        sleep(1);
    }

    end_of_transmission(serial_port);
    return 0;
}

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>

#include "utils.h"

int main() {
    struct ConnectionParams params = get_devices();
    printf("main PTY_T: %s\n", params.PTY_T);
    printf("main PTY_R: %s\n", params.PTY_R);

    int serial_port = open(params.PTY_R, O_RDONLY);
    if (serial_port < 0) {
        perror("Error opening serial port");
        return 1;
    }

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

        // Print message received
        if (bytes_read > 0 && proceed_receiving) {
            buffer[bytes_read] = '\0';
            printf("Received: %s\n", buffer);
        }
    }

    close(serial_port);
    return 0;
}
